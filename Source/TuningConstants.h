/*
  ==============================================================================

    TuningConstants.h
    Created: 15 Nov 2022 10:44:21am
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

class TuningConstants
{
public:
    // non-octave support: definition of period = [1, period)
    static constexpr float minPeriod = 1.f; // THIS MUST NEVER CHANGE
    static constexpr float defaultPeriod = 2.f; // THIS MUST NEVER CHANGE
    static constexpr float maxPeriod = 20.f; // we can play with this

    // octave
    static constexpr float defaultOctave = defaultPeriod; // THIS MUST NEVER CHANGE

    // default frequency at A NN=69
    static constexpr float defaultFrequencyA69 = 440.f;
    static constexpr float defaultNoteNumberA69 = 69;
    
    // default frequency at C NN = 60
    static constexpr float middleCFrequency = 261.6255653006f;
    static constexpr unsigned long middleCNoteNumber = 60;
};
