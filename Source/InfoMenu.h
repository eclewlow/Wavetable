/*
  ==============================================================================

    InfoMenu.h
    Created: 14 Nov 2023 4:39:44pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class InfoMenu: public State
{
public:
    enum InfoMenuState {
        INFO_MENU_NONE,
//        FX_MENU_LEFT_DEPTH,
    };
    InfoMenu();
    ~InfoMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    inline void setState(InfoMenuState state) { state_ = state; }

private:
    InfoMenuState state_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InfoMenu);
};