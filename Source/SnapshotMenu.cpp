/*
  ==============================================================================

    SnapshotMenu.cpp
    Created: 8 Dec 2023 8:42:12pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Display.h"
#include "graphics.h"
#include "Globals.h"

SnapshotMenu::SnapshotMenu() {
    setState(SNAPSHOT_MENU_NONE);
    snapshot_ = 0;
    snapshot_offset_ = 0;
}

SnapshotMenu::~SnapshotMenu() {
    
}

void SnapshotMenu::triggerUpdate(bool back_pressed) {
    if(!back_pressed) {
        snapshot_offset_ = 0;
        snapshot_ = 0;
        return;
    }
    if(snapshot_ < snapshot_offset_) {
        snapshot_offset_ = snapshot_;
    }
    if(snapshot_ > snapshot_offset_ + 3) {
        snapshot_offset_ = snapshot_ - 3;
    }
    
    ticker_timer_ = system_clock.milliseconds() - 2000;

}

void SnapshotMenu::ResetTicker()
{
    ticker_timer_ = system_clock.milliseconds();
    ticker_ = 0;
}

bool SnapshotMenu::handleKeyRelease(int key) {
    if(key == LEFT_ENCODER_CCW) {
        switch(state_) {
            case SNAPSHOT_MENU_NONE:
                snapshot_ = std::clamp<int16_t>(snapshot_ - 1, 0, USER_SNAPSHOT_COUNT - 1);
                
                if(snapshot_ < snapshot_offset_) {
                    snapshot_offset_ = snapshot_;
                }

                ResetTicker();
                break;
            default:
                break;
        }
    }
    if(key == LEFT_ENCODER_CW) {
        switch(state_) {
            case SNAPSHOT_MENU_NONE:
                snapshot_ = std::clamp<int16_t>(snapshot_ + 1, 0, USER_SNAPSHOT_COUNT - 1);
                
                if(snapshot_ > snapshot_offset_ + 3) {
                    snapshot_offset_ = snapshot_ - 3;
                }

                ResetTicker();
                break;
            default:
                break;
        }
    }
    if(key == RIGHT_ENCODER_CCW) {
    }
    if(key == RIGHT_ENCODER_CW) {
    }
    if(key == RIGHT_ENCODER_CLICK) {
    }
    if(key == LEFT_ENCODER_CLICK) {
        switch(state_) {
            case SNAPSHOT_MENU_NONE: {
                // TODO: recall snapshot
                break;
            }
            default:
                break;
        }
    }
    if(key == BACK_BUTTON) {
        switch(state_) {
            case SNAPSHOT_MENU_NONE:
                if(back_menu_)
                    context.setState(back_menu_, true);
                else
                    context.setState(&mainMenu);
                break;
            default:
                break;
        }
    }

    return true;
}

//void SnapshotMenu::SaveWavetable(char* param) {
//    storage.SaveWavetable(param, saveWaveMenu.wavetable_);
//}
//
//void SnapshotMenu::SaveWave(char* param) {
//    storage.SaveWave(param, saveWaveMenu.wavedata_, saveWaveMenu.wavetable_, saveWaveMenu.frame_);
//}

void SnapshotMenu::paint(juce::Graphics& g) {
    Display::clear_screen();
    if(state_ == SNAPSHOT_MENU_NONE) {

        char * title = (char *) "SNAPSHOT";

        int y_offset = 3;
        int x_offset = 1 + 2 * 4;

        Display::put_string_5x5((18 + 11 * 7) / 2 - strlen(title) * 6 / 2, y_offset, strlen(title), title);
        
        int func_width = 128 - 92;
        Display::put_string_5x5(92 + func_width / 2 - strlen("FUNC") * 6 / 2, y_offset, strlen("FUNC"), "FUNC");

        Display::invert_rectangle(0, 0, 128, 11);
        
        x_offset = 128 - 5;
        y_offset += 11;
        
        //9 * 4 + 5 * 3
        y_offset += 3;

        for(int i = 0; i < 4; i++)
        {
            char line[20];
            memset(line, 0, 20);
            snprintf(line, 20, "%*d", 2, i + snapshot_offset_ + 1);
            Display::put_string_3x5(2, y_offset + i * 12, strlen(line), line);
            
            char line2[9];
            
//            line2 = storage.GetSnapshot(i + snapshot_offset_)->name;
//            line2 = (char*)"WHOOPSIE";
            char* lines[4] = {
                (char*)"WHOOPSIE\0",
                (char*)"TEST\0",
                (char*)"TESTICL\0",
                (char*)"RIGHTO\0",
            };
            
            strncpy(line2, lines[i], 9);

            int32_t elapsed_time = system_clock.milliseconds() - ticker_timer_;

            int8_t num_chars = 6;

            if(i + snapshot_offset_ == snapshot_) {
                if(ticker_ == 0) {
                    if(elapsed_time > 1000) {
                        ticker_++;
                        ticker_timer_ = system_clock.milliseconds();
                    }
                } else if(ticker_ == (strlen(line2) - num_chars) * 9 + ((strlen(line2) - num_chars)) * 2) {
                    if(elapsed_time > 2000) {
                        ResetTicker();
                    }
                }
                else if (elapsed_time > 20) {
                    ticker_++;
                    ticker_timer_ = system_clock.milliseconds();
                }
                Display::put_string_9x9_loop(2 + 2 * 3 + 4, y_offset + i * 12 - 2, strlen(line2), line2, true, 2, num_chars, strlen(line2) > num_chars ? ticker_ : 0);
            } else {
                Display::put_string_9x9_loop(2 + 2 * 3 + 4, y_offset + i * 12 - 2, strlen(line2), line2, false, 2, num_chars, 0);
            }
        }

        y_offset = 12;
        int bar_height = 50;
        int y_cursor_offset = ((bar_height-2) * snapshot_offset_) / (USER_SNAPSHOT_COUNT + FACTORY_SNAPSHOT_COUNT - 1);
        x_offset = 12 + 11 * 7;
        Display::outline_rectangle(x_offset+1, y_offset + 1 + y_cursor_offset, 1, 3);
        Display::outline_rectangle(x_offset, y_offset, 3, bar_height);

        x_offset += 3;
        int action_width = 128 - x_offset;
        y_offset = 11;

        int action_height = 64 - y_offset;
//        x_offset = 96;

//        y_offset +=
        int center_x = x_offset + action_width / 2;
        int center_y = y_offset + action_height / 4;
        Display::put_image_22x23(center_x - 23 / 2, center_y - 22 / 2, Graphic_snapshot_menu_dice);

//        Display::outline_rectangle(center_x - 21 / 2, center_y - 21 / 2, 21, 21);
//        Display::put_string_5x5(center_x - strlen("RND") * 6, center_y - 3, strlen("RND"), "RND");
        center_y = y_offset + 3 * action_height / 4;
        Display::put_image_22x23(center_x - 23 / 2, center_y - 22 / 2, Graphic_snapshot_menu_home);

        //        Display::outline_rectangle(center_x - 21 / 2, center_y - 21/2, 21, 21);
//        Display::outline_rectangle(x_offset, y_offset, 21, 21);

        //        Display::put_image_22x23(x_offset, y_offset, Graphic_mode_menu_ab);
//        Graphic_icon_line_15x15[0][0],
//        &Graphic_icon_spectral_15x15[0][0],
//        &Graphic_icon_delete_15x15[0][0],
//        &Graphic_icon_load_15x15[0][0],
//        &Graphic_icon_save_15x15[0][0],
//    };
//    list[0]
//    for(int i = menu_selection_offset_; i < menu_selection_offset_ + 6; i++) {
//        Display::put_image_16bit(x_offset, y_offset, Graphic_icon_save_15x15, 15);

    } else {
        char * title;
        title = (char *) storage.GetSnapshot(snapshot_)->name;

        int y_offset = 5;
        int x_offset = 1 + 2 * 4;

        Display::put_string_5x5(x_offset, y_offset, strlen(title), title);
        
        Display::invert_rectangle(0, 0, 128, 15);
        
        x_offset = 20;
        y_offset = 20 + (64 - 20) / 2 - 14 * 3 / 2;
        
        if(storage.GetSnapshot(snapshot_)->factory_preset) {
            Display::put_image_16bit(x_offset, y_offset, Graphic_icon_edit_11x11, 11);
            Display::put_string_9x9(x_offset + 16, y_offset + 1, strlen("COPY"), "COPY", option_selected_ == SNAPSHOT_MENU_COPY, 3);
        }
        else {
            char *names[4] = {
                (char*)"SAVE",
                (char*)"COPY",
                (char*)"RENAME",
                (char*)"DELETE"
            };
            if(!storage.GetSnapshot(snapshot_)->is_empty) {
                names[0] = (char*)"RESAVE";
            }
            
            const uint8_t * list[] = {
                &Graphic_icon_edit_11x11[0][0],
                &Graphic_icon_copy_11x11[0][0],
                &Graphic_icon_rename_11x11[0][0],
                &Graphic_icon_delete_11x11[0][0],
            };
            
            y_offset += 7;
            for (int i = 0; i < 2; i++) {
                Display::put_image_16bit(x_offset, y_offset, (const unsigned char (*)[2])list[i + option_offset_], 11);
                Display::put_string_9x9(x_offset + 16, y_offset + 1, strlen(names[i + option_offset_]), names[i + option_offset_], option_selected_ == SNAPSHOT_MENU_SAVE + i + option_offset_, 3);

                y_offset += 14;
            }
            
            y_offset = 20 + (64 - 20) / 2 - 14 * 3 / 2;
            y_offset += 7;

            if(option_offset_ > 0) {
//                y_offset = 20 + (64 - 20) / 2 - 14 * 3 / 2;
//                y_offset -= 4;
                Display::put_image_16bit(128 - 12, y_offset, Graphic_icon_arrow_up_9x9, 9);
            }
            y_offset += 14;
            if(option_offset_ < 2) {
//                y_offset = 64 - 9;
                Display::put_image_16bit(128 - 12, y_offset, Graphic_icon_arrow_down_9x9, 9);
            }

//            Display::put_image_16bit(x_offset, y_offset, Graphic_icon_rename_11x11, 11);
//            Display::put_string_9x9(x_offset + 16, y_offset + 1, strlen("RENAME"), "RENAME", option_selected_ == MANAGE_MENU_RENAME, 3);
//
//            y_offset += 14;
//            Display::put_image_16bit(x_offset, y_offset, Graphic_icon_delete_11x11, 11);
//            Display::put_string_9x9(x_offset + 16, y_offset + 1, strlen("DELETE"), "DELETE", option_selected_ == MANAGE_MENU_DELETE, 3);
        }
    }
}
