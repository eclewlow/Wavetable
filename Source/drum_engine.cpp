/*
  ==============================================================================

    drum_engine.cpp
    Created: 30 Nov 2023 5:44:42pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Engine.h"
#include "wavetables.h"
#include "ParameterInterpolator.h"
#include "Globals.h"
#include "4x_downsampler.h"

DrumEngine::DrumEngine() {
    phase_ = 0.0f;
    amp_decay_ = 1.0f;
    fm_decay_ = 1.0f;
    fm_shape_ = 0.5f;
    fm_depth_ = 0.5f;
}

DrumEngine::~DrumEngine() {
    
}

void DrumEngine::Init() {
    phase_ = 0.0f;
    amp_decay_ = 1.0f;
    fm_decay_ = 1.0f;
    fm_shape_ = 0.5f;
    fm_depth_ = 0.5f;
}


float DrumEngine::GetSample(int16_t wavetable, int16_t frame, float phase) {
    float index = phase * 2048.0;
    uint16_t integral = floor(index);
    float fractional = index - integral;
    
    uint16_t nextIntegral = (integral + 1) % 2048;
    
    float sample = storage.LoadWaveSample(wavetable, frame, integral);
    float next_sample = storage.LoadWaveSample(wavetable, frame, nextIntegral);
    float interpolated16 = sample + (next_sample - sample) * fractional;
    
    float interpolatedFloat = interpolated16 / 32768.0f;
    
    return interpolatedFloat;
}

float DrumEngine::GetSampleBetweenFrames(float phase, float morph) {
    float frame = morph * 15.0f;
    uint16_t frame_integral = floor(frame);
    float frame_fractional = frame - frame_integral;
    
    uint16_t next_frame_integral = (frame_integral + 1) % 16;

    float frame1sample = GetSample(wavetable_, frame_integral, phase);
    float frame2sample = GetSample(wavetable_, next_frame_integral, phase);
    
    float sample = frame1sample * (1.0f - frame_fractional) + frame2sample * frame_fractional;
    return sample;
}

void DrumEngine::FillWaveform(int16_t * waveform, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph, bool withFx) {
    float frequency = 23.4375;

    float phaseIncrement = frequency / 48000.0f;
    
    float temp_phase = 0.0f;
    
    if(withFx)
        effect_manager.getEffect()->Sync_phases();

    for(int i = 0; i < 2048; i++) {
        float thisX = morph_;
        thisX = clamp(thisX, 0.0, 1.0);
        
        float calculated_phase = temp_phase;
        if(withFx)
            calculated_phase = effect_manager.RenderPhaseEffect(temp_phase, frequency, fx_amount, fx, true);
        
        float sample = GetSampleBetweenFrames(calculated_phase, thisX);
        
        if(withFx)
            sample = effect_manager.RenderSampleEffect(sample, temp_phase, frequency, fx_amount, fx, true);
        
        temp_phase += phaseIncrement;
        
        if(temp_phase >= 1.0f)
            temp_phase -= 1.0f;
        
        waveform[i] = static_cast<int16_t>(sample * 32767.0f);
    }
}

float DrumEngine::GetSampleNoFX(float phase, float fx, float morph) {
    float sample = GetSampleBetweenFrames(phase, morph);
    return sample;
}

void DrumEngine::triggerUpdate() {
    
}

void DrumEngine::Render(float* out, float* aux, uint32_t size, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph)
{
    //    float target = morph;
    // convert 12 bit uint 0-4095 to 0...15 float
    float morphTarget = morph * 1.0 / 4095.0;
    //    float interpolatedFloat = interpolated16 / 32768.0f;
    float tuneTarget = static_cast<float>(tune);
    
    uint16_t fx_amount_cv = adc.getChannel(Adc::ADC_CHANNEL_FX_AMOUNT_CV);
    
    if(fx_amount_cv > 2048) {
        if(amp_decay_trigger_ >= 1.0f && fm_decay_trigger_ >= 1.0f) {
            amp_decay_trigger_ = 0.0f;
            fm_decay_trigger_ = 0.0f;
        }
    }
    
    ParameterInterpolator morph_interpolator(&morph_, morphTarget, size);
    ParameterInterpolator tune_interpolator(&tune_, tuneTarget, size);
    Downsampler carrier_downsampler(&carrier_fir_);
    
    while (size--) {
        float amp_decay_trigger_increment = (1.0f / (6.0f * (amp_decay_ + 0.001f))) / 48000.0f;
        float fm_decay_trigger_increment = (1.0f / (6.0f * (fm_decay_ + 0.001f))) / 48000.0f;

        float curve = fm_shape_;
        float x;
        float y;
        
        x = cos(3 * M_PI_2 - (1 - fm_decay_trigger_) * M_PI_2) + 1;
        y = sin(3 * M_PI_2 - (1 - fm_decay_trigger_) * M_PI_2) + 1;
        x = x * (1 - curve) + cos((1 - fm_decay_trigger_) * M_PI_2) * curve;
        y = y * (1 - curve) + sin((1 - fm_decay_trigger_) * M_PI_2) * curve;

        
        float note = (120.0f * tune_interpolator.Next()) / 4095.0;
        note += 12 * y * (fm_depth_ * 2.0f - 1.0f);
        note = clamp(note, 0.0f, 120.0f);

        note = note - 24.0f;
        float a = 440; //frequency of A (coomon value is 440Hz)
        float frequency = (a / 32) * pow(2, ((note - 9) / 12.0));
        
        float phaseIncrement = frequency / 48000.0f;
        

        float interpolated_morph = morph_interpolator.Next();
        interpolated_morph = clamp(interpolated_morph, 0.0, 1.0);
        
        for (size_t j = 0; j < kOversampling; ++j) {
            float sample = GetSampleBetweenFrames(effect_manager.RenderPhaseEffect(phase_, frequency, fx_amount, fx, false, true), interpolated_morph);
            
            sample = effect_manager.RenderSampleEffect(sample, phase_, frequency, fx_amount, fx, false, true);
            
            sample = (1 - amp_decay_trigger_) * sample;
            
            amp_decay_trigger_ += amp_decay_trigger_increment;
            
            if(amp_decay_trigger_ >= 1.0f)
                amp_decay_trigger_ = 1.0f;

            fm_decay_trigger_ += fm_decay_trigger_increment;
            
            if(fm_decay_trigger_ >= 1.0f)
                fm_decay_trigger_ = 1.0f;

            phase_ += phaseIncrement;
            
            if(phase_ >= 1.0f)
                phase_ -= 1.0f;
            
            carrier_downsampler.Accumulate(j, sample);
        }
        
        float sample = carrier_downsampler.Read();
        
        *out++ = sample;
        *aux++ = sample;
    }
}

