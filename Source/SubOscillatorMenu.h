/*
  ==============================================================================

    SubOscillatorMenu.h
    Created: 14 Nov 2023 4:38:34pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class SubOscillatorMenu: public State
{
public:
    enum SubOscillatorMenuState {
        SUB_OSC_MENU_OFFSET,
        SUB_OSC_MENU_DETUNE,
        SUB_OSC_MENU_MIX,
        SUB_OSC_MENU_WAVE,

    };
    SubOscillatorMenu();
    ~SubOscillatorMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    void triggerUpdate() {};
    inline void setState(SubOscillatorMenuState state) { state_ = state; }

private:
    SubOscillatorMenuState state_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SubOscillatorMenu);
};
