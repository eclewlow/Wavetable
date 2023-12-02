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
        SETTING_SCOPE_LINE = 0,
        SETTING_SCOPE_FILL = 1,
    };
    enum SettingMorph {
        SETTING_MORPH_SMOOTH    = 0,
        SETTING_MORPH_DISCRETE  = 1,
    };

    enum SubOscWave {
        SUBOSC_WAVE_SINE        = 0,
        SUBOSC_WAVE_TRIANGLE    = 1,
        SUBOSC_WAVE_SAWTOOTH    = 2,
        SUBOSC_WAVE_RAMP        = 3,
        SUBOSC_WAVE_SQUARE      = 4,
        SUBOSC_WAVE_COPY        = 5,
        SUBOSC_WAVE_LAST        = 6,
    };
    
    enum IOConfigurationMenuGain {
        IO_CONFIG_GAIN_1V   = 0,
        IO_CONFIG_GAIN_2V5  = 1,
        IO_CONFIG_GAIN_5V   = 2,
        IO_CONFIG_GAIN_10V  = 3,
        IO_CONFIG_GAIN_LAST = 4,
    };

    inline void setBrightness(int8_t brightness) { brightness_ = std::clamp<int8_t>(brightness, 0, 100); }
    inline int8_t getBrightness() {return brightness_;}

    inline void setContrast(int8_t contrast) { contrast_ = std::clamp<int8_t>(contrast, 0, 100); }
    inline int8_t getContrast() {return contrast_;}

    inline void setInvert(bool invert) { invert_ = invert; }
    inline bool getInvert() {return invert_;}

    inline void setScopeSetting(int8_t scope_setting) { scope_setting_ = scope_setting; }
    inline int8_t getScopeSetting() {return scope_setting_;}

    inline void setMorphSetting(int8_t morph_setting) { morph_setting_ = morph_setting; }
    inline int8_t getMorphSetting() {return morph_setting_;}

    inline void setSubOscOffset(int8_t offset) { suboscOffset_ = std::clamp<int8_t>(offset, -24, 24); }
    inline int8_t getSubOscOffset() {return suboscOffset_;}

    inline void setSubOscDetune(int8_t detune) { suboscDetune_ = std::clamp<int8_t>(detune, -50, 50); }
    inline int8_t getSubOscDetune() {return suboscDetune_;}

    inline void setSubOscMix(uint8_t mix) { suboscMix_ = std::clamp<int8_t>(mix, 0, 100); }
    inline int8_t getSubOscMix() {return suboscMix_;}

    inline void setSubOscWave(int8_t wave) { suboscWave_ = wave; }
    inline int8_t getSubOscWave() {return suboscWave_;}
    
    inline int32_t getAppStartTime() { return app_start_time_; }

    inline void setIOGain(int8_t channel, int8_t gain) { io_gain_[channel] = gain; }
    inline int8_t getIOGain(int8_t channel) { return io_gain_[channel]; }

    inline void setIOBias(int8_t channel, float bias) { io_bias_[channel] = bias; }
    inline float getIOBias(int8_t channel) { return io_bias_[channel]; }

private:
    int8_t brightness_;
    int8_t contrast_;
    bool invert_;
    int8_t scope_setting_;
    int8_t morph_setting_;
    
    int8_t suboscOffset_;
    int8_t suboscDetune_;
    int8_t suboscMix_;
    int8_t suboscWave_;
    uint32_t app_start_time_;
    
    int8_t io_gain_[4];
    float io_bias_[4];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UserSettings);
};
