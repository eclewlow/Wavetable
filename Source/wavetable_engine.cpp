/*
  ==============================================================================

    wavetable_engine.cpp
    Created: 19 Nov 2023 3:52:47am
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Engine.h"
#include "wavetables.h"
#include "ParameterInterpolator.h"
#include "Globals.h"
#include "4x_downsampler.h"

WavetableEngine::WavetableEngine() {
    phase_ = 0.0f;
}

WavetableEngine::~WavetableEngine() {
    
}

void WavetableEngine::Init() {
    phase_ = 0.0f;
//    frame00 = (int16_t*)&Wavetable_harmonic_series[0];
//    frame01 = (int16_t*)&Wavetable_harmonic_series[2048];
}


float WavetableEngine::GetSample(int16_t wavetable, int16_t frame, float phase) {
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

float WavetableEngine::GetSampleBetweenFrames(float phase, float thisX) {
    float index = thisX;
    uint8_t integral = floor(index);
    float fractional = index - integral;
    
    uint8_t nextIntegral = integral + ceil(fractional);
    
//    float frame1sample = GetSample((int16_t*)&Wavetable_harmonic_series[integral * 2048], phase);
//    float frame2sample = GetSample((int16_t*)&Wavetable_harmonic_series[nextIntegral * 2048], phase);
    
//    float sample = frame1sample * (1.0f - fractional) + frame2sample * fractional;
    float sample = 0.0f;
    return sample;
}

void WavetableEngine::FillWaveform(int16_t * waveform, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph, bool withFx) {
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
//
//
//void WavetableEngine::GenerateWaveformData(uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph) {
//    float frequency = 23.4375;
//
//    float phaseIncrement = frequency / 48000.0f;
//    
//    float temp_phase = 0.0f;
//    
//    effect_manager.getEffect()->Sync_phases();
//    
//    for(int i = 0; i < 2048; i++) {
//        float thisX = morph_;
//        thisX = clamp(thisX, 0.0, 15.0);
//        
//        float calculated_phase = effect_manager.RenderPhaseEffect(temp_phase, frequency, fx_amount, fx, true);
//        
//        float sample = GetSampleBetweenFrames(calculated_phase, thisX);
//        
//        sample = effect_manager.RenderSampleEffect(sample, temp_phase, frequency, fx_amount, fx, true);
//        
//        temp_phase += phaseIncrement;
//        
//        if(temp_phase >= 1.0f)
//            temp_phase -= 1.0f;
//        
//        BUF9[i] = static_cast<int16_t>(sample * 32767.0f);
//    }
//}

//int16_t* WavetableEngine::GetWaveformData(uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph) {
//    GenerateWaveformData(tune, fx_amount, fx, morph);
//    return BUF9;
//}

float WavetableEngine::GetSampleNoFX(float phase, float morph) {
    float sample = GetSampleBetweenFrames(phase, morph);
    return sample;
}

void WavetableEngine::triggerUpdate() {
    
}

void WavetableEngine::Render(float* out, float* aux, uint32_t size, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph)
{
    //    float target = morph;
    // convert 12 bit uint 0-4095 to 0...15 float
    float morphTarget = morph * 15.0 / 4095.0;
    //    float interpolatedFloat = interpolated16 / 32768.0f;
    float tuneTarget = static_cast<float>(tune);
    
    ParameterInterpolator morph_interpolator(&morph_, morphTarget, size);
    ParameterInterpolator tune_interpolator(&tune_, tuneTarget, size);
    Downsampler carrier_downsampler(&carrier_fir_);
    
//    float note = (120.0f * tune)/4095.0;

//    float a = 440; //frequency of A (coomon value is 440Hz)
//    float frequency = (a / 32) * pow(2, ((note - 9) / 12.0));
//    float adjusted_phase = 0.0f;
//    float phaseIncrement = frequency / 48000.0f;

    while (size--) {
        float note = (120.0f * tune_interpolator.Next()) / 4095.0;
        note = clamp(note, 0.0f, 120.0f);

        note = note - 24.0f;
        float a = 440; //frequency of A (coomon value is 440Hz)
        float frequency = (a / 32) * pow(2, ((note - 9) / 12.0));
        float phaseIncrement = frequency / 48000.0f;
        
        float interpolated_morph = morph_interpolator.Next();
        interpolated_morph = clamp(interpolated_morph, 0.0, 15.0);
        
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
    
//    GenerateWaveformData(tune, fx_amount, fx, morph);
}
