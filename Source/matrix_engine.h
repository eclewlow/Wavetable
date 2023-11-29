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
    float GetSampleBetweenFrames(float phase, float thisX);
    bool handleKeyPress(const juce::KeyPress &key);
    void FillWaveform(int16_t * waveform, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph, bool withFx);
    float GetSample(float phase);
    float GetSampleNoFX(float phase, float morph);
    void triggerUpdate();
    
    inline void SetWavetable(int wavetable) { wavetable_ = std::clamp(wavetable, 0, USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 1); }
    inline int GetWavetable() { return wavetable_; }
    
    inline void SetX1(float x1) { x1_ = x1; }
    inline void SetY1(float y1) { y1_ = y1; }
    inline void SetX2(float x2) { x2_ = x2; }
    inline void SetY2(float y2) { y2_ = y2; }
    
    inline float GetX1() { return x1_; }
    inline float GetY1() { return y1_; }
    inline float GetX2() { return x2_; }
    inline float GetY2() { return y2_; }

private:
    int wavetable_;
    
    float x1_;
    float x2_;
    float y1_;
    float y2_;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MatrixEngine);
};
