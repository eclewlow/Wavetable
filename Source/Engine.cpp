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

Engine::Engine() {
    phaseIncrement = 43.06f / 48000.0f;
    phase = 0.0f;

}

Engine::~Engine() {
    
}

void Engine::Init() {
    phaseIncrement = 43.06f / 48000.0f;
    phase = 0.0f;
    frame00 = (int16_t*)&Wavetable_harmonic_series[0];
    frame01 = (int16_t*)&Wavetable_harmonic_series[2048];
}

float Engine::Render() {
    float sample = sin(2 * M_PI * phase);

    phase += phaseIncrement;
    if(phase >= 1.0f)
        phase -= 1.0f;
    return sample;
}

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

int16_t* Engine::GetWaveformData() {
    float index = clamp(x, 0.0, 15.0);
    uint8_t integral = floor(index);
    float fractional = index - integral;

    uint8_t nextIntegral = integral + ceil(fractional);

    int16_t waveform_data[2048];
    for (int i = 0 ; i < 2048; i++) {
        int16_t data1 = Wavetable_harmonic_series[integral * 2048 + i];
        int16_t data2 = Wavetable_harmonic_series[nextIntegral * 2048 + i];
        waveform_data[i] = data1 * (1.0f - fractional) + data2 * fractional;
    }
    return waveform_data;
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

void Engine::Render(float* out, float* aux, uint32_t size)
{
    ParameterInterpolator xInterpolator(&x, targetX, size);

    while (size--) {
        float thisX = xInterpolator.Next();
        thisX = clamp(thisX, 0.0, 15.0);
        float sample = GetSampleBetweenFrames(phase, thisX);

        sample = effect.renderSampleEffect(sample);
        
        phase += effect.renderPhaseEffect(phaseIncrement);
        if(phase >= 1.0f)
            phase -= 1.0f;
      
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
