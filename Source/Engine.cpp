/*
 ==============================================================================
 
 Engine.cpp
 Created: 9 Nov 2023 3:03:36pm
 Author:  Eugene Clewlow
 
 ==============================================================================
 */

#include "Engine.h"
#include "wavetables.h"
#include "ParameterInterpolator.h"
#include "Globals.h"
#include "4x_downsampler.h"

Engine::Engine() {
    phase_ = 0.0f;
}

//void Engine::Init() {
//    phase = 0.0f;
//    subosc_phase_ = 0.0f;
//    frame00 = (int16_t*)&Wavetable_harmonic_series[0];
//    frame01 = (int16_t*)&Wavetable_harmonic_series[2048];
//    memset(waveformData, 0, 2048*2);
//}

//float Engine::Render() {
//    float sample = sin(2 * M_PI * phase);
//
//    phase += phaseIncrement;
//    if(phase >= 1.0f)
//        phase -= 1.0f;
//    return sample;
//}

//float Engine::GetSample(int16_t* frame, float phase) {
//    float index = phase * 2048.0;
//    uint16_t integral = floor(index);
//    float fractional = index - integral;
//    
//    uint16_t nextIntegral = (integral + 1) % 2048;
//    
//    float interpolated16 = frame[integral] + (frame[nextIntegral]-frame[integral]) * fractional;
//    
//    float interpolatedFloat = interpolated16 / 32768.0f;
//    
//    return interpolatedFloat;
//}

//float Engine::GetSampleBetweenFrames(float phase, float thisX) {
//    float index = thisX;
//    uint8_t integral = floor(index);
//    float fractional = index - integral;
//    
//    uint8_t nextIntegral = integral + ceil(fractional);
//    
//    float frame1sample = GetSample((int16_t*)&Wavetable_harmonic_series[integral * 2048], phase);
//    float frame2sample = GetSample((int16_t*)&Wavetable_harmonic_series[nextIntegral * 2048], phase);
//    
//    float sample = frame1sample * (1.0f - fractional) + frame2sample * fractional;
//    return sample;
//}

//void Engine::GenerateWaveformData(uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph) {
//    float frequency = 23.4375;
//
//    float phaseIncrement = frequency / 48000.0f;
//    
//    float temp_phase = 0.0f;
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
//        waveformData[i] = static_cast<int16_t>(sample * 32767.0f);
//    }
//}

//int16_t* Engine::GetWaveformData(uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph) {
//    return waveformData;
//}

//66mhz 66000000 cycles / second
// 8bit, is 8 cycles
// 16 bit is 16 cycles. 2048 x 16.  32,768 cycles, 2,570hz timer
// so in ROM timer.  read potentiometer  x, y
//      read ROM for 4 wave frames = 2048*16*4, 131,072 cycles, at most 1281 frequency timer
//                  16386. 16kb of memory to store 4 waves  x 2 for interpolation, so 32kb.
//       set 4 frames.. interpolate?
// meanwhile, in 48khz audio timer
//      mix 4 tables based on x,y
//      potentiometer changes on pots for x,y
//          when x goes from frame0,1 to frame1,2. we need to load frame 2
//          meanwhile, we are still rendering audio.  so we keep rendering frame0,1... but x is a different value now.
//              so we use the old x.   and starting loading frames for the newX
//              the 4 frames will load in the background
//              once finished, now we have the new 4 frames... we want to sample x,y of the new 4 frames
//              but to avoid clicking we interpolate from the old x,y old 4 frames to the new x,y new 4 frames.
//              what if x,y changes before 4 frames could be loaded previously
//              we want to start over load process.

