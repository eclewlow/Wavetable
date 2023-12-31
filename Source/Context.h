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
    
    enum EngineType {
        ENGINE_TYPE_AB          = 0,
        ENGINE_TYPE_WAVETABLE   = 1,
        ENGINE_TYPE_MATRIX      = 2,
        ENGINE_TYPE_DRUM        = 3,
    };
    
    inline void setState(State* state, bool back_pressed = false) { if(_state == state) return; _state = state; _state->triggerUpdate(back_pressed); }
    inline State* getState() { return _state; }
    
    void setEngine(int8_t engine);
    Engine* getEngine();
    Engine* getLastEngine();
    inline void setLastEngine(int8_t engine) { last_engine_ = engine; }

    bool handleKeyPress(int key);
    bool handleKeyLongPress(int key);
    bool handleKeyRelease(int key);
    void paint(juce::Graphics& g);

private:
    State* _state;
    int8_t last_engine_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Context);
};
