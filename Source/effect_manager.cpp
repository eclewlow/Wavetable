/*
  ==============================================================================

    effect_manager.cpp
    Created: 13 Nov 2023 6:40:12pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "effect_manager.h"

void EffectManager::Init() {
    depth_ = 1.0f;
    sync_ = false;
    oscillator_shape_ = SINE_SHAPE;
    control_type_ = INTERNAL_MODULATOR;
}

void EffectManager::Reset() {
    depth_ = 1.0f;
    sync_ = false;
    oscillator_shape_ = SINE_SHAPE;
    control_type_ = INTERNAL_MODULATOR;
}

float EffectManager::RenderSampleEffect(float sample, float phase, float frequency, uint16_t fx_amount, uint16_t fx, bool isOscilloscope, bool downsampling) {
    if(effect_) {
        return effect_->RenderSampleEffect(sample, phase, frequency, fx_amount, fx, isOscilloscope, downsampling);
    }
    else {
        return sample;
    }
}
float EffectManager::RenderPhaseEffect(float phase, float frequency, uint16_t fx_amount, uint16_t fx, bool isOscilloscope, bool downsampling) {
    if(effect_) {
        return effect_->RenderPhaseEffect(phase, frequency, fx_amount, fx, isOscilloscope, downsampling);
    }
    else {
        return phase;
    }
}
