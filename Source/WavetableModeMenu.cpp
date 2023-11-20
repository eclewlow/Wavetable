/*
  ==============================================================================

    WavetableMenu.cpp
    Created: 18 Nov 2023 8:27:59pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Display.h"
#include "graphics.h"
#include "Globals.h"

WavetableModeMenu::WavetableModeMenu() {
    setState(CONTROL_STATUS_STATE_NONE);
}

WavetableModeMenu::~WavetableModeMenu() {
    
}

bool WavetableModeMenu::handleKeyPress(const juce::KeyPress &key) {
    if(key.getKeyCode() == LEFT_ENCODER_CCW) {
        switch(currentState) {
            default:
                break;
        }
    }
    if(key.getKeyCode() == LEFT_ENCODER_CW) {
        switch(currentState) {
            default:
                break;
        }
    }
    if(key.getKeyCode() == LEFT_ENCODER_CLICK) {
        switch(currentState) {
//            case CONTROL_STATUS_STATE_NONE:
//                context.setState(&oscilloscope);
//                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == BACK_BUTTON) {
        if(back_menu_)
            context.setState(back_menu_);
        else
            context.setState(&mainMenu);
    }

    return true;
}

void WavetableModeMenu::paint(juce::Graphics& g) {
    uint16_t morph = adc.getChannel(3);

    Display::clear_screen();
    Display::Draw_Wave(0, 0, 128, 64, wavetableEngine.GetWaveformDataNoFX(morph));
}
