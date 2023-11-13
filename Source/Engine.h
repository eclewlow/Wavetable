/*
  ==============================================================================

    Engine.h
    Created: 9 Nov 2023 3:03:36pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "effect.h"

class Engine
{
public:
    Engine();
    ~Engine();
    void Render(float* out, float* aux, uint32_t size, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph, Effect* effect);
    float Render();
    void Init();
    float GetSample(int16_t* frame, float phase);
    float GetSampleBetweenFrames(float phase, float thisX);
//    void SetX(float newX);
    bool handleKeyPress(const juce::KeyPress &key);
    int16_t* GetWaveformData(uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph, Effect* effect);
    //    void Reset();
    //    void LoadUserData(const uint8_t* user_data) { }
private:
    int16_t* frame00;
    int16_t* frame01;
    float phase;
    float x;
    float targetX;
    float carrier_fir_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Engine);
};
