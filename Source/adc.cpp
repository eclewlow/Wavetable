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
    memset(values_, 0, 8 * 2);
    values_[ADC_CHANNEL_PITCH_POT] = 2354;
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
    
    int delta = 20;
    
    if(juce::KeyPress::isKeyCurrentlyDown(PITCH_POT_CCW)) {
        values_[ADC_CHANNEL_PITCH_POT]-=delta;
        values_[ADC_CHANNEL_PITCH_POT] = clamp(values_[0], 0, 4095);
    }
    if(juce::KeyPress::isKeyCurrentlyDown(PITCH_POT_CW)) {
        values_[ADC_CHANNEL_PITCH_POT]+=delta;
        values_[ADC_CHANNEL_PITCH_POT] = clamp(values_[0], 0, 4095);
    }
    
    if(juce::KeyPress::isKeyCurrentlyDown(FX_AMOUNT_POT_CCW)) {
        values_[ADC_CHANNEL_FX_AMOUNT_POT]-=delta;
        values_[ADC_CHANNEL_FX_AMOUNT_POT] = clamp(values_[1], 0, 4095);
    }
    if(juce::KeyPress::isKeyCurrentlyDown(FX_AMOUNT_POT_CW)) {
        values_[ADC_CHANNEL_FX_AMOUNT_POT]+=delta;
        values_[ADC_CHANNEL_FX_AMOUNT_POT] = clamp(values_[1], 0, 4095);
    }
    
    if(juce::KeyPress::isKeyCurrentlyDown(FX_POT_CCW)) {
        values_[ADC_CHANNEL_FX_POT]-=delta;
        values_[ADC_CHANNEL_FX_POT] = clamp(values_[2], 0, 4095);
    }
    if(juce::KeyPress::isKeyCurrentlyDown(FX_POT_CW)) {
        values_[ADC_CHANNEL_FX_POT]+=delta;
        values_[ADC_CHANNEL_FX_POT] = clamp(values_[2], 0, 4095);
    }
    
    
    if(juce::KeyPress::isKeyCurrentlyDown(MORPH_POT_CCW)) {
        values_[ADC_CHANNEL_MORPH_POT]-=delta;
        values_[ADC_CHANNEL_MORPH_POT] = clamp(values_[3], 0, 4095);
    }
    if(juce::KeyPress::isKeyCurrentlyDown(MORPH_POT_CW)) {
        values_[ADC_CHANNEL_MORPH_POT]+=delta;
        values_[ADC_CHANNEL_MORPH_POT] = clamp(values_[3], 0, 4095);
    }

    if(juce::KeyPress::isKeyCurrentlyDown(FX_AMOUNT_CV_TRIGGER)) {
        values_[ADC_CHANNEL_FX_AMOUNT_CV] = 4095;
    } else {
        values_[ADC_CHANNEL_FX_AMOUNT_CV] = 0;
    }
    return true;
}

