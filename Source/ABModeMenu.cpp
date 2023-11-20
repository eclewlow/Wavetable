/*
  ==============================================================================

    ABWaveSelectMenu.cpp
    Created: 18 Nov 2023 8:29:46pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Display.h"
#include "graphics.h"
#include "Globals.h"

ABModeMenu::ABModeMenu() {
    setLeftState(AB_NONE);
    setRightState(AB_NONE);
    bank = 0;
    wave = 0;
}

ABModeMenu::~ABModeMenu() {
    
}

bool ABModeMenu::handleKeyPress(const juce::KeyPress &key) {
    if(key.getKeyCode() == LEFT_ENCODER_CCW) {
        wave--;
        wave = std::clamp(wave, 0, 15);
    }
    if(key.getKeyCode() == LEFT_ENCODER_CW) {
        wave++;
        wave = std::clamp(wave, 0, 15);
    }
    if(key.getKeyCode() == LEFT_ENCODER_CLICK) {
        abEngine.LoadWave(1, 1, wave);
    }
    if(key.getKeyCode() == BACK_BUTTON) {
        if(back_menu_)
            context.setState(back_menu_);
        else
            context.setState(&mainMenu);
    }

    return true;
}

void ABModeMenu::paint(juce::Graphics& g) {
    uint16_t morph = adc.getChannel(3);

    Display::clear_screen();

    int graph_y_offset = 3;
    int graph_height = 32 - graph_y_offset;
    int gap = 1;
    int graph_width = 128 / 2 - gap;
    Display::outline_rectangle(0, graph_y_offset, graph_width, graph_height);
    Display::outline_rectangle(graph_width + gap * 2, graph_y_offset, graph_width, graph_height);
    
    Display::Draw_Wave(1, graph_y_offset + 1, graph_width-2, graph_height-2, abEngine.GetWaveformDataNoFX(1, morph));

    Display::Draw_Wave(graph_width + gap * 2 + 1, graph_y_offset + 1, graph_width-2, graph_height-2, abEngine.GetWaveformDataNoFX(2, morph));
    
    for(int i = 0; i < 16; i++)
    {
        Display::put_string_5x5(5, 10 + i * 7, strlen("TEST"), "TEST", i==wave);
    }
    
}
