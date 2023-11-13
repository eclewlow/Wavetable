/*
  ==============================================================================

    Engine.h
    Created: 9 Nov 2023 3:03:36pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Engine
{
public:
    Engine();
    ~Engine();
    void Render(float* out, float* aux, uint32_t size);
    float Render();
    void Init();
    float GetSample(int16_t* frame, float phase);
    float GetSampleBetweenFrames(float phase, float thisX);
//    void SetX(float newX);
    bool handleKeyPress(const juce::KeyPress &key);
    int16_t* GetWaveformData();
    //    void Reset();
    //    void LoadUserData(const uint8_t* user_data) { }
private:
    int16_t* frame00;
    int16_t* frame01;
    float phaseIncrement;
    float phase;
    float x;
    float targetX;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Engine);
};
