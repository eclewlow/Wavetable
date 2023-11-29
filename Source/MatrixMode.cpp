/*
  ==============================================================================

    MatrixMode.cpp
    Created: 29 Nov 2023 12:27:07am
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Display.h"
#include "graphics.h"
#include "Globals.h"

MatrixMode::MatrixMode() {
}

MatrixMode::~MatrixMode() {
    
}

void MatrixMode::triggerUpdate(bool back_pressed) {
}

bool MatrixMode::handleKeyPress(const juce::KeyPress &key) {
    if(key.getKeyCode() == LEFT_ENCODER_CCW) {
    }
    if(key.getKeyCode() == LEFT_ENCODER_CW) {
    }
    if(key.getKeyCode() == RIGHT_ENCODER_CCW) {
    }
    if(key.getKeyCode() == RIGHT_ENCODER_CW) {
    }
    if(key.getKeyCode() == RIGHT_ENCODER_CLICK) {
    }
    if(key.getKeyCode() == LEFT_ENCODER_CLICK) {
    }
    if(key.getKeyCode() == BACK_BUTTON) {
        if(back_menu_)
            context.setState(back_menu_, true);
        else
            context.setState(&mainMenu);
    }

    return true;
}

void MatrixMode::paint(juce::Graphics& g) {
    Display::clear_screen();
    
    int grid_offset_x = 2;
    int grid_offset_y = 2;
    
    for(int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            Display::Put_Pixel(grid_offset_x + i * 4, grid_offset_y + j * 4, true);
        }
    }
    
    int x_offset = grid_offset_x + 15 * 4 + 4;
    Display::outline_rectangle(x_offset, 0, 128 - x_offset, 32);
    
    int16_t outline_x1 = matrixEngine.GetX1() * 4;
    int16_t outline_y1 = matrixEngine.GetY1() * 4;
    int16_t outline_x2 = matrixEngine.GetX2() * 4;
    int16_t outline_y2 = matrixEngine.GetY2() * 4;
    int16_t outline_width = outline_x2 - outline_x1 + 1;
    int16_t outline_height = outline_y2 - outline_y1 + 1;
    Display::outline_rectangle(outline_x1, outline_y1, outline_width, outline_height);

    // draw 4 corners
    Display::outline_rectangle(outline_x1 - 1, outline_y1 - 1, 3, 3);
    Display::outline_rectangle(outline_x1 - 1, outline_y2 - 1, 3, 3);
    Display::outline_rectangle(outline_x2 - 1, outline_y1 - 1, 3, 3);
    Display::outline_rectangle(outline_x2 - 1, outline_y2 - 1, 3, 3);

}
