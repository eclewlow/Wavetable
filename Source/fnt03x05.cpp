/*
  ==============================================================================

    fnt_03x05.cpp
    Created: 26 Nov 2023 6:04:56pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "fnt03x05.h"

const unsigned char Font_03x05[96][3] = {
    {0x00,0x00,0x00}, //  32 = 0x20 = " "
    {0xB8,0x00,0x00}, //  33 = 0x21 = "!"  !
    {0x00,0xE0,0xE0}, //  34 = 0x22 = """
    {0x50,0xF8,0x50}, //  35 = 0x23 = "#"  !
    {0x24,0x74,0x54}, //  36 = 0x24 = "$"
    {0x88,0x40,0x20}, //  37 = 0x25 = "%"  !
    {0x50,0xA8,0x50}, //  38 = 0x26 = "&"  !
    {0x00,0x00,0x20}, //  39 = 0x27 = "'"
    {0x00,0x38,0x7C}, //  40 = 0x28 = "("
    {0x00,0x82,0xC6}, //  41 = 0x29 = ")"
    {0x54,0x7C,0x7C}, //  42 = 0x2A = "*"
    {0x00,0x20,0x70}, //  43 = 0x2B = "+"  !
    {0xC0,0x00,0x00}, //  44 = 0x2C = ","  ! comma shifted% 6
    {0x00,0x20,0x20}, //  45 = 0x2D = "-"  !
    {0x80,0x00,0x00}, //  46 = 0x2E = "."  ! period shifted
    {0x80,0x40,0x20}, //  47 = 0x2F = "/"  !
    
    {0xF8,0x88,0xF8}, //  48 = 0x30 = "0"  !
    {0x88,0xF8,0x80}, //  49 = 0x31 = "1"  !
    {0xE8,0xA8,0xB8}, //  50 = 0x32 = "2"  !
    {0xA8,0xA8,0xF8}, //  51 = 0x33 = "3"  !
    {0x38,0x20,0xF8}, //  52 = 0x34 = "4"  !
    {0xB8,0xA8,0xE8}, //  53 = 0x35 = "5"  !
    {0xF8,0xA8,0xE8}, //  54 = 0x36 = "6"  !
    {0x08,0x08,0xF8}, //  55 = 0x37 = "7"  !
    {0xF8,0xA8,0xF8}, //  56 = 0x38 = "8"  !
    {0xB8,0xA8,0xF8}, //  57 = 0x39 = "9"  !
    
    
    {0x00,0x00,0x50}, //  58 = 0x3A = ":"  !
    {0x50,0x00,0x00}, //  59 = 0x3B = ";"  ! colon shifted
    {0x00,0x10,0x38}, //  60 = 0x3C = "<"
    {0x24,0x24,0x24}, //  61 = 0x3D = "="
    {0x00,0x82,0xC6}, //  62 = 0x3E = ">"
    {0x40,0xC0,0x80}, //  63 = 0x3F = "?"
    {0x7C,0xFE,0x82}, //  64 = 0x40 = "@"
    {0xF8,0x28,0x28}, //  65 = 0x41 = "A"  !
    {0xF8,0xA8,0xA8}, //  66 = 0x42 = "B"  !
    {0xF8,0x88,0x88}, //  67 = 0x43 = "C"  !
    {0xF8,0x88,0x88}, //  68 = 0x44 = "D"  !
    {0xF8,0xA8,0xA8}, //  69 = 0x45 = "E"  !
    {0xF8,0x28,0x28}, //  70 = 0x46 = "F"  !
    {0xF8,0x88,0x88}, //  71 = 0x47 = "G"  !
    {0xF8,0x20,0x20}, //  72 = 0x48 = "H"  !
    {0x88,0x88,0xF8}, //  73 = 0x49 = "I"  !
    {0xC0,0x80,0x80}, //  74 = 0x4A = "J"  !
    {0xF8,0x20,0x50}, //  75 = 0x4B = "K"  !
    {0xF8,0x80,0x80}, //  76 = 0x4C = "L"  !
    {0xF8,0x10,0x20}, //  77 = 0x4D = "M"  !
    {0xF8,0x10,0x20}, //  78 = 0x4E = "N"  !
    {0xF8,0x88,0x88}, //  79 = 0x4F = "O"  !
    {0xF8,0x28,0x28}, //  80 = 0x50 = "P"  !
    {0x78,0x48,0x48}, //  81 = 0x51 = "Q"  !
    {0xF8,0x28,0x68}, //  82 = 0x52 = "R"  !
    {0xB8,0xA8,0xA8}, //  83 = 0x53 = "S"  !
    {0x08,0x08,0xF8}, //  84 = 0x54 = "T"  !
    {0xF8,0x80,0x80}, //  85 = 0x55 = "U"  !
    {0x38,0x40,0x80}, //  86 = 0x56 = "V"  !
    {0x78,0x80,0x40}, //  87 = 0x57 = "W"  !
    {0x88,0x50,0x20}, //  88 = 0x58 = "X"  !
    {0x88,0x50,0x20}, //  89 = 0x59 = "Y"  !
    {0x88,0xC8,0xA8}, //  90 = 0x5A = "Z"  !
    {0x00,0xFE,0xFE}, //  91 = 0x5B = "["
    {0x80,0xC0,0x60}, //  92 = 0x5C = "\"
    {0x00,0x82,0x82}, //  93 = 0x5D = "]"
    {0x10,0x30,0x60}, //  94 = 0x5E = "^"
    {0x80,0x80,0x80}, //  95 = 0x5F = "_"  !
    {0x00,0x00,0xC0}, //  96 = 0x60 = "`"
    {0x04,0x2E,0x2A}, //  97 = 0x61 = "a"
    {0x82,0xFE,0xFE}, //  98 = 0x62 = "b"
    {0x1C,0x3E,0x22}, //  99 = 0x63 = "c"
    {0x1C,0x3E,0x22}, // 100 = 0x64 = "d"
    {0x1C,0x3E,0x2A}, // 101 = 0x65 = "e"
    {0x10,0x12,0x7E}, // 102 = 0x66 = "f"
    {0x18,0x3D,0x25}, // 103 = 0x67 = "g"
    {0x82,0xFE,0xFE}, // 104 = 0x68 = "h"
    {0x00,0x00,0x22}, // 105 = 0x69 = "i"
    {0x02,0x03,0x01}, // 106 = 0x6A = "j"
    {0x82,0xFE,0xFE}, // 107 = 0x6B = "k"
    {0x00,0x00,0x00}, // 108 = 0x6C = "l"
    {0x1E,0x3E,0x30}, // 109 = 0x6D = "m"
    {0x20,0x3E,0x1E}, // 110 = 0x6E = "n"
    {0x1C,0x3E,0x22}, // 111 = 0x6F = "o"
    {0x21,0x3F,0x1F}, // 112 = 0x70 = "p"
    {0x18,0x3C,0x24}, // 113 = 0x71 = "q"
    {0x22,0x3E,0x1E}, // 114 = 0x72 = "r"
    {0x10,0x3A,0x2A}, // 115 = 0x73 = "s"
    {0x20,0x20,0xFC}, // 116 = 0x74 = "t"
    {0x3C,0x3E,0x02}, // 117 = 0x75 = "u"
    {0x30,0x38,0x0C}, // 118 = 0x76 = "v"
    {0x3C,0x3E,0x06}, // 119 = 0x77 = "w"
    {0x22,0x36,0x1C}, // 120 = 0x78 = "x"
    {0x38,0x3D,0x05}, // 121 = 0x79 = "y"
    {0x32,0x26,0x2E}, // 122 = 0x7A = "z"
    {0x00,0x10,0x10}, // 123 = 0x7B = "{"
    {0x00,0x00,0x00}, // 124 = 0x7C = "|"
    {0x00,0x82,0x82}, // 125 = 0x7D = "}"
    {0x00,0x90,0xB8}, // 126 = 0x7E = "~"   ! plus-minus
    {0x02,0x0E,0x3E}};// 127 = 0x7F = ""