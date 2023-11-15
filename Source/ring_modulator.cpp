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

float RingModulator::RenderSampleEffect(float sample, float input_phase, uint16_t tune, uint16_t fx_amount, uint16_t fx, bool isOscilloscope) {
    float amount = effect_manager.getDepth() * (fx_amount / 4095.0f);
    
    // if sync
    //   calculate phase increment as a multiple of vco oscillator frequency WE NEED THIS AS INPUT
    // if not sync
    //   calculate phase increment from fx parameter.. fx is 0...4095,,, or 0.13 to 4189 4188?... logarithmic.  more precision on lower end, and quickly ramps up to 4189... upon cv input... the value is (fxamountknob = fxknob * (cv_value / 4095.0)
    // if contol type == INTERNAL_MODULATOR
    //     the coefficient is the result of a oscillator function
    // if control type == manual control
    //      the coefficient is a value from -1...1  based on 2*fx variable / 4095.0 - 1.0
    // if control type == external oscillator
    //      the coefficient is a value from -1... 1 based on adc.channel(4+2)   2xadc_value / 4095.0 - 1.0... NO fx knob acts as attenuator, so the adc value is scaled down. (fxKnobval / 4095.0) * (2xcv_value / 4095.0 - 1.0)
    
    //    float frequency =
    // calculate amount is fx amount (converted to 1.0) * depth
    // tune / 4095.0 * 10 octaves
    uint8_t note = static_cast<uint8_t>((120.0f * tune)/4095.0);
    // frequency = from 8.18 hz to 8372 hz.  2^ x/12
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

float RingModulator::RenderPhaseEffect(float input_phase, uint16_t tune, uint16_t fx_amount, uint16_t fx, bool isOscilloscope) {
    return input_phase;
    //    gain = 4 * volume / volume_increment
}
