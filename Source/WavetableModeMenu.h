/*
  ==============================================================================

    WavetableMenu.h
    Created: 18 Nov 2023 8:27:59pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class WavetableModeMenu: public State
{
public:
    enum WavetableModeMenuState {
        LOAD_WAVE_MENU_NONE,
        LOAD_WAVE_MENU_SELECT_WAVETABLE,
        LOAD_WAVE_MENU_SELECT_FRAME,
    };
    enum WavetableModeMenuTarget {
        AB_ENGINE_A,
        AB_ENGINE_B,
    };
    WavetableModeMenu();
    ~WavetableModeMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    void triggerUpdate(bool back_pressed);
    inline void setState(WavetableModeMenuState state) { state_ = state; }
    inline void setTarget(WavetableModeMenuTarget target) { target_ = target; }

private:
    WavetableModeMenuState state_;
    int16_t wavetable_offset_;
    int16_t frame_offset_;
    int16_t wavetable_;
    int16_t frame_;
    float morph_;
    WavetableModeMenuTarget target_;
    int32_t ticker_timer_ = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WavetableModeMenu);
};
