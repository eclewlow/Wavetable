/*
  ==============================================================================

    suboscillator.cpp
    Created: 19 Nov 2023 4:08:34am
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Engine.h"
#include "wavetables.h"
#include "ParameterInterpolator.h"
#include "Globals.h"
#include "4x_downsampler.h"

Suboscillator::Suboscillator() {
    phase_ = 0.0f;
}

Suboscillator::~Suboscillator() {
    
}

void Suboscillator::Init() {
    phase_ = 0.0f;
}

float Suboscillator::GetSample(int16_t wavetable, int16_t frame, float phase){
    return 0.0f;
}


float Suboscillator::GetSampleNoFX(float phase, float morph) {
    return 0.0f;
}

void Suboscillator::FillWaveform(int16_t * waveform, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph, bool withFx)
{
}

void Suboscillator::triggerUpdate() {
    
}

void Suboscillator::Render(float* out, float* aux, uint32_t size, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph)
{
    //    float target = morph;
    // convert 12 bit uint 0-4095 to 0...15 float
    float morphTarget;
    if(context.getEngine() == &abEngine) {
        morphTarget = morph / 4095.0;
    } else {
        morphTarget = morph * 15.0 / 4095.0;
    }
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
        float phase_increment = frequency / 48000.0f;
        
        frequency = (a / 32) * pow(2, (((note + user_settings.getSubOscDetune() / 100.0f + user_settings.getSubOscOffset()) - 9) / 12.0));
        phase_increment = frequency / 48000.0f;

        float interpolated_morph = morph_interpolator.Next();
        if(context.getEngine() == &abEngine) {
            interpolated_morph = clamp(interpolated_morph, 0.0, 1.0);
        } else {
            interpolated_morph = clamp(interpolated_morph, 0.0, 15.0);
        }
        
        for (size_t j = 0; j < kOversampling; ++j) {
            float sample = 0.0f;
            if(user_settings.getSubOscWave() == UserSettings::SUBOSC_WAVE_SINE)
                sample = GetSine(phase_);
            else if(user_settings.getSubOscWave() == UserSettings::SUBOSC_WAVE_TRIANGLE)
                sample = GetTriangle(phase_);
            else if(user_settings.getSubOscWave() == UserSettings::SUBOSC_WAVE_SAWTOOTH)
                sample = GetSawtooth(phase_, phase_increment);
            else if(user_settings.getSubOscWave() == UserSettings::SUBOSC_WAVE_RAMP)
                sample = GetRamp(phase_, phase_increment);
            else if(user_settings.getSubOscWave() == UserSettings::SUBOSC_WAVE_SQUARE)
                sample = GetSquare(phase_, phase_increment);
            else if(user_settings.getSubOscWave() == UserSettings::SUBOSC_WAVE_COPY) {
                sample = context.getEngine()->GetSampleNoFX(phase_, interpolated_morph);
            }

            phase_ += phase_increment;
            
            if(phase_ >= 1.0f)
                phase_ -= 1.0f;
            
            carrier_downsampler.Accumulate(j, sample);
        }
        
        float sample = carrier_downsampler.Read();
        
        *out++ = sample;
        *aux++ = sample;
    }
}