//void Engine::SetX(float newX) {
//    x = newX;
//    // 0...1.0  -> 0 to 15  ->  wave 0,0  0,1  1,2 ... 14,15 ... 15,15
//    // ... 0.0  to 15.0// first table = integral.  second table = integral + ceil(fractional)
//    float index = x * 15.0;
//    uint8_t integral = floor(index);
//    float fractional = index - integral;
//
//    uint8_t nextIntegral = integral + ceil(fractional);
//
//    printf("%d %d", integral, nextIntegral);
//
//    frame00 = (int16_t*)&Wavetable_harmonic_series[integral * 2048];
//    frame01 = (int16_t*)&Wavetable_harmonic_series[nextIntegral * 2048];
//}

//void Engine::Render(float* out, float* aux, uint32_t size, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph)
//{
//    //    float target = morph;
//    // convert 12 bit uint 0-4095 to 0...15 float
//    float morphTarget = morph * 15.0 / 4095.0;
//    //    float interpolatedFloat = interpolated16 / 32768.0f;
//    float tuneTarget = static_cast<float>(tune);
//    
//    ParameterInterpolator morph_interpolator(&morph_, morphTarget, size);
//    ParameterInterpolator tune_interpolator(&tune_, tuneTarget, size);
//    Downsampler carrier_downsampler(&carrier_fir_);
//    
////    float note = (120.0f * tune)/4095.0;
//
////    float a = 440; //frequency of A (coomon value is 440Hz)
////    float frequency = (a / 32) * pow(2, ((note - 9) / 12.0));
////    float adjusted_phase = 0.0f;
////    float phaseIncrement = frequency / 48000.0f;
//
//    while (size--) {
//        float note = (120.0f * tune_interpolator.Next()) / 4095.0;
//        note = clamp(note, 0.0f, 120.0f);
//
//        note = note - 24.0f;
//        float a = 440; //frequency of A (coomon value is 440Hz)
//        float frequency = (a / 32) * pow(2, ((note - 9) / 12.0));
//        float phaseIncrement = frequency / 48000.0f;
//        
//        float subosc_frequency = (a / 32) * pow(2, (((note + user_settings.getSubOscDetune() / 100.0f + user_settings.getSubOscOffset()) - 9) / 12.0));
//        float subosc_phase_increment = subosc_frequency / 48000.0f;
//
//        float interpolated_morph = morph_interpolator.Next();
//        interpolated_morph = clamp(interpolated_morph, 0.0, 15.0);
//        
//        for (size_t j = 0; j < kOversampling; ++j) {
//            float sample = GetSampleBetweenFrames(effect_manager.RenderPhaseEffect(phase, frequency, fx_amount, fx, false, true), interpolated_morph);
//            
//            sample = effect_manager.RenderSampleEffect(sample, phase, frequency, fx_amount, fx, false, true);
//            
//            phase += phaseIncrement;
//            
//            if(phase >= 1.0f)
//                phase -= 1.0f;
//            
//            sample = (user_settings.getSubOscMix() / 100.0f) * sample + (1.0f - user_settings.getSubOscMix() / 100.0f) * GetSubOscillatorSample(subosc_phase_, subosc_phase_increment, interpolated_morph);
//            
//            subosc_phase_ += subosc_phase_increment;
//            
//            if(subosc_phase_ >= 1.0f)
//                subosc_phase_ -= 1.0f;
//            
//            carrier_downsampler.Accumulate(j, sample);
//        }
//        
//        float sample = carrier_downsampler.Read();
//        
//        *out++ = sample;
//        *aux++ = sample;
//    }
//    
//    GenerateWaveformData(tune, fx_amount, fx, morph);
//}

float Engine::GetSine(float phase) {
    float sample = sin(2 * M_PI * phase);
    return sample;
}

// This function calculates the PolyBLEPs
float Engine::poly_blep(float t, float dt)
{
//    double dt = phase;
    
    // t-t^2/2 +1/2
    // 0 < t <= 1
    // discontinuities between 0 & 1
    if (t < dt)
    {
        t /= dt;
        return t + t - t * t - 1.0;
    }
    
    // t^2/2 +t +1/2
    // -1 <= t <= 0
    // discontinuities between -1 & 0
    else if (t > 1 - dt)
    {
        t = (t - 1.0) / dt;
        return t * t + t + t + 1.0;
    }
    
    // no discontinuities
    // 0 otherwise
    else return 0.0;
}

