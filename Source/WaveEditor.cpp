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
    selection_x1_ = 10;
    selection_x2_ = 30;
    right_state_ = WAVE_EDITOR_RIGHT_ENCODER_DRAW;
    shape_ = WAVE_EDITOR_SHAPE_SINE;
    state_ = WAVE_EDITOR_STATE_EDITOR;
    menu_offset_y_ = -30;
    menu_target_offset_y_ = -30;
}

WaveEditor::~WaveEditor() {
    
}
//AB_NONE,
//AB_LOAD_HOVER,
//AB_EDIT_HOVER,
//AB_SELECT_WAVETABLE,
//AB_SELECT_FRAME,

bool WaveEditor::handleKeyPress(const juce::KeyPress &key) {
    if(state_ == WAVE_EDITOR_STATE_EDITOR) {
        if(key.getKeyCode() == LEFT_ENCODER_CCW) {
            selection_x1_ = std::clamp(--selection_x1_, 0, 127);
            selection_x2_ = std::clamp(--selection_x2_, 0, 127);
            
        }
        if(key.getKeyCode() == LEFT_ENCODER_CW) {
            selection_x1_ = std::clamp(++selection_x1_, 0, 127);
            selection_x2_ = std::clamp(++selection_x2_, 0, 127);
        }
        if(key.getKeyCode() == RIGHT_ENCODER_CCW) {
            if(right_state_ == WAVE_EDITOR_RIGHT_ENCODER_EXPAND) {
                if(selection_x2_ - selection_x1_ > 2) {
                    selection_x1_++;
                    selection_x2_--;
                    selection_x1_ = std::clamp(selection_x1_, 0, selection_x2_ - 2);
                    selection_x2_ = std::clamp(selection_x2_, selection_x1_ + 2, 127);
                }
            } else {
                int c = 0.0f;
                int width = (selection_x2_ - selection_x1_) * 16;
                // draw wave
                for (int i = selection_x1_; i < selection_x2_; i++) {
                    int integral = i * 16; // 16 = 2048 / 128
                    for(int j = integral; j < integral + 16; j++) {
                        switch(shape_) {
                            case WAVE_EDITOR_SHAPE_SINE: {
                                float sample = sin(M_PI * c / width);
                                c += 1.0f;
                                wavedata_[j] = std::clamp<int32_t>(wavedata_[j]-512*4*sample, -32768, 32767);
                                break;
                            }
                            default:
                                wavedata_[j] = std::clamp<int32_t>(wavedata_[j]-512*2, -32768, 32767);
                                break;
                        }
                    }
                }
                
            }
            
        }
        if(key.getKeyCode() == RIGHT_ENCODER_CW) {
            if(right_state_ == WAVE_EDITOR_RIGHT_ENCODER_EXPAND) {
                selection_x1_--;
                selection_x2_++;
                selection_x1_ = std::clamp(selection_x1_, 0, selection_x2_ - 2);
                selection_x2_ = std::clamp(selection_x2_, selection_x1_ + 2, 127);
            } else {
                // draw wave
                int c = 0.0f;
                int width = (selection_x2_ - selection_x1_) * 16;
                
                for (int i = selection_x1_; i < selection_x2_; i++) {
                    int integral = i * 16; // 16 = 2048 / 128
                    // add sine based on phase = PI / (x2 - x1) width
                    for(int j = integral; j < integral + 16; j++) {
                        switch(shape_) {
                            case WAVE_EDITOR_SHAPE_SINE: {
                                float sample = sin(M_PI * c / width);
                                c += 1.0f;
                                wavedata_[j] = std::clamp<int32_t>(wavedata_[j]+512*4*sample, -32768, 32767);
                                break;
                            }
                            default:
                                wavedata_[j] = std::clamp<int32_t>(wavedata_[j]+512*2, -32768, 32767);
                                break;
                        }
                    }
                }
                
            }
        }
        if(key.getKeyCode() == RIGHT_ENCODER_CLICK) {
            right_state_ = right_state_ == WAVE_EDITOR_RIGHT_ENCODER_DRAW ? WAVE_EDITOR_RIGHT_ENCODER_EXPAND : WAVE_EDITOR_RIGHT_ENCODER_DRAW;
        }
        if(key.getKeyCode() == LEFT_ENCODER_CLICK) {
            state_ = WAVE_EDITOR_STATE_MENU;
            menu_offset_y_ = -30;
            menu_target_offset_y_ = 0;
            timer_ = juce::Time::currentTimeMillis();
        }
        if(key.getKeyCode() == BACK_BUTTON) {
            if(back_menu_)
                context.setState(back_menu_);
            else
                context.setState(&abModeMenu);
        }
    }
    else if(state_ == WAVE_EDITOR_STATE_MENU) {
        if(key.getKeyCode() == LEFT_ENCODER_CCW) {
        }
        if(key.getKeyCode() == LEFT_ENCODER_CW) {
        }
        if(key.getKeyCode() == RIGHT_ENCODER_CCW) {
        }
        if(key.getKeyCode() == RIGHT_ENCODER_CW) {
        }
        if(key.getKeyCode() == RIGHT_ENCODER_CLICK) {
        }
        if(key.getKeyCode() == LEFT_ENCODER_CLICK) {
        }
        if(key.getKeyCode() == BACK_BUTTON) {
            state_ = WAVE_EDITOR_STATE_EDITOR;
//            menu_offset_y_ = -32;
            menu_target_offset_y_ = -30;
            timer_ = juce::Time::currentTimeMillis();
//            if(back_menu_)
//                context.setState(back_menu_);
//            else
//                context.setState(&abModeMenu);
        }
    }
    return true;
}

