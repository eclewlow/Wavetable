/*
  ==============================================================================

    ab_engine.cpp
    Created: 19 Nov 2023 3:52:35am
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Engine.h"
#include "wavetables.h"
#include "ParameterInterpolator.h"
#include "Globals.h"
#include "4x_downsampler.h"

ABEngine::ABEngine() {
    phase_ = 0.0f;
    is_editing_left_ = false;
    is_editing_right_ = false;
}

ABEngine::~ABEngine() {
    
}

void ABEngine::Init() {
    phase_ = 0.0f;
}

float ABEngine::GetSample(int16_t wavetable, int16_t frame, float phase) {
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

float ABEngine::GetSample(int16_t wavetable, int16_t frame, float phase, bool isLeft) {
    float index = phase * 2048.0;
    uint16_t integral = floor(index);
    float fractional = index - integral;
    
    uint16_t nextIntegral = (integral + 1) % 2048;
    
    float sample;
    float next_sample;
    
    if(IsEditingLeft() && isLeft) {
        sample = BUF3[integral];
        next_sample = BUF3[nextIntegral];
    } else if (IsEditingRight() && !isLeft) {
        sample = BUF4[integral];
        next_sample = BUF4[nextIntegral];
    } else {
        sample = storage.LoadWaveSample(wavetable, frame, integral);
        next_sample = storage.LoadWaveSample(wavetable, frame, nextIntegral);
    }
    
    float interpolated16 = sample + (next_sample - sample) * fractional;
    
    float interpolatedFloat = interpolated16 / 32768.0f;
    
    return interpolatedFloat;
}

float ABEngine::GetSampleBetweenFrames(float phase, float morph) {
    float index = morph;
    uint8_t integral = floor(index);
    float fractional = index - integral;
    
    uint8_t nextIntegral = integral + ceil(fractional);
    
    float frame1sample = GetSample(left_wavetable_, left_frame_, phase, true);
    float frame2sample = GetSample(right_wavetable_, right_frame_, phase, false);
    
    float sample = frame1sample * (1.0f - fractional) + frame2sample * fractional;
    return sample;
}

void ABEngine::FillWaveform(int16_t * waveform, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph, bool withFx) {
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

void ABEngine::FillWaveform(int16_t * waveform, int16_t wavetable, int16_t frame) {
    storage.LoadWaveSample(waveform, wavetable, frame);
}

float ABEngine::GetSampleNoFX(float phase, float morph) {
    float sample = GetSampleBetweenFrames(phase, morph);
    return sample;
}

void ABEngine::triggerUpdate() {
//    SetIsEditingLeft(false);
//    SetIsEditingRight(false);
//    SetLeftFrame(0);
//    SetLeftWavetable(0);
//    abModeMenu.SetLeftFrame(0);
//    abModeMenu.SetLeftWavetable(0);
}

void ABEngine::Render(float* out, float* aux, uint32_t size, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph)
{
    // convert 12 bit uint 0-4095 to 0...15 float
    float morphTarget = morph * 1.0 / 4095.0;
    //    float interpolatedFloat = interpolated16 / 32768.0f;
    float tuneTarget = static_cast<float>(tune);
    
    ParameterInterpolator morph_interpolator(&morph_, morphTarget, size);
    ParameterInterpolator tune_interpolator(&tune_, tuneTarget, size);
    Downsampler carrier_downsampler(&carrier_fir_);
    
    while (size--) {
        float note = (120.0f * tune_interpolator.Next()) / 4095.0;
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

bool ABEngine::SetLeftWave(int table, int frame) {
    if(storage.WaveDoesExist(table, frame)) {
        left_wavetable_ = table;
        left_frame_ = frame;
        return true;
    }
    return false;
}

bool ABEngine::SetRightWave(int table, int frame) {
    if(storage.WaveDoesExist(table, frame)) {
        right_wavetable_ = table;
        right_frame_ = frame;
        return true;
    }
    return false;
}
