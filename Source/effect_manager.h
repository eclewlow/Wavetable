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
        SINE_SHAPE,
        TRIANGLE_SHAPE,
        SNH_SHAPE,
        RAMP_SHAPE,
        SAWTOOTH_SHAPE,
        SQUARE_SHAPE,
    };
    enum EffectType {
        FM,
        RING_MODULATION,
        WAVEFOLDER,
        PHASE_DISTORTION,
    };
    enum ControlType {
        MANUAL_CONTROL,
        EXTERNAL_MODULATOR,
        INTERNAL_MODULATOR,
    };

    EffectManager() {
        depth = 1.0f;
        sync = false;
        oscillatorShape = SINE_SHAPE;
        effectType = FM;
        controlType = INTERNAL_MODULATOR;
        ratio_ = 1;
    }
    ~EffectManager() {}
    void Init();
    void Reset();
    inline void setEffect(Effect* newEffect) { effect_ = newEffect; effect_->triggerUpdate(); }
    inline Effect* getEffect() { return effect_; }

    float RenderSampleEffect(float sample, float phase, float frequency, uint16_t fx_amount, uint16_t fx, bool isOscillcope=false, bool downsampling=false);
    float RenderPhaseEffect(float phase, float frequency, uint16_t fx_amount, uint16_t fx, bool isOscillcope=false, bool downsampling=false);
    float GetSample(float phase);
    
    inline ControlType getControlType() { return controlType; }
    inline void setControlType(ControlType newControlType) { controlType = newControlType; }
    
    inline OscillatorShape getOscillatorShape() { return oscillatorShape; }
    inline void setOscillatorShape(OscillatorShape newOscillatorShape) { oscillatorShape = newOscillatorShape; }

    inline EffectType getEffectType() { return effectType; }
    inline void setEffectType(EffectType newEffectType) { effectType = newEffectType; }

    inline bool getSync() { return sync; }
    inline void setSync(bool newSync) { sync = newSync; }

    inline float getDepth() { return depth; }
    inline void setDepth(float newDepth) { depth = std::clamp(newDepth, 0.0f, 1.0f); }

    inline int getScale() { return scale_; }
    inline void setScale(int scale) { scale_ = std::clamp<int>(scale, 0, 100); }

    inline int getRange() { return range_; }
    inline void setRange(int range) { range_ = std::clamp<int>(range, 1, 10); }

protected:
    float depth;
    bool sync;
    float ratio_;
    int scale_;
    int range_;
    OscillatorShape oscillatorShape;
    EffectType effectType;
    ControlType controlType;
    Effect* effect_;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectManager);
};
