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
    bool handleKeyPress(const juce::KeyPress &key);
    inline uint16_t getChannel(int channel) { return values_[channel]; }
private:
    int16_t values_[8];
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Adc);
};
