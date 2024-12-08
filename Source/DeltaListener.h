/*
  ==============================================================================

    DeltaListener.h
    Created: 11 Apr 2023 5:12:39pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"
#include "DeltaBroadcaster.h"

class DeltaListener : public ChangeListener
{
public:
    // lifecycle
    DeltaListener();
    ~DeltaListener() override;

    // public member functions
    void changeListenerCallback (ChangeBroadcaster* source) override;
};
