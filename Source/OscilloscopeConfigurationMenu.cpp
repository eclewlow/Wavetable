/*
  ==============================================================================

    OscilloscopeConfigurationMenu.cpp
    Created: 14 Nov 2023 4:42:15pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Display.h"
#include "graphics.h"
#include "Globals.h"

OscilloscopeConfigurationMenu::OscilloscopeConfigurationMenu() {
}

OscilloscopeConfigurationMenu::~OscilloscopeConfigurationMenu() {
    
}

bool OscilloscopeConfigurationMenu::handleKeyPress(const juce::KeyPress &key) {

    if(key.getKeyCode() == BACK_BUTTON) {
        context.setState(&deviceConfigurationMenu);
    }
    else if(key.getKeyCode() == LEFT_ENCODER_CCW) {
        user_settings.setMorphSetting(user_settings.getMorphSetting()==UserSettings::SETTING_MORPH_SMOOTH ? UserSettings::SETTING_MORPH_DISCRETE:UserSettings::SETTING_MORPH_SMOOTH);
    }
    else if(key.getKeyCode() == LEFT_ENCODER_CW) {
        user_settings.setMorphSetting(user_settings.getMorphSetting()==UserSettings::SETTING_MORPH_SMOOTH ? UserSettings::SETTING_MORPH_DISCRETE:UserSettings::SETTING_MORPH_SMOOTH);
    }
    else if(key.getKeyCode() == LEFT_ENCODER_CLICK) {
        context.setState(&deviceConfigurationMenu);
    }
    return true;
}

void OscilloscopeConfigurationMenu::paint(juce::Graphics& g) {
    Display::clear_screen();
    
    int y_offset = 5;
    
    Display::put_string_9x9(128 / 2 - strlen("OSC") * 10 / 2, y_offset, strlen("OSC"), "OSC");

    y_offset += 10 + 5;
    
    char line[20];

    int wavetable_count = 32;
    int snapshot_count = 4;
    
    int center = 128 / 2 - 6 / 2;
//    snprintf(line, 20, "   VERSION; %s", "0.07");
    Display::put_string_5x5(center, y_offset, 1, ":");
    Display::put_string_5x5(center - strlen("MORPH") * 6, y_offset, strlen("MORPH"), "MORPH");
    snprintf(line, 20, "%s", user_settings.getMorphSetting() == UserSettings::SETTING_MORPH_SMOOTH ? "SMOOTH":"DISCRETE");
    Display::put_string_5x5(center + 6, y_offset, strlen(line), line, true);
}