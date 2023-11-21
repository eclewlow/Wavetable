/*
  ==============================================================================

    Storage.h
    Created: 20 Nov 2023 5:41:08pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Storage {
public:
    Storage() {};
    ~Storage() {};
    int16_t LoadWaveSample(int table, int frame, int index);
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Storage);
};
