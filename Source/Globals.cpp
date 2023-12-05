/*
  ==============================================================================

    Globals.cpp
    Created: 7 Nov 2023 5:32:04pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Globals.h"

Context context;
UserSettings user_settings;
Storage storage;

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
EnterNameMenu enterNameMenu;
WavetableModeMenu wavetableModeMenu;
ABModeMenu abModeMenu;
WaveEditor waveEditor;
LoadWaveMenu loadWaveMenu;
SaveWaveMenu saveWaveMenu;
Popup popup;
MatrixMode matrixMode;
DrumMode drumMode;
IOConfigurationMenu ioConfigurationMenu;
CalibrationMenu calibrationMenu;
QuantizerMenu quantizerMenu;

ABEngine abEngine;
WavetableEngine wavetableEngine;
MatrixEngine matrixEngine;
DrumEngine drumEngine;
Suboscillator suboscillator;

EffectManager effect_manager;
FM fm;
PhaseDistortion phase_distortion;
RingModulator ring_modulator;
Wavefolder wavefolder;
Wavewrapper wavewrapper;
Bitcrush bitcrush;
Drive drive;
Bypass bypass;

Quantizer quantizer;

Adc adc;

int16_t BUF1[2048];
int16_t BUF2[2048];
int16_t BUF3[2048];
int16_t BUF4[2048];

const float lut_test[] = {
  -1.200000000e+02, -1.180000000e+02, -1.160000000e+02, -1.130000000e+02,
  -1.110000000e+02, -1.080000000e+02, -1.080000000e+02, -1.060000000e+02,
  -1.040000000e+02, -1.010000000e+02, -9.900000000e+01, -9.600000000e+01,
  -9.600000000e+01, -9.400000000e+01, -9.200000000e+01, -8.900000000e+01,
  -8.700000000e+01, -8.400000000e+01, -8.400000000e+01, -8.200000000e+01,
  -8.000000000e+01, -7.700000000e+01, -7.500000000e+01, -7.200000000e+01,
  -7.200000000e+01, -7.000000000e+01, -6.800000000e+01, -6.500000000e+01,
  -6.300000000e+01, -6.000000000e+01, -6.000000000e+01, -5.800000000e+01,
  -5.600000000e+01, -5.300000000e+01, -5.100000000e+01, -4.800000000e+01,
  -4.800000000e+01, -4.600000000e+01, -4.400000000e+01, -4.100000000e+01,
  -3.900000000e+01, -3.600000000e+01, -3.600000000e+01, -3.400000000e+01,
  -3.200000000e+01, -2.900000000e+01, -2.700000000e+01, -2.400000000e+01,
  -2.400000000e+01, -2.200000000e+01, -2.000000000e+01, -1.700000000e+01,
  -1.500000000e+01, -1.200000000e+01, -1.200000000e+01, -1.000000000e+01,
  -8.000000000e+00, -5.000000000e+00, -3.000000000e+00,  0.000000000e+00,
   0.000000000e+00,  2.000000000e+00,  4.000000000e+00,  7.000000000e+00,
   9.000000000e+00,  1.200000000e+01,  1.200000000e+01,  1.400000000e+01,
   1.600000000e+01,  1.900000000e+01,  2.100000000e+01,  2.400000000e+01,
   2.400000000e+01,  2.600000000e+01,  2.800000000e+01,  3.100000000e+01,
   3.300000000e+01,  3.600000000e+01,  3.600000000e+01,  3.800000000e+01,
   4.000000000e+01,  4.300000000e+01,  4.500000000e+01,  4.800000000e+01,
   4.800000000e+01,  5.000000000e+01,  5.200000000e+01,  5.500000000e+01,
   5.700000000e+01,  6.000000000e+01,  6.000000000e+01,  6.200000000e+01,
   6.400000000e+01,  6.700000000e+01,  6.900000000e+01,  7.200000000e+01,
   7.200000000e+01,  7.400000000e+01,  7.600000000e+01,  7.900000000e+01,
   8.100000000e+01,  8.400000000e+01,  8.400000000e+01,  8.600000000e+01,
   8.800000000e+01,  9.100000000e+01,  9.300000000e+01,  9.600000000e+01,
   9.600000000e+01,  9.800000000e+01,  1.000000000e+02,  1.030000000e+02,
   1.050000000e+02,  1.080000000e+02,  1.080000000e+02,  1.100000000e+02,
   1.120000000e+02,  1.150000000e+02,  1.170000000e+02,  1.200000000e+02,
};
