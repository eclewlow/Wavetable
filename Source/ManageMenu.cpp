/*
  ==============================================================================

    ManageMenu.cpp
    Created: 5 Dec 2023 2:46:59pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Display.h"
#include "graphics.h"
#include "Globals.h"

ManageMenu::ManageMenu() {
    setState(MANAGE_MENU_SELECT_WAVETABLE);
    wavetable_ = 0;
    frame_ = 0;
}

ManageMenu::~ManageMenu() {
    
}

void ManageMenu::triggerUpdate(bool back_pressed) {
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

bool ManageMenu::handleKeyPress(const juce::KeyPress &key) {
    if(key.getKeyCode() == LEFT_ENCODER_CCW) {
        switch(state_) {
            case MANAGE_MENU_SELECT_WAVETABLE:
                wavetable_ = std::clamp<int16_t>(wavetable_ - 1, 0, USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 1);
                
                if(wavetable_ < wavetable_offset_) {
                    wavetable_offset_ = wavetable_;
                }

                morph_ = 0.0f;

                ticker_timer_ = juce::Time::currentTimeMillis() - 2000;

                break;
            case MANAGE_MENU_SELECT_FRAME:
                frame_ = std::clamp<int16_t>(frame_ - 1, 0, 15);

                if(frame_ < frame_offset_) {
                    frame_offset_ = frame_;
                }

                ticker_timer_ = juce::Time::currentTimeMillis() - 2000;

                break;
            case MANAGE_MENU_WAVETABLE_OPTIONS:
                setOptionSelected(std::clamp<int8_t>(option_selected_ - 1, MANAGE_MENU_EDIT, MANAGE_MENU_DELETE));
                break;
            case MANAGE_MENU_CONFIRM_DELETE:
                setOptionSelected(std::clamp<int8_t>(option_selected_ - 1, MANAGE_MENU_NO, MANAGE_MENU_YES));
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == LEFT_ENCODER_CW) {
        switch(state_) {
            case MANAGE_MENU_SELECT_WAVETABLE:
                wavetable_ = std::clamp<int16_t>(wavetable_ + 1, 0, USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 1);
                
                if(wavetable_ > wavetable_offset_ + 5) {
                    wavetable_offset_ = wavetable_ - 5;
                }

                morph_ = 0.0f;
                
                ticker_timer_ = juce::Time::currentTimeMillis() - 2000;
                
                break;
            case MANAGE_MENU_SELECT_FRAME:
                frame_ = std::clamp<int16_t>(frame_ + 1, 0, 15);

                if(frame_ > frame_offset_ + 5) {
                    frame_offset_ = frame_ - 5;
                }

                ticker_timer_ = juce::Time::currentTimeMillis() - 2000;

                break;
            case MANAGE_MENU_WAVETABLE_OPTIONS:
                setOptionSelected(std::clamp<int8_t>(option_selected_ + 1, MANAGE_MENU_EDIT, MANAGE_MENU_DELETE));
                break;
            case MANAGE_MENU_CONFIRM_DELETE:
                setOptionSelected(std::clamp<int8_t>(option_selected_ + 1, MANAGE_MENU_NO, MANAGE_MENU_YES));
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == RIGHT_ENCODER_CCW) {
        switch(state_) {
            case MANAGE_MENU_SELECT_WAVETABLE:
                morph_ = std::clamp<float>(morph_ - 1.0f / 30.0f, 0.0f, 1.0f);
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == RIGHT_ENCODER_CW) {
        switch(state_) {
            case MANAGE_MENU_SELECT_WAVETABLE:
                morph_ = std::clamp<float>(morph_ + 1.0f / 30.0f, 0.0f, 1.0f);
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == RIGHT_ENCODER_CLICK) {
        switch(state_) {
            case MANAGE_MENU_SELECT_WAVETABLE:
//                setState(MANAGE_MENU_SELECT_FRAME);
                break;
            case MANAGE_MENU_SELECT_FRAME:
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
            case MANAGE_MENU_SELECT_WAVETABLE:
//                if(storage.GetWavetable(wavetable_).name[0] != '\0')
                option_selected_ = MANAGE_MENU_EDIT;
                setState(MANAGE_MENU_WAVETABLE_OPTIONS);
//                else {
//                    popup.show();
//                    popup.SetLine(0, (char*)"CANNOT SELECT");
//                    popup.SetLine(1, (char*)"EMPTY WAVETABLE!");
//                    popup.SetLine(2, (char*)"\0");
//
//                }
//                ticker_timer_ = juce::Time::currentTimeMillis() - 2000;
//                setState(MANAGE_MENU_SELECT_FRAME);
//                frame_ = 0;
//                frame_offset_ = 0;
                break;
            case MANAGE_MENU_SELECT_FRAME: {
                setState(MANAGE_MENU_SELECT_WAVETABLE);
                wavetable_ = 0;
                frame_ = 0;
                
                if(back_menu_)
                    context.setState(back_menu_);
                else
                    context.setState(&mainMenu);
                break;
            }
            case MANAGE_MENU_WAVETABLE_OPTIONS:
                if(option_selected_ == MANAGE_MENU_EDIT) {
                    // TODO:  what does this do???
                } else if(option_selected_ == MANAGE_MENU_RENAME) {
                    context.setState(&enterNameMenu);
                    enterNameMenu.setBackMenu(this);
                    enterNameMenu.setExecFunc(ManageMenu::SaveWavetable);
                    enterNameMenu.setNameChars(storage.GetWavetable(wavetable_).name);
                } else if(option_selected_ == MANAGE_MENU_DELETE) {
                    option_selected_ = MANAGE_MENU_NO;
                    setState(MANAGE_MENU_CONFIRM_DELETE);
                }
                break;
            case MANAGE_MENU_CONFIRM_DELETE:
                if(option_selected_ == MANAGE_MENU_NO) {
                    option_selected_ = MANAGE_MENU_EDIT;
                    setState(MANAGE_MENU_WAVETABLE_OPTIONS);
                } else if(option_selected_ == MANAGE_MENU_YES) {
//                    setState(MANAGE_MENU_WAVETABLE_OPTIONS);
                    storage.DeleteWavetable(wavetable_);
                    setState(MANAGE_MENU_SELECT_WAVETABLE);
                }
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == BACK_BUTTON) {
        switch(state_) {
            case MANAGE_MENU_SELECT_WAVETABLE:
                if(back_menu_)
                    context.setState(back_menu_, true);
                else
                    context.setState(&mainMenu);
                break;
            case MANAGE_MENU_SELECT_FRAME:
                ticker_timer_ = juce::Time::currentTimeMillis() - 2000;
                setState(MANAGE_MENU_SELECT_WAVETABLE);
                morph_ = 0.0f;
                break;
            case MANAGE_MENU_WAVETABLE_OPTIONS:
                setState(MANAGE_MENU_SELECT_WAVETABLE);
                break;
            case MANAGE_MENU_CONFIRM_DELETE:
                option_selected_ = MANAGE_MENU_EDIT;
                setState(MANAGE_MENU_WAVETABLE_OPTIONS);
            default:
                break;
        }
    }

    return true;
}

void ManageMenu::SaveWavetable(char* param) {
    storage.SaveWavetable(param, manageMenu.wavetable_);
    manageMenu.setState(MANAGE_MENU_SELECT_WAVETABLE);
}



void ManageMenu::paint(juce::Graphics& g) {
    Display::clear_screen();
    if(state_ == MANAGE_MENU_WAVETABLE_OPTIONS) {
        char * title;
        if(storage.GetWavetable(wavetable_).name[0] == '\0')
            title = (char*) "--------";
        else
            title = (char *) storage.GetWavetable(wavetable_).name;

        int y_offset = 5;
        int x_offset = 1 + 2 * 4;

        Display::put_string_5x5(x_offset, y_offset, strlen(title), title);
        
        Display::invert_rectangle(0, 0, 128, 15);
        
        x_offset = 20;
        y_offset = 20 + (64 - 20) / 2 - 14 * 3 / 2;
        
        Display::put_image_16bit(x_offset, y_offset, Graphic_icon_edit_11x11, 11);
        Display::put_string_9x9(x_offset + 16, y_offset + 1, strlen("EDIT"), "EDIT", option_selected_ == MANAGE_MENU_EDIT, 3);

        y_offset += 14;
        Display::put_image_16bit(x_offset, y_offset, Graphic_icon_rename_11x11, 11);
        Display::put_string_9x9(x_offset + 16, y_offset + 1, strlen("RENAME"), "RENAME", option_selected_ == MANAGE_MENU_RENAME, 3);

        y_offset += 14;
        Display::put_image_16bit(x_offset, y_offset, Graphic_icon_delete_11x11, 11);
        Display::put_string_9x9(x_offset + 16, y_offset + 1, strlen("DELETE"), "DELETE", option_selected_ == MANAGE_MENU_DELETE, 3);

    }
    else if(state_ == MANAGE_MENU_CONFIRM_DELETE) {
//        char * title;
//        if(storage.GetWavetable(wavetable_).name[0] == '\0')
//            title = (char*) "--------";
//        else
//            title = (char *) storage.GetWavetable(wavetable_).name;

        int y_offset = 16 - 6 / 2;
        int x_offset = 0;

        Display::put_string_5x5(64 - strlen("DELETE?") * 6 / 2, y_offset, strlen("DELETE?"), "DELETE?");
        
//        Display::invert_rectangle(0, 0, 128, 15);
//        
//        x_offset = 20;
//        y_offset = 20 + (64 - 20) / 2 - 14 * 3 / 2;
//
        y_offset = 48 - 10 / 2;
        x_offset = 32 - (16 + Display::get_string_9x9_width("NO", 3)) / 2;
        Display::put_image_16bit(x_offset, y_offset, Graphic_icon_cancel_11x11, 11);
        Display::put_string_9x9(x_offset + 16, y_offset, strlen("NO"), "NO", option_selected_ == MANAGE_MENU_NO, 3);

        x_offset = 96 - (16 + Display::get_string_9x9_width("YES", 3)) / 2;
        Display::put_image_16bit(x_offset, y_offset, Graphic_icon_delete_11x11, 11);
        Display::put_string_9x9(x_offset + 16, y_offset, strlen("YES"), "YES", option_selected_ == MANAGE_MENU_YES, 3);

        //
//        y_offset += 14;
//        Display::put_image_16bit(x_offset, y_offset, Graphic_icon_rename_11x11, 11);
//        Display::put_string_9x9(x_offset + 16, y_offset + 1, strlen("RENAME"), "RENAME", option_selected_ == MANAGE_MENU_RENAME, 3);
//
//        y_offset += 14;
//        Display::put_image_16bit(x_offset, y_offset, Graphic_icon_delete_11x11, 11);
//        Display::put_string_9x9(x_offset + 16, y_offset + 1, strlen("DELETE"), "DELETE", option_selected_ == MANAGE_MENU_DELETE, 3);

    }
    else if(state_ == MANAGE_MENU_SELECT_WAVETABLE) {

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
            
            char * name = storage.GetWavetable(i + wavetable_offset_).name;

            char line2[20];
            memset(line2, 0, 20);
            if(name[0] == '\0')
                strncpy(line2, "-------", 7);
            else {
                int name_index = 0;
                int32_t elapsed_time = juce::Time::currentTimeMillis() - ticker_timer_;

                if (elapsed_time > 4000) {
                    ticker_timer_ = juce::Time::currentTimeMillis();
                }
                if(i+wavetable_offset_ == wavetable_ && strlen(name) > 7 && (elapsed_time) > 0) {
                    name_index = (elapsed_time) / 1000;
                    name_index = std::clamp(name_index, 0, 1);
                }
                // if timer is passed 2000, name_index = 1
                strncpy(line2, &name[name_index], 7);
            }

            Display::put_string_5x5(2 + 2 * 3 + 4, y_offset + i * 7, strlen(line2), line2, i+wavetable_offset_ == wavetable_);
        }

        int y_shift = 2;
        int bar_height = 64 - y_offset - 1;
        int y_cursor_offset = ((bar_height-1) * wavetable_offset_) / (USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 1);
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
            
            char * name = storage.GetWavetable(wavetable_).waves[i + frame_offset_].name;

            char line2[20];
            memset(line2, 0, 20);
            if(name[0] == '\0')
                strncpy(line2, "-------", 7);
            else {
                int name_index = 0;
                int32_t elapsed_time = juce::Time::currentTimeMillis() - ticker_timer_;

                if (elapsed_time > 4000) {
                    ticker_timer_ = juce::Time::currentTimeMillis();
                }
                if(i+frame_offset_ == frame_ && strlen(name) > 7 && (elapsed_time) > 0) {
                    name_index = (elapsed_time) / 1000;
                    name_index = std::clamp(name_index, 0, 1);
                }
                // if timer is passed 2000, name_index = 1
                strncpy(line2, &name[name_index], 7);
            }
            
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