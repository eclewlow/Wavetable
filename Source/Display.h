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
#include "fnt05x05.h"
//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */
class Display
{
public:
    //==============================================================================
    Display() {
        memset(framebuffer, 0, 128*8);
        Put_Pixel(10,10,1);
        Put_Pixel(20,20,1);
        Put_Pixel(30,30,1);
        Put_Pixel(40,40,1);
        LCD_Line(128/3, 60, 128, 64, 1);
        put_string_5x5(0 + 1 + 1,
                   20 + 1 + 1,
                   16,
                   "ABCDEFGHIJKLMNOP");
        put_string_5x5(0 + 1 + 1,
                   27 + 1 + 1,
                   16,
                   "QRSTUVWXYZ012345", true);
        put_string_5x5(0 + 1 + 1,
                   34 + 1 + 1,
                   6,
                   "6789_-");
    }
    ~Display() {
        
    }
    
    //==============================================================================
    void paint(juce::Graphics& g)
    {
        g.setColour(juce::Colour(0xFF, 0xFF, 0xFF));
        g.fillRect(0, 0, 128, 64);
        
        for(int page=0;page<8;page++)
        {
            for(int column=0;column<128;column++)
            {
                for (int row = 0; row < 8; row++) {
                    bool is_set = (framebuffer[page][column] >> row) & 0x1;
                    if(is_set) {
                        //                    g.setColour(Colour newColour)
                        g.setColour(juce::Colour(0x00, 0x00, 0x00));
                        g.drawRect(column, page * 8 + row, 1, 1);
                    }
                }
            }
        }
    }
    void Put_Pixel(uint8_t x, uint8_t y, uint8_t set) {
        //2.48uS ~ 4.70uS
        if(0 != set)
        {
            //Setting the bit
            framebuffer[y>>3][x]|=(0x01 << (y&0x07));
        }
        else
        {
            //Clearing the bit
            framebuffer[y>>3][x]&=~(0x01 << (y&0x07));
        }
    }
    void LCD_Line(uint8_t x0, uint8_t y0,
                  uint8_t x1, uint8_t y1,
                  uint8_t set) {
        int8_t
        dx;
        int8_t
        sx;
        int8_t
        dy;
        int8_t
        sy;
        int8_t
        err;
        int8_t
        e2;
        dx = abs((int16_t )x1 - (int16_t )x0);
        sx = x0 < x1 ? 1 : -1;
        dy = abs((int16_t )y1 - (int16_t )y0);
        sy = y0 < y1 ? 1 : -1;
        err = (dx > dy ? dx : -dy) / 2;
        
        for (;;)
        {
            Put_Pixel(x0, y0, set);
            if ((x0 == x1) && (y0 == y1))
                break;
            e2 = err;
            if (e2 > -dx)
            {
                err -= dy;
                x0 = (uint16_t)((int16_t) x0 + sx);
            }
            if (e2 < dy)
            {
                err += dx;
                y0 = (uint16_t)((int16_t) y0 + sy);
            }
        }
        
    }
    
    typedef union
      {
      uint8_t
        as_bytes[2];
      uint16_t
        as_word;
      }WORD_UNION;
    
