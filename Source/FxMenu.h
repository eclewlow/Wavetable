/*
  ==============================================================================

    FxMenu.h
    Created: 12 Nov 2023 9:46:54pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class FxMenu: public State
{
public:
    enum FxMenuState {
        FX_MENU_EDIT_NONE,
        FX_MENU_EDIT_DEPTH,
        FX_MENU_EDIT_RATIO,
        FX_MENU_EDIT_SYNC,
        FX_MENU_EDIT_WAVE,
    };
    FxMenu();
    ~FxMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    inline void setState(FxMenuState newState) { currentState = newState; }

private:
    FxMenuState currentState;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FxMenu);
};
