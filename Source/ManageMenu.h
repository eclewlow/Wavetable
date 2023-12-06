/*
  ==============================================================================

    ManageMenu.h
    Created: 5 Dec 2023 2:46:59pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class ManageMenu: public State
{
public:
    enum ManageMenuState {
        MANAGE_MENU_NONE                = 0,
        MANAGE_MENU_SELECT_WAVETABLE    = 1,
        MANAGE_MENU_SELECT_FRAME        = 2,
        MANAGE_MENU_WAVETABLE_OPTIONS   = 3,
    };

    ManageMenu();
    ~ManageMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    void triggerUpdate(bool back_pressed);
    inline void setState(int8_t state) { state_ = state; }
    inline void setTarget(int8_t target) { target_ = target; }

private:
    int8_t state_;
    int16_t wavetable_offset_;
    int16_t frame_offset_;
    int16_t wavetable_;
    int16_t frame_;
    float morph_;
    int8_t target_;
    int32_t ticker_timer_ = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ManageMenu);
};
