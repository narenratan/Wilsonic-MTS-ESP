/*
  ==============================================================================

    EqualTemperamentMorphModel.h
    Created: 17 Dec 2023 1:34:17pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MorphModelBase.h"
#include "Tuning_Include.h"

// forward
class EqualTemperament;

//
class EqualTemperamentMorphModel final
: public MorphModelBase
{
public:
    EqualTemperamentMorphModel();
    ~EqualTemperamentMorphModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqualTemperamentMorphModel)

public:
    /**
     * @brief Public methods.
     */
    void parameterChanged(const String& parameterID, float newValue) override;
    shared_ptr<Tuning> getTuning() override;

private:
    /**
     * @brief Private members and methods.
     */
    shared_ptr<EqualTemperament> _scale;
};
