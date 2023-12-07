/*
  ==============================================================================

    Storage.cpp
    Created: 20 Nov 2023 5:41:08pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "wavetables.h"
#include "Globals.h"

bool Storage::EraseAll() {
    for(int table = 0; table < FACTORY_WAVETABLE_COUNT + USER_WAVETABLE_COUNT; table++) {
        if(table < FACTORY_WAVETABLE_COUNT) {
            snprintf(WaveTables[table].name, 9, "TABLE %d", table);
            WaveTables[table].factory_preset = true;
        } else {
            strncpy(WaveTables[table].name, "\0", 9);
            WaveTables[table].factory_preset = false;
        }
        for(int frame = 0; frame < 16; frame++) {
            WaveTables[table].waves[frame].memory_location = table * 16 * 2048 + frame * 2048;
            if(table < FACTORY_WAVETABLE_COUNT) {
                snprintf(WaveTables[table].waves[frame].name, 9, "%02d", frame);
            } else {
                strncpy(WaveTables[table].waves[frame].name, "\0", 9);
            }
        }
    }
    for(int table = FACTORY_WAVETABLE_COUNT; table <  FACTORY_WAVETABLE_COUNT + USER_WAVETABLE_COUNT; table++) {
        for(int frame = 0; frame < 16; frame++)
            memset(&ROM[WaveTables[table].waves[frame].memory_location], 0, 2048 * 2);

    }
}

int16_t Storage::LoadWaveSample(int table, int frame, int index) {

    WAVETABLE t = WaveTables[table];
        
    // TODO: this should be a read to ROM data
    // the wavetable struct data exists in MCU flash
    // and the wave struct data exists in MCU flash
    // but the wave struct data field points to a memory location in ROM.
    return ROM[t.waves[frame].memory_location + index];
}

void Storage::LoadWaveSample(int16_t * wavedata, int16_t table, int16_t frame) {
    WAVETABLE t = WaveTables[table];

    const int16_t * data = &ROM[t.waves[frame].memory_location];
    memcpy(wavedata, data, 2048 * 2);
}


void Storage::LoadWaveSample(int16_t * wavedata, int16_t table, float morph) {
    
    float frequency = 23.4375;

    float phaseIncrement = frequency / 48000.0f;
    
    float phase = 0.0f;
    
    for(int i = 0; i < 2048; i++) {
        float index = phase * 2048.0f;
        uint16_t integral = floor(index);
        float fractional = index - integral;
        
        uint16_t nextIntegral = (integral + 1) % 2048;
        
        float frame = morph * 15.0f;
        uint16_t frame_integral = floor(frame);
        float frame_fractional = frame - frame_integral;
        
        uint16_t next_frame_integral = (frame_integral + 1) % 16;

        float sample;

        if(frame_fractional > 0.0f) {
            // we need to morph between frames
            float sample1 = LoadWaveSample(table, frame_integral, integral);
            float sample2 = LoadWaveSample(table, frame_integral, nextIntegral);
            
            float interpolated16 = sample1 + (sample2 - sample1) * fractional;
            
            float interpolatedFloat = interpolated16 / 32768.0f;
            
            sample = interpolatedFloat;
            
            sample1 = LoadWaveSample(table, next_frame_integral, integral);
            sample2 = LoadWaveSample(table, next_frame_integral, nextIntegral);
            
            interpolated16 = sample1 + (sample2 - sample1) * fractional;
            
            interpolatedFloat = interpolated16 / 32768.0f;
            
            sample = (1 - frame_fractional) * sample + frame_fractional * interpolatedFloat;

        } else {
            // just do the phase morph
            float sample1 = LoadWaveSample(table, frame_integral, integral);
            float sample2 = LoadWaveSample(table, frame_integral, nextIntegral);
            
            float interpolated16 = sample1 + (sample2 - sample1) * fractional;
            
            float interpolatedFloat = interpolated16 / 32768.0f;
            
            sample = interpolatedFloat;
        }
                
        phase += phaseIncrement;
        
        if(phase >= 1.0f)
            phase -= 1.0f;
        
        wavedata[i] = static_cast<int16_t>(sample * 32767.0f);
    }
}

int8_t Storage::GetNumberOfWavesInTable(int16_t table) {
    int8_t count = 0;
    
    WAVETABLE t = WaveTables[table];
    if(t.factory_preset)
        return 16;
    
    for(int8_t i = 0; i < 16; i++) {
        if(t.waves[i].name[0] != '\0')
            count++;
    }
    
    return count;
}

bool Storage::SaveWavetable(char * name, int table) {
    // make sure wavetable is not in factory memory
    WAVETABLE * t = GetWavetable(table);

    if(t->factory_preset)
        return false;

    strncpy(t->name, name, 9);
    
    return true;
}

bool Storage::SaveWave(const char * name, int16_t * data, int table, int frame) {
    WAVETABLE * t = GetWavetable(table);
    if(t->factory_preset)
        return false;

    std::strncpy(t->waves[frame].name, name, 9);
    
    t->waves[frame].memory_location = 2048 * 16 * table + 2048 * frame;
    
    std::memcpy((void*)&ROM[t->waves[frame].memory_location], data, 2048 * 2);

    return true;
}

bool Storage::DeleteWavetable(int table) {
    WAVETABLE * t = GetWavetable(table);
    if(t->factory_preset)
        return false;

    for (int8_t i = 0; i < 16; i++) {
        memset(t->waves[i].name, 0, 9);
        memset(&ROM[t->waves[i].memory_location], 0, 2048 * 2);

    }
    memset(t->name, 0, 9);
    return true;
}

bool Storage::DeleteWave(int table, int frame) {
    WAVETABLE * t = GetWavetable(table);
    if(t->factory_preset)
        return false;
    
    memset(t->waves[frame].name, 0, 9);
    memset(&ROM[t->waves[frame].memory_location], 0, 2048 * 2);
    return true;
}

bool Storage::SwapWaves(int table, int frame1, int frame2) {
    WAVETABLE wt = WaveTables[table];
    
    if(wt.factory_preset)
        return false;
    
    WAVE w = WaveTables[table].waves[frame1];
    
    WaveTables[table].waves[frame1] = WaveTables[table].waves[frame2];
    WaveTables[table].waves[frame2] = w;
    return true;
}

bool Storage::SwapWavetables(int table1, int table2) {
        // easy swap
    WAVETABLE wt = WaveTables[table1];
    WaveTables[table1] = WaveTables[table2];
    WaveTables[table2] = wt;
    return true;
    /*
     // swapping wavetables requires swapping of all wave data memory locations.
    char name_buffer1[9];
    char name_buffer2[9];

    for(int frame = 0; frame < 16; frame++) {
        // TODO: if the wave doesn't exist, we have to update the memory_location before swapping
        if(!WaveDoesExist(table1, frame)) {
            WaveTables[table1].waves[frame].memory_location = 2048 * 16 * table1 + 2048 * frame;
        }
        if(!WaveDoesExist(table2, frame)) {
            WaveTables[table2].waves[frame].memory_location = 2048 * 16 * table2 + 2048 * frame;
        }

        // swap frames between tables
        uint16_t swap_buffer1[2048];
        uint16_t swap_buffer2[2048];

        std::memcpy(swap_buffer1, &ROM[WaveTables[table1].waves[frame].memory_location], 2048 * 2);
        std::memcpy(swap_buffer2, &ROM[WaveTables[table2].waves[frame].memory_location], 2048 * 2);
        strncpy(name_buffer1, WaveTables[table1].waves[frame].name, 9);
        strncpy(name_buffer2, WaveTables[table2].waves[frame].name, 9);

        std::memcpy(&ROM[WaveTables[table1].waves[frame].memory_location], swap_buffer2, 2048 * 2);
        std::memcpy(&ROM[WaveTables[table2].waves[frame].memory_location], swap_buffer1, 2048 * 2);
        strncpy(WaveTables[table1].waves[frame].name, name_buffer2, 9);
        strncpy(WaveTables[table2].waves[frame].name, name_buffer1, 9);
    }

    strncpy(name_buffer1, WaveTables[table1].name, 9);
    strncpy(name_buffer2, WaveTables[table2].name, 9);
    strncpy(WaveTables[table1].name, name_buffer2, 9);
    strncpy(WaveTables[table2].name, name_buffer1, 9);

    return false;
     //*/
}
//
//int16_t Storage::NumAvailableWaveSlots() {
//    int16_t count = 0;
//    for(int i = 0; i < FACTORY_WAVE_COUNT + USER_WAVE_COUNT; i ++) {
//        if(Waves[i].name[0] != '\0')
//            count ++;
//    }
//    return count;
//}
//
//int16_t Storage::NextAvailableWaveSlot() {
//    for(int i = 0; i < FACTORY_WAVE_COUNT + USER_WAVE_COUNT; i ++) {
//        if(Waves[i].name[0] != '\0')
//            return i;
//    }
//    return -1;
//}