float Engine::GetRamp(float phase, float phase_increment) {
    float value = 2.0f * phase - 1.0f;
    
    if(phase + phase_increment >= 1.0f) {
        phase = phase + phase_increment - 1.0f;
        float t = phase / phase_increment;
        value -= ThisBlepSample(t);
    } else if(phase < phase_increment) {
        float t = phase / phase_increment;
        value -= NextBlepSample(t);
    }
    
    return value;
}

float Engine::GetSawtooth(float phase, float phase_increment) {
    float value = 2.0f * (1.0-phase) - 1.0f;
    
    if(phase + phase_increment >= 1.0f) {
        phase = phase + phase_increment - 1.0f;
        float t = phase / phase_increment;
        value += ThisBlepSample(t);
    } else if(phase < phase_increment) {
        float t = phase / phase_increment;
        value += NextBlepSample(t);
    }
    
    return value;
}

float Engine::GetSquare(float phase, float phase_increment) {
    float value = phase < 0.5 ? 0.0 : 1.0;
    //(2.0f * phase - 1.0f) * 1.0;
    
    if(phase + phase_increment >= 0.5f && phase < 0.5f) {
        phase = phase + phase_increment - 0.5f;
        float t = phase / phase_increment;
        value += ThisBlepSample(t);
    } else if(phase >= 0.5f && phase - phase_increment < 0.5f) {
        float t = (phase - 0.5f) / phase_increment;
        value += NextBlepSample(t);
    }

    if(phase + phase_increment >= 1.0f) {
        phase = phase + phase_increment - 1.0f;
        float t = phase / phase_increment;
        value -= ThisBlepSample(t);
    } else if(phase < phase_increment) {
        float t = phase / phase_increment;
        value -= NextBlepSample(t);
    }

    return value;
}

float Engine::GetTriangle(float phase) {
    float value = -1.0 + (2.0 * phase);
    value = 2.0 * (fabs(value) - 0.5);
    return value;
}

float Engine::GetOscillatorSample(float phase, float phase_increment) {
    if(effect_manager.getOscillatorShape() == EffectManager::SINE_SHAPE)
        return GetSine(phase);
    else if(effect_manager.getOscillatorShape() == EffectManager::TRIANGLE_SHAPE)
        return GetTriangle(phase);
    else if(effect_manager.getOscillatorShape() == EffectManager::SAWTOOTH_SHAPE)
        return GetSawtooth(phase, phase_increment);
    else if(effect_manager.getOscillatorShape() == EffectManager::RAMP_SHAPE)
        return GetRamp(phase, phase_increment);
    else if(effect_manager.getOscillatorShape() == EffectManager::SQUARE_SHAPE)
        return GetSquare(phase, phase_increment);
    else return 0.0f;
}

//float Engine::GetSubOscillatorSample(float phase, float phase_increment, float morph) {
//    if(user_settings.getSubOscWave() == UserSettings::SUBOSC_WAVE_SINE)
//        return GetSine(phase);
//    else if(user_settings.getSubOscWave() == UserSettings::SUBOSC_WAVE_TRIANGLE)
//        return GetTriangle(phase);
//    else if(user_settings.getSubOscWave() == UserSettings::SUBOSC_WAVE_SAWTOOTH)
//        return GetSawtooth(phase, phase_increment);
//    else if(user_settings.getSubOscWave() == UserSettings::SUBOSC_WAVE_RAMP)
//        return GetRamp(phase, phase_increment);
//    else if(user_settings.getSubOscWave() == UserSettings::SUBOSC_WAVE_SQUARE)
//        return GetSquare(phase, phase_increment);
//    else if(user_settings.getSubOscWave() == UserSettings::SUBOSC_WAVE_COPY) {
//        return GetSampleBetweenFrames(phase, morph);
//    }
//    else return 0.0f;
//}
