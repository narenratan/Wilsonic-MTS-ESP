/*
  ==============================================================================

    VoiceState.h
    Created: 15 May 2021 3:13:19pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "Tuning_Include.h"
#include "TuningConstants.h"

struct VoiceState
{
public:
    VoiceState() = default;
    VoiceState(unsigned long _nn, float _frequency, float _velocity, float _rms, float _peak);
    unsigned long nn = 60;
    float frequency = TuningConstants::middleCFrequency;
    float velocity = 1.f;
    float rms = 0.f;
    float peak = 0.f;
    string getDescription();
};
