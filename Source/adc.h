/*
  ==============================================================================

    adc.h
    Created: 12 Nov 2023 5:24:14pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once


class Adc {
public:
    Adc();
    ~Adc() {}
    
    enum Adc_Channel {
        ADC_CHANNEL_PITCH_POT        = 0,
        ADC_CHANNEL_FX_AMOUNT_POT    = 1,
        ADC_CHANNEL_FX_POT           = 2,
        ADC_CHANNEL_MORPH_POT        = 3,
        ADC_CHANNEL_PITCH_CV         = 4,
        ADC_CHANNEL_FX_AMOUNT_CV     = 5,
        ADC_CHANNEL_FX_CV            = 6,
        ADC_CHANNEL_MORPH_CV         = 7,
    };
    
    bool handleKeyPress();
    inline uint16_t getChannel(int channel) { return values_[channel]; }
    uint16_t getChannelProcessed(int channel);
    inline void setChannel(int channel, uint16_t value) { values_[channel] = value; }
private:
    int16_t values_[8];
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Adc);
};
