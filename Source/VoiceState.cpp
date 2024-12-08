/*
  ==============================================================================

    VoiceState.cpp
    Created: 15 May 2021 3:13:19pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "VoiceState.h"

VoiceState::VoiceState(unsigned long _nn, float _frequency, float _velocity, float _rms, float _peak)
{
    nn = _nn;
    frequency = _frequency;
    velocity = _velocity;
    rms = _rms;
    peak = _peak;
}

string VoiceState::getDescription()
{
    auto retVal = "nn:" + to_string (nn) + ",";
    retVal += "f:" + to_string (frequency) + ",";
    retVal += "vel:" + to_string (velocity) + ",";
    retVal += "rms:" + to_string (rms) + ",";
    retVal += "peak:" + to_string (peak);

    return retVal;
}
