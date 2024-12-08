/*
  ==============================================================================

    ParameterListeners.h
    Created: 7 Nov 2021 12:37:44pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

using VtsListener = AudioProcessorValueTreeState::Listener;

struct BoolListener : public VtsListener
{
    bool& workingValue;

    BoolListener (bool& wv) : VtsListener(), workingValue(wv) {}
    void parameterChanged (const String&, float newValue) override
    {
        workingValue = newValue >= 0.5f;
    }
};

struct IntegerListener : public VtsListener
{
    int& workingValue;
    int offset, multiplier;

    IntegerListener (int& wv, int ofs=0, int mp=1)
        : VtsListener(), workingValue (wv), offset (ofs), multiplier (mp) {}
    void parameterChanged (const String&, float newValue) override
    {
        workingValue = int (newValue) * multiplier + offset;
    }
};

struct FloatListener : public VtsListener
{
    float& workingValue;
    float scaleFactor;

    FloatListener (float& wv, float sf = 1.0f) : VtsListener(), workingValue (wv), scaleFactor (sf) {}
    void parameterChanged (const String&, float newValue) override
    {
        workingValue = scaleFactor * newValue;
    }
};
