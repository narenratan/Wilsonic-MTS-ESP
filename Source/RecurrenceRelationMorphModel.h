/*
  ==============================================================================

    RecurrenceRelationMorphModel.h
    Created: 17 Dec 2023 1:37:13pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MorphModelBase.h"
#include "Tuning_Include.h"

// forward
class RecurrenceRelation;

//
class RecurrenceRelationMorphModel final
: public MorphModelBase
{
public:
    RecurrenceRelationMorphModel();
    ~RecurrenceRelationMorphModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RecurrenceRelationMorphModel)
    
public:
    /**
     * @brief Public methods.
     */
    void parameterChanged(const String& parameterID, float newValue) override;
    shared_ptr<Tuning> getTuning() override;

private:
    // private members
    shared_ptr<RecurrenceRelation> _recurrenceRelation;
};
