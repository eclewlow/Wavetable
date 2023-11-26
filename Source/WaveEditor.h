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
#include "fft.h"

class State;

class WaveEditor: public State
{
public:
    enum WaveEditorState {
        WAVE_EDITOR_STATE_MENU = 0,
        WAVE_EDITOR_STATE_EDITOR = 1,
        WAVE_EDITOR_STATE_PEN = 2,
        WAVE_EDITOR_STATE_LINE = 3,
        WAVE_EDITOR_STATE_SPECTRAL = 4,
    };

    enum WaveEditorSelection {
        WAVE_EDITOR_SELECTION_SQUARE    = 0,
        WAVE_EDITOR_SELECTION_TRIANGLE  = 1,
        WAVE_EDITOR_SELECTION_SINE      = 2,
        WAVE_EDITOR_SELECTION_RAMP      = 3,
        WAVE_EDITOR_SELECTION_SAW       = 4,
        WAVE_EDITOR_SELECTION_PEAK      = 5,
        WAVE_EDITOR_SELECTION_PEN       = 6,
        WAVE_EDITOR_SELECTION_LINE      = 7,
        WAVE_EDITOR_SELECTION_SPECTRAL  = 8,
        WAVE_EDITOR_SELECTION_CLEAR     = 9,
        WAVE_EDITOR_SELECTION_LOAD      = 10,
        WAVE_EDITOR_SELECTION_SAVE      = 11,
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
    virtual void triggerUpdate();
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
    void CalculateFFT();
    void CalculateIFFT();
    void DrawMenu();
    void DrawTriangle(int x, int y, bool reversed);
    inline void setWavedata(int16_t * data) { wavedata_ = data; }
private:
    int16_t * wavedata_;
    WaveEditorRightEncoderState right_state_;
    int8_t selection_;
    int8_t mode_;
    WaveEditorState state_;
    int16_t menu_selection_offset_;
    int16_t timer_;
    int menu_target_offset_y_;
    int menu_offset_y_;
    int selection_x1_;
    int selection_x2_;
    int spectral_cursor_;
    float spectral_gain_[32];
    FFT::COMPLEX_NUMBER spectral_phasors_[2048];
    float spectral_angles_[32];
    uint16_t pen_x_;
    uint16_t pen_y_;
    uint16_t line_x_;
    uint16_t line_y_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveEditor);
};
