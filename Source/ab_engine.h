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
    float GetSample(int16_t wavetable, int16_t frame, float phase);
    float GetSample(int16_t wavetable, int16_t frame, float phase, bool isLeft);
    float GetSampleBetweenFrames(float phase, float morph);
//    void SetX(float newX);
    bool handleKeyPress(const juce::KeyPress &key);
    void FillWaveform(int16_t * waveform, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph, bool withFx);
    void FillWaveform(int16_t * waveform, int16_t wavetable, int16_t frame);
    float GetSample(float phase);
    float GetSampleNoFX(float phase, float morph);
    
    inline void SetLeftWavetable(int left_wavetable) { left_wavetable_ = std::clamp(left_wavetable, 0, 15); }
    inline void SetLeftFrame(int left_frame) { left_frame_ = std::clamp(left_frame, 0, 15); }
    inline int GetLeftWavetable() { return left_wavetable_; }
    inline int GetLeftFrame() { return left_frame_; }

    inline void SetRightWavetable(int right_wavetable) { right_wavetable_ = std::clamp(right_wavetable, 0, 15); }
    inline void SetRightFrame(int right_frame) { right_frame_ = std::clamp(right_frame, 0, 15); }
    inline int GetRightWavetable() { return right_wavetable_; }
    inline int GetRightFrame() { return right_frame_; }

    inline bool IsEditingLeft() { return is_editing_left_; }
    inline bool IsEditingRight() { return is_editing_right_; }
    inline void SetIsEditingLeft(bool is_editing_left) { is_editing_left_ = is_editing_left; }
    inline void SetIsEditingRight(bool is_editing_right) { is_editing_right_ = is_editing_right; }

private:
    int left_wavetable_;
    int left_frame_;
    
    int right_wavetable_;
    int right_frame_;
    
    bool is_editing_left_;
    bool is_editing_right_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ABEngine);
};
