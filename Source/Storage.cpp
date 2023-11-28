/*
  ==============================================================================

    Storage.cpp
    Created: 20 Nov 2023 5:41:08pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Storage.h"
#include "wavetables.h"

int16_t Storage::LoadWaveSample(int table, int frame, int index) {
    WAVETABLE wavetable = getWavetable(table);
    return wavetable.waves[frame][index];
}

void Storage::LoadWaveSample(int16_t * waveform, int16_t wavetable, int16_t frame) {
    memcpy(waveform, getWavetable(wavetable).waves[frame], 2048 * 2);
}


void Storage::LoadWaveSample(int16_t * waveform, int16_t wavetable, float morph) {
    float frequency = 23.4375;

    float phaseIncrement = frequency / 48000.0f;
    
    float phase = 0.0f;
    
    for(int i = 0; i < 2048; i++) {
        float index = phase * 2048.0f;
        uint16_t integral = floor(index);
        float fractional = index - integral;
        
        uint16_t nextIntegral = (integral + 1) % 2048;
        
        float frame = morph * 15.0f;
        uint16_t frame_integral = floor(frame);
        float frame_fractional = frame - frame_integral;
        
        uint16_t next_frame_integral = (frame_integral + 1) % 16;

        float sample;

        if(frame_fractional > 0.0f) {
            // we need to morph between frames
            float sample1 = LoadWaveSample(wavetable, frame_integral, integral);
            float sample2 = LoadWaveSample(wavetable, frame_integral, nextIntegral);
            
            float interpolated16 = sample1 + (sample2 - sample1) * fractional;
            
            float interpolatedFloat = interpolated16 / 32768.0f;
            
            sample = interpolatedFloat;
            
            sample1 = LoadWaveSample(wavetable, next_frame_integral, integral);
            sample2 = LoadWaveSample(wavetable, next_frame_integral, nextIntegral);
            
            interpolated16 = sample1 + (sample2 - sample1) * fractional;
            
            interpolatedFloat = interpolated16 / 32768.0f;
            
            sample = (1 - frame_fractional) * sample + frame_fractional * interpolatedFloat;

        } else {
            // just do the phase morph
            float sample1 = LoadWaveSample(wavetable, frame_integral, integral);
            float sample2 = LoadWaveSample(wavetable, frame_integral, nextIntegral);
            
            float interpolated16 = sample1 + (sample2 - sample1) * fractional;
            
            float interpolatedFloat = interpolated16 / 32768.0f;
            
            sample = interpolatedFloat;
        }
                
        phase += phaseIncrement;
        
        if(phase >= 1.0f)
            phase -= 1.0f;
        
        waveform[i] = static_cast<int16_t>(sample * 32767.0f);
    }
}
