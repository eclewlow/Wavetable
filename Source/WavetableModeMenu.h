/*
  ==============================================================================

    WavetableMenu.h
    Created: 18 Nov 2023 8:27:59pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class WavetableModeMenu: public State
{
public:
    WavetableModeMenu();
    ~WavetableModeMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    void triggerUpdate(bool back_pressed);

private:
    int16_t wavetable_offset_;
    int16_t wavetable_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WavetableModeMenu);
};
