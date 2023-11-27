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
//        FX_MENU_LEFT_DEPTH,
    };
    LoadWaveMenu();
    ~LoadWaveMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    void triggerUpdate() {};
    inline void setState(LoadWaveMenuState state) { state_ = state; }

private:
    LoadWaveMenuState state_;
    int16_t wavetable_offset_;
    int16_t frame_offset_;
//    int16_t right_wavetable_offset_;
//    int16_t right_frame_offset_;
//    ABActiveMenuSide active_menu_;
//    ABMenuState left_state_;
//    ABMenuState right_state_;
    int wavetable_;
    int frame_;
//    int right_wavetable_;
//    int right_frame_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoadWaveMenu);
};
