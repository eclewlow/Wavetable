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
        SETTING_SCOPE_FILL,
    };
    enum SettingMorph {
        SETTING_MORPH_SMOOTH,
        SETTING_MORPH_DISCRETE,
    };

    enum SubOscWave {
        SUBOSC_WAVE_COPY,
        SUBOSC_WAVE_SINE,
        SUBOSC_WAVE_TRIANGLE,
        SUBOSC_WAVE_SAWTOOTH,
        SUBOSC_WAVE_RAMP,
        SUBOSC_WAVE_SQUARE,
        SUBOSC_WAVE_SELECT,
    };

    inline void setBrightness(int8_t brightness) { brightness_ = std::clamp<int8_t>(brightness, 0, 100); }
    inline int8_t getBrightness() {return brightness_;}

    inline void setContrast(int8_t contrast) { contrast_ = std::clamp<int8_t>(contrast, 0, 100); }
    inline int8_t getContrast() {return contrast_;}

    inline void setInvert(bool invert) { invert_ = invert; }
    inline bool getInvert() {return invert_;}

    inline void setScopeSetting(SettingScope scope_setting) { scope_setting_ = scope_setting; }
    inline SettingScope getScopeSetting() {return scope_setting_;}

    inline void setMorphSetting(SettingMorph morph_setting) { morph_setting_ = morph_setting; }
    inline SettingMorph getMorphSetting() {return morph_setting_;}

    inline void setSubOscOffset(int8_t offset) { suboscOffset_ = std::clamp<int8_t>(offset, -24, 24); }
    inline int8_t getSubOscOffset() {return suboscOffset_;}

    inline void setSubOscDetune(int8_t detune) { suboscDetune_ = std::clamp<int8_t>(detune, -50, 50); }
    inline int8_t getSubOscDetune() {return suboscDetune_;}

    inline void setSubOscMix(uint8_t mix) { suboscMix_ = std::clamp<int8_t>(mix, 0, 100); }
    inline int8_t getSubOscMix() {return suboscMix_;}

    inline void setSubOscWave(SubOscWave wave) { suboscWave_ = wave; }
    inline SubOscWave getSubOscWave() {return suboscWave_;}
    
    inline int32_t getAppStartTime() { return app_start_time_; }

private:
    int8_t brightness_;
    int8_t contrast_;
    bool invert_;
    SettingScope scope_setting_;
    SettingMorph morph_setting_;
    
    int8_t suboscOffset_;
    int8_t suboscDetune_;
    int8_t suboscMix_;
    SubOscWave suboscWave_;
    uint32_t app_start_time_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UserSettings);
};
