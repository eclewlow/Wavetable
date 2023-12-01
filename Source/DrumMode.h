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
        DRUM_MODE_EDIT_WAVETABLE = 0,
        DRUM_MODE_EDIT_AMP_DECAY = 1,
        DRUM_MODE_EDIT_FM_DECAY = 2,
        DRUM_MODE_EDIT_FM_SHAPE = 3,
        DRUM_MODE_EDIT_FM_DEPTH = 4,
        DRUM_MODE_EDIT_LAST = 5,
    };
    DrumMode();
    ~DrumMode();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    void triggerUpdate(bool back_pressed);
    inline void setEditing(bool editing) { is_editing_ = editing; timer_ = juce::Time::currentTimeMillis(); }

private:
    // depth -50 to 50
    // decays 0 to 100
    // shape -50 to 50
    int32_t timer_;
    bool is_editing_;
    int8_t edit_state_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrumMode);
};
