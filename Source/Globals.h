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
#include "Context.h"
#include "Engine.h"
#include "adc.h"

extern Context context;
extern MainMenu mainMenu;
extern ModeMenu modeMenu;
extern FxMenu fxMenu;
extern Engine engine;
extern Effect fx_engine;
extern Effect osc_fx_engine;
extern Adc adc;


inline double clamp(double input, double low, double high) {
    return std::min(std::max(input, low), high);
}
