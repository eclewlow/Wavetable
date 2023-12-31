/*
  ==============================================================================

    matrix_engine.h
    Created: 19 Nov 2023 3:53:03am
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "effect.h"
#include "Engine.h"

class Engine;

class MatrixEngine: public Engine
{
public:
    MatrixEngine();
    ~MatrixEngine();
    virtual void Render(float* out, float* aux, uint32_t size, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph);
    float Render();
    void Init();
    float GetSample(int16_t wavetable, int16_t frame, float phase);
    float GetSampleBetweenFrames(float phase, float morph_x, float morph_y);
    bool handleKeyPress(const juce::KeyPress &key);
    void FillWaveform(int16_t * waveform, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph, bool withFx);
    float GetSample(float phase);
    float GetSampleNoFX(float phase, float fx, float morph);
    void triggerUpdate();
    
    void SetX1(int8_t x1);
    void SetY1(int8_t y1);
    void SetX2(int8_t x2);
    void SetY2(int8_t y2);

    void IncrementX1(int8_t dx);
    void IncrementY1(int8_t dy);
    void IncrementX2(int8_t dx);
    void IncrementY2(int8_t dy);

    int8_t GetX1();
    int8_t GetY1();
    int8_t GetX2();
    int8_t GetY2();
    
    void SetWavelistOffset(int8_t offset);
    int8_t GetWavelistOffset();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MatrixEngine);
};
