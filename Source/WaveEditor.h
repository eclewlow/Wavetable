/*
  ==============================================================================

    WaveEditor.h
    Created: 14 Nov 2023 4:45:52pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class WaveEditor: public State
{
public:
    enum WaveEditorState {
        WAVE_EDITOR_STATE_MENU,
        WAVE_EDITOR_STATE_EDITOR,
    };
    enum WaveEditorShape {
        WAVE_EDITOR_SHAPE_SQUARE,
        WAVE_EDITOR_SHAPE_TRIANGLE,
        WAVE_EDITOR_SHAPE_SINE,
        WAVE_EDITOR_SHAPE_RAMP,
        WAVE_EDITOR_SHAPE_SAW,
        WAVE_EDITOR_SHAPE_PEAK,
    };
    enum WaveEditorRightEncoderState {
        WAVE_EDITOR_RIGHT_ENCODER_DRAW,
        WAVE_EDITOR_RIGHT_ENCODER_EXPAND
    };
//    enum ABActiveMenuSide {
//        LEFT,
//        RIGHT,
//        NONE
//    };
    WaveEditor();
    ~WaveEditor();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
//    inline void setLeftState(ABMenuState state) { left_state_ = state; }
//    inline void setRightState(ABMenuState state) { right_state_ = state; }
//
//    inline void SetLeftWavetable(int left_wavetable) { left_wavetable_ = std::clamp(left_wavetable, 0, 15); }
//    inline void SetLeftFrame(int left_frame) { left_frame_ = std::clamp(left_frame, 0, 15); }
//    inline int GetLeftWavetable() { return left_wavetable_; }
//    inline int GetLeftFrame() { return left_frame_; }
//
//    inline void SetRightWavetable(int right_wavetable) { right_wavetable_ = std::clamp(right_wavetable, 0, 15); }
//    inline void SetRightFrame(int right_frame) { right_frame_ = std::clamp(right_frame, 0, 15); }
//    inline int GetRightWavetable() { return right_wavetable_; }
//    inline int GetRightFrame() { return right_frame_; }
    void DrawMenu();
    void DrawTriangle(int x, int y, bool reversed);
    inline void setWavedata(int16_t * data) { wavedata_ = data; }
private:
    int16_t * wavedata_;
    WaveEditorRightEncoderState right_state_;
    WaveEditorShape shape_;
    WaveEditorState state_;
    int16_t timer_;
    int menu_target_offset_y_;
    int menu_offset_y_;
    int selection_x1_;
    int selection_x2_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveEditor);
};
