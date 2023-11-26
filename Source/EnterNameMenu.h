/*
  ==============================================================================

    EnterNameMenu.h
    Created: 14 Nov 2023 4:45:29pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class EnterNameMenu: public State
{
public:
    enum EnterNameMenuState {
        CONTROL_STATUS_STATE_NONE,
    };
    EnterNameMenu();
    ~EnterNameMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    void triggerUpdate() {};
    inline void setState(EnterNameMenuState newState) { currentState = newState; }
    inline void setExecFunc(void (* func)(char* param)) { exec_func = func; }
    inline void setBackState(State* state) { back_state = state; }
    static void test(char* param);

private:
    int num_of_chars = 41;
    int num_of_name_chars = 8;
    char * char_list = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_- //";
    int char_index;
    int name_index;
    char name_chars[8];
    bool clear_selected = false;
    bool ok_selected = false;
    void (*exec_func)(char* param);
    State* back_state;
    EnterNameMenuState currentState;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnterNameMenu);
};
