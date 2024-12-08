/*
  ==============================================================================

    BrunPitchWheel.h
    Created: 16 Nov 2021 2:10:36pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "WilsonicPitchWheelComponent.h"

// this subclass is to help out with crash reports/stack traces

class BrunPitchWheel 
: public WilsonicPitchWheelComponent
{
    // lifecycle
public:
    BrunPitchWheel (WilsonicProcessor&, bool start_timer);
    ~BrunPitchWheel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrunPitchWheel)

};
