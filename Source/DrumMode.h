/*
  ==============================================================================

    DrumMode.h
    Created: 30 Nov 2023 5:44:53pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class DrumMode: public State
{
public:
    enum DrumModeEditState {
        MATRIX_MODE_EDIT_DEFAULT = 0,
        MATRIX_MODE_EDIT_TOPLEFT = 1,
        MATRIX_MODE_EDIT_BOTTOMRIGHT = 2,
        MATRIX_MODE_EDIT_LAST = 3,
        MATRIX_MODE_EDIT_OFFSET = 4,
    };
    DrumMode();
    ~DrumMode();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    void triggerUpdate(bool back_pressed);

private:
    uint8_t edit_state_;
    bool editing_offset_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrumMode);
};
