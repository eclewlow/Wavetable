/*
  ==============================================================================

    Context.cpp
    Created: 7 Nov 2023 1:06:53pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Context.h"

Context::Context() {_state = NULL;}
Context::~Context() {}

bool Context::handleKeyPress(int key) {
    if(_state)
        return _state->handleKeyPress(key);
    else
        return false;
}

bool Context::handleKeyLongPress(int key) {
    if(_state)
        return _state->handleKeyLongPress(key);
    else
        return false;
}

bool Context::handleKeyRelease(int key) {
    if(_state)
        return _state->handleKeyRelease(key);
    else
        return false;
}


void Context::paint(juce::Graphics& g) {
    if(_state)
        _state->paint(g);
}
