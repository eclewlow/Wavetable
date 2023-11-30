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
    
    inline void SetX1(int8_t x1) { x1_ = x1; }
    inline void SetY1(int8_t y1) { y1_ = y1; }
    inline void SetX2(int8_t x2) { x2_ = x2; }
    inline void SetY2(int8_t y2) { y2_ = y2; }

    inline void IncrementX1(int8_t dx) { x1_ = std::clamp<int8_t>(x1_ + dx, 0, x2_); }
    inline void IncrementY1(int8_t dy) { y1_ = std::clamp<int8_t>(y1_ + dy, 0, y2_); }
    inline void IncrementX2(int8_t dx) { x2_ = std::clamp<int8_t>(x2_ + dx, x1_, 15); }
    inline void IncrementY2(int8_t dy) { y2_ = std::clamp<int8_t>(y2_ + dy, y1_, 15); }

    inline int8_t GetX1() { return x1_; }
    inline int8_t GetY1() { return y1_; }
    inline int8_t GetX2() { return x2_; }
    inline int8_t GetY2() { return y2_; }
    
    inline void SetWavelistOffset(int8_t offset) { wavelist_offset_ = offset; }
    inline int8_t GetWavelistOffset() { return wavelist_offset_; }

private:
    int8_t x1_;
    int8_t x2_;
    int8_t y1_;
    int8_t y2_;
    
    float morph_x_;
    float morph_y_;
    
    int8_t wavelist_offset_;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MatrixEngine);
};
