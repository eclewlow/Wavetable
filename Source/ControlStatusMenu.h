/*
  ==============================================================================

    ControlStatusMenu.h
    Created: 14 Nov 2023 4:39:09pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class ControlStatusMenu: public State
{
public:
    enum ControlStatusMenuState {
        CONTROL_STATUS_STATE_NONE,
    };
    ControlStatusMenu();
    ~ControlStatusMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    inline void setState(ControlStatusMenuState newState) { currentState = newState; }

private:
    ControlStatusMenuState currentState;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlStatusMenu);
};
