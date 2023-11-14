/*
 ==============================================================================
 
 ModeMenu.cpp
 Created: 7 Nov 2023 4:54:56pm
 Author:  Eugene Clewlow
 
 ==============================================================================
 */

#include "Display.h"
#include "graphics.h"
#include "Globals.h"

ModeMenu::ModeMenu() {
    setState(MODE_AB);
}

ModeMenu::~ModeMenu() {
    
}

bool ModeMenu::handleKeyPress(const juce::KeyPress &key) {
    //    MODE_AB,
    //    MODE_WAVETABLE,
    //    MODE_MATRIX,
    //    MODE_DRUM,
    
    if(key.getKeyCode() == LEFT_ENCODER_CCW) {
        switch(currentState) {
            case MODE_AB:
                break;
            case MODE_WAVETABLE:
                setState(MODE_AB);
                break;
            case MODE_MATRIX:
                setState(MODE_WAVETABLE);
                break;
            case MODE_DRUM:
                setState(MODE_MATRIX);
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == LEFT_ENCODER_CW) {
        switch(currentState) {
            case MODE_AB:
                setState(MODE_WAVETABLE);
                break;
            case MODE_WAVETABLE:
                setState(MODE_MATRIX);
                break;
            case MODE_MATRIX:
                setState(MODE_DRUM);
                break;
            case MODE_DRUM:
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == LEFT_ENCODER_CLICK) {
        switch(currentState) {
                //            case MODE_AB:
                //                setState(MODE_WAVETABLE);
                //                break;
                //            case MODE_WAVETABLE:
                //                setState(MODE_MATRIX);
                //                break;
                //            case MODE_MATRIX:
                //                setState(MODE_DRUM);
                //                break;
            case MODE_DRUM:
                context.setState(&mainMenu);
                break;
            default:
                break;
                
        }
    }
    if(key.getKeyCode() == BACK_BUTTON) {
        context.setState(&mainMenu);
    }
    
    return true;
}

void ModeMenu::paint(juce::Graphics& g) {
    Display::clear_screen();
    
    int y_offset = 32 - (22+2) / 2;
    int x_offset = 64 - (23+2) * 2;
    int row = 0;
    int col = 0;
    char *caption;
    
    //    MODE_AB,
    //    MODE_WAVETABLE,
    //    MODE_MATRIX,
    //    MODE_DRUM,
    
    switch(currentState) {
        case MODE_AB:
            caption = (char*)"AB WAVE";
            break;
        case MODE_WAVETABLE:
            caption = (char*)"WAVETABLE";
            break;
        case MODE_MATRIX:
            caption = (char*)"MATRIX";
            break;
        case MODE_DRUM:
            caption = (char*)"DRUM";
            break;
        default:
            break;
    }
    
    Display::put_string_9x9(64-4*10/2,5,strlen(caption),"MODE");
    
    Display::put_string_9x9(64-strlen(caption)*10/2,64-11,strlen(caption),caption);
    
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_mode_menu_ab);
    
    col++;
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_mode_menu_wavetable);
    
    col++;
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_mode_menu_wave_matrix);
    
    col++;
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_mode_menu_drum);
    
    
    switch(currentState) {
        case MODE_AB:
            col = 0; row = 0;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        case MODE_WAVETABLE:
            col = 1; row = 0;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        case MODE_MATRIX:
            col = 2; row = 0;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        case MODE_DRUM:
            col = 3; row = 0;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
        default:
            break;
    }
}
