/*
  ==============================================================================

    Oscilloscope.cpp
    Created: 13 Nov 2023 6:13:45pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Display.h"
#include "graphics.h"
#include "Globals.h"

Oscilloscope::Oscilloscope() {
    setState(OSCILLOSCOPE_STATE_NONE);
}

Oscilloscope::~Oscilloscope() {
    
}

bool Oscilloscope::handleKeyPress(const juce::KeyPress &key) {
//    FX_MENU_EDIT_NONE
//    FX_MENU_EDIT_DEPTH,
//    FX_MENU_EDIT_RATIO,
//    FX_MENU_EDIT_SYNC,
//    FX_MENU_EDIT_WAVE,

    
    if(key.getKeyCode() == LEFT_ENCODER_CCW) {
        switch(currentState) {
            case OSCILLOSCOPE_STATE_NONE:
                break;
//            case MODE_SELECT:
//                setState(MAIN_WAVE_DESIGN);
//                break;
//            case FX_MANAGEMENT:
//                setState(MODE_SELECT);
//                break;
//            case SUBOSCILLATOR_CONFIG:
//                setState(FX_MANAGEMENT);
//                break;
//            case PLAYBACK_MONITORING:
//                setState(SUBOSCILLATOR_CONFIG);
//                break;
//            case SNAPSHOTS_LIST:
//                setState(PLAYBACK_MONITORING);
//                break;
//            case WAVETABLE_MANAGEMENT:
//                setState(SNAPSHOTS_LIST);
//                break;
//            case MODULE_SETUP_CONFIG:
//                setState(WAVETABLE_MANAGEMENT);
//                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == LEFT_ENCODER_CW) {
        switch(currentState) {
//            case MAIN_WAVE_DESIGN:
//                setState(MODE_SELECT);
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
    if(key.getKeyCode() == LEFT_ENCODER_CLICK) {
//        uint16_t tune = adc.getChannel(0);
//        uint16_t fx_amount = adc.getChannel(1);
//        uint16_t fx = adc.getChannel(2);
//        uint16_t morph = adc.getChannel(3);
//
//        int16_t* wavedata = engine.GetWaveformData( tune,  fx_amount,  fx,  morph);
//        printf("=======================");
//        for(int i = 0; i < 2048; i++) {
//            printf("%i\n", wavedata[i]);
//        }
//        printf("=======================");

        switch(currentState) {
            case OSCILLOSCOPE_STATE_NONE:
//                context.setState(&modeMenu);
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == BACK_BUTTON) {
        switch(currentState) {
            case OSCILLOSCOPE_STATE_NONE:
                context.setState(&mainMenu);
                break;
            default:
                break;
        }
    }

    return true;
}

void Oscilloscope::paint(juce::Graphics& g) {
    Display::clear_screen();
    
    int y_offset = 4;
    int x_offset = 64 - (23+2) * 2;
    int row = 0;
    int col = 0;
    char *caption;
    
    switch(currentState) {
//        case MAIN_WAVE_DESIGN:
//            caption = (char*)"AB WAVE";
//            break;
//        case MODE_SELECT:
//            caption = (char*)"MODE";
//            break;
//        case FX_MANAGEMENT:
//            caption = (char*)"FX";
//            break;
//        case SUBOSCILLATOR_CONFIG:
//            caption = (char*)"SUB";
//            break;
//        case PLAYBACK_MONITORING:
//            caption = (char*)"SCOPE";
//            break;
//        case SNAPSHOTS_LIST:
//            caption = (char*)"SNAPSHOT";
//            break;
//        case WAVETABLE_MANAGEMENT:
//            caption = (char*)"MANAGE";
//            break;
//        case MODULE_SETUP_CONFIG:
//            caption = (char*)"CONFIG";
//            break;
        default:
            break;
    }
    uint16_t tune = adc.getChannel(0);
    uint16_t fx_amount = adc.getChannel(1);
    uint16_t fx = adc.getChannel(2);
    uint16_t morph = adc.getChannel(3);
    
    int x = 0;
    int width = 128;
    int y = 5;
    int height = 40;
    Display::outline_rectangle(x, y, width, height);
    Display::Draw_Wave(x, y, width, height, engine.GetWaveformData( tune,  fx_amount,  fx,  morph), true);
}
