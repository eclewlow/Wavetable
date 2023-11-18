/*
  ==============================================================================

    Globals.cpp
    Created: 7 Nov 2023 5:32:04pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Globals.h"

MainMenu mainMenu;
ModeMenu modeMenu;
FxMenu fxMenu;
Oscilloscope oscilloscope;
ControlStatusMenu controlStatusMenu;
DeviceConfigurationMenu deviceConfigurationMenu;
InfoMenu infoMenu;
DisplayConfigurationMenu displayConfigurationMenu;
OscilloscopeConfigurationMenu oscilloscopeConfigurationMenu;
SubOscillatorMenu subOscillatorMenu;

Context context;
Engine engine;
UserSettings user_settings;

EffectManager effect_manager;
FM fm;
PhaseDistortion phase_distortion;
RingModulator ring_modulator;
Wavefolder wavefolder;
Wavewrapper wavewrapper;
Bitcrush bitcrush;
Drive drive;
Bypass bypass;

Adc adc;
