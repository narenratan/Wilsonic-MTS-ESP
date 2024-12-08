/*
  ==============================================================================

    SynthSound.h
    Created: 9 Mar 2021 8:35:18pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public SynthesiserSound
{
    
public:

    bool appliesToNote (int midiNoteNumber) override;
    
    bool appliesToChannel (int midiChannel) override;
    
};
