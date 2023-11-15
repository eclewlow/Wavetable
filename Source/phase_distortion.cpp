/*
 ==============================================================================
 
 phase_distortion.cpp
 Created: 13 Nov 2023 6:31:26pm
 Author:  Eugene Clewlow
 
 ==============================================================================
 */

#include "phase_distortion.h"

#include "Effect.h"
#include "Globals.h"

void PhaseDistortion::Init() {
    phase = 0.0f;
}

void PhaseDistortion::Reset() {
    phase = 0.0f;
}

float PhaseDistortion::GetSample(float phase) {
    float sample = sin(2 * M_PI * phase);
    return sample;
}

float PhaseDistortion::RenderSampleEffect(float sample, float input_phase, uint16_t tune, uint16_t fx_amount, uint16_t fx, bool isOscilloscope, bool downsampling) {
    return sample;
}

float PhaseDistortion::RenderPhaseEffect(float input_phase, uint16_t tune, uint16_t fx_amount, uint16_t fx, bool isOscilloscope, bool downsampling) {
    float amount = effect_manager.getDepth() * (fx_amount / 4095.0f);
    
    uint8_t note = static_cast<uint8_t>((120.0f * tune)/4095.0);

    float a = 440; //frequency of A (coomon value is 440Hz)
    float frequency = (a / 32) * pow(2, ((note - 9) / 12.0));
    float adjusted_phase = 0.0f;
    float phaseIncrement = frequency / 48000.0f;
    
    float warpedPos;
    float m1, m2, b2;
    float x1 = 0.2;
    
    if(!effect_manager.getSync())
        frequency = pow(2, ((15.0 * fx) / 4095.0) - 3.0f);
    else {
        if(fx * 25.0f / 4095 < 10.0f)
            frequency *= (int(fx * 25.0f / 4095) / 10.0f);
        else {
            frequency *= (int(fx*25.0f/4095) - 9);
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
            
            
            if(effect_manager.getOscillatorShape() == EffectManager::SINE_SHAPE)
                x1 = (amount * GetSine(*target_phase) + 1.0f) / 2.0f;
            else if(effect_manager.getOscillatorShape() == EffectManager::SAWTOOTH_SHAPE)
                x1 = (amount * GetSawtooth(*target_phase, phaseIncrement) + 1.0f) / 2.0f;
            else if(effect_manager.getOscillatorShape() == EffectManager::SQUARE_SHAPE)
                x1 = (amount * GetSquare(*target_phase, phaseIncrement) + 1.0f) / 2.0f;
            
            *target_phase += phaseIncrement;
            if(*target_phase >= 1.0)
                *target_phase -= 1.0;
            
            break;
        }
        case EffectManager::EXTERNAL_MODULATOR:
        {
            break;
        }
        case EffectManager::MANUAL_CONTROL:
        {
            x1 = 0.5f + amount * (1.0f * fx / 4095.0f - 0.5f);

            break;
        }
        default:
        {
            break;
        }
    }
    
    m1 = .5 / x1;
    m2 = .5 / (1.0 - x1);
    b2 = 1.0 - m2;
    
    if(input_phase < x1) {
        warpedPos = m1 * input_phase;
    } else {
        warpedPos = m2 * input_phase + b2;
    }
    adjusted_phase = warpedPos;
    
    while(adjusted_phase >= 1.0)
        adjusted_phase -= 1.0;
    while(adjusted_phase < 0.0)
        adjusted_phase += 1.0;
    
    return adjusted_phase;
    
    //    gain = 4 * volume / volume_increment
}
