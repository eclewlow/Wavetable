/*
  ==============================================================================

    UserSettings.h
    Created: 15 Nov 2023 1:42:55am
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class UserSettings {
public:
    UserSettings();
    ~UserSettings();

    enum SettingScope {
        SETTING_SCOPE_LINE,
        SETTING_SCOPE_SHADED,
    };
    enum SettingMorph {
        SETTING_MORPH_SMOOTH,
        SETTING_MORPH_DISCRETE,
    };

    inline void setBrightness(uint8_t brightness) { brightness_ = std::clamp<uint8_t>(brightness, 0, 100); }
    inline uint8_t getBrightness() {return brightness_;}

    inline void setContrast(uint8_t contrast) { contrast_ = std::clamp<uint8_t>(contrast, 0, 100); }
    inline uint8_t getContrast() {return contrast_;}

    inline void setInvert(bool invert) { invert_ = invert; }
    inline bool getInvert() {return invert_;}

    inline void setScopeSetting(SettingScope scope_setting) { scope_setting_ = scope_setting; }
    inline SettingScope getScopeSetting() {return scope_setting_;}

    inline void setMorphSetting(SettingMorph morph_setting) { morph_setting_ = morph_setting; }
    inline SettingMorph getMorphSetting() {return morph_setting_;}

private:
    uint8_t brightness_;
    uint8_t contrast_;
    bool invert_;
    SettingScope scope_setting_;
    SettingMorph morph_setting_;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UserSettings);
};
