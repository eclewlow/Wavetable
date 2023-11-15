/*
  ==============================================================================

    DeviceConfigurationMenu.h
    Created: 14 Nov 2023 4:40:15pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "State.h"

class State;

class DeviceConfigurationMenu: public State
{
public:
    enum DeviceConfigurationMenuState {
        DEVICE_INFO,
        DEVICE_DISPLAY,
        DEVICE_OSCILLOSCOPE,
        DEVICE_IO,
        DEVICE_CALIBRATION,
        DEVICE_QUANTIZER,
        DEVICE_MEMORY,
    };
    DeviceConfigurationMenu();
    ~DeviceConfigurationMenu();
    virtual bool handleKeyPress(const juce::KeyPress &key);
    virtual void paint(juce::Graphics& g);
    inline void setState(DeviceConfigurationMenuState newState) { currentState = newState; }

private:
    
    DeviceConfigurationMenuState currentState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeviceConfigurationMenu);
};
