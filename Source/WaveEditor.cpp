/*
  ==============================================================================

    WaveEditor.cpp
    Created: 14 Nov 2023 4:45:53pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Display.h"
#include "graphics.h"
#include "Globals.h"

WaveEditor::WaveEditor() {
//    setLeftState(AB_LOAD_HOVER);
//    setRightState(AB_LOAD_HOVER);
//    left_wavetable_ = 0;
//    left_frame_ = 0;
//    right_wavetable_ = 0;
//    right_frame_ = 0;
//    left_wavetable_offset_ = 0;
//    left_frame_offset_ = 0;
//    right_wavetable_offset_ = 0;
//    right_frame_offset_ = 0;
//    active_menu_ = NONE;
}

WaveEditor::~WaveEditor() {
    
}
//AB_NONE,
//AB_LOAD_HOVER,
//AB_EDIT_HOVER,
//AB_SELECT_WAVETABLE,
//AB_SELECT_FRAME,

bool WaveEditor::handleKeyPress(const juce::KeyPress &key) {
    if(key.getKeyCode() == LEFT_ENCODER_CCW) {
    }
    if(key.getKeyCode() == LEFT_ENCODER_CW) {
    }
    if(key.getKeyCode() == LEFT_ENCODER_CLICK) {
        for(int i = 0; i < 2048; i++)
            BUF3[i] = 2048;
    }
    if(key.getKeyCode() == BACK_BUTTON) {
        if(back_menu_)
            context.setState(back_menu_);
        else
            context.setState(&abModeMenu);
    }

    return true;
}

void WaveEditor::paint(juce::Graphics& g) {
    uint16_t morph = adc.getChannel(3);

    Display::clear_screen();
//
//    int graph_y_offset = 3;
//    int graph_height = 32 - graph_y_offset;
//    int gap = 1;
//    int graph_width = 128 / 2 - gap;
//    
//    Display::outline_rectangle(0, graph_y_offset, graph_width, graph_height);
//    Display::outline_rectangle(graph_width + gap * 2, graph_y_offset, graph_width, graph_height);
//    
//    abEngine.FillWaveform(BUF1, left_wavetable_, left_frame_);
//
//    Display::Draw_Wave(1, graph_y_offset + 1, graph_width-2, graph_height-2, BUF1);
//
//    abEngine.FillWaveform(BUF2, right_wavetable_, right_frame_);
//
//    Display::Draw_Wave(graph_width + gap * 2 + 1, graph_y_offset + 1, graph_width-2, graph_height-2, BUF2);
//
//    int y_offset = graph_y_offset + graph_height + 5;
//    int x_offset = 64 - 5;
//    if(left_state_ == AB_SELECT_WAVETABLE) {
//        for(int i = 0; i < 3; i++)
//        {
//            char line[20];
//            snprintf(line, 20, "TABLE %d", i + left_wavetable_offset_);
//            Display::put_string_5x5(5, y_offset + i * 7, strlen(line), line, i+left_wavetable_offset_ == left_wavetable_);
//
//            int y_shift = 2;
//            int bar_height = 3 * 7 + y_shift * 2;
//            int y_cursor_offset = ((bar_height-3/2) * left_wavetable_offset_) / 15;
//            Display::outline_rectangle(x_offset+1, y_offset + 1 - y_shift + y_cursor_offset, 1, 3);
//            Display::invert_rectangle(x_offset, y_offset - y_shift, 3, bar_height);
//        }
//    } else if (left_state_ == AB_SELECT_FRAME) {
//        for(int i = 0; i < 3; i++)
//        {
//            char line[20];
//            snprintf(line, 20, "FRAME %d", i + left_frame_offset_);
//            Display::put_string_5x5(5, y_offset + i * 7, strlen(line), line, i+left_frame_offset_ == left_frame_);
//
//            int y_shift = 2;
//            int bar_height = 3 * 7 + y_shift * 2;
//            int y_cursor_offset = ((bar_height-3/2) * left_frame_offset_) / 15;
//            Display::outline_rectangle(x_offset+1, y_offset + 1 - y_shift + y_cursor_offset, 1, 3);
//            Display::invert_rectangle(x_offset, y_offset - y_shift, 3, bar_height);
//        }
//    }
//    else if(left_state_ == AB_LOAD_HOVER || left_state_ == AB_EDIT_HOVER) {
//        int y_offset = graph_y_offset + graph_height + 5;
//        int x_offset = 64 / 2 - (15 + 1);
//        Display::put_image_16bit(x_offset, y_offset, Graphic_icon_load_15x15, 15);
//        Display::put_image_16bit(x_offset + 15 + 2, y_offset, Graphic_icon_edit_15x15, 15);
//        
//        if(left_state_ == AB_LOAD_HOVER) {
//            Display::invert_rectangle(x_offset+1, y_offset+1, 13, 13);
//        } else {
//            Display::invert_rectangle(x_offset+1 + 15 + 2, y_offset+1, 13, 13);
//        }
//    }
    
}
