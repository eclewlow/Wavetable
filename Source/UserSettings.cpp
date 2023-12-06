/*
  ==============================================================================

    UserSettings.cpp
    Created: 15 Nov 2023 1:42:55am
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "UserSettings.h"
#include "Globals.h"

UserSettings::UserSettings() {
    brightness_ = 100;
    contrast_ = 100;
    invert_ = false;
    scope_setting_ = SETTING_SCOPE_LINE;
    morph_setting_ = SETTING_MORPH_SMOOTH;
    
    suboscOffset_ = 0;
    suboscDetune_ = 0;
    suboscMix_ = 100;
    suboscWave_ = SUBOSC_WAVE_SINE;
    app_start_time_ = system_clock.milliseconds();
    
    memset(io_gain_, 0, 4 * 4);
    io_gain_ [0] = 1.0f;
    io_gain_ [1] = 1.0f;
    io_gain_ [2] = 1.0f;
    io_gain_ [3] = 1.0f;
    memset(io_bias_, 0, 4 * 4);
    
    calibration_x_ = 0.029304029304029f;
    calibration_y_ = 0.0f;
}
UserSettings::~UserSettings() {}

void UserSettings::Calibrate(uint16_t c1, uint16_t c5) {
    calibration_x_ = 48.0f / (c5 - c1);
    calibration_y_ = 24.0f - c1 * calibration_x_;
}
