/*
  ==============================================================================

    MorphTuningComponent.h
    Created: 30 Jan 2024 8:03:52pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"
#include "WilsonicComponentBase.h"

class MorphTuningComponent
: public WilsonicComponentBase
{
public:
    MorphTuningComponent(WilsonicProcessor&);
    ~MorphTuningComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MorphTuningComponent)

public:
    void paint (juce::Graphics&) override;
    void resized() override;
};
