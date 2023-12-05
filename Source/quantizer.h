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
        QUANTIZER_SCALE_OFF = 0,
        QUANTIZER_SCALE_PENTATONIC = 0, // c d e g a
        QUANTIZER_SCALE_BLUES = 1,  // c d d# e, g, a
        QUANTIZER_SCALE_DIMINISH = 1, // C , D D#
        QUANTIZER_SCALE_WHOLETONE = 1, // whole steps
        QUANTIZER_SCALE_CHROMATIC = 1, // EVERY NOTE
        QUANTIZER_SCALE_DIATONIC = 0, // MAJOR SCALE
        QUANTIZER_SCALE_ARABIAN = 0, // INFECTED MUSHROOM
        QUANTIZER_SCALE_HARMONIC_MAJOR = 0,  // major with flat 6th
        QUANTIZER_CALE_HARMONIC_MINOR = 0, // minor with major 7th
    }
    Quantizer();
    ~Quantizer();
    void Init();
    void triggerUpdate();
    float Quantize(float input_note);
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Quantizer);
};
