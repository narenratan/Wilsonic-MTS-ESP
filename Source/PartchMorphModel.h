/*
  ==============================================================================

    PartchMorphModel.h
    Created: 6 Jun 2024 10:22:35pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MorphModelBase.h"
#include "PartchModel.h"

class PartchMorphModel final
: public MorphModelBase
{
public:
    PartchMorphModel(WilsonicProcessor&);
    ~PartchMorphModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PartchMorphModel)
    
public:
    void parameterChanged(const String& parameterID, float newValue) override;
    shared_ptr<Tuning> getTuning() override;

private:
    WilsonicProcessor& _processor;
    shared_ptr<Partch> _partch;
};
