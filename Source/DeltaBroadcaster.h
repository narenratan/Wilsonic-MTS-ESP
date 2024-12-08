/*
  ==============================================================================

    DeltaBroadcaster.h
    Created: 11 Apr 2023 5:12:09pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"

class DeltaBroadcaster 
: public ChangeBroadcaster
{
public:
    // lifecycle
    DeltaBroadcaster();
    ~DeltaBroadcaster() override;

    // public member functions
    void setDelta(Point<int> newDelta);
    Point<int> getDelta() const;

private:
    // private members
    Point<int> _delta;
};
