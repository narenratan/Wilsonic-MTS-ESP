/*
 ==============================================================================

 WilsonicAppTuningComponent.cpp
 Created: 26 Aug 2021 7:43:40pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "WilsonicAppTuningComponent.h"
#include "AppExperiments.h"
#include "WilsonicAppSkin.h"
#include "WilsonicProcessor.h"

#pragma mark - lifecycle

WilsonicAppTuningComponent::WilsonicAppTuningComponent (WilsonicProcessor& processor)
: WilsonicComponentBase (processor)
{

}

WilsonicAppTuningComponent::~WilsonicAppTuningComponent()
{

}

#pragma mark - drawing

void WilsonicAppTuningComponent::paint (Graphics& g)
{
    // BG
    g.fillAll (_processor.getAppSkin().getBgColor());
    
    if (AppExperiments::showDebugBoundingBox)
    {
        // DEBUG
        g.setColour (Colours::magenta);
        g.drawRect (getLocalBounds(), 2);

        // counter
        g.drawText (String (_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }
}

void WilsonicAppTuningComponent::resized()
{

}

int WilsonicAppTuningComponent::getFirstComboBoxInset()
{
    auto const margin = static_cast<int>(WilsonicAppSkin::tuningComponentInteriorMargin);
    auto const minHitpointSize = WilsonicAppSkin::minHitPointSize;
    auto const retVal = 2 * margin + minHitpointSize;

    return static_cast<int>(retVal);
}
