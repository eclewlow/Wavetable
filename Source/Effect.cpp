/*
  ==============================================================================

    Effect.cpp
    Created: 12 Nov 2023 4:26:44pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Effect.h"
#include "Globals.h"

void Effect::Init() {
    phase = 0.0f;
    oscilloscopePhase = 0.0f;
}

void Effect::Reset() {
    phase = 0.0f;
    oscilloscopePhase = 0.0f;
}
