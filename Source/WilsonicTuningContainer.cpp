/*
 ==============================================================================
 
 RootTuningContainer.cpp
 Created: 7 Mar 2021 5:01:17pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include <JuceHeader.h>
#include "WilsonicTuningContainer.h"

//==============================================================================
WilsonicTuningContainer::WilsonicTuningContainer (WilsonicProcessor& processor)
: WilsonicComponentBase(processor)
{
    
}

WilsonicTuningContainer::~WilsonicTuningContainer()
{
    
}

void WilsonicTuningContainer::paint(Graphics& g)
{
    // BG
    g.fillAll (_processor.getAppSkin().getBgColor());
    
    if (AppExperiments::showDebugBoundingBox)
    {
        // DEBUG
        g.setColour (Colours::magenta);
        g.drawRect (getLocalBounds(), 1);

        // counter
        g.drawText (String (_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }
}

void WilsonicTuningContainer::resized()
{
    
}
