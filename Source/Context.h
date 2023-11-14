/*
  ==============================================================================

    Context.h
    Created: 7 Nov 2023 1:06:53pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"
#include "effect.h"

class Context {
public:
    Context();
    ~Context();
    
    inline void setState(State* newState) { _state = newState; _state->triggerUpdate(); }
    inline State* getState() { return _state; }

    inline void setEffect(Effect* newEffect) { _effect = newState; _effect->triggerUpdate(); }
    inline Effect* getEffect() { return _effect; }

    bool handleKeyPress(const juce::KeyPress &key);
    void paint(juce::Graphics& g);

private:
    State* _state;
    Effect* _effect;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Context);
};
