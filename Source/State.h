/*
  ==============================================================================

    State.h
    Created: 7 Nov 2023 1:06:48pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class State {
public:
    State() {}
    virtual ~State() {};

    virtual bool handleKeyPress(const juce::KeyPress &key) = 0;
    virtual void paint(juce::Graphics& g) = 0;
    virtual void triggerUpdate() = 0;
    inline void setBackMenu(State* back_menu) {back_menu_ = back_menu;}

protected:
    State* back_menu_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (State);
};
