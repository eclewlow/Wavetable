/*
  ==============================================================================

    Storage.cpp
    Created: 20 Nov 2023 5:41:08pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Storage.h"
#include "wavetables.h"

int16_t Storage::LoadWaveSample(int table, int frame, int index) {
//    return ROM[table * (2048 * 16) + frame * 2048 + index];
    WAVETABLE wavetable = getWavetable(table);
    return wavetable.waves[frame][index];
}
