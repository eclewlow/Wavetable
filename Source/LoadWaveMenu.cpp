/*
  ==============================================================================

    LoadWaveMenu.cpp
    Created: 26 Nov 2023 5:50:03pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Display.h"
#include "graphics.h"
#include "Globals.h"

LoadWaveMenu::LoadWaveMenu() {
    setState(LOAD_WAVE_MENU_SELECT_WAVETABLE);
    wavetable_ = 0;
    frame_ = 0;
}

LoadWaveMenu::~LoadWaveMenu() {
    
}

void LoadWaveMenu::triggerUpdate() {
    if(wavetable_ < wavetable_offset_) {
        wavetable_offset_ = wavetable_;
    }

    if(frame_ < frame_offset_) {
        frame_offset_ = frame_;
    }
    
    if(wavetable_ > wavetable_offset_ + 5) {
        wavetable_offset_ = wavetable_ - 5;
    }

    if(frame_ > frame_offset_ + 5) {
        frame_offset_ = frame_ - 5;
    }
}

bool LoadWaveMenu::handleKeyPress(const juce::KeyPress &key) {
    if(key.getKeyCode() == LEFT_ENCODER_CCW) {
        switch(state_) {
            case LOAD_WAVE_MENU_SELECT_WAVETABLE:
                wavetable_ = std::clamp<int16_t>(wavetable_ - 1, 0, 15);
                
                if(wavetable_ < wavetable_offset_) {
                    wavetable_offset_ = wavetable_;
                }

                morph_ = 0.0f;

                break;
            case LOAD_WAVE_MENU_SELECT_FRAME:
                frame_ = std::clamp<int16_t>(frame_ - 1, 0, 15);

                if(frame_ < frame_offset_) {
                    frame_offset_ = frame_;
                }

                break;
            default:
                break;
        }    
    }
    if(key.getKeyCode() == LEFT_ENCODER_CW) {
        switch(state_) {
            case LOAD_WAVE_MENU_SELECT_WAVETABLE:
                wavetable_ = std::clamp<int16_t>(wavetable_ + 1, 0, 15);
                
                if(wavetable_ > wavetable_offset_ + 5) {
                    wavetable_offset_ = wavetable_ - 5;
                }

                morph_ = 0.0f;
                
                break;
            case LOAD_WAVE_MENU_SELECT_FRAME:
                frame_ = std::clamp<int16_t>(frame_ + 1, 0, 15);

                if(frame_ > frame_offset_ + 5) {
                    frame_offset_ = frame_ - 5;
                }

                break;
            default:
                break;
        }   
    }
    if(key.getKeyCode() == RIGHT_ENCODER_CCW) {
        switch(state_) {
            case LOAD_WAVE_MENU_SELECT_WAVETABLE:
                morph_ = std::clamp<float>(morph_ - 0.02, 0.0f, 1.0f);
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == RIGHT_ENCODER_CW) {
        switch(state_) {
            case LOAD_WAVE_MENU_SELECT_WAVETABLE:
                morph_ = std::clamp<float>(morph_ + 0.02, 0.0f, 1.0f);
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == RIGHT_ENCODER_CLICK) {
        switch(state_) {
            case LOAD_WAVE_MENU_SELECT_WAVETABLE:
//                setState(LOAD_WAVE_MENU_SELECT_FRAME);
                break;
            case LOAD_WAVE_MENU_SELECT_FRAME:
//                if(target_ == AB_ENGINE_A) {
//                    abEngine.SetLeftWavetable(wavetable_);
//                    abEngine.SetLeftFrame(frame_);
//                } else if(target_ == AB_ENGINE_B) {
//                    abEngine.SetRightWavetable(wavetable_);
//                    abEngine.SetRightFrame(frame_);
//                }
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == LEFT_ENCODER_CLICK) {
        switch(state_) {
            case LOAD_WAVE_MENU_SELECT_WAVETABLE:
                setState(LOAD_WAVE_MENU_SELECT_FRAME);
                frame_ = 0;
                break;
            case LOAD_WAVE_MENU_SELECT_FRAME:
                if(target_ == AB_ENGINE_A) {
                    abEngine.SetLeftWavetable(wavetable_);
                    abEngine.SetLeftFrame(frame_);
                    abEngine.FillWaveform(BUF3, wavetable_, frame_);
                } else if(target_ == AB_ENGINE_B) {
                    abEngine.SetRightWavetable(wavetable_);
                    abEngine.SetRightFrame(frame_);
                    abEngine.FillWaveform(BUF4, wavetable_, frame_);
                }

                setState(LOAD_WAVE_MENU_SELECT_WAVETABLE);
                wavetable_ = 0;
                frame_ = 0;
                

                if(back_menu_)
                    context.setState(back_menu_);
                else
                    context.setState(&mainMenu);
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == BACK_BUTTON) {
        switch(state_) {
            case LOAD_WAVE_MENU_SELECT_WAVETABLE:
                if(back_menu_)
                    context.setState(back_menu_);
                else
                    context.setState(&mainMenu);
                break;
            case LOAD_WAVE_MENU_SELECT_FRAME:
                setState(LOAD_WAVE_MENU_SELECT_WAVETABLE);
                morph_ = 0.0f;
                break;
            default:
                break;
        }
    }

    return true;
}

void LoadWaveMenu::paint(juce::Graphics& g) {
    Display::clear_screen();
    if(state_ == LOAD_WAVE_MENU_SELECT_WAVETABLE) {

        char * title = (char *) "SELECT WAVETABLE";

        int y_offset = 5;
        int x_offset = 1 + 2 * 4;

        Display::put_string_5x5(x_offset, y_offset, strlen(title), title);
        
        Display::invert_rectangle(0, 0, 128, 15);
        
        x_offset = 64 - 5;
        y_offset += 15;

        for(int i = 0; i < 6; i++)
        {
            char line[20];
            snprintf(line, 20, "%*d", 2, i + wavetable_offset_ + 1);
            Display::put_string_3x5(2, y_offset + i * 7, strlen(line), line);
            
            char * line2 = storage.getWavetable(i + wavetable_offset_).name;
            Display::put_string_5x5(2 + 2 * 3 + 4, y_offset + i * 7, std::min<int16_t>(strlen(line2), 7), line2, i+wavetable_offset_ == wavetable_);
        }

        int y_shift = 2;
        int bar_height = 64 - y_offset - 1;
        int y_cursor_offset = ((bar_height-1) * wavetable_offset_) / 11;
        Display::outline_rectangle(x_offset+1, y_offset + 1 - y_shift + y_cursor_offset, 1, 3);
        Display::invert_rectangle(x_offset, y_offset - y_shift, 3, bar_height);

        storage.LoadWaveSample(BUF1, wavetable_, morph_);

        Display::Draw_Wave(64, y_offset - y_shift, 64, bar_height - 3, BUF1);

        int bar_width = 48;
        int x_cursor_offset = morph_ * (bar_width - 5);
        Display::outline_rectangle(95 - bar_width / 2 + 1 + x_cursor_offset, y_offset - y_shift + bar_height - 3 + 1, 3, 1);
        Display::invert_rectangle(95 - bar_width / 2, y_offset - y_shift + bar_height - 3, bar_width, 3);
    } else {
        char * title = (char *) "SELECT WAVE";

        int y_offset = 5;
        int x_offset = 1 + 2 * 4;

        Display::put_string_5x5(x_offset, y_offset, strlen(title), title);
        
        Display::invert_rectangle(0, 0, 128, 15);
        
        x_offset = 64 - 5;
        y_offset += 15;

        for(int i = 0; i < 6; i++)
        {
            char line[20];
            snprintf(line, 20, "%*d", 2, i + frame_offset_ + 1);
            Display::put_string_3x5(2, y_offset + i * 7, strlen(line), line);
            
            snprintf(line, 20, "%02d", i + frame_offset_);
            Display::put_string_5x5(2 + 2 * 3 + 4, y_offset + i * 7, std::min<int16_t>(strlen(line), 7), line, i+frame_offset_ == frame_);
        }

        int y_shift = 2;
        int bar_height = 64 - y_offset - 1;
        int y_cursor_offset = ((bar_height-1) * wavetable_offset_) / 11;
        Display::outline_rectangle(x_offset+1, y_offset + 1 - y_shift + y_cursor_offset, 1, 3);
        Display::invert_rectangle(x_offset, y_offset - y_shift, 3, bar_height);

        storage.LoadWaveSample(BUF1, wavetable_, frame_);

        Display::Draw_Wave(64, y_offset - y_shift, 64, bar_height - 3, BUF1);
    }
}