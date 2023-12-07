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
        MANAGE_MENU_CONFIRM_DELETE      = 4,
        MANAGE_MENU_MOVE_WAVETABLE      = 5,
    };
    enum ManageMenuOptions {
        MANAGE_MENU_EDIT                = 0,
        MANAGE_MENU_RENAME              = 1,
        MANAGE_MENU_DELETE              = 2,
        MANAGE_MENU_NO                  = 3,
        MANAGE_MENU_YES                 = 4,
    };

    ManageMenu();
    ~ManageMenu();
    virtual bool handleKeyPress(int key);
    virtual bool handleKeyRelease(int key);
    virtual bool handleKeyLongPress(int key);
    virtual void paint(juce::Graphics& g);
    void triggerUpdate(bool back_pressed);
    inline void setState(int8_t state) { state_ = state; }
    inline void setTarget(int8_t target) { target_ = target; }
    inline void setOptionSelected(int8_t option_selected) { option_selected_ = option_selected; }
    static void SaveWavetable(char* param);

private:
    int8_t state_;
    int8_t option_selected_;
    int16_t wavetable_offset_;
    int16_t frame_offset_;
    int16_t wavetable_;
    int16_t frame_;
    float morph_;
    int8_t target_;
    uint32_t ticker_timer_;
    uint32_t press_timer_;
    bool absorb_keypress_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ManageMenu);
};
