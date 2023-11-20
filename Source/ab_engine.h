/*
  ==============================================================================

    ab_engine.h
    Created: 19 Nov 2023 3:52:35am
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "effect.h"
#include "Engine.h"

class Engine;

class ABEngine: public Engine
{
public:
    ABEngine();
    ~ABEngine();
    virtual void Render(float* out, float* aux, uint32_t size, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph);
    float Render();
    void Init();
    float GetSample(int16_t* frame, float phase);
    float GetSampleBetweenFrames(float phase, float thisX);
//    void SetX(float newX);
    bool handleKeyPress(const juce::KeyPress &key);
    void GenerateWaveformData(uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph);
    int16_t* GetWaveformData(uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph);
    float GetSample(float phase);
    float GetSampleNoFX(float phase, float morph);
    int16_t* GetWaveformDataNoFX(int index, uint16_t morph);
    void LoadWave(int index, int wavetable, int wave);
    void SwapBuf(int16_t * front_buf, int16_t * back_buf);
    //    void Reset();
    //    void LoadUserData(const uint8_t* user_data) { }
private:
    int16_t* left_wave_;
    int16_t* right_wave_;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ABEngine);
};
