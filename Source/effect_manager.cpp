/*
  ==============================================================================

    effect_manager.cpp
    Created: 13 Nov 2023 6:40:12pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "effect_manager.h"

void EffectManager::Init() {
    depth = 1.0f;
    sync = false;
    oscillatorShape = SINE_SHAPE;
    effectType = FM;
    controlType = INTERNAL_MODULATOR;
    ratio_ = 0.1f;
}

void EffectManager::Reset() {
    depth = 1.0f;
    sync = false;
    oscillatorShape = SINE_SHAPE;
    effectType = FM;
    controlType = INTERNAL_MODULATOR;
    ratio_ = 0.1f;
}

float EffectManager::RenderSampleEffect(float sample, float phase, uint16_t tune, uint16_t fx_amount, uint16_t fx, bool isOscilloscope, bool downsampling) {
    if(effect_) {
        return effect_->RenderSampleEffect(sample, phase, tune, fx_amount, fx, isOscilloscope, downsampling);
    }
    else {
        return sample;
    }
}
float EffectManager::RenderPhaseEffect(float phase, uint16_t tune, uint16_t fx_amount, uint16_t fx, bool isOscilloscope, bool downsampling) {
    if(effect_) {
        return effect_->RenderPhaseEffect(phase, tune, fx_amount, fx, isOscilloscope, downsampling);
    }
    else {
        return phase;
    }
}
