/*
  ==============================================================================

    Persian17NorthIndianMorphModel.h
    Created: 17 Dec 2023 1:36:03pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MorphModelBase.h"
#include "Persian17NorthIndianModel.h"

class Persian17NorthIndianMorphModel final
: public MorphModelBase
{
public:
    Persian17NorthIndianMorphModel();
    ~Persian17NorthIndianMorphModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Persian17NorthIndianMorphModel)

public:
    void parameterChanged(const String& parameterID, float newValue) override;
    shared_ptr<Tuning> getTuning() override;

private:
    shared_ptr<Persian17NorthIndian> _persian17NorthIndian;
};
