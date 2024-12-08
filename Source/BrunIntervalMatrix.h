/*
  ==============================================================================

    BrunIntervalMatrix.h
    Created: 16 Nov 2021 2:10:49pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "WilsonicIntervalMatrixComponent.h"

// this subclass is to help out with crash reports/stack traces

class BrunIntervalMatrix : public WilsonicIntervalMatrixComponent
{
    // public methods
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrunIntervalMatrix)

public:
    BrunIntervalMatrix (WilsonicProcessor&);
    ~BrunIntervalMatrix() override;
};
