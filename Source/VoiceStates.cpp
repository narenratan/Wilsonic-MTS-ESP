/*
  ==============================================================================

    VoiceStates.cpp
    Created: 16 May 2021 12:43:05pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "VoiceStates.h"

VoiceStates::VoiceStates()
{
    for (unsigned long i = 0; i < WilsonicProcessorConstants::numVoices; i++)
    {
        voiceState[i] = VoiceState();
    }
}

// sum of rms is near zero
bool VoiceStates::noVoicesPlaying()
{
    auto rms = 0.0f;
    for (unsigned long i = 0; i < WilsonicProcessorConstants::numVoices; i++)
    {
        rms += voiceState[i].rms;
    }
    return fabsf(rms) < 0.1f;
}

