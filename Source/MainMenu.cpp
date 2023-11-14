/*
 ==============================================================================
 
 MainMenu.cpp
 Created: 7 Nov 2023 1:30:39pm
 Author:  Eugene Clewlow
 
 ==============================================================================
 */

#include "Display.h"
#include "graphics.h"
#include "Globals.h"

MainMenu::MainMenu() {
    setState(MAIN_WAVE_DESIGN);
}

MainMenu::~MainMenu() {
    
}

bool MainMenu::handleKeyPress(const juce::KeyPress &key) {
    //    MAIN_WAVE_DESIGN,
    //    MODE_SELECT,
    //    FX_MANAGEMENT,
    //    SUBOSCILLATOR_CONFIG,
    //    PLAYBACK_MONITORING,
    //    SNAPSHOTS_LIST,
    //    WAVETABLE_MANAGEMENT,
    //    MODULE_SETUP_CONFIG
    
    if(key.getKeyCode() == LEFT_ENCODER_CCW) {
        switch(currentState) {
            case MAIN_WAVE_DESIGN:
                break;
            case MODE_SELECT:
                setState(MAIN_WAVE_DESIGN);
                break;
            case FX_MANAGEMENT:
                setState(MODE_SELECT);
                break;
            case SUBOSCILLATOR_CONFIG:
                setState(FX_MANAGEMENT);
                break;
            case PLAYBACK_MONITORING:
                setState(SUBOSCILLATOR_CONFIG);
                break;
            case SNAPSHOTS_LIST:
                setState(PLAYBACK_MONITORING);
                break;
            case WAVETABLE_MANAGEMENT:
                setState(SNAPSHOTS_LIST);
                break;
            case MODULE_SETUP_CONFIG:
                setState(WAVETABLE_MANAGEMENT);
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == LEFT_ENCODER_CW) {
        switch(currentState) {
            case MAIN_WAVE_DESIGN:
                setState(MODE_SELECT);
                break;
            case MODE_SELECT:
                setState(FX_MANAGEMENT);
                break;
            case FX_MANAGEMENT:
                setState(SUBOSCILLATOR_CONFIG);
                break;
            case SUBOSCILLATOR_CONFIG:
                setState(PLAYBACK_MONITORING);
                break;
            case PLAYBACK_MONITORING:
                setState(SNAPSHOTS_LIST);
                break;
            case SNAPSHOTS_LIST:
                setState(WAVETABLE_MANAGEMENT);
                break;
            case WAVETABLE_MANAGEMENT:
                setState(MODULE_SETUP_CONFIG);
                break;
            case MODULE_SETUP_CONFIG:
                break;
            default:
                break;
        }
    }
    //    printf("%d, %d\n", key.getKeyCode(), juce::KeyPress::returnKey, currentState, );
    if(key.getKeyCode() == LEFT_ENCODER_CLICK) {
        switch(currentState) {
            case MODE_SELECT:
                context.setState(&modeMenu);
                break;
            case PLAYBACK_MONITORING:
                context.setState(&oscilloscope);
                //            case MAIN_WAVE_DESIGN:
                //                getContext()->setState(new ModeMenu());
                //                break;
                //            case MODE_SELECT:
                //                setState(FX_MANAGEMENT);
                //                break;
                //            case FX_MANAGEMENT:
                //                setState(SUBOSCILLATOR_CONFIG);
                //                break;
                //            case SUBOSCILLATOR_CONFIG:
                //                setState(PLAYBACK_MONITORING);
                //                break;
                //            case PLAYBACK_MONITORING:
                //                setState(SNAPSHOTS_LIST);
                //                break;
                //            case SNAPSHOTS_LIST:
                //                setState(WAVETABLE_MANAGEMENT);
                //                break;
                //            case WAVETABLE_MANAGEMENT:
                //                setState(MODULE_SETUP_CONFIG);
                //                break;
                //            case MODULE_SETUP_CONFIG:
                //                break;
            default:
                break;
        }
    }
    return true;
}

void MainMenu::paint(juce::Graphics& g) {
    Display::clear_screen();
    
    int y_offset = 4;
    int x_offset = 64 - (23+2) * 2;
    int row = 0;
    int col = 0;
    char *caption;
    
    switch(currentState) {
        case MAIN_WAVE_DESIGN:
            caption = (char*)"AB WAVE";
            break;
        case MODE_SELECT:
            caption = (char*)"MODE";
            break;
        case FX_MANAGEMENT:
            caption = (char*)"FX";
            break;
        case SUBOSCILLATOR_CONFIG:
            caption = (char*)"SUB";
            break;
        case PLAYBACK_MONITORING:
            caption = (char*)"SCOPE";
            break;
        case SNAPSHOTS_LIST:
            caption = (char*)"SNAPSHOT";
            break;
        case WAVETABLE_MANAGEMENT:
            caption = (char*)"MANAGE";
            break;
        case MODULE_SETUP_CONFIG:
            caption = (char*)"CONFIG";
            break;
        default:
            break;
    }
    //    Display::put_string_5x5(0,0,16,"ABCDEFGHIJKLMNOP");
    //    Display::put_string_9x9(0 + 1 + 1,
    //                               0 + 1 + 1,
    //                               8,
    //                               "ABCDEFGH");
    //    Display::put_string_9x9(0 + 1 + 1,
    //                               10 + 1 + 1,
    //                               8,
    //                               "IJKLMNOP");
    //    Display::put_string_9x9(0 + 1 + 1,
    //                               20 + 1 + 1,
    //                               8,
    //                               "QRSTUVWX");
    //    Display::put_string_9x9(0 + 1 + 1,
    //                               30 + 1 + 1,
    //                               8,
    //                               "YZ012345");
    //    Display::put_string_9x9(0 + 1 + 1,
    //                               40 + 1 + 1,
    //                               6,
    //                               "6789_-");
    
    //    Display::put_image_16bit(100, 2, Graphic_icon_arrow_9x9, 9);
    //
    //    Display::put_image_16bit(100, 13, Graphic_icon_wave_hump, 15);
    //    Display::put_image_16bit(100, 30, Graphic_icon_wave_square, 15);
    //    Display::put_image_16bit(100, 47, Graphic_icon_delete_15x15, 15);
    //    return;
    //
    Display::put_string_9x9(64-strlen(caption)*10/2,64-11,strlen(caption),caption);
    
    //    Display::put_string_5x5(0,0,1,"A");
    //    Display::put_string_5x5(10,0,1,"B");
    //    Display::put_string_5x5(20,0,1,"CZ");
    
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_main_menu_ab);
    
    col++;
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_main_menu_mode_select);
    
    col++;
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_main_menu_fx);
    
    col++;
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_main_menu_sub);
    
    
    row++;
    col=0;
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_main_menu_oscilloscope);
    
    col++;
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_main_menu_snapshots);
    
    col++;
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_main_menu_wave_management);
    
    col++;
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_main_menu_setup);
    
    switch(currentState) {
        case MAIN_WAVE_DESIGN:
            col = 0; row = 0;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        case MODE_SELECT:
            col = 1; row = 0;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        case FX_MANAGEMENT:
            col = 2; row = 0;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        case SUBOSCILLATOR_CONFIG:
            col = 3; row = 0;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        case PLAYBACK_MONITORING:
            col = 0; row = 1;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        case SNAPSHOTS_LIST:
            col = 1; row = 1;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        case WAVETABLE_MANAGEMENT:
            col = 2; row = 1;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        case MODULE_SETUP_CONFIG:
            col = 3; row = 1;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        default:
            break;
    }
}
