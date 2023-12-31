/*
  ==============================================================================

    bypass.h
    Created: 17 Nov 2023 5:42:23pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include "effect.h"

class Bypass: public Effect {
public:

    Bypass() {
        phase = 0.0f;
    }
    ~Bypass() {}
    void Init();
    void Reset();
    float RenderSampleEffect(float sample, float input_phase, float frequency, uint16_t fx_amount, uint16_t fx, bool isOscilloscope, bool downsampling);
    float RenderPhaseEffect(float input_phase, float frequency, uint16_t fx_amount, uint16_t fx, bool isOscilloscope, bool downsampling);
    float GetSample(float phase);
protected:
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Bypass);
};
