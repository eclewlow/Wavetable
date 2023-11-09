/*
 ==============================================================================
 
 Display.h
 Created: 6 Nov 2023 6:25:47pm
 Author:  Eugene Clewlow
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "fnt08x08.h"
#include "fnt09x09.h"
#include "fnt05x05.h"
#include "graphics.h"
//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */
class Display
{
public:
    static uint8_t framebuffer[8][128];

    //==============================================================================
    Display();
////        menu = Menu();
//        clear_screen();
////        Put_Pixel(10,10,1);
////        Put_Pixel(20,20,1);
////        Put_Pixel(30,30,1);
////        Put_Pixel(40,40,1);
////        LCD_Line(128/3, 60, 128, 64, 1);
//        if(false) {
//            put_string_5x5(0 + 1 + 1,
//                           0 + 1 + 1,
//                           16,
//                           "ABCDEFGHIJKLMNOP");
//            put_string_5x5(0 + 1 + 1,
//                           27 + 1 + 1,
//                           16,
//                           "QRSTUVWXYZ012345", true);
//            put_string_5x5(0 + 1 + 1,
//                           34 + 1 + 1,
//                           9,
//                           "6789_-/.:");
//        }
//        put_image_22x23(10, 10, Graphic_main_menu_ab);
//        put_string_5x5(0 + 1 + 1,
//                       40 + 1 + 1,
//                       16,
//                       "ABCDEFGHIJKLMNOP");
//        invert_rectangle(10, 10, 40, 40);
//    }
        ~Display();
    
    //==============================================================================
    static void paint(juce::Graphics& g);
    static void clear_screen();
    static void Put_Pixel(uint8_t x, uint8_t y, uint8_t set);
    static void LCD_Line(uint8_t x0, uint8_t y0,
                  uint8_t x1, uint8_t y1,
                         uint8_t set);
    typedef union
      {
      uint8_t
        as_bytes[2];
      uint16_t
        as_word;
      }WORD_UNION;
    
    static void put_string(uint8_t x, uint8_t y, uint8_t Field_Width, const char *input);
    static void put_string_5x5(uint8_t x, uint8_t y, uint8_t Field_Width, const char *input, bool inverted=false);
    static void put_string_9x9(uint8_t x, uint8_t y, uint8_t Field_Width, const char *input);

    typedef union
      {
      uint8_t
        as_bytes[4];
      uint32_t
        as_word;
      }DBLWORD_UNION;
    
    static void put_image_22x23(uint8_t x, uint8_t y, const uint8_t image[3][23]);
    static void invert_rectangle(uint8_t x,uint8_t y,uint8_t width,uint8_t height);

private:
    //==============================================================================
    // Your private member variables go here...
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Display)
};
