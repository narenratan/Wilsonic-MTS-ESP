/*
  ==============================================================================

    MeterComponent.h
    Created: 27 Feb 2021 2:11:36am
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomComponent.h"
#include "WilsonicProcessor.h"

class MeterComponent : public CustomComponent
{
    // lifecycle
public:
    MeterComponent (WilsonicProcessor& p);
    ~MeterComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterComponent)

public:
    // public methods
    void paintOverChildren (Graphics& g) override;
    void resized() override;

private:
    // private members
    WilsonicProcessor& processor;
};
