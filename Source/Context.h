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
#include "Engine.h"

class Context {
public:
    Context();
    ~Context();
    
    inline void setState(State* state) { if(_state == state) return; _state = state; _state->triggerUpdate(); }
    inline State* getState() { return _state; }
    
    inline void setEngine(Engine* engine) { if(engine_ == engine) return; engine_ = engine; engine_->triggerUpdate(); }
    inline Engine* getEngine() { return engine_; }

    bool handleKeyPress(const juce::KeyPress &key);
    void paint(juce::Graphics& g);

private:
    State* _state;
    Engine* engine_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Context);
};
