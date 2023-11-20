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
}

ABEngine::~ABEngine() {
    
}

void ABEngine::Init() {
    phase_ = 0.0f;
    memset(BUF1, 0, 2048 * 2);
    memset(BUF2, 0, 2048 * 2);
    memset(BUF3, 0, 2048 * 2);
    memset(BUF4, 0, 2048 * 2);
    memcpy(BUF1, &Wavetable_harmonic_series[0], 2048 * 2);
    memcpy(BUF2, &Wavetable_harmonic_series[2048], 2048 * 2);
    left_wave_ = BUF1;
    right_wave_ = BUF2;
}

float ABEngine::GetSample(int16_t* frame, float phase) {
    float index = phase * 2048.0;
    uint16_t integral = floor(index);
    float fractional = index - integral;
    
    uint16_t nextIntegral = (integral + 1) % 2048;
    
    float interpolated16 = frame[integral] + (frame[nextIntegral]-frame[integral]) * fractional;
    
    float interpolatedFloat = interpolated16 / 32768.0f;
    
    return interpolatedFloat;
}

float ABEngine::GetSampleBetweenFrames(float phase, float thisX) {
    float index = thisX;
    uint8_t integral = floor(index);
    float fractional = index - integral;
    
    uint8_t nextIntegral = integral + ceil(fractional);
    
    float frame1sample = GetSample(left_wave_, phase);
    float frame2sample = GetSample(right_wave_, phase);
    
    float sample = frame1sample * (1.0f - fractional) + frame2sample * fractional;
    return sample;
}


int16_t* ABEngine::GetWaveformDataNoFX(int index, uint16_t morph) {
    if(index == 1)
        return left_wave_;
    else
        return right_wave_;
}

void ABEngine::GenerateWaveformData(uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph) {
    float frequency = 23.4375;

    float phaseIncrement = frequency / 48000.0f;
    
    float temp_phase = 0.0f;
    
    effect_manager.getEffect()->Sync_phases();

    for(int i = 0; i < 2048; i++) {
        float thisX = morph_;
        thisX = clamp(thisX, 0.0, 1.0);
        
        float calculated_phase = effect_manager.RenderPhaseEffect(temp_phase, frequency, fx_amount, fx, true);
        
        float sample = GetSampleBetweenFrames(calculated_phase, thisX);
        
        sample = effect_manager.RenderSampleEffect(sample, temp_phase, frequency, fx_amount, fx, true);
        
        temp_phase += phaseIncrement;
        
        if(temp_phase >= 1.0f)
            temp_phase -= 1.0f;
        
        BUF9[i] = static_cast<int16_t>(sample * 32767.0f);
    }
}

int16_t* ABEngine::GetWaveformData(uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph) {
    GenerateWaveformData(tune, fx_amount, fx, morph);
    return BUF9;
}

float ABEngine::GetSampleNoFX(float phase, float morph) {
    float sample = GetSampleBetweenFrames(phase, morph);
    return sample;
}

void ABEngine::LoadWave(int index, int wavetable, int wave) {
    int16_t * back_buf = (left_wave_ == BUF1 ? BUF3 : BUF1);
//    int16_t * front_buf = (left_wave_ == BUF1 ? BUF1 : BUF3);
    memcpy(back_buf, &Wavetable_harmonic_series[2048*wave], 2048 * 2);
//    SwapBuf(front_buf, back_buf);
    left_wave_ = back_buf;
    reset_phase();
}

void SwapBuf(int16_t * front_buf, int16_t * back_buf) {
    
}

void ABEngine::Render(float* out, float* aux, uint32_t size, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph)
{
    //    float target = morph;
    // convert 12 bit uint 0-4095 to 0...15 float
    float morphTarget = morph * 1.0 / 4095.0;
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
    
//    GenerateWaveformData(tune, fx_amount, fx, morph);
}

