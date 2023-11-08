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
    setState(MainMenu::lastState);
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
    
    if(key.getKeyCode() == juce::KeyPress::leftKey) {
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
    if(key.getKeyCode() == juce::KeyPress::rightKey) {
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
    if(key.getKeyCode() == juce::KeyPress::returnKey) {
        switch(currentState) {
            case SUBOSCILLATOR_CONFIG:
                context.setState(&modeMenu);
                break;
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

    int row = 0;
    int col = 0;
    
    Display::put_image_22x23(col*(23+2), row*(22+2), Graphic_main_menu_wave_design);

    col++;
    Display::put_image_22x23(col*(23+2), row*(22+2), Graphic_main_menu_mode);

    col++;
    Display::put_image_22x23(col*(23+2), row*(22+2), Graphic_main_menu_wave_design);

    col++;
    Display::put_image_22x23(col*(23+2), row*(22+2), Graphic_main_menu_wave_design);

    
    row++;
    col=0;
    Display::put_image_22x23(col*(23+2), row*(22+2), Graphic_main_menu_wave_design);

    col++;
    Display::put_image_22x23(col*(23+2), row*(22+2), Graphic_main_menu_wave_design);

    col++;
    Display::put_image_22x23(col*(23+2), row*(22+2), Graphic_main_menu_wave_design);

    col++;
    Display::put_image_22x23(col*(23+2), row*(22+2), Graphic_main_menu_wave_design);
    
    switch(currentState) {
        case MAIN_WAVE_DESIGN:
            col = 0; row = 0;
            Display::invert_rectangle(col*(23+2), row*(22+2), 23, 22);
            break;
        case MODE_SELECT:
            col = 1; row = 0;
            Display::invert_rectangle(col*(23+2), row*(22+2), 23, 22);
            break;
        case FX_MANAGEMENT:
            col = 2; row = 0;
            Display::invert_rectangle(col*(23+2), row*(22+2), 23, 22);
            break;
        case SUBOSCILLATOR_CONFIG:
            col = 3; row = 0;
            Display::invert_rectangle(col*(23+2), row*(22+2), 23, 22);
            break;
        case PLAYBACK_MONITORING:
            col = 0; row = 1;
            Display::invert_rectangle(col*(23+2), row*(22+2), 23, 22);
            break;
        case SNAPSHOTS_LIST:
            col = 1; row = 1;
            Display::invert_rectangle(col*(23+2), row*(22+2), 23, 22);
            break;
        case WAVETABLE_MANAGEMENT:
            col = 2; row = 1;
            Display::invert_rectangle(col*(23+2), row*(22+2), 23, 22);
            break;
        case MODULE_SETUP_CONFIG:
            col = 3; row = 1;
            Display::invert_rectangle(col*(23+2), row*(22+2), 23, 22);
            break;
        default:
            break;
    }
}

MainMenu::MainMenuState MainMenu::lastState = MAIN_WAVE_DESIGN;
