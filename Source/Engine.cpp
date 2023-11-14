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
    phase = 0.0f;
    memset(waveformData, 0, 2048*2);
}

Engine::~Engine() {
    
}

void Engine::Init() {
    phase = 0.0f;
    frame00 = (int16_t*)&Wavetable_harmonic_series[0];
    frame01 = (int16_t*)&Wavetable_harmonic_series[2048];
    memset(waveformData, 0, 2048*2);
}

//float Engine::Render() {
//    float sample = sin(2 * M_PI * phase);
//
//    phase += phaseIncrement;
//    if(phase >= 1.0f)
//        phase -= 1.0f;
//    return sample;
//}

float Engine::GetSample(int16_t* frame, float phase) {
    float index = phase * 2048.0;
    uint16_t integral = floor(index);
    float fractional = index - integral;
    
    uint16_t nextIntegral = (integral + 1) % 2048;
    
    float interpolated16 = frame[integral] + (frame[nextIntegral]-frame[integral]) * fractional;
    
    float interpolatedFloat = interpolated16 / 32768.0f;
    
    return interpolatedFloat;
}

float Engine::GetSampleBetweenFrames(float phase, float thisX) {
    float index = thisX;
    uint8_t integral = floor(index);
    float fractional = index - integral;
    
    uint8_t nextIntegral = integral + ceil(fractional);
    
    float frame1sample = GetSample((int16_t*)&Wavetable_harmonic_series[integral * 2048], phase);
    float frame2sample = GetSample((int16_t*)&Wavetable_harmonic_series[nextIntegral * 2048], phase);
    
    float sample = frame1sample * (1.0f - fractional) + frame2sample * fractional;
    return sample;
}

float Engine::GetSample(float phase) {
    float sample = sin(2 * M_PI * phase);
    return sample;
}

int16_t* Engine::GetWaveformData(uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph) {
    //    float index = clamp(x, 0.0, 15.0);
    //    uint8_t integral = floor(index);
    //    float fractional = index - integral;
    //
    //    uint8_t nextIntegral = integral + ceil(fractional);
    //
    //    int16_t waveform_data[2048];
    //    for (int i = 0 ; i < 2048; i++) {
    //        int16_t data1 = Wavetable_harmonic_series[integral * 2048 + i];
    //        int16_t data2 = Wavetable_harmonic_series[nextIntegral * 2048 + i];
    //        waveform_data[i] = data1 * (1.0f - fractional) + data2 * fractional;
    //    }
    //    return waveform_data;
    //    uint8_t note = static_cast<uint8_t>((120.0f * tune)/4095.0);
    // frequency = from 8.18 hz to 8372 hz.  2^ x/12
    //    float a = 440; //frequency of A (coomon value is 440Hz)
//    int16_t note = static_cast<uint8_t>((120.0f * tune)/4095.0);
    // frequency = from 8.18 hz to 8372 hz.  2^ x/12
//    note = note - 24;
//    float a = 440; //frequency of A (coomon value is 440Hz)
//    float frequency = (a / 32) * pow(2, ((note - 9) / 12.0));
    //    float adjusted_phase = 0.0f;
//    float phaseIncrement = frequency / 48000.0f;

    float frequency = 23.4375;
    //    float adjusted_phase = 0.0f;
    float phaseIncrement = frequency / 48000.0f;
    
    //    float target = morph;
    // convert 12 bit uint 0-4095 to 0...15 float
    //    float morphTarget = morph * 15.0 / 4095.0;
    //    float interpolatedFloat = interpolated16 / 32768.0f;
    float temp_phase = 0.0f;
//    effect->Reset();
    //    ParameterInterpolator xInterpolator(&x, morphTarget, size);
//    int16_t waveform_data[2048];
    
    for(int i = 0; i < 2048; i++) {
        float thisX = x;
        thisX = clamp(thisX, 0.0, 15.0);
        
        float calculated_phase = effect_manager.RenderPhaseEffect(temp_phase, tune, fx_amount, fx, true);
//        float calculated_phase = temp_phase;
//        printf("%f\n", calculated_phase);
        
        float sample = GetSampleBetweenFrames(calculated_phase, thisX);
        
        sample = effect_manager.RenderSampleEffect(sample, temp_phase, tune, fx_amount, fx, true);
        
//        sample = GetSample(temp_phase);
//        if(calculated_phase < temp_phase) break;
        temp_phase += phaseIncrement;
        
        if(temp_phase >= 1.0f)
            temp_phase -= 1.0f;
        
        waveformData[i] = static_cast<int16_t>(sample * 32767.0f);
    }
//    printf("done\n");
    //      *out++ = sample;
    //      *aux++ = sample;
    return waveformData;
}

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

void Engine::Render(float* out, float* aux, uint32_t size, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph)
{
    int16_t note = static_cast<uint8_t>((120.0f * tune)/4095.0);
    // frequency = from 8.18 hz to 8372 hz.  2^ x/12
//    note = note - 24;
    float a = 440; //frequency of A (coomon value is 440Hz)
    float frequency = (a / 32) * pow(2, ((note - 9) / 12.0));
    //    float adjusted_phase = 0.0f;
    float phaseIncrement = frequency / 48000.0f;
    
    //    float target = morph;
    // convert 12 bit uint 0-4095 to 0...15 float
    float morphTarget = morph * 15.0 / 4095.0;
    //    float interpolatedFloat = interpolated16 / 32768.0f;
    
    ParameterInterpolator xInterpolator(&x, morphTarget, size);
    Downsampler carrier_downsampler(&carrier_fir_);
    
    while (size--) {
        float thisX = xInterpolator.Next();
        thisX = clamp(thisX, 0.0, 15.0);
        
//        for (size_t j = 0; j < kOversampling; ++j) {
            float sample = GetSampleBetweenFrames(effect_manager.RenderPhaseEffect(phase, tune, fx_amount, fx), thisX);
            
            sample = effect_manager.RenderSampleEffect(sample, phase, tune, fx_amount, fx);
            
            phase += phaseIncrement;
            
            if(phase >= 1.0f)
                phase -= 1.0f;
            
//            carrier_downsampler.Accumulate(j, sample);
//        }
        
//        float sample = carrier_downsampler.Read();
        *out++ = sample;
        *aux++ = sample;
    }
}


bool Engine::handleKeyPress(const juce::KeyPress &key) {
    if(key.getKeyCode() == 78) {
        float newX = x - 0.05;
        if(newX < 0.0)
            newX = 0.0;
        targetX = newX;
        return true;
    }
    if(key.getKeyCode() == 77) {
        float newX = x + 0.05;
        if(newX > 15.0)
            newX = 15.0;
        targetX = newX;
        return true;
    }
    //    printf("%f", targetX);
    return false;
}
