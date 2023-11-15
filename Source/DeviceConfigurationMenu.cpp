/*
  ==============================================================================

    DeviceConfigurationMenu.cpp
    Created: 14 Nov 2023 4:40:15pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Display.h"
#include "graphics.h"
#include "Globals.h"

DeviceConfigurationMenu::DeviceConfigurationMenu() {
    setState(DEVICE_INFO);
}

DeviceConfigurationMenu::~DeviceConfigurationMenu() {
    
}

bool DeviceConfigurationMenu::handleKeyPress(const juce::KeyPress &key) {
//    DEVICE_INFO,
//    DEVICE_DISPLAY,
//    DEVICE_OSCILLOSCOPE,
//    DEVICE_IO,
//    DEVICE_CALIBRATION,
//    DEVICE_QUANTIZER,
//    DEVICE_MEMORY,

    if(key.getKeyCode() == LEFT_ENCODER_CCW) {
        switch(currentState) {
            case DEVICE_INFO:
                break;
            case DEVICE_DISPLAY:
                setState(DEVICE_INFO);
                break;
            case DEVICE_OSCILLOSCOPE:
                setState(DEVICE_DISPLAY);
                break;
            case DEVICE_IO:
                setState(DEVICE_OSCILLOSCOPE);
                break;
            case DEVICE_CALIBRATION:
                setState(DEVICE_IO);
                break;
            case DEVICE_QUANTIZER:
                setState(DEVICE_CALIBRATION);
                break;
            case DEVICE_MEMORY:
                setState(DEVICE_QUANTIZER);
                break;
            default:
                break;
        }
    }
    if(key.getKeyCode() == LEFT_ENCODER_CW) {
        switch(currentState) {
            case DEVICE_INFO:
                setState(DEVICE_DISPLAY);
                break;
            case DEVICE_DISPLAY:
                setState(DEVICE_OSCILLOSCOPE);
                break;
            case DEVICE_OSCILLOSCOPE:
                setState(DEVICE_IO);
                break;
            case DEVICE_IO:
                setState(DEVICE_CALIBRATION);
                break;
            case DEVICE_CALIBRATION:
                setState(DEVICE_QUANTIZER);
                break;
            case DEVICE_QUANTIZER:
                setState(DEVICE_MEMORY);
                break;
            case DEVICE_MEMORY:
                break;
            default:
                break;
        }
    }
    //    printf("%d, %d\n", key.getKeyCode(), juce::KeyPress::returnKey, currentState, );
    if(key.getKeyCode() == LEFT_ENCODER_CLICK) {
        switch(currentState) {
            case DEVICE_INFO:
//                setState(DEVICE_DISPLAY);
                break;
            case DEVICE_DISPLAY:
//                setState(DEVICE_OSCILLOSCOPE);
                break;
            case DEVICE_OSCILLOSCOPE:
//                setState(DEVICE_IO);
                break;
            case DEVICE_IO:
//                setState(DEVICE_CALIBRATION);
                break;
            case DEVICE_CALIBRATION:
//                setState(DEVICE_QUANTIZER);
                break;
            case DEVICE_QUANTIZER:
//                setState(DEVICE_MEMORY);
                break;
            case DEVICE_MEMORY:
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

void DeviceConfigurationMenu::paint(juce::Graphics& g) {
    Display::clear_screen();
    
    int y_offset = 4;
    int x_offset = 64 - (23+2) * 2;
    int row = 0;
    int col = 0;
    char *caption;
    
    switch(currentState) {
        case DEVICE_INFO:
            caption = (char*)"INFO";
            break;
        case DEVICE_DISPLAY:
            caption = (char*)"DISPLAY";
            break;
        case DEVICE_OSCILLOSCOPE:
            caption = (char*)"OSC";
            break;
        case DEVICE_IO:
            caption = (char*)"I/O";
            break;
        case DEVICE_CALIBRATION:
            caption = (char*)"CALIBRATE";
            break;
        case DEVICE_QUANTIZER:
            caption = (char*)"QUANT";
            break;
        case DEVICE_MEMORY:
            caption = (char*)"MEMORY";
            break;
        default:
            break;
    }

    
    Display::put_string_9x9(64-strlen(caption)*10/2,64-11,strlen(caption),caption);
    
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_setup_menu_info);
    
    col++;
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_setup_menu_brightness);
    
    col++;
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_setup_menu_oscilloscope);
    
    col++;
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_setup_menu_io);
    
    
    row++;
    col=0;
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_setup_menu_calibration);
    
    col++;
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_setup_menu_quantizer);
    
    col++;
    Display::put_image_22x23(col*(23+2)+x_offset, row*(22+2)+y_offset, Graphic_setup_menu_memory);
    
    switch(currentState) {
        case DEVICE_INFO:
            col = 0; row = 0;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        case DEVICE_DISPLAY:
            col = 1; row = 0;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        case DEVICE_OSCILLOSCOPE:
            col = 2; row = 0;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        case DEVICE_IO:
            col = 3; row = 0;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        case DEVICE_CALIBRATION:
            col = 0; row = 1;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        case DEVICE_QUANTIZER:
            col = 1; row = 1;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        case DEVICE_MEMORY:
            col = 2; row = 1;
            Display::invert_rectangle(col*(23+2)+x_offset, row*(22+2)+y_offset, 23, 22);
            break;
        default:
            break;
    }
}
