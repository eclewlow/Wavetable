/*
  ==============================================================================

    IOConfiguration.cpp
    Created: 14 Nov 2023 4:42:37pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Display.h"
#include "graphics.h"
#include "Globals.h"

IOConfigurationMenu::IOConfigurationMenu() {
    setState(IO_CONFIG_MENU_INPUT);
}

IOConfigurationMenu::~IOConfigurationMenu() {
    
}

bool IOConfigurationMenu::handleKeyPress(const juce::KeyPress &key) {
//    DISPLAY_MENU_BRIGHTNESS,
//    DISPLAY_MENU_CONTRAST,
//    DISPLAY_MENU_INVERT,
//    DISPLAY_MENU_SCOPE,

    if(key.getKeyCode() == BACK_BUTTON) {
        context.setState(&deviceConfigurationMenu);
    }
    else if(key.getKeyCode() == LEFT_ENCODER_CCW) {
        state_ = std::clamp<int8_t>(state_ - 1, IO_CONFIG_MENU_INPUT, IO_CONFIG_MENU_BIAS);
    }
    else if(key.getKeyCode() == LEFT_ENCODER_CW) {
        state_ = std::clamp<int8_t>(state_ + 1, IO_CONFIG_MENU_INPUT, IO_CONFIG_MENU_BIAS);
    }
    else if(key.getKeyCode() == RIGHT_ENCODER_CCW) {
        switch(state_) {
            case IO_CONFIG_MENU_INPUT: {
                input_ = std::clamp<int8_t>(input_ - 1, IO_CONFIG_PITCH, IO_CONFIG_MORPH);
                break;
            }
            case IO_CONFIG_MENU_GAIN: {
                break;
            }
            case IO_CONFIG_MENU_BIAS: {
                break;
            }
            default:
                break;
        }
    }
    else if(key.getKeyCode() == RIGHT_ENCODER_CW) {
    }
    else if(key.getKeyCode() == LEFT_ENCODER_CLICK) {
    }
    return true;
}

void IOConfigurationMenu::paint(juce::Graphics& g) {
    Display::clear_screen();

    int x_offset = (64) / 2;
    int y_offset = 10;
    Display::put_string_9x9(x_offset - strlen("IO") * 10 / 2, y_offset, strlen("IO"), "IO");
    
    x_offset = 0;
    y_offset += 16;
    Display::put_string_5x5(x_offset, y_offset, strlen("INPUT:"), "INPUT:");
    char *line;
    switch(input_) {
        case IO_CONFIG_PITCH:
            line = (char* ) "PITCH";
            break;
        case IO_CONFIG_FX_AMOUNT:
            line = (char* ) "FX AMOUNT";
            break;
        case IO_CONFIG_FX:
            line = (char* ) "FX";
            break;
        case IO_CONFIG_MORPH:
            line = (char* ) "MORPH";
            break;
        default:
            break;
    }
    Display::put_string_5x5(x_offset + strlen("INPUT:") * 6, y_offset, strlen(line), line, state_ == IO_CONFIG_MENU_INPUT);

    y_offset += 7;
    Display::put_string_5x5(x_offset+6, y_offset, strlen("GAIN:"), "GAIN:");
    switch(user_settings.getIOGain(input_)) {
        case UserSettings::IO_CONFIG_GAIN_1V:
            line = (char* ) "+1V";
            break;
        case UserSettings::IO_CONFIG_GAIN_2V5:
            line = (char* ) "+2.5V";
            break;
        case UserSettings::IO_CONFIG_GAIN_5V:
            line = (char* ) "+5V";
            break;
        case UserSettings::IO_CONFIG_GAIN_10V:
            line = (char* ) "+10V";
            break;
        default:
            break;
    }
    Display::put_string_5x5(x_offset + strlen("GAIN:") * 6, y_offset, strlen(line), line, state_ == IO_CONFIG_MENU_GAIN);

    
    y_offset += 7;
    Display::put_string_5x5(x_offset+6, y_offset, strlen("BIAS:"), "BIAS:");
}
