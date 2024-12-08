/*
  ==============================================================================

    RootTuningContainer.h
    Created: 7 Mar 2021 5:01:17pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WilsonicAppSkin.h"
#include "WilsonicComponentBase.h"
#include "WilsonicProcessor.h"

class WilsonicTuningContainer 
: public WilsonicComponentBase
{
// lifecycle
public:
    WilsonicTuningContainer(WilsonicProcessor&);
    ~WilsonicTuningContainer() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WilsonicTuningContainer)


public:
    // drawing
    void paint(Graphics&) override;
    void resized() override;
};
