/*
  ==============================================================================

    drum_engine.h
    Created: 30 Nov 2023 5:44:42pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "effect.h"
#include "Engine.h"

class Engine;

class DrumEngine: public Engine
{
public:
    DrumEngine();
    ~DrumEngine();
    virtual void Render(float* out, float* aux, uint32_t size, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph);
    float Render();
    void Init();
    float GetSample(int16_t wavetable, int16_t frame, float phase);
    float GetSampleBetweenFrames(float phase, float thisX);
    bool handleKeyPress(const juce::KeyPress &key);
    void FillWaveform(int16_t * waveform, uint16_t tune, uint16_t fx_amount, uint16_t fx, uint16_t morph, bool withFx);
    float GetSample(float phase);
    float GetSampleNoFX(float phase, float fx, float morph);
    void triggerUpdate();
    
    inline void SetWavetable(int wavetable) { wavetable_ = std::clamp(wavetable, 0, USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 1); }
    inline int GetWavetable() { return wavetable_; }
    
    inline void SetAmpDecay(float value) { amp_decay_ = std::clamp(value, 0.0f, 1.0f); }
    inline float GetAmpDecay() { return amp_decay_; }
    
    inline void SetFMDecay(float value) { fm_decay_ = std::clamp(value, 0.0f, 1.0f); }
    inline float GetFMDecay() { return fm_decay_; }

    inline void SetFMShape(float value) { fm_shape_ = std::clamp(value, 0.0f, 1.0f); }
    inline float GetFMShape() { return fm_shape_; }

    inline void SetFMDepth(float value) { fm_depth_ = std::clamp(value, 0.0f, 1.0f); }
    inline float GetFMDepth() { return fm_depth_; }

private:
    // depth -50 to 50
    // decays 0 to 100
    // shape -50 to 50
    float amp_decay_trigger_;
    float fm_decay_trigger_;
    float amp_decay_;
    float fm_decay_;
    float fm_shape_;
    float fm_depth_;

    int wavetable_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrumEngine);
};
