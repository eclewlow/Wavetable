/*
  ==============================================================================

    quantizer.cpp
    Created: 4 Dec 2023 4:50:49pm
    Author:  Eugene Clewlow

  ==============================================================================
*/

#include "Globals.h"
#define ONE_OCTAVE_12BIT (12.0f * 4095.0f / 120.0f)

Quantizer::Quantizer() {
    scale_ = QUANTIZER_SCALE_PENTATONIC;
}

Quantizer::~Quantizer() {
    
}

void Quantizer::Init() {
    scale_ = QUANTIZER_SCALE_PENTATONIC;
}

void Quantizer::triggerUpdate() {
}

// Returns element closest to target in arr[]
float Quantizer::findClosest(const float arr[], int n, float target)
{
    // Corner cases
    //left-side case
    if (target <= arr[0])
        return arr[0];
    //right-side case
    if (target >= arr[n - 1])
        return arr[n - 1];

    // Doing binary search
    int i = 0, j = n, mid = 0;
    while (i < j) {
        mid = (i + j) / 2;

        if (arr[mid] == target)
            return arr[mid];

        /* If target is less than array element,
            then search in left */
        if (target < arr[mid]) {

            // If target is greater than previous
            // to mid, return closest of two
            if (mid > 0 && target > arr[mid - 1])
                return getClosest(arr[mid - 1], arr[mid], target);
            j = mid;
        }
        /* Repeat for left half */

        // If target is greater than mid
        else {
            if (mid < n - 1 && target < arr[mid + 1])
                return getClosest(arr[mid], arr[mid + 1], target);
            // update i
            i = mid + 1;
        }
    }
    // Only single element left after search
    return arr[mid];
}

// Method to compare which one is the more close.
// We find the closest by taking the difference
// between the target and both values. It assumes
// that val2 is greater than val1 and target lies
// between these two.
float Quantizer::getClosest(float val1, float val2,
                            float target)
{
    if (target - val1 >= val2 - target)
        return val2;
    else
        return val1;
}

float Quantizer::Quantize(float input) {

    if(scale_ == QUANTIZER_SCALE_OFF)
        return input;
    
    // input is a 0.0f to 120.0f [???]  float - type midi value.
    
    uint16_t tune = adc.getChannel(Adc::ADC_CHANNEL_PITCH_POT);
    float tonic = (120.0f * tune) / 4095.0;
    
    float offset = input - tonic;
    // ^ this is the current tuning of the tune pot
    // without cv modulation
    // we want to be able to set a dersired tonic note, and quantize the CV input.
    // now we want to quantize the CV input midi_note offset from the tonic note.
    // so if tonic note = 24.0 (C-1?) and midi_note offset = 26.0f.
    // so we subtract input_midi - tonic = 2.0f, quantize to C scale 0.0f, then add to tonic
    // and if tonic_note = 25.0 (C#-1?) and midi_note offset = 26.0f.
    // so we subtract input_midi - tonic = 1.0f, quantize to C scale 0.0f, then add to tonic
    // what if offset is negative?
    //  well we need to have a midi c scale range from 0 - 120 .  0 - 120.  -120 to 120.

    
//    input = CLAMP<uint16_t>(input, 0, 4095);

    // if current input is close enough to the last input, then we use the last input
    // if (abs(static_cast<int>(input) - static_cast<int>(last_input_)) < 24) {
    //     input = last_input_;
    // }

    // last_input_ = input;


    const float* arr = lut_test;

    float closest = findClosest(arr, 120, offset);
    
    closest = tonic + closest;

    while (closest < 0.0f) {
        closest += 12.0f;
    }
    while (closest > 120.0f) {
        closest -= 12.0f;
    }

    return closest;
}
