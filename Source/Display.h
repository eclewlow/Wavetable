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
#include "fnt03x05.h"
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
    static void Put_Pixel(uint8_t x, uint8_t y, uint8_t set, bool toggle=false);
    static void Draw_Wave(uint8_t x, uint8_t y, uint8_t width, uint8_t height, int16_t* waveform_data, bool shade=false);
    static void Draw_NWave(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t* waveform_data, int16_t n);
    static void LCD_Circle(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t set);
    static void LCD_FillCircle(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t set);
    static void LCD_Line(int16_t x0, int16_t y0,
                         int16_t x1, int16_t y1,
                         uint8_t set, bool toggle=false);
    static void LCD_DottedLine(uint8_t x0, uint8_t y0,
                  uint8_t x1, uint8_t y1, int16_t dash_width, int16_t gap_width,
                         uint8_t set);
    typedef union
      {
      uint8_t
        as_bytes[2];
      uint16_t
        as_word;
      }WORD_UNION;
    
    static void put_string(uint8_t x, uint8_t y, uint8_t Field_Width, const char *input);
    static void put_string_3x5(uint8_t x, int8_t y, uint8_t Field_Width, const char *input, bool inverted=false);
    static void put_string_5x5(uint8_t x, int8_t y, uint8_t Field_Width, const char *input, bool inverted=false);
    static int16_t get_string_9x9_width(const char *input, int8_t gap);
    static void put_string_9x9(uint8_t x, uint8_t y, uint8_t Field_Width, const char *input, bool inverted=false, int8_t gap=2);
    static void put_string_9x9_loop(uint8_t x, uint8_t y, uint8_t Field_Width, const char *input, bool inverted, int8_t gap, int8_t num_chars, int8_t position);
    static void put_string_5x5_loop(uint8_t x, int8_t y, uint8_t Field_Width, const char *input, bool inverted, int8_t num_chars, int8_t position);
    static void clear_rectangle(uint8_t x,uint8_t y,uint8_t width,uint8_t height);
    static void clear_rectangle_simple(uint8_t x,uint8_t y,uint8_t width,uint8_t height, bool set = false);
    static void clear_rectangle_grey(uint8_t x,uint8_t y,uint8_t width,uint8_t height);
    static void outline_rectangle(int16_t x, int16_t y, int16_t width, int16_t height);
    static void invert_rectangle(int8_t x,int8_t y,uint8_t width,uint8_t height);

    typedef union
      {
      uint8_t
        as_bytes[4];
      uint32_t
        as_word;
      }DBLWORD_UNION;
    
    static void put_image_16bit(int16_t x, int16_t y, const uint8_t image[][2], uint8_t width);
    static void put_image_22x23(uint8_t x, uint8_t y, const uint8_t image[3][23]);

private:
    //==============================================================================
    // Your private member variables go here...
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Display)
};
