/*
 ==============================================================================
 
 system_clock.h
 Created: 6 Dec 2023 2:46:36pm
 Author:  Eugene Clewlow
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>

class SystemClock {
public:
    SystemClock() { }
    ~SystemClock() { }
    
    inline void Init() { count_ = 0; }
    inline void Tick() { ++count_; }
    inline volatile uint32_t milliseconds() const { return count_; }
    inline void Delay(uint32_t ms) {
        uint32_t target = milliseconds() + ms;
        while (milliseconds() <= target);
    }
    
private:
    volatile uint32_t count_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SystemClock);
};

//extern SystemClock system_clock;
