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

void LoadWaveMenu::triggerUpdate(bool back_pressed) {
    if(!back_pressed) {
        wavetable_offset_ = 0;
        wavetable_ = 0;
        frame_ = 0;
        frame_offset_ = 0;
        return;
    }

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

void LoadWaveMenu::ResetTicker() {
    ticker_timer_ = system_clock.milliseconds();
    ticker_ = 0;
}

bool LoadWaveMenu::handleKeyRelease(int key) {
    if(key == LEFT_ENCODER_CCW) {
        switch(state_) {
            case LOAD_WAVE_MENU_SELECT_WAVETABLE:
                wavetable_ = std::clamp<int16_t>(wavetable_ - 1, 0, USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 1);
                
                if(wavetable_ < wavetable_offset_) {
                    wavetable_offset_ = wavetable_;
                }

                morph_ = 0.0f;

                ResetTicker();

                break;
            case LOAD_WAVE_MENU_SELECT_FRAME:
                frame_ = std::clamp<int16_t>(frame_ - 1, 0, 15);

                if(frame_ < frame_offset_) {
                    frame_offset_ = frame_;
                }

                ResetTicker();

                break;
            default:
                break;
        }    
    }
    if(key == LEFT_ENCODER_CW) {
        switch(state_) {
            case LOAD_WAVE_MENU_SELECT_WAVETABLE:
                wavetable_ = std::clamp<int16_t>(wavetable_ + 1, 0, USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 1);
                
                if(wavetable_ > wavetable_offset_ + 5) {
                    wavetable_offset_ = wavetable_ - 5;
                }

                morph_ = 0.0f;
                
                ResetTicker();
                
                break;
            case LOAD_WAVE_MENU_SELECT_FRAME:
                frame_ = std::clamp<int16_t>(frame_ + 1, 0, 15);

                if(frame_ > frame_offset_ + 5) {
                    frame_offset_ = frame_ - 5;
                }

                ResetTicker();

                break;
            default:
                break;
        }   
    }
    if(key == RIGHT_ENCODER_CCW) {
        switch(state_) {
            case LOAD_WAVE_MENU_SELECT_WAVETABLE:
                morph_ = std::clamp<float>(morph_ - 1.0f / 30.0f, 0.0f, 1.0f);
                break;
            default:
                break;
        }
    }
    if(key == RIGHT_ENCODER_CW) {
        switch(state_) {
            case LOAD_WAVE_MENU_SELECT_WAVETABLE:
                morph_ = std::clamp<float>(morph_ + 1.0f / 30.0f, 0.0f, 1.0f);
                break;
            default:
                break;
        }
    }
    if(key == RIGHT_ENCODER_CLICK) {
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
    if(key == LEFT_ENCODER_CLICK) {
        switch(state_) {
            case LOAD_WAVE_MENU_SELECT_WAVETABLE:
                ResetTicker();
                setState(LOAD_WAVE_MENU_SELECT_FRAME);
                frame_ = 0;
                frame_offset_ = 0;
                break;
            case LOAD_WAVE_MENU_SELECT_FRAME: {
                bool success = false;
                if(target_ == AB_ENGINE_A) {
                    success = abEngine.SetLeftWave(wavetable_, frame_);
                    if(success)
                        abEngine.FillWaveform(BUF3, wavetable_, frame_);
                } else if(target_ == AB_ENGINE_B) {
                    success = abEngine.SetRightWave(wavetable_, frame_);
                    if(success)
                        abEngine.FillWaveform(BUF4, wavetable_, frame_);
                } else if(target_ == WAVE_MANAGER) {
                    storage.LoadWaveSample(BUF5, wavetable_, frame_);
                    success = true;
                }
                
                if(success) {
                    setState(LOAD_WAVE_MENU_SELECT_WAVETABLE);
                    wavetable_ = 0;
                    frame_ = 0;
                    
                    if(back_menu_)
                        context.setState(back_menu_);
                    else
                        context.setState(&mainMenu);
                }
                break;
            }
            default:
                break;
        }
    }
    if(key == BACK_BUTTON) {
        switch(state_) {
            case LOAD_WAVE_MENU_SELECT_WAVETABLE:
                if(back_menu_)
                    context.setState(back_menu_, true);
                else
                    context.setState(&mainMenu, true);
                break;
            case LOAD_WAVE_MENU_SELECT_FRAME:
                ResetTicker();
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

        int y_offset = 3;
        int x_offset = 1 + 2 * 4;

        Display::put_string_5x5(x_offset, y_offset, strlen(title), title);
        
        Display::invert_rectangle(0, 0, 128, 11);
        
        x_offset = 64 - 5;
        y_offset += 11;

        for(int i = 0; i < 6; i++)
        {
            char line[20];
            snprintf(line, 20, "%*d", 2, i + wavetable_offset_ + 1);
            Display::put_string_3x5(2, y_offset + i * 8, strlen(line), line);
            
            char * name = storage.GetWavetable(i + wavetable_offset_)->name;

            char * line2 = name;

            int32_t elapsed_time = system_clock.milliseconds() - ticker_timer_;

            int8_t num_chars = 7;

            if(i + wavetable_offset_ == wavetable_) {
                if(ticker_ == 0) {
                    if(elapsed_time > 1000) {
                        ticker_++;
                        ticker_timer_ = system_clock.milliseconds();
                    }
                } else if(ticker_ == (strlen(line2) - num_chars) * 6) {
                    if(elapsed_time > 2000) {
                        ResetTicker();
                    }
                }
                else if (elapsed_time > 20) {
                    ticker_++;
                    ticker_timer_ = system_clock.milliseconds();
                }
                Display::put_string_5x5_loop(2 + 2 * 3 + 4, y_offset + i * 8, strlen(line2), line2, i+wavetable_offset_ == wavetable_, num_chars, strlen(line2) > num_chars ? ticker_ : 0);
            } else {
                Display::put_string_5x5_loop(2 + 2 * 3 + 4, y_offset + i * 8, strlen(line2), line2, i+wavetable_offset_ == wavetable_, num_chars, 0);
            }
        }

        int y_shift = 2;
        int bar_height = 64 - y_offset - 1;
        int y_cursor_offset = ((bar_height - 5) * wavetable_offset_) / (USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 1 - 5);
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
        title = storage.GetWavetable(wavetable_)->name;

        int y_offset = 3;
        int x_offset = 1 + 2 * 4;

        Display::put_string_5x5(x_offset, y_offset, strlen(title), title);
        
        Display::invert_rectangle(0, 0, 128, 11);
        
        x_offset = 64 - 5;
        y_offset += 11;

        for(int i = 0; i < 6; i++)
        {
            char line[20];
            snprintf(line, 20, "%*d", 2, i + frame_offset_ + 1);
            Display::put_string_3x5(2, y_offset + i * 8, strlen(line), line);
            
            char * name = storage.GetWavetable(wavetable_)->waves[i + frame_offset_].name;
            
            char * line2 = name;

            int32_t elapsed_time = system_clock.milliseconds() - ticker_timer_;

            int8_t num_chars = 7;

            if(i + frame_offset_ == frame_) {
                if(ticker_ == 0) {
                    if(elapsed_time > 1000) {
                        ticker_++;
                        ticker_timer_ = system_clock.milliseconds();
                    }
                } else if(ticker_ == (strlen(line2) - num_chars) * 6) {
                    if(elapsed_time > 2000) {
                        ResetTicker();
                    }
                }
                else if (elapsed_time > 20) {
                    ticker_++;
                    ticker_timer_ = system_clock.milliseconds();
                }
                Display::put_string_5x5_loop(2 + 2 * 3 + 4, y_offset + i * 8, strlen(line2), line2, i+frame_offset_ == frame_, num_chars, strlen(line2) > num_chars ? ticker_ : 0);
            } else {
                Display::put_string_5x5_loop(2 + 2 * 3 + 4, y_offset + i * 8, strlen(line2), line2, i+frame_offset_ == frame_, num_chars, 0);
            }
        }

        int y_shift = 2;
        int bar_height = 64 - y_offset - 1;
        int y_cursor_offset = ((bar_height - 5) * frame_offset_) / 10;
        Display::outline_rectangle(x_offset+1, y_offset + 1 - y_shift + y_cursor_offset, 1, 3);
        Display::invert_rectangle(x_offset, y_offset - y_shift, 3, bar_height);

        storage.LoadWaveSample(BUF1, wavetable_, frame_);

        Display::Draw_Wave(64, y_offset - y_shift, 64, bar_height - 3, BUF1);
    }
}
