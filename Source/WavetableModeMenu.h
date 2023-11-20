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
    enum WavetableModeMenuState {
        CONTROL_STATUS_STATE_NONE,
    };
    WavetableModeMenu();
    ~WavetableModeMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    inline void setState(WavetableModeMenuState newState) { currentState = newState; }

private:
    WavetableModeMenuState currentState;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WavetableModeMenu);
};
