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
    }
    else if(key.getKeyCode() == LEFT_ENCODER_CW) {
    }
    else if(key.getKeyCode() == LEFT_ENCODER_CLICK) {
    }
    return true;
}

void IOConfigurationMenu::paint(juce::Graphics& g) {
    Display::clear_screen();

    int y_offset = 0;
    Display::put_string_9x9(0, y_offset, strlen("IO"), "IO");
    
    y_offset += 10;
    Display::put_string_5x5(0, y_offset, strlen("INPUT:"), "INPUT:");

    y_offset += 7;
    Display::put_string_5x5(0, y_offset, strlen("GAIN:"), "GAIN:");

    y_offset += 7;
    Display::put_string_5x5(0, y_offset, strlen("BIAS:"), "BIAS:");
}
