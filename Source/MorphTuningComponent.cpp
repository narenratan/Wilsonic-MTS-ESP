/*
  ==============================================================================

    MorphTuningComponent.cpp
    Created: 30 Jan 2024 8:03:52pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DesignsModel.h"
#include "MorphModel.h"
#include "MorphTuningComponent.h"
#include "WilsonicProcessor.h"

MorphTuningComponent::MorphTuningComponent(WilsonicProcessor& processor)
: WilsonicComponentBase(processor)
{

}

MorphTuningComponent::~MorphTuningComponent()
{

}

void MorphTuningComponent::paint(juce::Graphics& g)
{
    // BG
    g.fillAll(_processor.getAppSkin().getBgColor());

    if (AppExperiments::showDebugBoundingBox)
    {
        // DEBUG
        g.setColour(Colours::lightgreen);
        g.drawRect(getLocalBounds(), 1);

        // counter
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }

    // paint Morph
    _processor.getMorphModel()->getTuning()->paint(_processor, g, getLocalBounds());
}

void MorphTuningComponent::resized()
{
    repaint();
}
