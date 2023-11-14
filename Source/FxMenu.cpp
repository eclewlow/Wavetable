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
    
    
    
    if(key.getKeyCode() == RIGHT_ENCODER_CCW) {
        switch(right_state_) {
            case FX_MENU_RIGHT_MOD:
                if(effect_manager.getControlType() == EffectManager::MANUAL_CONTROL)
                    effect_manager.setControlType(EffectManager::EXTERNAL_MODULATOR);
                else if(effect_manager.getControlType() == EffectManager::INTERNAL_MODULATOR)
                    effect_manager.setControlType(EffectManager::MANUAL_CONTROL);
                else if(effect_manager.getControlType() == EffectManager::EXTERNAL_MODULATOR)
                    effect_manager.setControlType(EffectManager::INTERNAL_MODULATOR);
                break;
            case FX_MENU_RIGHT_SYNC:
                effect_manager.setSync(!effect_manager.getSync());
                break;

            case FX_MENU_RIGHT_WAVE:
                if(effect_manager.getOscillatorShape() == EffectManager::SINE_SHAPE)
                {
                    effect_manager.setOscillatorShape(EffectManager::SNH_SHAPE);
                }
                else if(effect_manager.getOscillatorShape() == EffectManager::TRIANGLE_SHAPE)
                {
                    effect_manager.setOscillatorShape(EffectManager::SINE_SHAPE);
                }
                else if(effect_manager.getOscillatorShape() == EffectManager::RAMP_SHAPE)
                {
                    effect_manager.setOscillatorShape(EffectManager::TRIANGLE_SHAPE);
                }
                else if(effect_manager.getOscillatorShape() == EffectManager::SAWTOOTH_SHAPE)
                {
                    effect_manager.setOscillatorShape(EffectManager::RAMP_SHAPE);
                }
                else if(effect_manager.getOscillatorShape() == EffectManager::SQUARE_SHAPE)
                {
                    effect_manager.setOscillatorShape(EffectManager::SAWTOOTH_SHAPE);
                }
                else if(effect_manager.getOscillatorShape() == EffectManager::SNH_SHAPE)
                {
                    effect_manager.setOscillatorShape(EffectManager::SQUARE_SHAPE);
                }
                break;
            case FX_MENU_RIGHT_RATIO:
                effect_manager.setRatio(effect_manager.getRatio()-1);
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == RIGHT_ENCODER_CW) {
        switch(right_state_) {
            case FX_MENU_RIGHT_MOD:
                if(effect_manager.getControlType() == EffectManager::MANUAL_CONTROL)
                    effect_manager.setControlType(EffectManager::INTERNAL_MODULATOR);
                else if(effect_manager.getControlType() == EffectManager::INTERNAL_MODULATOR)
                    effect_manager.setControlType(EffectManager::EXTERNAL_MODULATOR);
                else if(effect_manager.getControlType() == EffectManager::EXTERNAL_MODULATOR)
                    effect_manager.setControlType(EffectManager::MANUAL_CONTROL);
                break;
            case FX_MENU_RIGHT_SYNC:
                effect_manager.setSync(!effect_manager.getSync());
                break;
            case FX_MENU_RIGHT_WAVE:
                if(effect_manager.getOscillatorShape() == EffectManager::SINE_SHAPE)
                {
                    effect_manager.setOscillatorShape(EffectManager::TRIANGLE_SHAPE);
                }
                else if(effect_manager.getOscillatorShape() == EffectManager::TRIANGLE_SHAPE)
                {
                    effect_manager.setOscillatorShape(EffectManager::RAMP_SHAPE);
                }
                else if(effect_manager.getOscillatorShape() == EffectManager::RAMP_SHAPE)
                {
                    effect_manager.setOscillatorShape(EffectManager::SAWTOOTH_SHAPE);
                }
                else if(effect_manager.getOscillatorShape() == EffectManager::SAWTOOTH_SHAPE)
                {
                    effect_manager.setOscillatorShape(EffectManager::SQUARE_SHAPE);
                }
                else if(effect_manager.getOscillatorShape() == EffectManager::SQUARE_SHAPE)
                {
                    effect_manager.setOscillatorShape(EffectManager::SNH_SHAPE);
                }
                else if(effect_manager.getOscillatorShape() == EffectManager::SNH_SHAPE)
                {
                    effect_manager.setOscillatorShape(EffectManager::SINE_SHAPE);
                }
                break;
            case FX_MENU_RIGHT_RATIO:
                effect_manager.setRatio(effect_manager.getRatio()+1);
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
    
    int row_height = 9;
    x_offset = 5;
    Display::put_string_9x9(x_offset, y_offset, strlen("FX"), "FX");
    
    int centered_effect_name = (69 + 5 + 10 * 2) / 2 - strlen(effectName) * 6 / 2;
    Display::put_string_5x5(centered_effect_name, y_offset + (row_height-5) / 2, strlen(effectName), effectName, left_state_ == FX_MENU_LEFT_FX);
    
    
    
    x_offset += 64;
    Display::put_string_9x9(x_offset, y_offset, strlen("MOD"), "MOD");
    
    char * controlName;
    if(effect_manager.getControlType() == EffectManager::MANUAL_CONTROL)
    {
        controlName = (char*)"POT";
    }
    else if(effect_manager.getControlType() == EffectManager::INTERNAL_MODULATOR)
    {
        controlName = (char*)"OSC";
    }
    else if(effect_manager.getControlType() == EffectManager::EXTERNAL_MODULATOR)
    {
        controlName = (char*)"IN";
    }
    
    int centered_control_name = (64 + 5 + 10 * 3 + 128) / 2 - strlen(controlName) * 6 / 2;
    Display::put_string_5x5(centered_control_name, y_offset + (row_height-5) / 2, strlen(controlName), controlName, right_state_ == FX_MENU_RIGHT_MOD);
    
    int graph_height = 22;
    int graph_y_offset = y_offset + row_height + 1;
    Display::outline_rectangle(0, graph_y_offset, 64 - 3, graph_height);
    Display::outline_rectangle(64, graph_y_offset, 64 - 3, graph_height);
    
    uint16_t tune = adc.getChannel(0);
    uint16_t fx_amount = adc.getChannel(1);
    uint16_t fx = adc.getChannel(2);
    uint16_t morph = adc.getChannel(3);

    int depth_y_offset = graph_y_offset + graph_height + 3;
    Display::put_string_5x5(1, depth_y_offset, strlen("DEPTH:"), "DEPTH:");
    
    char depth_string[5];
    
    snprintf(depth_string, 5, "%d%%", static_cast<uint8_t>(effect_manager.getDepth() * 100.0f));
    
    Display::put_string_5x5(strlen("DEPTH:")*6 + 1, depth_y_offset, strlen(depth_string), depth_string, left_state_ == FX_MENU_LEFT_DEPTH);

    Display::Draw_Wave(1, graph_y_offset, 64-3-1, graph_height, engine.GetWaveformData( tune,  fx_amount,  fx,  morph));

    if(effect_manager.getControlType() == EffectManager::MANUAL_CONTROL) {
        char pot_value_string[4];
        snprintf(pot_value_string, 4, "%d", (fx * 100) / 4095);
        Display::put_string_9x9(64 + (64-3) / 2 - strlen(pot_value_string) * 10 / 2, graph_y_offset + graph_height / 2 - 4, strlen(pot_value_string), pot_value_string);
    }
    else if(effect_manager.getControlType() == EffectManager::INTERNAL_MODULATOR) {
        Display::Draw_Wave(64+1, graph_y_offset, 64-3-1, graph_height, engine.GetWaveformData( tune,  fx_amount,  fx,  morph));
        
        char * waveName;
        if(effect_manager.getOscillatorShape() == EffectManager::SINE_SHAPE)
        {
            waveName = (char*)"SINE";
        }
        else if(effect_manager.getOscillatorShape() == EffectManager::TRIANGLE_SHAPE)
        {
            waveName = (char*)"TRI";
        }
        else if(effect_manager.getOscillatorShape() == EffectManager::SNH_SHAPE)
        {
            waveName = (char*)"S&H";
        }
        else if(effect_manager.getOscillatorShape() == EffectManager::SQUARE_SHAPE)
        {
            waveName = (char*)"SQUA";
        }
        else if(effect_manager.getOscillatorShape() == EffectManager::RAMP_SHAPE)
        {
            waveName = (char*)"RAMP";
        }
        else if(effect_manager.getOscillatorShape() == EffectManager::SAWTOOTH_SHAPE)
        {
            waveName = (char*)"SAW";
        }
        
        char rs_strings[5];
        row_height = 7;
        Display::put_string_5x5(64, depth_y_offset, strlen(" WAVE:"), " WAVE:");
        Display::put_string_5x5(64 + 6*6+1, depth_y_offset, strlen(waveName), waveName, right_state_ == FX_MENU_RIGHT_WAVE);
        depth_y_offset += row_height;
        
        Display::put_string_5x5(64, depth_y_offset, strlen(" SYNC:"), " SYNC:");
        snprintf(rs_strings, 5, "%s", effect_manager.getSync() ? "ON":"OFF");
        Display::put_string_5x5(64 + 6*6+1, depth_y_offset, strlen(rs_strings), rs_strings, right_state_ == FX_MENU_RIGHT_SYNC);
        depth_y_offset += row_height;
        
        if(effect_manager.getSync()) {
            Display::put_string_5x5(64, depth_y_offset, strlen("RATIO:"), "RATIO:");
            snprintf(rs_strings, 5, "X%d", effect_manager.getRatio());
            Display::put_string_5x5(64 + 6*6+1, depth_y_offset, strlen(rs_strings), rs_strings, right_state_ == FX_MENU_RIGHT_RATIO);
        } else {
            float frequency = pow(2, ((15.0 * fx) / 4095.0) - 3.0f);
            
            Display::put_string_5x5(64, depth_y_offset, strlen(" FREQ:"), " FREQ:");
            
            if(frequency < 10.0f)
                snprintf(rs_strings, 5, "%.2f", frequency);
            else
                snprintf(rs_strings, 5, "%.0f", frequency);
            Display::put_string_5x5(64 + 6*6+1, depth_y_offset, strlen(rs_strings), rs_strings, right_state_ == FX_MENU_RIGHT_FREQUENCY);
        }
    }
}
