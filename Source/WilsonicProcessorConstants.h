/*
  ==============================================================================

    WilsonicProcessorConstants.h
    Created: 26 May 2021 7:34:11pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

/**
 * @file WilsonicProcessorConstants.h
 * @brief This file contains the constants used by the WilsonicProcessor.
 */

#pragma once

/**
 * @class WilsonicProcessorConstants
 * @brief This class contains constants used by the WilsonicProcessor.
 */
class WilsonicProcessorConstants
{
public:
    /**
     * @brief Depending on the plugin type, different constants are defined.
     * 
     * If the plugin is a synth, numVoices is set to 5 and identifier is set to "Wilsonic".
     * If the plugin is a MIDI effect, numVoices is set to 5 and identifier is set to "WilsonicController".
     * If the plugin is neither, an assertion failure is triggered and numVoices is set to 5 and identifier is set to "Fubar".
     */
#if JucePlugin_IsSynth
    static constexpr unsigned long numVoices = 5;
    static constexpr const char* identifier = "Wilsonic";
#elif JucePlugin_IsMidiEffect
    static constexpr unsigned long numVoices = 5;
    static constexpr const char* identifier = "WilsonicController";
#else
    jassertfalse;
    static constexpr unsigned long numVoices = 5;
    static constexpr const char* identifier = "Fubar";
#endif
    static constexpr unsigned long numChannelsToProcess = 2;
    static constexpr int defaultMidiChannel = 1;
    static constexpr float defaultVelocity = 0.9f;
    static constexpr int defaultNumPrecisionDigits = 6;
    static constexpr int defaultUIUpdateFrequencyHz = 24; // Hz
    
    /**
     * @brief The number of MIDI notes. This value must never change.
     */
    static constexpr unsigned long numMidiNotes = 128; 
};
