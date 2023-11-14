/*
  ==============================================================================

    FxMenu.cpp
    Created: 12 Nov 2023 9:46:54pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Display.h"
#include "graphics.h"
#include "Globals.h"

FxMenu::FxMenu() {
    setLeftState(FX_MENU_LEFT_FX);
    setRightState(FX_MENU_RIGHT_MOD);
}

FxMenu::~FxMenu() {
    
}

bool FxMenu::handleKeyPress(const juce::KeyPress &key) {

    if(key.getKeyCode() == LEFT_ENCODER_CCW) {
        switch(left_state_) {
            case FX_MENU_LEFT_FX:
                if(effect_manager.getEffect() == &fm) {
                    effect_manager.setEffect(&phase_distortion);
                }
                else if(effect_manager.getEffect() == &phase_distortion) {
                    effect_manager.setEffect(&fm);
                }
                break;
            case FX_MENU_LEFT_DEPTH:
                effect_manager.setDepth(effect_manager.getDepth()-0.1f);
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == LEFT_ENCODER_CW) {
        switch(left_state_) {
            case FX_MENU_LEFT_FX:
                if(effect_manager.getEffect() == &fm) {
                    effect_manager.setEffect(&phase_distortion);
                }
                else if(effect_manager.getEffect() == &phase_distortion) {
                    effect_manager.setEffect(&fm);
                }
                break;
            case FX_MENU_LEFT_DEPTH:
                effect_manager.setDepth(effect_manager.getDepth()+0.1f);
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == LEFT_ENCODER_CLICK) {
        switch(left_state_) {
            case FX_MENU_LEFT_FX:
                setLeftState(FX_MENU_LEFT_DEPTH);
                break;
            case FX_MENU_LEFT_DEPTH:
                setLeftState(FX_MENU_LEFT_FX);
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == RIGHT_ENCODER_CLICK) {
        switch(right_state_) {
            case FX_MENU_RIGHT_MOD:
                if(effect_manager.getControlType() == EffectManager::MANUAL_CONTROL) {
                    break;
                }
                else if(effect_manager.getControlType() == EffectManager::EXTERNAL_MODULATOR) {
                    setRightState(FX_MENU_RIGHT_SCALE);
                    break;
                }
                else if(effect_manager.getControlType() == EffectManager::INTERNAL_MODULATOR) {
                    setRightState(FX_MENU_RIGHT_WAVE);
                    break;
                }
                break;
            case FX_MENU_RIGHT_SCALE:
                setRightState(FX_MENU_RIGHT_RANGE);
                break;
            case FX_MENU_RIGHT_WAVE:
                setRightState(FX_MENU_RIGHT_SYNC);
                break;
            case FX_MENU_RIGHT_SYNC:
                if(effect_manager.getSync()) {
                    setRightState(FX_MENU_RIGHT_RATIO);
                    break;
                } else {
                    setRightState(FX_MENU_RIGHT_FREQUENCY);
                    break;
                }
                break;
            case FX_MENU_RIGHT_RATIO:
            case FX_MENU_RIGHT_FREQUENCY:
            case FX_MENU_RIGHT_RANGE:
                setRightState(FX_MENU_RIGHT_MOD);
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

void FxMenu::paint(juce::Graphics& g) {
    Display::clear_screen();
    
    int y_offset = 4;
    int x_offset = 64 - (23+2) * 2;
    int row = 0;
    int col = 0;
    char *caption;
    char *effectName;
    if(effect_manager.getEffect()==&fm)
    {
        effectName = (char*)"FM";
    }
    else if(effect_manager.getEffect()==&phase_distortion)
    {
        effectName = (char*)"PHDIST";
    }
//    else if(effect_manager.getEffect()==&fm)
//    {
//        effectName = "FM";
//    }
    int row_height = 9;
    x_offset = 5;
    Display::put_string_9x9(x_offset, y_offset, strlen("FX"), "FX");
    
    int centered_effect_name = (69 + 5 + 10 * 2) / 2 - strlen(effectName) * 6 / 2;
    Display::put_string_5x5(centered_effect_name, y_offset + (row_height-5) / 2, strlen(effectName), effectName, left_state_ == FX_MENU_LEFT_FX);

    
    
    x_offset += 64;
    Display::put_string_9x9(x_offset, y_offset, strlen("MOD"), "MOD");

    int graph_height = 22;
    int graph_y_offset = y_offset + row_height + 1;
    Display::outline_rectangle(0, graph_y_offset, 64 - 3, graph_height);
    Display::outline_rectangle(64, graph_y_offset, 64 - 3, graph_height);
    
    uint16_t tune = adc.getChannel(0);
    uint16_t fx_amount = adc.getChannel(1);
    uint16_t fx = adc.getChannel(2);
    uint16_t morph = adc.getChannel(3);
    
    Display::Draw_Wave(1, graph_y_offset, 64-3-1, graph_height, engine.GetWaveformData( tune,  fx_amount,  fx,  morph));
    Display::Draw_Wave(64+1, graph_y_offset, 64-3-1, graph_height, engine.GetWaveformData( tune,  fx_amount,  fx,  morph));
    
    int depth_y_offset = graph_y_offset + graph_height + 2;
    Display::put_string_5x5(1, depth_y_offset, strlen("DEPTH:"), "DEPTH:");

    Display::put_string_5x5(strlen("DEPTH:")*6 + 1, depth_y_offset, strlen("25%"), "25%", left_state_ == FX_MENU_LEFT_DEPTH);

}
