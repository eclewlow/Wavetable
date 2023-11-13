/*
  ==============================================================================

    adc.cpp
    Created: 12 Nov 2023 5:24:14pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include <JuceHeader.h>
#include "adc.h"
#include "Globals.h"

Adc::Adc() {
    memset(values_, 0, 8*2);
    values_[0] = 2354;
}

bool Adc::handleKeyPress(const juce::KeyPress &key) {
//    uint16_t fxKnob;
//    uint16_t fxAmountKnob;
//    uint16_t morphKnob;
//    uint16_t tuneKnob;
//86, 66 v, b
    //88, 67  x, c
    if(key.getKeyCode() == 81) {
        values_[0]-=4;
        values_[0] = clamp(values_[0], 0, 4095);
        return true;
    }
    if(key.getKeyCode() == 87) {
        values_[0]+=4;
        values_[0] = clamp(values_[0], 0, 4095);
        return true;
    }

    if(key.getKeyCode() == 88) {
        values_[1]-=4;
        values_[1] = clamp(values_[1], 0, 4095);
        return true;
    }
    if(key.getKeyCode() == 67) {
        values_[1]+=4;
        values_[1] = clamp(values_[1], 0, 4095);
        return true;
    }

    if(key.getKeyCode() == 86) {
        values_[2]-=4;
        values_[2] = clamp(values_[2], 0, 4095);
        return true;
    }
    if(key.getKeyCode() == 66) {
        values_[2]+=4;
        values_[2] = clamp(values_[2], 0, 4095);
        return true;
    }


    if(key.getKeyCode() == 78) {
        values_[3]-=4;
        values_[3] = clamp(values_[3], 0, 4095);
        return true;
    }
    if(key.getKeyCode() == 77) {
        values_[3]+=4;
        values_[3] = clamp(values_[3], 0, 4095);
        return true;
    }
//    printf("%f", targetX);
    return false;
}

