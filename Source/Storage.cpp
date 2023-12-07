/*
  ==============================================================================

    Storage.cpp
    Created: 20 Nov 2023 5:41:08pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "wavetables.h"
#include "Globals.h"

int16_t Storage::LoadWaveSample(int table, int frame, int index) {
    if(!WaveDoesExist(table, frame))
        return 0;

    WAVETABLE wavetable = WaveTables[table];
        
    // TODO: this should be a read to ROM data
    // the wavetable struct data exists in MCU flash
    // and the wave struct data exists in MCU flash
    // but the wave struct data field points to a memory location in ROM.
    return ROM[wavetable.waves[frame].memory_location + index];
}

void Storage::LoadWaveSample(int16_t * waveform, int16_t wavetable, int16_t frame) {
    if(!WaveDoesExist(wavetable, frame))
    {
        memset(waveform, 0, 2048 * 2);
        return;
    }

    const int16_t * data = &ROM[WaveTables[wavetable].waves[frame].memory_location];
    memcpy(waveform, data, 2048 * 2);
}


void Storage::LoadWaveSample(int16_t * waveform, int16_t wavetable, float morph) {
    
    if(WaveTables[wavetable].name[0] == '\0')
    {
        memset(waveform, 0, 2048 * 2);
        return;
    }
    
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
            float sample1 = LoadWaveSample(wavetable, frame_integral, integral);
            float sample2 = LoadWaveSample(wavetable, frame_integral, nextIntegral);
            
            float interpolated16 = sample1 + (sample2 - sample1) * fractional;
            
            float interpolatedFloat = interpolated16 / 32768.0f;
            
            sample = interpolatedFloat;
            
            sample1 = LoadWaveSample(wavetable, next_frame_integral, integral);
            sample2 = LoadWaveSample(wavetable, next_frame_integral, nextIntegral);
            
            interpolated16 = sample1 + (sample2 - sample1) * fractional;
            
            interpolatedFloat = interpolated16 / 32768.0f;
            
            sample = (1 - frame_fractional) * sample + frame_fractional * interpolatedFloat;

        } else {
            // just do the phase morph
            float sample1 = LoadWaveSample(wavetable, frame_integral, integral);
            float sample2 = LoadWaveSample(wavetable, frame_integral, nextIntegral);
            
            float interpolated16 = sample1 + (sample2 - sample1) * fractional;
            
            float interpolatedFloat = interpolated16 / 32768.0f;
            
            sample = interpolatedFloat;
        }
                
        phase += phaseIncrement;
        
        if(phase >= 1.0f)
            phase -= 1.0f;
        
        waveform[i] = static_cast<int16_t>(sample * 32767.0f);
    }
}

int8_t Storage::GetNumberOfWavesInTable(int16_t table) {
    int8_t count = 0;
    
//    if(table < FACTORY_WAVETABLE_COUNT)
//        return 16;
    if(WaveTables[table].name[0] == '\0')
        return 0;
    
    for(int8_t i = 0; i < 16; i++) {
        if(WaveTables[table].waves[i].name[0] != '\0')
            count++;
    }
    
    return count;
}

bool Storage::SaveWavetable(char * name, int table) {
    // make sure wavetable is not in factory memory
    if(table < FACTORY_WAVETABLE_COUNT)
        return false;
    
    memcpy(WaveTables[table].name, name, 9);
    
    return true;
}

bool Storage::SaveWave(const char * name, int16_t * data, int table, int frame) {
    if(table < FACTORY_WAVETABLE_COUNT)
        return false;

    std::strncpy(WaveTables[table].waves[frame].name, name, 9);
    
    WaveTables[table].waves[frame].memory_location = 2048 * 16 * table + 2048 * frame;
    
    std::memcpy((void*)&ROM[WaveTables[table].waves[frame].memory_location], data, 2048 * 2);

    return true;
}

bool Storage::DeleteWavetable(int table) {
    if(table < FACTORY_WAVETABLE_COUNT)
        return false;

    for (int8_t i = 0; i < 16; i++) {
        memset(WaveTables[table].waves[i].name, 0, 9);
    }
    memset(WaveTables[table].name, 0, 9);
    return true;
}

bool Storage::SwapWavetables(int table1, int table2) {
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

bool Storage::WaveDoesExist(int table, int frame) {
    if(table < FACTORY_WAVETABLE_COUNT)
        return true;

    return WaveTables[table].name[0] != '\0' && WaveTables[table].waves[frame].name[0] != '\0';
}
