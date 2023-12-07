/*
  ==============================================================================

    effect_manager.h
    Created: 13 Nov 2023 6:40:12pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "effect.h"

class EffectManager {
public:
    enum OscillatorShape {
        SINE_SHAPE              = 0,
        TRIANGLE_SHAPE          = 1,
        SAWTOOTH_SHAPE          = 2,
        RAMP_SHAPE              = 3,
        SQUARE_SHAPE            = 4,
        SNH_SHAPE               = 5,
        OSCILLATOR_SHAPE_LAST   = 6,
    };

    enum ControlType {
        MANUAL_CONTROL      = 0,
        EXTERNAL_MODULATOR  = 1,
        INTERNAL_MODULATOR  = 2,
        CONTROL_TYPE_LAST   = 3,
    };
    
    enum EffectType {
        EFFECT_TYPE_BYPASS              = 0,
        EFFECT_TYPE_FM                  = 1,
        EFFECT_TYPE_RING_MODULATOR      = 2,
        EFFECT_TYPE_PHASE_DISTORTION    = 3,
        EFFECT_TYPE_WAVEFOLDER          = 4,
        EFFECT_TYPE_WAVEFOLDER          = 5,
        EFFECT_TYPE_WAVEWRAPPER         = 6,
        EFFECT_TYPE_BITCRUSH            = 7,
        EFFECT_TYPE_DRIVE               = 8,
    };

    
    EffectManager() {
        depth_ = 1.0f;
        sync_ = false;
        oscillator_shape_ = SINE_SHAPE;
        control_type_ = INTERNAL_MODULATOR;
    }
    ~EffectManager() {}
    void Init();
    void Reset();
    inline void setEffect(Effect* newEffect) { effect_ = newEffect; effect_->triggerUpdate(); }
    inline Effect* getEffect() { return effect_; }

    float RenderSampleEffect(float sample, float phase, float frequency, uint16_t fx_amount, uint16_t fx, bool isOscillcope=false, bool downsampling=false);
    float RenderPhaseEffect(float phase, float frequency, uint16_t fx_amount, uint16_t fx, bool isOscillcope=false, bool downsampling=false);
    float GetSample(float phase);
    
    inline int8_t getControlType() { return control_type_; }
    inline void setControlType(int8_t control_type) { control_type_ = control_type; }
    
    inline int8_t getOscillatorShape() { return oscillator_shape_; }
    inline void setOscillatorShape(int8_t oscillator_shape) { oscillator_shape_ = oscillator_shape; }

    inline bool getSync() { return sync_; }
    inline void setSync(bool sync) { sync_ = sync; }

    inline float getDepth() { return depth_; }
    inline void setDepth(float depth) { depth_ = std::clamp(depth, 0.0f, 1.0f); }

    inline int getScale() { return scale_; }
    inline void setScale(int scale) { scale_ = std::clamp<int>(scale, 0, 100); }

    inline int getRange() { return range_; }
    inline void setRange(int range) { range_ = std::clamp<int>(range, 1, 10); }

protected:
    float depth_;
    bool sync_;
    int scale_;
    int range_;
    int8_t oscillator_shape_;
    int8_t control_type_;
    Effect* effect_;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectManager);
};
