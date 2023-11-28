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
    enum FxMenuLeftState {
        FX_MENU_LEFT_FX,
        FX_MENU_LEFT_DEPTH,
    };
    enum FxMenuRightState {
        FX_MENU_RIGHT_MOD,
        FX_MENU_RIGHT_RATIO,
        FX_MENU_RIGHT_FREQUENCY,
        FX_MENU_RIGHT_SYNC,
        FX_MENU_RIGHT_WAVE,
        FX_MENU_RIGHT_SCALE,
        FX_MENU_RIGHT_RANGE,
    };
    FxMenu();
    ~FxMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    void triggerUpdate(bool back_pressed) {};
    inline void setLeftState(FxMenuLeftState left_state) { left_state_ = left_state; }
    inline void setRightState(FxMenuRightState right_state) { right_state_ = right_state; }

private:
    FxMenuLeftState left_state_;
    FxMenuRightState right_state_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FxMenu);
};
