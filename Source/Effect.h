/*
  ==============================================================================

    Effect.h
    Created: 12 Nov 2023 4:26:44pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

class Effect {
public:
    enum EffectState {
        FREQUENCY_MODULATION,
        RING_MODULATION,
        WAVEFOLDING,
        PHASE_DISTORTION
    };
    Effect() {}
    ~Effect() {}
    void renderPhaseEffect(float phase);
    void renderSampleEffect(float sample);
    inline void setEffect(EffectState newEffectState) { effectState = newEffectState; }
    inline EffectState getEffect() { return effectState; }
private:
    float fxKnob;
    float fxAmountKnob;
    
    EffectState effectState;
}