    void put_string(uint8_t x, uint8_t y, uint8_t Field_Width, const char *input)
    {
        uint8_t
        Terminator_Found;
        uint8_t
        Characters_Placed;
        uint8_t
        this_character;
        uint8_t
        *LCD_Memory;
        uint8_t
        column;
        uint8_t
        row;
        WORD_UNION
        Clearing_Mask;
        WORD_UNION
        Pixel_Data;
        
        //Get the first row of the display character.
        row=y>>3;
        //Calculate the address of the first uint8_t in display in LCD_Memory
        LCD_Memory=&framebuffer[row][x];
        
        //Calculate Clearing_Mask, the vertical mask that we will and with
        //LCD_Memory to clear the space before we or in the data from the
        //font. It is 9 pixels.
        Clearing_Mask.as_word=~(0x01FF<<(y&0x07));
        
        //Clear the first col to the left of the string.
        LCD_Memory[0]&=Clearing_Mask.as_bytes[0];
        if(row<7)
            LCD_Memory[128]&=Clearing_Mask.as_bytes[1];
        LCD_Memory++;
        
        //Initialize Terminator_Found.
        Terminator_Found=0;
        //Move across the field. We will either put the character or a blank
        //in every position of Field_Width.
        for(Characters_Placed=0;Characters_Placed<Field_Width;Characters_Placed++)
        {
            //If we have not passed the terminator, then get the next
            //character in the string. If we find the terminator,
            //remember that we are out of characters.
            if(!Terminator_Found)
            {
                this_character=*input++;
                if(!this_character)
                {
                    Terminator_Found=1;
                    this_character=' ';
                }
            }
            else
                this_character=' ';
            //Get a pointer into the font information for this
            //character.
            
            //Write the eight columns of this character.
            for(column=0;column<=7;column++)
            {
                //Clear the correct bits in this row and the next row down.
                LCD_Memory[0]&=Clearing_Mask.as_bytes[0];
                if(row<7)
                {
                    LCD_Memory[128]&=Clearing_Mask.as_bytes[1];
                }
                //Get the font data, convert it to a word and shift it down. Leave
                //one blank row of pixels above as a spacer.
                Pixel_Data.as_word=((uint16_t)Font_08x08[(this_character-FONT_08X08_BASE)][column])<<((y&0x07));
                
                //Set the correct bits in this row and the next row down.
                LCD_Memory[0]|=Pixel_Data.as_bytes[0];
                if(row<7)
                {
                    LCD_Memory[128]|=Pixel_Data.as_bytes[1];
                }
                LCD_Memory++;
            }
            printf("\n");
        }
    }
    
    void put_string_5x5(uint8_t x, uint8_t y, uint8_t Field_Width, const char *input, bool inverted=false)
    {
        uint8_t
        Terminator_Found;
        uint8_t
        Characters_Placed;
        uint8_t
        this_character;
        uint8_t
        *LCD_Memory;
        uint8_t
        column;
        uint8_t
        row;
        WORD_UNION
        Clearing_Mask;
        WORD_UNION
        Pixel_Data;
        
        //Get the first row of the display character.
        row=y>>3;
        //Calculate the address of the first uint8_t in display in LCD_Memory
        LCD_Memory=&framebuffer[row][x];
        
//        //Calculate Clearing_Mask, the vertical mask that we will and with
//        //LCD_Memory to clear the space before we or in the data from the
//        //font. It is 9 pixels.
//        Clearing_Mask.as_word=~(0x01FF<<(y&0x07));
//
//        //Clear the first col to the left of the string.
//        LCD_Memory[0]&=Clearing_Mask.as_bytes[0];
//        if(row<7)
//            LCD_Memory[128]&=Clearing_Mask.as_bytes[1];
        LCD_Memory++;
        
        //Initialize Terminator_Found.
        Terminator_Found=0;
        //Move across the field. We will either put the character or a blank
        //in every position of Field_Width.
        for(Characters_Placed=0;Characters_Placed<Field_Width;Characters_Placed++)
        {
            //If we have not passed the terminator, then get the next
            //character in the string. If we find the terminator,
            //remember that we are out of characters.
            if(!Terminator_Found)
            {
                this_character=*input++;
                if(!this_character)
                {
                    Terminator_Found=1;
                    this_character=' ';
                }
            }
            else
                this_character=' ';
            //Get a pointer into the font information for this
            //character.
            
            //Write the eight columns of this character.
            for(column=0;column<=6;column++)
            {
                //Clear the correct bits in this row and the next row down.
//                LCD_Memory[0]&=Clearing_Mask.as_bytes[0];
//                if(row<7)
//                {
//                    LCD_Memory[128]&=Clearing_Mask.as_bytes[1];
//                }
                //Get the font data, convert it to a word and shift it down. Leave
                //one blank row of pixels above as a spacer.
                if(inverted)
                    Pixel_Data.as_word=((uint16_t)Font_05x05[(this_character-FONT_05X05_BASE)][column])<<((y&0x07))^0x3F80;
                else
                    Pixel_Data.as_word=((uint16_t)Font_05x05[(this_character-FONT_05X05_BASE)][column])<<((y&0x07));
                                
                //Set the correct bits in this row and the next row down.
                LCD_Memory[0]|=Pixel_Data.as_bytes[0];
                if(row<7)
                {
                    LCD_Memory[128]|=Pixel_Data.as_bytes[1];
                }
                LCD_Memory++;
            }
//            LCD_Memory++;
            printf("\n");
        }
    }
private:
    //==============================================================================
    // Your private member variables go here...
    float phase = 0.0f;
    uint8_t framebuffer[8][128];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Display)
};
