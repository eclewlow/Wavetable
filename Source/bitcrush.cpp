/*
  ==============================================================================

    bitcrusher.cpp
    Created: 14 Nov 2023 4:36:59pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Effect.h"
#include "Globals.h"

void Bitcrush::Init() {
    phase = 0.0f;
}

void Bitcrush::Reset() {
    phase = 0.0f;
}

float Bitcrush::GetSample(float phase) {
    float sample = sin(2 * M_PI * phase);
    return sample;
}

float Bitcrush::RenderSampleEffect(float sample, float input_phase, float frequency, uint16_t fx_amount, uint16_t fx, bool isOscilloscope, bool downsampling) {
    float amount = effect_manager.getDepth() * (fx_amount / 4095.0f);
    
    float adjusted_phase = 0.0f;
    float phaseIncrement = frequency / 48000.0f;
    
    if(!effect_manager.getSync())
        frequency = pow(2, ((15.0 * fx) / 4095.0) - 3.0f);
    else {
        if(fx >= 2048) {
            frequency *= int(1.0f + (fx - 2048.0f) * 15.0f / 2047.0f);
        } else {
            frequency /= int(1.0f + (2047 - fx) * 15.0f / 2047.0f);
        }
    }
    
    phaseIncrement = frequency / 48000.0f;
    
    float *target_phase;
    
    if(isOscilloscope)
        target_phase = &oscilloscopePhase;
    else
        target_phase = &phase;
    
    
    switch(effect_manager.getControlType()) {
        case EffectManager::INTERNAL_MODULATOR: {
            
            float modulator_sample = 0.0f;
            
            modulator_sample = context.getEngine()->GetOscillatorSample(*target_phase, phaseIncrement);
            
            *target_phase += phaseIncrement;
            if(*target_phase >= 1.0)
                *target_phase -= 1.0;
            
            // amount of bitcrush fx
            // reduce sample
            // -1 to 1
            // round to nearest multiple of 0.25
            // 0.75  / 0.25 = 3
            //
            // // 1 means low bit rate.  0.001 means high bit rate
            float bit_rate_divisor = std::clamp((modulator_sample + 1.0f) / 2.0f, 0.001f, 1.0f);
            // bit rate = 1 / divisor
            float calculated_sample = static_cast<int>(sample / bit_rate_divisor) * bit_rate_divisor;

            sample = sample * (1 - amount) + amount * calculated_sample;

            
            break;
        }
        case EffectManager::EXTERNAL_MODULATOR:
        {
            float modulator_sample = fx / 4095.0;
            
            float bit_rate_divisor = std::clamp(modulator_sample, 0.001f, 1.0f);

            float calculated_sample = static_cast<int>(sample / bit_rate_divisor) * bit_rate_divisor;

            sample = sample * (1 - amount) + amount * calculated_sample;

            break;
        }
        case EffectManager::MANUAL_CONTROL:
        {
            float modulator_sample = fx / 4095.0;
            
            float bit_rate_divisor = std::clamp(modulator_sample, 0.001f, 1.0f);

            float calculated_sample = static_cast<int>(sample / bit_rate_divisor) * bit_rate_divisor;

            sample = sample * (1 - amount) + amount * calculated_sample;

            break;
        }
        default:
        {
            break;
        }
    }
    
    return sample;
}

float Bitcrush::RenderPhaseEffect(float input_phase, float frequency, uint16_t fx_amount, uint16_t fx, bool isOscilloscope, bool downsampling) {
    return input_phase;
}
