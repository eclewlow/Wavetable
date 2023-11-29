/*
  ==============================================================================

    LoadWaveMenu.h
    Created: 26 Nov 2023 5:50:03pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class LoadWaveMenu: public State
{
public:
    enum LoadWaveMenuState {
        LOAD_WAVE_MENU_NONE,
        LOAD_WAVE_MENU_SELECT_WAVETABLE,
        LOAD_WAVE_MENU_SELECT_FRAME,
    };
    enum LoadWaveMenuTarget {
        AB_ENGINE_A,
        AB_ENGINE_B,
    };
    LoadWaveMenu();
    ~LoadWaveMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    void triggerUpdate(bool back_pressed);
    inline void setState(LoadWaveMenuState state) { state_ = state; }
    inline void setTarget(LoadWaveMenuTarget target) { target_ = target; }

private:
    LoadWaveMenuState state_;
    int16_t wavetable_offset_;
    int16_t frame_offset_;
    int16_t wavetable_;
    int16_t frame_;
    float morph_;
    LoadWaveMenuTarget target_;
    int32_t ticker_timer_ = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoadWaveMenu);
};
