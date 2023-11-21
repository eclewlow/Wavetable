/*
  ==============================================================================

    suboscillator.h
    Created: 19 Nov 2023 4:08:34am
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "effect.h"
#include "Engine.h"

class Suboscillator;

class Suboscillator: public Engine
{
public:
    Suboscillator();
    ~Suboscillator();
    virtual void Render(float* out, float* aux, uint32_t size, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph);
    float Render();
    void Init();
    float GetSample(int16_t wavetable, int16_t frame, float phase);
    float GetSampleBetweenFrames(float phase, float thisX);
//    void SetX(float newX);
    bool handleKeyPress(const juce::KeyPress &key);
    float GetSampleNoFX(float phase, float morph);
    void FillWaveform(int16_t * waveform, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph, bool withFx);

//    inline void sync_suboscillator_phase() { subosc_phase_ = phase; }
    //    void Reset();
    //    void LoadUserData(const uint8_t* user_data) { }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Suboscillator);
};
