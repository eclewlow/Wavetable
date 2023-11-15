/*
  ==============================================================================

    Effect.cpp
    Created: 12 Nov 2023 4:26:44pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Effect.h"
#include "Globals.h"

void Effect::Init() {
    phase = 0.0f;
    oscilloscopePhase = 0.0f;
}

void Effect::Reset() {
    phase = 0.0f;
    oscilloscopePhase = 0.0f;
}

float Effect::GetSine(float phase) {
    float sample = sin(2 * M_PI * phase);
    return sample;
}

// This function calculates the PolyBLEPs
float Effect::poly_blep(float t, float dt)
{
//    double dt = phase;
    
    // t-t^2/2 +1/2
    // 0 < t <= 1
    // discontinuities between 0 & 1
    if (t < dt)
    {
        t /= dt;
        return t + t - t * t - 1.0;
    }
    
    // t^2/2 +t +1/2
    // -1 <= t <= 0
    // discontinuities between -1 & 0
    else if (t > 1 - dt)
    {
        t = (t - 1.0) / dt;
        return t * t + t + t + 1.0;
    }
    
    // no discontinuities
    // 0 otherwise
    else return 0.0;
}

float Effect::GetSawtooth(float phase, float phase_increment) {
    float value = (2.0f * phase - 1.0f) * 1.0;
    
    if(phase + phase_increment >= 1.0f) {
        phase = phase + phase_increment - 1.0f;
        float t = phase / phase_increment;
        value -= ThisBlepSample(t);
    } else if(phase < phase_increment) {
        float t = phase / phase_increment;
        value -= NextBlepSample(t);
    }
    
    return value;
}

float Effect::GetSquare(float phase, float phase_increment) {
    float value = phase < 0.5 ? 0.0 : 1.0;
    //(2.0f * phase - 1.0f) * 1.0;
    
    if(phase + phase_increment >= 0.5f && phase < 0.5f) {
        phase = phase + phase_increment - 0.5f;
        float t = phase / phase_increment;
        value += ThisBlepSample(t);
    } else if(phase >= 0.5f && phase - phase_increment < 0.5f) {
        float t = (phase - 0.5f) / phase_increment;
        value += NextBlepSample(t);
    }

    if(phase + phase_increment >= 1.0f) {
        phase = phase + phase_increment - 1.0f;
        float t = phase / phase_increment;
        value -= ThisBlepSample(t);
    } else if(phase < phase_increment) {
        float t = phase / phase_increment;
        value -= NextBlepSample(t);
    }

    return value;
}

float Effect::GetTriangle(float phase) {
    
}
