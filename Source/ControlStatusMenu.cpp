/*
  ==============================================================================

    ControlStatusMenu.cpp
    Created: 14 Nov 2023 4:39:09pm
    Author:  Eugene Clewlow

  ==============================================================================
*/


#include "Display.h"
#include "graphics.h"
#include "Globals.h"

ControlStatusMenu::ControlStatusMenu() {
    setState(CONTROL_STATUS_STATE_NONE);
}

ControlStatusMenu::~ControlStatusMenu() {
    
}

bool ControlStatusMenu::handleKeyPress(const juce::KeyPress &key) {
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
            case CONTROL_STATUS_STATE_NONE:
                context.setState(&oscilloscope);
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == BACK_BUTTON) {
        switch(currentState) {
            case CONTROL_STATUS_STATE_NONE:
                context.setState(&oscilloscope);
                break;
            default:
                break;
        }
    }

    return true;
}

void ControlStatusMenu::paint(juce::Graphics& g) {
    Display::clear_screen();
    
    uint16_t tune = adc.getChannel(0);
    uint16_t fx_amount = adc.getChannel(1);
    uint16_t fx = adc.getChannel(2);
    uint16_t morph = adc.getChannel(3);

    int y_offset;
    int x_offset;
    // 5 gaps + 4 circules
    // 5*g + 4*d = 128
    int radius = 11;
    int gap = (128 - 4 * radius * 2) / 5;

    float angle;

    x_offset = gap + radius;
    y_offset = 22;
    int text_gap = 7;
    Display::LCD_Circle(x_offset, y_offset, radius, true);
    Display::put_string_5x5(x_offset - strlen("TUNE") * 6 / 2, y_offset - radius - text_gap, strlen("TUNE"), "TUNE");
    angle = 2 * M_PI * ((1.0f - tune / 4095.0f) * 300.0f - 60.0f) / 360.0f;
    Display::LCD_Line(x_offset, y_offset, radius * cos(angle) + x_offset, y_offset - radius * sin(angle), true);
    
    x_offset += gap + radius * 2;
    Display::LCD_Circle(x_offset, y_offset, radius, true);
    Display::put_string_5x5(x_offset - strlen("AMT") * 6 / 2, y_offset - radius - text_gap, strlen("AMT"), "AMT");
    angle = 2 * M_PI * ((1.0f - fx_amount / 4095.0f) * 300.0f - 60.0f) / 360.0f;
    Display::LCD_Line(x_offset, y_offset, radius * cos(angle) + x_offset, y_offset - radius * sin(angle), true);

    x_offset += gap + radius * 2;
    Display::LCD_Circle(x_offset, y_offset, radius, true);
    Display::put_string_5x5(x_offset - strlen("FX") * 6 / 2, y_offset - radius - text_gap, strlen("FX"), "FX");
    angle = 2 * M_PI * ((1.0f - fx / 4095.0f) * 300.0f - 60.0f) / 360.0f;
    Display::LCD_Line(x_offset, y_offset, radius * cos(angle) + x_offset, y_offset - radius * sin(angle), true);

    x_offset += gap + radius * 2;
    Display::LCD_Circle(x_offset, y_offset, radius, true);
    Display::put_string_5x5(x_offset - strlen("MORPH") * 6 / 2, y_offset - radius - text_gap, strlen("MORPH"), "MORPH");
    angle = 2 * M_PI * ((1.0f - morph / 4095.0f) * 300.0f - 60.0f) / 360.0f;
    Display::LCD_Line(x_offset, y_offset, radius * cos(angle) + x_offset, y_offset - radius * sin(angle), true);

    int row_gap = 4;
    x_offset = gap;
    Display::outline_rectangle(x_offset, y_offset + radius + row_gap, radius * 2, radius * 2);

    x_offset += gap + radius * 2;
    Display::outline_rectangle(x_offset, y_offset + radius + row_gap, radius * 2, radius * 2);

    x_offset += gap + radius * 2;
    Display::outline_rectangle(x_offset, y_offset + radius + row_gap, radius * 2, radius * 2);

    x_offset += gap + radius * 2;
    Display::outline_rectangle(x_offset, y_offset + radius + row_gap, radius * 2, radius * 2);

}