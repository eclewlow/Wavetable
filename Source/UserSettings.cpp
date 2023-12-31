/*
  ==============================================================================

    UserSettings.cpp
    Created: 15 Nov 2023 1:42:55am
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Globals.h"

UserSettings::UserSettings() {
    app_start_time_ = system_clock.milliseconds();
    ResetSettings();
}
UserSettings::~UserSettings() {}

void UserSettings::Calibrate(uint16_t c1, uint16_t c5) {
    settings_.calibration_x = 48.0f / (c5 - c1);
    // c1 2457 4095
    // perfect pitch
    // 0v * 33k / 80.6k = 0
    // 8V * 33k / 80.6k = 3.275434243176179 = x
    // x / 3.3  = 0.992555831265509
    // * 4095 = 4064.516129032259355
    // 1 V -> 508.064516129032258
    // 5 V -> 2540.32258064516129
    // x = 0.023619047619048
    // y = 12
    
    // 0 4095   is 0-8 volts   c0 to c8. 33k / 80k
    // c1 = 511.875
    // c5 2559.375
    // x = 0.023443223443223
    // y = 12
    
    // 0 4095 -5 to 5 volts
    // x = 0.029304029304029
    // y = -48
    settings_.calibration_y = 24.0f - c1 * settings_.calibration_x;
}

bool UserSettings::ResetSettings() {
    storage.EraseSnapshot(&settings_, FACTORY_SNAPSHOT_COUNT, false);
    return true;
}

bool UserSettings::LoadSnapshot(int8_t snapshot) {
    memcpy(&settings_, storage.GetSnapshot(snapshot), sizeof(Storage::SNAPSHOT));
    return true;
}

float UserSettings::RandomFloat(float min, float max)
{
    // this  function assumes max > min, you may want
    // more robust error checking for a non-debug build
//    assert(max > min);
    float random = ((float) rand()) / (float) RAND_MAX;

    // generate (in your case) a float between 0 and (4.5-.78)
    // then add .78, giving you a float between .78 and 4.5
    float range = max - min;
    return (random * range) + min;
}

int32_t UserSettings::RandomInt(int32_t min, int32_t max)
{
    return rand() % (max - min + 1) + min;
}

bool UserSettings::RandomizeSettings() {
    settings_.factory_preset = false;
    settings_.is_empty = false;
    strncpy(settings_.name, "INIT", 9);
    settings_.brightness = 100;
    settings_.contrast = 100;
    settings_.invert = false;
    settings_.scope_setting = UserSettings::SETTING_SCOPE_LINE;
    settings_.morph_setting = UserSettings::SETTING_MORPH_SMOOTH;
    
    // sub osc parameters
    settings_.subosc_offset = RandomInt(-24, 24);
    settings_.subosc_detune = RandomInt(-50, 50);
    settings_.subosc_mix = RandomInt(0, 100);
    settings_.subosc_wave = RandomInt(0, 5);
    
    settings_.fx_depth = RandomFloat(0.0f, 1.0f);
    settings_.fx_sync = RandomInt(0, 1);
    settings_.fx_scale = 0;
    settings_.fx_range = 1;
    settings_.fx_oscillator_shape = RandomInt(0, 5);
    settings_.fx_control_type = RandomInt(0, 2);
    settings_.fx_effect = RandomInt(0, 7);

    settings_.engine = RandomInt(0, 3);
    // ab engine parameters
    settings_.ab_engine_left_wavetable = RandomInt(0, FACTORY_WAVETABLE_COUNT - 1);
    settings_.ab_engine_left_frame = RandomInt(0, 15);
    settings_.ab_engine_right_wavetable = RandomInt(0, FACTORY_WAVETABLE_COUNT - 1);
    settings_.ab_engine_right_frame = RandomInt(0, 15);
    settings_.ab_engine_is_editing_left = false;
    settings_.ab_engine_is_editing_right = false;

    // wavetable engine parameters
    settings_.wavetable_engine_wavetable = RandomInt(0, FACTORY_WAVETABLE_COUNT - 1);
    
    // matrix engine parameters
    settings_.matrix_engine_x1 = RandomInt(0, 15);
    settings_.matrix_engine_x2 = RandomInt(settings_.matrix_engine_x1, 15);
    settings_.matrix_engine_y1 = RandomInt(0, 15);
    settings_.matrix_engine_y2 = RandomInt(settings_.matrix_engine_y1, 15);
    settings_.matrix_engine_wavelist_offset = 0; //(0, USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 16 - 1);
    
    // drum engine parameters
    settings_.drum_engine_amp_decay = RandomFloat(0.0f, 1.0f);
    settings_.drum_engine_fm_decay = RandomFloat(0.0f, 1.0f);
    settings_.drum_engine_fm_shape = RandomFloat(0.0f, 1.0f);
    settings_.drum_engine_fm_depth = RandomFloat(0.0f, 1.0f);
    settings_.drum_engine_wavetable = RandomInt(0, FACTORY_WAVETABLE_COUNT - 1);

    // pot settings
    settings_.pot_fx_amount = RandomInt(0, 4095);
    settings_.pot_fx = RandomInt(0, 4095);
    settings_.pot_morph = RandomInt(0, 4095);
    
    // calibration settings
    for(int i = 0; i < 4; i++) {
        settings_.io_gain[i] = 1.0f;   // don't randomize this, but save in snapshot
        settings_.io_bias[i] = 0.0f;   // don't randomize this, but save in snapshot
    }

    settings_.calibration_x = 0.023619047619048;    // don't randomize this, but save in snapshot
    settings_.calibration_y = 12;    // don't randomize this, but save in snapshot
    
    return true;
}

bool UserSettings::SaveSnapshot(const char * name, uint8_t index) {
    storage.SaveSnapshot(name, index, &settings_);
    return true;
}
