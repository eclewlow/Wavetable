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
}

LoadWaveMenu::~LoadWaveMenu() {
    
}

bool LoadWaveMenu::handleKeyPress(const juce::KeyPress &key) {
    if(key.getKeyCode() == LEFT_ENCODER_CCW) {
        switch(state_) {
            case LOAD_WAVE_MENU_SELECT_WAVETABLE:
                wavetable_ = std::clamp<int16_t>(wavetable_ - 1, 0, 15);
                
                if(wavetable_ < wavetable_offset_) {
                    wavetable_offset_ = wavetable_;
                }
                
//                if(abEngine.GetLeftWavetable() == GetLeftWavetable())
//                    SetFrame(abEngine.GetLeftFrame());
//                else
//                    SetFrame(0);
                break;
            case LOAD_WAVE_MENU_SELECT_FRAME:
                frame_ = std::clamp<int16_t>(frame_ - 1, 0, 15);

                if(frame_ < frame_offset_) {
                    frame_offset_ = frame_;
                }

                break;
            default:
                break;
        }    }
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
        if(back_menu_)
            context.setState(back_menu_);
        else
            context.setState(&mainMenu);
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
        int y_cursor_offset = ((bar_height-3/2) * wavetable_offset_) / 15;
        Display::outline_rectangle(x_offset+1, y_offset + 1 - y_shift + y_cursor_offset, 1, 3);
        Display::invert_rectangle(x_offset, y_offset - y_shift, 3, bar_height);

//        for (int i = 0; )
    } else {
        
    }
}
