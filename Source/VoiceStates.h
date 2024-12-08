/*
  ==============================================================================

    VoiceStates.h
    Created: 16 May 2021 12:43:05pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "WilsonicProcessorConstants.h"
#include "VoiceState.h"

struct VoiceStates
{

public:

    VoiceStates();

    VoiceState voiceState[WilsonicProcessorConstants::numVoices] {};

    bool noVoicesPlaying(); // sum of rms is near zero
};
