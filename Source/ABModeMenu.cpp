/*
  ==============================================================================

    ABWaveSelectMenu.cpp
    Created: 18 Nov 2023 8:29:46pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Display.h"
#include "graphics.h"
#include "Globals.h"

ABModeMenu::ABModeMenu() {
    setLeftState(AB_LOAD_HOVER);
    setRightState(AB_LOAD_HOVER);
    left_wavetable_ = 0;
    left_frame_ = 0;
    right_wavetable_ = 0;
    right_frame_ = 0;
    left_wavetable_offset_ = 0;
    left_frame_offset_ = 0;
    right_wavetable_offset_ = 0;
    right_frame_offset_ = 0;
    active_menu_ = NONE;
}

ABModeMenu::~ABModeMenu() {
    
}
//AB_NONE,
//AB_LOAD_HOVER,
//AB_EDIT_HOVER,
//AB_SELECT_WAVETABLE,
//AB_SELECT_FRAME,

bool ABModeMenu::handleKeyPress(const juce::KeyPress &key) {
    if(key.getKeyCode() == LEFT_ENCODER_CCW) {
        active_menu_ = LEFT;
        switch(left_state_) {
            case AB_LOAD_HOVER:
                break;
            case AB_EDIT_HOVER:
                setLeftState(AB_LOAD_HOVER);
                break;
            case AB_SELECT_WAVETABLE:
                SetLeftWavetable(GetLeftWavetable()-1);
                
                if(GetLeftWavetable() < left_wavetable_offset_) {
                    left_wavetable_offset_ = GetLeftWavetable();
                }
                
                if(abEngine.GetLeftWavetable() == GetLeftWavetable())
                    SetLeftFrame(abEngine.GetLeftFrame());
                else
                    SetLeftFrame(0);
                break;
            case AB_SELECT_FRAME:
                SetLeftFrame(GetLeftFrame()-1);

                if(GetLeftFrame() < left_frame_offset_) {
                    left_frame_offset_ = GetLeftFrame();
                }

                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == LEFT_ENCODER_CW) {
        active_menu_ = LEFT;
        switch(left_state_) {
            case AB_LOAD_HOVER:
                setLeftState(AB_EDIT_HOVER);
                break;
            case AB_EDIT_HOVER:
                break;
            case AB_SELECT_WAVETABLE:
                SetLeftWavetable(GetLeftWavetable()+1);
                
                if(GetLeftWavetable() > left_wavetable_offset_ + 2) {
                    left_wavetable_offset_ = GetLeftWavetable() - 2;
                }
                
                if(abEngine.GetLeftWavetable() == GetLeftWavetable())
                    SetLeftFrame(abEngine.GetLeftFrame());
                else
                    SetLeftFrame(0);
                break;
            case AB_SELECT_FRAME:
                SetLeftFrame(GetLeftFrame()+1);

                if(GetLeftFrame() > left_frame_offset_ + 2) {
                    left_frame_offset_ = GetLeftFrame() - 2;
                }

                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == LEFT_ENCODER_CLICK) {
        active_menu_ = LEFT;
        switch(left_state_) {
            case AB_LOAD_HOVER:
                setLeftState(AB_SELECT_WAVETABLE);
                break;
            case AB_EDIT_HOVER:
                abEngine.FillWaveform(BUF3, left_wavetable_, left_frame_);
                abEngine.SetIsEditingLeft(true);
                waveEditor.setTargetState(WaveEditor::WAVE_TARGET_A);
                waveEditor.setWavedata(BUF3);
                context.setState(&waveEditor);
                break;
            case AB_SELECT_WAVETABLE:
                setLeftState(AB_SELECT_FRAME);
                if(GetLeftWavetable() != abEngine.GetLeftWavetable())
                    left_frame_offset_ = 0;
                else
                    left_frame_offset_ = std::clamp(abEngine.GetLeftFrame(), 0, 15-2);
                break;
            case AB_SELECT_FRAME:
                abEngine.SetIsEditingLeft(false);
                abEngine.SetLeftWavetable(GetLeftWavetable());
                abEngine.SetLeftFrame(GetLeftFrame());
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == BACK_BUTTON) {
        if(active_menu_ == LEFT) {
            switch(left_state_) {
                case AB_LOAD_HOVER:
                    if(back_menu_)
                        context.setState(back_menu_);
                    else
                        context.setState(&mainMenu);
                    break;
                case AB_EDIT_HOVER:
                    if(back_menu_)
                        context.setState(back_menu_);
                    else
                        context.setState(&mainMenu);
                    break;
                case AB_SELECT_WAVETABLE:
                    setLeftState(AB_LOAD_HOVER);
                    break;
                case AB_SELECT_FRAME:
                    setLeftState(AB_SELECT_WAVETABLE);
                    break;
                default:
                    break;
            }
        }
    }

    return true;
}

void ABModeMenu::paint(juce::Graphics& g) {
    uint16_t morph = adc.getChannel(3);

    Display::clear_screen();

    int graph_y_offset = 3;
    int graph_height = 32 - graph_y_offset;
    int gap = 1;
    int graph_width = 128 / 2 - gap;
    
    Display::outline_rectangle(0, graph_y_offset, graph_width, graph_height);
    Display::outline_rectangle(graph_width + gap * 2, graph_y_offset, graph_width, graph_height);
    
    if(left_state_ == AB_SELECT_FRAME || left_state_ == AB_SELECT_WAVETABLE)
        abEngine.FillWaveform(BUF1, left_wavetable_, left_frame_);
    else
        abEngine.FillWaveform(BUF1, abEngine.GetLeftWavetable(), abEngine.GetLeftFrame());

    if(left_state_ == AB_SELECT_FRAME || left_state_ == AB_SELECT_WAVETABLE)
        Display::Draw_Wave(1, graph_y_offset + 1, graph_width-2, graph_height-2, BUF1);
    else
        Display::Draw_Wave(1, graph_y_offset + 1, graph_width-2, graph_height-2, abEngine.IsEditingLeft() ? BUF3 : BUF1);

    abEngine.FillWaveform(BUF2, right_wavetable_, right_frame_);

    Display::Draw_Wave(graph_width + gap * 2 + 1, graph_y_offset + 1, graph_width-2, graph_height-2, BUF2);

    int y_offset = graph_y_offset + graph_height + 5;
    int x_offset = 64 - 5;
    if(left_state_ == AB_SELECT_WAVETABLE) {
        for(int i = 0; i < 3; i++)
        {
            char line[20];
            snprintf(line, 20, "TABLE %d", i + left_wavetable_offset_);
            Display::put_string_5x5(5, y_offset + i * 7, strlen(line), line, i+left_wavetable_offset_ == left_wavetable_);

            int y_shift = 2;
            int bar_height = 3 * 7 + y_shift * 2;
            int y_cursor_offset = ((bar_height-3/2) * left_wavetable_offset_) / 15;
            Display::outline_rectangle(x_offset+1, y_offset + 1 - y_shift + y_cursor_offset, 1, 3);
            Display::invert_rectangle(x_offset, y_offset - y_shift, 3, bar_height);
        }
    } else if (left_state_ == AB_SELECT_FRAME) {
        for(int i = 0; i < 3; i++)
        {
            char line[20];
            snprintf(line, 20, "FRAME %d", i + left_frame_offset_);
            Display::put_string_5x5(5, y_offset + i * 7, strlen(line), line, i+left_frame_offset_ == left_frame_);

            int y_shift = 2;
            int bar_height = 3 * 7 + y_shift * 2;
            int y_cursor_offset = ((bar_height-3/2) * left_frame_offset_) / 15;
            Display::outline_rectangle(x_offset+1, y_offset + 1 - y_shift + y_cursor_offset, 1, 3);
            Display::invert_rectangle(x_offset, y_offset - y_shift, 3, bar_height);
        }
    }
    else if(left_state_ == AB_LOAD_HOVER || left_state_ == AB_EDIT_HOVER) {
        int y_offset = graph_y_offset + graph_height + 5;
        int x_offset = 64 / 2 - (15 + 1);
        Display::put_image_16bit(x_offset, y_offset, Graphic_icon_load_15x15, 15);
        Display::put_image_16bit(x_offset + 15 + 2, y_offset, Graphic_icon_edit_15x15, 15);
        
        if(left_state_ == AB_LOAD_HOVER) {
            Display::invert_rectangle(x_offset+1, y_offset+1, 13, 13);
        } else {
            Display::invert_rectangle(x_offset+1 + 15 + 2, y_offset+1, 13, 13);
        }
    }
    
}
