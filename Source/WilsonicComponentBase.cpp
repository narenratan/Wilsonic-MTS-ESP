/*
 ==============================================================================

 WilsonicComponentBase.cpp
 Created: 10 Jul 2021 1:46:26pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "WilsonicComponentBase.h"
#include "AppExperiments.h"
#include "WilsonicProcessor.h"

#pragma mark - lifecycle

WilsonicComponentBase::WilsonicComponentBase(WilsonicProcessor& processor)
: _processor(processor)
{
    setOpaque(true);
}

WilsonicComponentBase::~WilsonicComponentBase()
{

}

#pragma mark - drawing

void WilsonicComponentBase::paint(Graphics& g)
{
    // BG
    g.fillAll(_processor.getAppSkin().getBgColor());

    if(AppExperiments::showDebugBoundingBox)
    {
        // DEBUG
        g.setColour(Colours::magenta);
        g.drawRect(getLocalBounds(), 2);

        // counter
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }
}

void WilsonicComponentBase::resized()
{
    
}
