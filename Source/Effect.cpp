/*
  ==============================================================================

    Effect.cpp
    Created: 12 Nov 2023 4:26:44pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Effect.h"
#include "Globals.h"

void Effect::Init() {
    phase = 0.0f;
    depth = 1.0f;
    sync = false;
    oscShape = SINE_SHAPE;
    effectType = FM;
    controlType = INTERNAL_MODULATOR;
}

void Effect::Reset() {
    phase = 0.0f;
}

float Effect::GetSample(float phase) {
    float sample = sin(2 * M_PI * phase);
    return sample;
}

float Effect::RenderSampleEffect(float sample, float phase, uint16_t tune, uint16_t fx_amount, uint16_t fx) {
    return sample;
}

float Effect::RenderPhaseEffect(float input_phase, uint16_t tune, uint16_t fx_amount, uint16_t fx) {
    float amount = depth * (fx_amount / 4095.0f);
    
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
    
    switch(controlType) {
        case INTERNAL_MODULATOR: {
            if(!sync) {
                float warpedPos;
                float m1, m2, b2;
                float x1 = 0.2;
                
                float frequency = pow(2, ((15.0 * fx) / 4095.0) - 3.0f);
                float phaseIncrement = frequency / 48000.0f;
                
                x1 = (amount * GetSample(phase) + 1.0f) / 2.0f;
                phase += phaseIncrement;
                if(phase >= 1.0)
                    phase -= 1.0;
                
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

                // frequency = from 8.18 hz to 8372 hz.  2^ x/12
//                (440 / 32) * 2 ^(-x / 12.0) = 0.13
//                0.13 * 32 / 440 = 2^(-x/12.0)
//                log2(.00945454545454545) = =-x/12.0
//                -6.725 = -x/12.0
//                x = 80.7
                //0.13...4189
                // 2^(0 x X) = 0.13, log2 = -2.9434.. -3
                // 2^(1 x X) = 4189  log2 = 12.032
//                1 * 15 - 3
//                float frequency = pow(2, ((15.0 * fx) / 4095.0) - 3.0f);
//                frequency = 220.0f/64.0f;
//                float phaseIncrement = frequency / 48000.0f;
//
//                float sample = GetSample(phase);
//                phase += phaseIncrement;
//                if(phase >= 1.0)
//                    phase -= 1.0;
//                adjusted_phase = (0.5 * sample + 1.0) / 2.0;
//                printf("%f\n", adjusted_phase);
//                while(adjusted_phase >= 1.0)
//                    adjusted_phase -= 1.0;
//                while(adjusted_phase < 0.0)
//                    adjusted_phase += 1.0;
            }
            break;
        }
        case EXTERNAL_MODULATOR:
        {
            break;
        }
        case MANUAL_CONTROL:
        {
            break;
        }
        default:
        {
            break;
        }
    }

    
    return adjusted_phase;

    //    gain = 4 * volume / volume_increment
}



float Effect::RenderFMSample(float sample, float phase, uint16_t tune, uint16_t fx_amount, uint16_t fx) {
    return sample;
}

float Effect::RenderFMPhase(float input_phase, uint16_t tune, uint16_t fx_amount, uint16_t fx) {
    float amount = depth * (fx_amount / 4095.0f);
    
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
    
    switch(controlType) {
        case INTERNAL_MODULATOR: {
            if(!sync) {
                // frequency = from 8.18 hz to 8372 hz.  2^ x/12
//                (440 / 32) * 2 ^(-x / 12.0) = 0.13
//                0.13 * 32 / 440 = 2^(-x/12.0)
//                log2(.00945454545454545) = =-x/12.0
//                -6.725 = -x/12.0
//                x = 80.7
                //0.13...4189
                // 2^(0 x X) = 0.13, log2 = -2.9434.. -3
                // 2^(1 x X) = 4189  log2 = 12.032
//                1 * 15 - 3
                float frequency = pow(2, ((15.0 * fx) / 4095.0) - 3.0f);
                float phaseIncrement = frequency / 48000.0f;

                float sample = GetSample(phase);
                phase += phaseIncrement;
                if(phase >= 1.0)
                    phase -= 1.0;
                adjusted_phase = input_phase + amount * sample;
                
                while(adjusted_phase >= 1.0)
                    adjusted_phase -= 1.0;
                while(adjusted_phase < 0.0)
                    adjusted_phase += 1.0;
            }
            break;
        }
        case EXTERNAL_MODULATOR:
        {
            break;
        }
        case MANUAL_CONTROL:
        {
            break;
        }
        default:
        {
            break;
        }
    }

    
    return adjusted_phase;

    //    gain = 4 * volume / volume_increment
}
