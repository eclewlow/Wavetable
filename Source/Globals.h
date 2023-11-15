/*
  ==============================================================================

    Globals.h
    Created: 7 Nov 2023 5:16:51pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include "MainMenu.h"
#include "ModeMenu.h"
#include "FxMenu.h"
#include "Oscilloscope.h"
#include "ControlStatusMenu.h"
#include "DeviceConfigurationMenu.h"

#include "effect_manager.h"
#include "fm.h"
#include "phase_distortion.h"
#include "ring_modulator.h"
#include "wavefolder.h"
#include "wavewrapper.h"
#include "bitcrush.h"
#include "drive.h"

#include "Context.h"
#include "Engine.h"

#include "adc.h"

extern MainMenu mainMenu;
extern ModeMenu modeMenu;
extern FxMenu fxMenu;
extern Oscilloscope oscilloscope;
extern ControlStatusMenu controlStatusMenu;
extern DeviceConfigurationMenu deviceConfigurationMenu;

extern Context context;
extern Engine engine;

extern EffectManager effect_manager;
extern FM fm;
extern PhaseDistortion phase_distortion;
extern RingModulator ring_modulator;
extern Wavefolder wavefolder;
extern Wavewrapper wavewrapper;
extern Bitcrush bitcrush;
extern Drive drive;

extern Adc adc;


inline double clamp(double input, double low, double high) {
    return std::min(std::max(input, low), high);
}

#define KEYCODE_A   65
#define KEYCODE_B   66
#define KEYCODE_C   67
#define KEYCODE_D   68
#define KEYCODE_E   69
#define KEYCODE_F   70
#define KEYCODE_G   71
#define KEYCODE_H   72
#define KEYCODE_I   73
#define KEYCODE_J   74
#define KEYCODE_K   75
#define KEYCODE_L   76
#define KEYCODE_M   77
#define KEYCODE_N   78
#define KEYCODE_O   79
#define KEYCODE_P   80
#define KEYCODE_Q   81
#define KEYCODE_R   82
#define KEYCODE_S   83
#define KEYCODE_T   84
#define KEYCODE_U   85
#define KEYCODE_V   86
#define KEYCODE_W   87
#define KEYCODE_X   88
#define KEYCODE_Y   89
#define KEYCODE_Z   90
#define KEYCODE_ENTER   13
#define KEYCODE_ESCAPE  27

#define LEFT_ENCODER_CCW        KEYCODE_Q
#define LEFT_ENCODER_CLICK      KEYCODE_W
#define LEFT_ENCODER_CW         KEYCODE_E

#define RIGHT_ENCODER_CCW       KEYCODE_I
#define RIGHT_ENCODER_CLICK     KEYCODE_O
#define RIGHT_ENCODER_CW        KEYCODE_P

#define PITCH_POT_CCW           KEYCODE_A
#define PITCH_POT_CW            KEYCODE_S

#define FX_AMOUNT_POT_CCW       KEYCODE_D
#define FX_AMOUNT_POT_CW        KEYCODE_F

#define FX_POT_CCW              KEYCODE_G
#define FX_POT_CW               KEYCODE_H

#define MORPH_POT_CCW           KEYCODE_J
#define MORPH_POT_CW            KEYCODE_K

#define BACK_BUTTON             KEYCODE_ESCAPE
