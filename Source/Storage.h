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
    
    typedef struct {
        char name[9];

        // misc settings
        int8_t scope_setting_;                  // (0, 1)
        int8_t morph_setting_;                  // (0, 1)

        // sub osc parameters
        int8_t suboscOffset;                    // (-24, 24)
        int8_t suboscDetune;                    // (-50, 50)
        int8_t suboscMix;                       // (0, 100)
        int8_t suboscWave;                      // (0, 5)
        
        // fx parameters
        int8_t fx_depth;                        // (0, 0)
        bool fx_sync;                           // (false, true)
        int8_t fx_scale;                        // (0, 100)
        int8_t fx_range;                        // (1, 10)
        int8_t fx_oscillator_shape;             // (0, 5)
        int8_t fx_control_type;                 // (0, 2)
        int8_t fx_effect;                       // (0, 8)

        // ab engine parameters
        int8_t ab_engine_left_wavetable;        // (0, USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 1)
        int8_t ab_engine_left_frame;            // (0, 15)
        int8_t ab_engine_right_wavetable;       // (0, USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 1)
        int8_t ab_engine_right_frame;           // (0, 15)
//        bool ab_engine_is_editing; set to false for both left and right

        // wavetable engine parameters
        int8_t wavetable_engine_wavetable;      // (0, USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 1)

        // matrix engine parameters
        int8_t matrix_engine_x1;                // (0, 15)
        int8_t matrix_engine_x2;                // (x1, 15)
        int8_t matrix_engine_y1;                // (0, 15)
        int8_t matrix_engine_y2;                // (y1, 15)
        int8_t matrix_engine_wavelist_offset;   // (0, USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 16 - 1)

        // drum engine parameters
        float drum_engine_amp_decay;            // (0.0, 1.0)
        float drum_engine_fm_decay;             // (0.0, 1.0)
        float drum_engine_fm_shape;             // (0.0, 1.0)
        float drum_engine_fm_depth;             // (0.0, 1.0)
        int8_t drum_engine_wavetable;           // (0, USER_WAVETABLE_COUNT + FACTORY_WAVETABLE_COUNT - 1)

        // pot positions
        uint16_t pot_fx_amount;                 // (0, 4095)
        uint16_t pot_fx;                        // (0, 4095)
        uint16_t pot_morph;                     // (0, 4095)
        
        // wavetables list
        // TODO: we need a way of backing up out master wavetables list in memory
        // TODO: so we can recall a snapshot, or revert back to the master list.
//        WAVETABLE WaveTables[FACTORY_WAVETABLE_COUNT + USER_WAVETABLE_COUNT];
        // TODO: can we randomize this?  not the factory presets. but the table order (prioritized for
        // first sixteen waves of wavetables that have 16 waves present, and the wave order can be randomized for non-factory tables.
    } SNAPSHOT;
    
    Storage() {};
    ~Storage() {};
    int16_t LoadWaveSample(int table, int frame, int index);
    void LoadWaveSample(int16_t * wavedata, int16_t table, float morph);
    void LoadWaveSample(int16_t * wavedata, int16_t table, int16_t frame);
    bool SaveWavetable(char * name, int table);
    bool SaveWave(const char * name, int16_t * data, int table, int frame);
    bool SwapWavetables(int table1, int table2);
    bool SwapWaves(int table, int frame1, int frame2);
    bool DeleteWavetable(int table);
    bool DeleteWave(int table, int frame);
    bool CopyWavetable(int table_dst, int table_src);
    bool CopyWave(int table_dst, int frame_dst, int table_src, int frame_src);
    bool EraseAll();
//    bool SaveAllData();
//    bool RestoreAllData();
    int8_t GetNumberOfWavesInTable(int16_t table);
    inline WAVETABLE* GetWavetable(int8_t table) { return &WaveTables[table]; }
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
