/*
  ==============================================================================

    QuantizerMenu.h
    Created: 14 Nov 2023 4:43:19pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class QuantizerMenu: public State
{
public:
    QuantizerMenu();
    ~QuantizerMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    void triggerUpdate(bool back_pressed) {};
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QuantizerMenu);
};
