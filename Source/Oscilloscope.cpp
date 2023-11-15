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
            case OSCILLOSCOPE_STATE_NONE:
                context.setState(&controlStatusMenu);
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
    
    int y_offset;
    int x_offset;
    
    uint16_t tune = adc.getChannel(0);
    uint16_t fx_amount = adc.getChannel(1);
    uint16_t fx = adc.getChannel(2);
    uint16_t morph = adc.getChannel(3);
    
    uint8_t note = static_cast<uint8_t>((120.0f * tune)/4095.0);
    float a = 440; //frequency of A (coomon value is 440Hz)
    float frequency = (a / 32) * pow(2, ((note - 9) / 12.0));
    
    int x = 0;
    int width = 128-1;
    int y = 2;
    int height = 40;
    Display::outline_rectangle(x, y, width, height);
    
    Display::Draw_Wave(x, y, width, height, engine.GetWaveformData( tune,  fx_amount,  fx,  morph), user_settings.getScopeSetting() == UserSettings::SETTING_SCOPE_SHADED);
    
    std::string note_letter = "C C#D D#E F F#G G#A A#B ";
    int note_index = note % 12;

    char first_line[20];
    snprintf(first_line, 20, "TUNE;%d%s, %5.0fHZ", (note / 12 - 1), note_letter.substr(note_index * 2, 2).c_str(), frequency);
    
    x_offset = 5;
    y_offset = y + height + 3;
    Display::put_string_5x5(x_offset, y_offset, strlen(first_line), first_line);

    x_offset = 5;
    y_offset += 7;

    char second_line[20];
    unsigned long long currentTime = juce::Time::currentTimeMillis();
    unsigned int hours = (currentTime / (1000*60*60)) % 24;
    unsigned int minutes = (currentTime / (1000*60)) % 60;
    unsigned int seconds = (currentTime / (1000)) % 60;
    unsigned int milliseconds = (currentTime / 100) % 10;
        
    snprintf(second_line, 20, "TIME;%02d;%02d;%02d.%01d", hours, minutes, seconds, milliseconds);

    Display::put_string_5x5(x_offset, y_offset, strlen(second_line), second_line);
}
