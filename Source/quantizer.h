/*
  ==============================================================================

    quantizer.h
    Created: 4 Dec 2023 4:50:49pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Globals.h"

class Quantizer {
public:
    enum QuantizerScale {
        QUANTIZER_SCALE_OFF             = 0,
        QUANTIZER_SCALE_PENTATONIC      = 1, // c d e g a
        QUANTIZER_SCALE_BLUES           = 2,  // c d d# e, g, a
        QUANTIZER_SCALE_DIMINISH        = 3, // C , D D#
        QUANTIZER_SCALE_HARMONIC_MAJOR  = 4,  // major with flat 6th
        QUANTIZER_CALE_HARMONIC_MINOR   = 5, // minor with major 7th
        QUANTIZER_SCALE_WHOLETONE       = 6, // whole steps
        QUANTIZER_SCALE_CHROMATIC       = 7, // EVERY NOTE
        QUANTIZER_SCALE_ARABIAN         = 8, // INFECTED MUSHROOM
        QUANTIZER_SCALE_DIATONIC        = 9, // MAJOR SCALE
        QUANTIZER_SCALE_LAST            = 10,
    };
    
    Quantizer();
    ~Quantizer();
    void Init();
    void triggerUpdate();
    float Quantize(float input_note);
    inline void setScale(int8_t scale) { scale_ = std::clamp<int8_t>(scale, QUANTIZER_SCALE_OFF, QUANTIZER_SCALE_LAST - 1); }
    inline int8_t getScale() { return scale_; }
    float getClosest(float, float, float);
    float findClosest(const float arr[], int n, float target);

private:
    
    const float quantizer_scale_pentatonic[11] = { -12.0,-10.0,-8.0,-5.0,-3.0,0.0,2.0,4.0,7.0,9.0,12.0 };
    const float quantizer_scale_blues[13] = { -12.0,-10.0,-9.0,-8.0,-5.0,-3.0,0.0,2.0,3.0,4.0,7.0,9.0,12.0 };
    const float quantizer_scale_diminish[17] = { -12.0,-10.0,-9.0,-7.0,-6.0,-4.0,-3.0,-1.0,0.0,2.0,3.0,5.0,6.0,8.0,9.0,11.0,12.0 };
    const float quantizer_scale_harmonic_major[15] = { -12.0,-10.0,-8.0,-7.0,-5.0,-4.0,-1.0,0.0,2.0,4.0,5.0,7.0,8.0,11.0,12.0 };
    const float quantizer_scale_harmonic_minor[15] = { -12.0,-10.0,-9.0,-7.0,-5.0,-4.0,-1.0,0.0,2.0,3.0,5.0,7.0,8.0,11.0,12.0 };
    const float quantizer_scale_wholetone[13] = { -12.0,-10.0,-8.0,-6.0,-4.0,-2.0,0.0,2.0,4.0,6.0,8.0,10.0,12.0 };
    const float quantizer_scale_chromatic[25] = { -12.0,-11.0,-10.0,-9.0,-8.0,-7.0,-6.0,-5.0,-4.0,-3.0,-2.0,-1.0,0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0 };
    const float quantizer_scale_arabian[15] = { -12.0,-11.0,-8.0,-7.0,-5.0,-4.0,-1.0,0.0,1.0,4.0,5.0,7.0,8.0,11.0,12.0 };
    const float quantizer_scale_diatonic[15] = { -12.0,-10.0,-8.0,-7.0,-5.0,-3.0,-1.0,0.0,2.0,4.0,5.0,7.0,9.0,11.0,12.0 };
    
    int8_t scale_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Quantizer);
};
