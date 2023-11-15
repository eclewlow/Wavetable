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
}
UserSettings::~UserSettings() {}
