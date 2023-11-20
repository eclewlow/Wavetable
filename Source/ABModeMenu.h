/*
  ==============================================================================

    ABWaveSelectMenu.h
    Created: 18 Nov 2023 8:29:46pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class ABModeMenu: public State
{
public:
    enum ABMenuState {
        AB_NONE,
        AB_LOAD_HOVER,
        AB_EDIT_HOVER,
        AB_LOADING,
    };
    ABModeMenu();
    ~ABModeMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    inline void setLeftState(ABMenuState state) { left_state_ = state; }
    inline void setRightState(ABMenuState state) { right_state_ = state; }

private:
    ABMenuState left_state_;
    ABMenuState right_state_;
    int bank;
    int wave;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ABModeMenu);
};
