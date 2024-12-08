/*
  ==============================================================================

    TritriadicMorphModel.h
    Created: 17 Dec 2023 1:38:46pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MorphModelBase.h"
#include "Tuning_Include.h"

class TritriadicTuning;

class TritriadicMorphModel final
: public MorphModelBase
{
public:
    TritriadicMorphModel();
    ~TritriadicMorphModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TritriadicMorphModel)
    
public:
    void parameterChanged(const String& parameterID, float newValue) override;
    shared_ptr<Tuning> getTuning() override;

private:
    // private members
    shared_ptr<TritriadicTuning> _tritriadicTuning;
};
