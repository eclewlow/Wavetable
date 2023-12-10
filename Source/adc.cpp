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
        values_[ADC_CHANNEL_FX_AMOUNT_CV] = 2048;
    }
    return true;
}

uint16_t Adc::getChannelProcessed(int channel) {
    uint16_t unprocessed = getChannel(channel);
    if(channel > 3) {
        float normalized = (unprocessed / 2048.0f - 1.0f);   // -1.0 to 1.0
        normalized = normalized * user_settings.getIOGain(channel - 4) + user_settings.getIOBias(channel - 4);  // -x.0 to x.0 + bias
        normalized = (normalized + 1.0f) * 2048.0f;
        normalized = std::clamp(normalized, 0.0f, 4095.0f);
        return (uint16_t)(normalized);
    } else {
        return std::clamp(unprocessed + (int16_t)(((getChannelProcessed(channel + 4) / 2048.0f) - 1.0f) * 4095.0f), 0, 4095);
    }
}

uint16_t Adc::getChannel(int channel) {
    return values_[channel];
}

void Adc::setChannel(int channel, uint16_t value) {
    int16_t threshold = 100;
    if(channel < 4 && freeze_[channel]) {
        if(abs(static_cast<int16_t>(value) - static_cast<int16_t>(values_[channel])) > threshold) {
            freeze_[channel] = false;
            values_[channel] = value;
        }
    } else {
        values_[channel] = value;
    }
}
