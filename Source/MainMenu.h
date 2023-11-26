/*
  ==============================================================================

    MainMenu.h
    Created: 7 Nov 2023 1:30:39pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class MainMenu: public State
{
public:
    enum MainMenuState {
        MAIN_WAVE_DESIGN,
        MODE_SELECT,
        FX_MANAGEMENT,
        SUBOSCILLATOR_CONFIG,
        PLAYBACK_MONITORING,
        SNAPSHOTS_LIST,
        WAVETABLE_MANAGEMENT,
        MODULE_SETUP_CONFIG
    };
    MainMenu();
    ~MainMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    void triggerUpdate() {};
    inline void setState(MainMenuState newState) { currentState = newState; }

private:
    
    MainMenuState currentState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainMenu);
};
