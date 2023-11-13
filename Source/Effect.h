/*
  ==============================================================================

    Effect.h
    Created: 12 Nov 2023 4:26:44pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Effect {
public:
    enum OscillatorShape {
        SINE_SHAPE,
        TRIANGLE_SHAPE,
        SNH_SHAPE,
        RAMP_SHAPE,
        SAWTOOTH_SHAPE,
    };
    enum EffectType {
        FM,
        RING_MODULATION,
        WAVEFOLDER,
        PHASE_DISTORTION,
    };
    enum ControlType {
        MANUAL_CONTROL,
        EXTERNAL_MODULATOR,
        INTERNAL_MODULATOR,
    };

    Effect() {
        phase = 0.0f;
        depth = 1.0f;
        sync = false;
        oscShape = SINE_SHAPE;
        effectType = FM;
        controlType = INTERNAL_MODULATOR;
    }
    ~Effect() {}
    void Init();
    void Reset();
    float RenderSampleEffect(float sample, float phase, uint16_t tune, uint16_t fx_amount, uint16_t fx);
    float RenderPhaseEffect(float phase, uint16_t tune, uint16_t fx_amount, uint16_t fx);
    float RenderFMSample(float sample, float phase, uint16_t tune, uint16_t fx_amount, uint16_t fx);
    float RenderFMPhase(float phase, uint16_t tune, uint16_t fx_amount, uint16_t fx);
    float GetSample(float phase);
protected:
    float phase;
    float depth;
    bool sync;
    OscillatorShape oscShape;
    EffectType effectType;
    ControlType controlType;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Effect);
};
