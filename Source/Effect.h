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
    Effect() {
        phase = 0.0f;
        oscilloscopePhase = 0.0f;
    }
    virtual ~Effect() {}
    virtual void Init() = 0;
    virtual void Reset() = 0;
    virtual float RenderSampleEffect(float sample, float phase, uint16_t tune, uint16_t fx_amount, uint16_t fx, bool isOscilloscope) = 0;
    virtual float RenderPhaseEffect(float phase, uint16_t tune, uint16_t fx_amount, uint16_t fx, bool isOscilloscope) = 0;
    float GetSine(float phase);
    float GetSawtooth(float phase, float phase_increment);
    float GetSquare(float phase, float phase_increment);
    float GetTriangle(float phase);
    double poly_blep(double t);
    inline float ThisBlepSample(float t) { return 0.5f * t * t; }
    inline float NextBlepSample(float t) { t = 1.0f - t; return -0.5f * t * t; }
    float poly_blep(float t, float dt);
    
    inline void triggerUpdate() { /*phase = 0.0f; oscilloscopePhase = 0.0f;*/ }
protected:
    float phase;
    float oscilloscopePhase;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Effect);
};
