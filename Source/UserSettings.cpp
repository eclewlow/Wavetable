/*
  ==============================================================================

    UserSettings.cpp
    Created: 15 Nov 2023 1:42:55am
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "UserSettings.h"

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
    app_start_time_ = juce::Time::currentTimeMillis();
    
    memset(io_gain_, 0, 4);
    memset(io_bias_, 0, 4 * 4);
}
UserSettings::~UserSettings() {}
