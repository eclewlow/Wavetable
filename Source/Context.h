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
    
    inline void setState(State* state, bool back_pressed = false) { if(_state == state) return; _state = state; _state->triggerUpdate(back_pressed); }
    inline State* getState() { return _state; }
    
    inline void setEngine(Engine* engine) { if(engine_ == engine) return; last_engine_ = engine_; engine_ = engine; engine_->triggerUpdate(); }
    inline Engine* getEngine() { return engine_; }
    inline Engine* getLastEngine() { return last_engine_; }
    inline void setLastEngine(Engine* engine) { last_engine_ = engine; }

    bool handleKeyPress(int key);
    bool handleKeyLongPress(int key);
    bool handleKeyRelease(int key);
    void paint(juce::Graphics& g);

private:
    State* _state;
    Engine* engine_;
    Engine* last_engine_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Context);
};