void WaveEditor::DrawTriangle(int x, int y, bool reversed) {
    if(reversed) {
        Display::Put_Pixel(x, y + 2, true);
        Display::Put_Pixel(x + 1, y+1, true);
        Display::Put_Pixel(x + 1, y+2, true);
        Display::Put_Pixel(x + 1, y+3, true);
        Display::Put_Pixel(x + 2, y, true);
        Display::Put_Pixel(x + 2, y+1, true);
        Display::Put_Pixel(x + 2, y+2, true);
        Display::Put_Pixel(x + 2, y+3, true);
        Display::Put_Pixel(x + 2, y+4, true);
    } else {
        Display::Put_Pixel(x + 2, y + 2, true);
        Display::Put_Pixel(x + 1, y+1, true);
        Display::Put_Pixel(x + 1, y+2, true);
        Display::Put_Pixel(x + 1, y+3, true);
        Display::Put_Pixel(x, y, true);
        Display::Put_Pixel(x, y+1, true);
        Display::Put_Pixel(x, y+2, true);
        Display::Put_Pixel(x, y+3, true);
        Display::Put_Pixel(x, y+4, true);
    }
}

void WaveEditor::DrawMenu() {
    if(menu_target_offset_y_ != menu_offset_y_ && juce::Time::currentTimeMillis() - timer_ > 1000) {
        timer_ = juce::Time::currentTimeMillis();
        if(menu_target_offset_y_ > menu_offset_y_)
            menu_offset_y_++;
        else if(menu_target_offset_y_ < menu_offset_y_)
            menu_offset_y_--;
    }
    Display::clear_rectangle_simple(0, menu_offset_y_, 128, 26);
    Display::LCD_Line(0, menu_offset_y_+26, 127, menu_offset_y_+26, true);
    Display::put_image_16bit(5, menu_offset_y_ + 5, Graphic_icon_wave_ramp, 15);
    Display::put_string_5x5(5, menu_offset_y_ + 21, strlen("SQUARE"), "SQUARE");
}

void WaveEditor::paint(juce::Graphics& g) {
    uint16_t morph = adc.getChannel(3);

    Display::clear_screen();

//    abEngine.FillWaveform(BUF1, left_wavetable_, left_frame_);
    Display::LCD_DottedLine(0, 32, 127, 32, 4, 2, true);
    Display::LCD_DottedLine(selection_x1_, 0, selection_x1_, 63, 1, 1, true);
    Display::LCD_DottedLine(selection_x2_, 0, selection_x2_, 63, 1, 1, true);
    if(right_state_ == WAVE_EDITOR_RIGHT_ENCODER_EXPAND) {
        // draw triangles
        DrawTriangle(selection_x1_ - 3, 64 - 5, false);
        DrawTriangle(selection_x2_+1, 64 - 5, true);
        DrawTriangle(selection_x1_ - 3, 0, false);
        DrawTriangle(selection_x2_+1, 0, true);
    }
    if(wavedata_)
        Display::Draw_Wave(0, 0, 128, 64, wavedata_);

    DrawMenu();
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
