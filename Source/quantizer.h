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
    
    int8_t scale_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Quantizer);
};
