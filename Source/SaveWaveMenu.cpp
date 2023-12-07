/*
  ==============================================================================

    SaveWaveMenu.cpp
    Created: 26 Nov 2023 5:50:08pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Display.h"
#include "graphics.h"
#include "Globals.h"

SaveWaveMenu::SaveWaveMenu() {
    setState(SAVE_WAVE_MENU_SELECT_WAVETABLE);
    wavetable_ = 0;
    frame_ = 0;
}

SaveWaveMenu::~SaveWaveMenu() {
    
}

void SaveWaveMenu::triggerUpdate(bool back_pressed) {
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
    
    ticker_timer_ = system_clock.milliseconds() - 2000;

}

bool SaveWaveMenu::handleKeyRelease(int key) {
    if(key == LEFT_ENCODER_CCW) {
        switch(state_) {
            case SAVE_WAVE_MENU_SELECT_WAVETABLE:
                wavetable_ = std::clamp<int16_t>(wavetable_ - 1, 0, USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 1);
                
                if(wavetable_ < wavetable_offset_) {
                    wavetable_offset_ = wavetable_;
                }

                break;
            case SAVE_WAVE_MENU_SELECT_FRAME:
                ticker_timer_ = system_clock.milliseconds() - 2000;

                frame_ = std::clamp<int16_t>(frame_ - 1, 0, 15);

                if(frame_ < frame_offset_) {
                    frame_offset_ = frame_;
                }

                break;
            default:
                break;
        }
    }
    if(key == LEFT_ENCODER_CW) {
        switch(state_) {
            case SAVE_WAVE_MENU_SELECT_WAVETABLE:
                wavetable_ = std::clamp<int16_t>(wavetable_ + 1, 0, USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 1);
                
                if(wavetable_ > wavetable_offset_ + 5) {
                    wavetable_offset_ = wavetable_ - 5;
                }

                break;
            case SAVE_WAVE_MENU_SELECT_FRAME:
                ticker_timer_ = system_clock.milliseconds() - 2000;

                frame_ = std::clamp<int16_t>(frame_ + 1, 0, 15);

                if(frame_ > frame_offset_ + 5) {
                    frame_offset_ = frame_ - 5;
                }

                break;
            default:
                break;
        }
    }
    if(key == RIGHT_ENCODER_CCW) {
        switch(state_) {
            case SAVE_WAVE_MENU_SELECT_WAVETABLE:
                break;
            default:
                break;
        }
    }
    if(key == RIGHT_ENCODER_CW) {
        switch(state_) {
            case SAVE_WAVE_MENU_SELECT_WAVETABLE:
                break;
            default:
                break;
        }
    }
    if(key == RIGHT_ENCODER_CLICK) {
        switch(state_) {
            case SAVE_WAVE_MENU_SELECT_WAVETABLE:
//                setState(LOAD_WAVE_MENU_SELECT_FRAME);
                break;
            case SAVE_WAVE_MENU_SELECT_FRAME:
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
            case SAVE_WAVE_MENU_SELECT_WAVETABLE:
                if(storage.GetWavetable(wavetable_).name[0] == '\0') {
                    context.setState(&enterNameMenu);
                    enterNameMenu.setBackMenu(&saveWaveMenu);
                    enterNameMenu.setExecFunc(SaveWaveMenu::SaveWavetable);
                } else {
                    ticker_timer_ = system_clock.milliseconds() - 2000;

                    setState(SAVE_WAVE_MENU_SELECT_FRAME);
                    frame_ = 0;
                    frame_offset_ = 0;
                }
                break;
            case SAVE_WAVE_MENU_SELECT_FRAME: {
                if(wavetable_ < FACTORY_WAVETABLE_COUNT) {
                    popup.show();
                    popup.SetLine(0, (char*)"CANNOT OVERWRITE");
                    popup.SetLine(1, (char*)"FACTORY PRESETS!");
                    popup.SetLine(2, (char*)"\0");
                }
                else {
                    context.setState(&enterNameMenu);
                    enterNameMenu.setBackMenu(&saveWaveMenu);
                    enterNameMenu.setExecFunc(SaveWaveMenu::SaveWave);
                }
                break;
            }
            default:
                break;
        }
    }
    if(key == BACK_BUTTON) {
        switch(state_) {
            case SAVE_WAVE_MENU_SELECT_WAVETABLE:
                if(back_menu_)
                    context.setState(back_menu_, true);
                else
                    context.setState(&mainMenu);
                break;
            case SAVE_WAVE_MENU_SELECT_FRAME:
                setState(SAVE_WAVE_MENU_SELECT_WAVETABLE);
                break;
            default:
                break;
        }
    }

    return true;
}

void SaveWaveMenu::SaveWavetable(char* param) {
    storage.SaveWavetable(param, saveWaveMenu.wavetable_);
}

void SaveWaveMenu::SaveWave(char* param) {
    storage.SaveWave(param, saveWaveMenu.wavedata_, saveWaveMenu.wavetable_, saveWaveMenu.frame_);
}

void SaveWaveMenu::paint(juce::Graphics& g) {
    Display::clear_screen();
    if(state_ == SAVE_WAVE_MENU_SELECT_WAVETABLE) {

        char * title = (char *) "SELECT WAVETABLE";

        int y_offset = 5;
        int x_offset = 1 + 2 * 4;

        Display::put_string_5x5(x_offset, y_offset, strlen(title), title);
        
        Display::invert_rectangle(0, 0, 128, 15);
        
        x_offset = 128 - 5;
        y_offset += 15;

        for(int i = 0; i < 6; i++)
        {
            char line[20];
            memset(line, 0, 20);
            snprintf(line, 20, "%*d", 2, i + wavetable_offset_ + 1);
            Display::put_string_3x5(2, y_offset + i * 7, strlen(line), line);
            
            char line2[20];
            memset(line2, 0, 20);
            if(storage.GetWavetable(i + wavetable_offset_).name[0] == '\0') {
                strncpy(line2, "+NEW WAVETABLE", strlen("+NEW WAVETABLE"));
            }
            else {
                snprintf(line2, 20, "%-8s    [%02d]", storage.GetWavetable(i + wavetable_offset_).name, storage.GetNumberOfWavesInTable(i + wavetable_offset_));
            }
            
            Display::put_string_5x5(2 + 2 * 3 + 4, y_offset + i * 7, strlen(line2), line2, i+wavetable_offset_ == wavetable_);
        }

        int y_shift = 2;
        int bar_height = 64 - y_offset - 1;
        int y_cursor_offset = ((bar_height-1) * wavetable_offset_) / (USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 1);
        Display::outline_rectangle(x_offset+1, y_offset + 1 - y_shift + y_cursor_offset, 1, 3);
        Display::invert_rectangle(x_offset, y_offset - y_shift, 3, bar_height);

    } else {
        char * title = (char *) "SELECT WAVE SLOT";

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
            
            
            char * name = storage.GetWavetable(wavetable_).waves[i + frame_offset_].name;

            char line2[20];
            memset(line2, 0, 20);
            if(name[0] == '\0')
                strncpy(line2, "[EMPTY]", strlen("[EMPTY]"));
            else {
                int name_index = 0;
                int32_t elapsed_time = system_clock.milliseconds() - ticker_timer_;

                if (elapsed_time > 4000) {
                    ticker_timer_ = system_clock.milliseconds();
                }
                if(i+frame_offset_ == frame_ && strlen(name) > 7 && (elapsed_time) > 0) {
                    name_index = (elapsed_time) / 1000;
                    name_index = std::clamp(name_index, 0, 1);
                }
                // if timer is passed 2000, name_index = 1
                strncpy(line2, &name[name_index], 7);
            }
//
//            char line2[20];
//            memset(line2, 0, 20);
//            if(storage.GetWavetable(wavetable_).waves[i + frame_offset_].name[0] == '\0') {
//                strncpy(line2, "[EMPTY]", strlen("[EMPTY]"));
//            }
//            else {
//                snprintf(line2, 20, "%-8s", storage.GetWavetable(wavetable_).waves[i + frame_offset_].name);
//            }
            
            Display::put_string_5x5(2 + 2 * 3 + 4, y_offset + i * 7, strlen(line2), line2, i+frame_offset_ == frame_);
        }

        int y_shift = 2;
        int bar_height = 64 - y_offset - 1;
        int y_cursor_offset = ((bar_height-1) * frame_offset_) / 11;
        Display::outline_rectangle(x_offset+1, y_offset + 1 - y_shift + y_cursor_offset, 1, 3);
        Display::invert_rectangle(x_offset, y_offset - y_shift, 3, bar_height);

        storage.LoadWaveSample(BUF1, wavetable_, frame_);

        Display::Draw_Wave(64, y_offset - y_shift, 64, bar_height - 3, BUF1);
    }
}
