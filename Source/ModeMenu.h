/*
  ==============================================================================

    ModeMenu.h
    Created: 7 Nov 2023 4:54:56pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class ModeMenu: public State
{
public:
    enum ModeMenuState {
        MODE_AB,
        MODE_WAVETABLE,
        MODE_MATRIX,
        MODE_DRUM,
    };
    ModeMenu();
    ~ModeMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    inline void setState(ModeMenuState newState) { currentState = newState; }

private:
    
    ModeMenuState currentState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModeMenu);
};
