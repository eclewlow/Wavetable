/*
  ==============================================================================

    MatrixMode.h
    Created: 29 Nov 2023 12:27:07am
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class MatrixMode: public State
{
public:
    MatrixMode();
    ~MatrixMode();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    void triggerUpdate(bool back_pressed);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MatrixMode);
};
