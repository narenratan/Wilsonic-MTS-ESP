/*
  ==============================================================================

    Brun2MorphModel.h
    Created: 17 Dec 2023 1:32:01pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Brun2Model.h"
#include "MorphModelBase.h"

class Brun2MorphModel final
: public MorphModelBase
{
public:
    Brun2MorphModel();
    ~Brun2MorphModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Brun2MorphModel)

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
    shared_ptr<Brun> _brun;
};
