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
        MAIN_WAVE_DESIGN,
        MODE_SELECT,
        FX_MANAGEMENT,
        SUBOSCILLATOR_CONFIG,
        PLAYBACK_MONITORING,
        SNAPSHOTS_LIST,
        WAVETABLE_MANAGEMENT,
        MODULE_SETUP_CONFIG
    };
    ModeMenu();
    ~ModeMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    inline void setState(ModeMenuState newState) { currentState = newState; lastState = newState; }
    
    static ModeMenuState lastState;
private:
    
    ModeMenuState currentState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModeMenu);
};
