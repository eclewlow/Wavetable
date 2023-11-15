/*
 ==============================================================================
 
 ring_modulator.cpp
 Created: 13 Nov 2023 6:31:18pm
 Author:  Eugene Clewlow
 
 ==============================================================================
 */

#include "Effect.h"
#include "Globals.h"

void RingModulator::Init() {
    phase = 0.0f;
}

void RingModulator::Reset() {
    phase = 0.0f;
}

float RingModulator::GetSample(float phase) {
    float sample = sin(2 * M_PI * phase);
    return sample;
}

float RingModulator::RenderSampleEffect(float sample, float input_phase, uint16_t tune, uint16_t fx_amount, uint16_t fx, bool isOscilloscope, bool downsampling) {
    float amount = effect_manager.getDepth() * (fx_amount / 4095.0f);
    
    uint8_t note = static_cast<uint8_t>((120.0f * tune)/4095.0);

    float a = 440; //frequency of A (coomon value is 440Hz)
    float frequency = (a / 32) * pow(2, ((note - 9) / 12.0));
    float adjusted_phase = 0.0f;
    float phaseIncrement = frequency / 48000.0f;
    
    if(!effect_manager.getSync())
        frequency = pow(2, ((15.0 * fx) / 4095.0) - 3.0f);
    else {
        if(fx * 25.0f / 4095 < 10.0f)
            frequency *= (int(fx * 25.0f / 4095) / 10.0f);
        else {
            frequency *= (int(fx*25.0f/4095) - 9);
        }
    }
    
    if(downsampling)
        frequency /= 4.0f;
    
    phaseIncrement = frequency / 48000.0f;
    
    float *target_phase;
    
    if(isOscilloscope)
        target_phase = &oscilloscopePhase;
    else
        target_phase = &phase;
    
    
    switch(effect_manager.getControlType()) {
        case EffectManager::INTERNAL_MODULATOR: {
            
            float modulator_sample = 0.0f;
            
            if(effect_manager.getOscillatorShape() == EffectManager::SINE_SHAPE)
                modulator_sample = GetSine(*target_phase);
            else if(effect_manager.getOscillatorShape() == EffectManager::SAWTOOTH_SHAPE)
                modulator_sample = GetSawtooth(*target_phase, phaseIncrement);
            else if(effect_manager.getOscillatorShape() == EffectManager::SQUARE_SHAPE)
                modulator_sample = GetSquare(*target_phase, phaseIncrement);
            
            *target_phase += phaseIncrement;
            if(*target_phase >= 1.0)
                *target_phase -= 1.0;
            sample = sample * (1 - amount) + amount * sample * modulator_sample;
            
            break;
        }
        case EffectManager::EXTERNAL_MODULATOR:
        {
            break;
        }
        case EffectManager::MANUAL_CONTROL:
        {
            
            float modulator_sample = 2.0 * fx / 4095.0 - 1.0;
            
            sample = sample * (1 - amount) + amount * sample * modulator_sample;
            break;
        }
        default:
        {
            break;
        }
    }
    
    return sample;
}

float RingModulator::RenderPhaseEffect(float input_phase, uint16_t tune, uint16_t fx_amount, uint16_t fx, bool isOscilloscope, bool downsampling) {
    return input_phase;
}
