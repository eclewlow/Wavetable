/*
  ==============================================================================

    Oscilloscope.h
    Created: 13 Nov 2023 6:13:45pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class Oscilloscope: public State
{
public:
    enum OscilloscopeState {
        OSCILLOSCOPE_STATE_NONE,
//        FX_MENU_EDIT_NONE,
//        FX_MENU_EDIT_DEPTH,
//        FX_MENU_EDIT_RATIO,
//        FX_MENU_EDIT_SYNC,
//        FX_MENU_EDIT_WAVE,
    };
    Oscilloscope();
    ~Oscilloscope();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    inline void setState(OscilloscopeState newState) { currentState = newState; }

private:
    OscilloscopeState currentState;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscilloscope);
};
