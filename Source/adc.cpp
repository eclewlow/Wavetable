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

bool Adc::handleKeyPress() {
    
    //    if(juce::KeyPress::isKeyCurrentlyDown(MORPH_POT_CW)) {
    //    if(juce::KeyPress::isKeyCurrentlyDown(MORPH_POT_CCW)) {
    //    if(juce::KeyPress::isKeyCurrentlyDown(FX_POT_CW)) {
    //    if(juce::KeyPress::isKeyCurrentlyDown(FX_POT_CCW)) {
    //    if(juce::KeyPress::isKeyCurrentlyDown(FX_AMOUNT_POT_CW)) {
    //    if(juce::KeyPress::isKeyCurrentlyDown(FX_AMOUNT_POT_CCW)) {
    //    if(juce::KeyPress::isKeyCurrentlyDown(PITCH_POT_CW)) {
    //    if(juce::KeyPress::isKeyCurrentlyDown(PITCH_POT_CCW)) {
    //
    
    int delta = 4;
    
    if(juce::KeyPress::isKeyCurrentlyDown(PITCH_POT_CCW)) {
        values_[0]-=delta;
        values_[0] = clamp(values_[0], 0, 4095);
    }
    if(juce::KeyPress::isKeyCurrentlyDown(PITCH_POT_CW)) {
        values_[0]+=delta;
        values_[0] = clamp(values_[0], 0, 4095);
    }
    
    if(juce::KeyPress::isKeyCurrentlyDown(FX_AMOUNT_POT_CCW)) {
        values_[1]-=delta;
        values_[1] = clamp(values_[1], 0, 4095);
    }
    if(juce::KeyPress::isKeyCurrentlyDown(FX_AMOUNT_POT_CW)) {
        values_[1]+=delta;
        values_[1] = clamp(values_[1], 0, 4095);
    }
    
    if(juce::KeyPress::isKeyCurrentlyDown(FX_POT_CCW)) {
        values_[2]-=delta;
        values_[2] = clamp(values_[2], 0, 4095);
    }
    if(juce::KeyPress::isKeyCurrentlyDown(FX_POT_CW)) {
        values_[2]+=delta;
        values_[2] = clamp(values_[2], 0, 4095);
    }
    
    
    if(juce::KeyPress::isKeyCurrentlyDown(MORPH_POT_CCW)) {
        values_[3]-=delta;
        values_[3] = clamp(values_[3], 0, 4095);
    }
    if(juce::KeyPress::isKeyCurrentlyDown(MORPH_POT_CW)) {
        values_[3]+=delta;
        values_[3] = clamp(values_[3], 0, 4095);
    }
    //    printf("%f", targetX);
    return true;
}

