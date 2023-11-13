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
#include "Context.h"
#include "Engine.h"
#include "Effect.h"

extern Context context;
extern MainMenu mainMenu;
extern ModeMenu modeMenu;
extern Engine engine;
extern Effect effect;
extern uint16_t fxKnob;
extern uint16_t fxAmountKnob;
extern uint16_t morphKnob;
extern uint16_t tuneKnob;

inline double clamp(double input, double low, double high) {
    return std::min(std::max(input, low), high);
}
