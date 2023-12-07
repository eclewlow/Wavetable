/*
 ==============================================================================
 
 Storage.h
 Created: 20 Nov 2023 5:41:08pm
 Author:  Eugene Clewlow
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "wavetables.h"
#include "Globals.h"

class Storage {
public:
    typedef struct {
        char name[9];
        uint32_t memory_location;
        bool factory_preset;
    } WAVE;
    
    typedef struct {
        char name[9];
        WAVE waves[16];
        bool factory_preset;
    } WAVETABLE;
    
    Storage() {};
    ~Storage() {};
    int16_t LoadWaveSample(int table, int frame, int index);
    void LoadWaveSample(int16_t * waveform, int16_t wavetable, float morph);
    void LoadWaveSample(int16_t * waveform, int16_t wavetable, int16_t frame);
    bool SaveWavetable(char * name, int table);
    bool SaveWave(const char * name, int16_t * data, int table, int frame);
    bool SwapWavetables(int table1, int table2);
    bool DeleteWavetable(int table);
    bool WaveDoesExist(int table, int frame);
    bool EraseAll();
    int8_t GetNumberOfWavesInTable(int16_t table);
    inline WAVETABLE GetWavetable(int8_t table) { return WaveTables[table]; }
    inline WAVETABLE* GetWavetables() { return WaveTables; }
    //    int16_t NumAvailableWaveSlots();
    //    int16_t NextAvailableWaveSlot();
private:
    // 64 wavetables.  32 Factory, 32 User
    // 1024 waves.  512 Facotry, 512 User
    // 64 snapshots.  64 user.
    int16_t USER_ROM[2048 * USER_WAVE_COUNT];
    
    WAVETABLE WaveTables[FACTORY_WAVETABLE_COUNT + USER_WAVETABLE_COUNT];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Storage);
};
