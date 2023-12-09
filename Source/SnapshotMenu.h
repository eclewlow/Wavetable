/*
  ==============================================================================

    SnapshotMenu.h
    Created: 8 Dec 2023 8:42:11pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class SnapshotMenu: public State
{
public:
    enum SnapshotMenuState {
        SNAPSHOT_MENU_NONE,
        SNAPSHOT_MENU_OPTIONS,
    };
    enum SnapshotMenuOptions {
        SNAPSHOT_MENU_SAVE              = 0,
        SNAPSHOT_MENU_COPY              = 1,
        SNAPSHOT_MENU_RENAME            = 2,
        SNAPSHOT_MENU_DELETE            = 3,
        SNAPSHOT_MENU_NO                = 4,
        SNAPSHOT_MENU_YES               = 5,
    };
    

    SnapshotMenu();
    ~SnapshotMenu();
    virtual bool handleKeyPress(int key) { return false; }
    virtual bool handleKeyRelease(int key);
    virtual bool handleKeyLongPress(int key) { return false; }
    virtual void paint(juce::Graphics& g);
    void triggerUpdate(bool back_pressed);
    inline void setState(int8_t state) { state_ = state; }
    inline void setOptionSelected(int8_t option_selected) { option_selected_ = option_selected; }
//    static void SaveWavetable(char* param);
//    static void SaveWave(char* param);

//    inline void setWavedata(int16_t * data) { wavedata_ = data; }
    void ResetTicker();

private:

    int8_t state_;

    int16_t snapshot_offset_;
    int16_t snapshot_;

    int8_t option_selected_;
    int8_t option_offset_;

    uint32_t ticker_timer_ = 0;
    uint8_t ticker_ = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SnapshotMenu);
};
