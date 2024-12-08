/*
  ==============================================================================

    MorphModelBase.h
    Created: 7 Jan 2024 2:07:09pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning.h"
#include "Tuning_Include.h"

class MorphModelBase
{
public:
    virtual ~MorphModelBase() noexcept = default;

    virtual void parameterChanged(const String& parameterID, float newValue) = 0;
    virtual shared_ptr<Tuning> getTuning() = 0;
    
protected:
    CriticalSection _lock;
};
