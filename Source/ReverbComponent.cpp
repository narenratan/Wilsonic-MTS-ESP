/*
  ==============================================================================

    ReverbComponent.cpp
    Created: 19 Feb 2021 9:18:11pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"

ReverbComponent::ReverbComponent (shared_ptr<AudioProcessorValueTreeState> apvts, String sizeId, String dampingId, String widthId, String dryId, String wetId, String freezeId)
: size ("Size", sizeId, apvts, dialWidth, dialHeight)
, damping ("Damping", dampingId, apvts, dialWidth, dialHeight)
, stereoWidth ("Width", widthId, apvts, dialWidth, dialHeight)
, dry ("Dry", dryId, apvts, dialWidth, dialHeight)
, wet ("Wet", wetId, apvts, dialWidth, dialHeight)
, freeze ("Freeze", freezeId, apvts, dialWidth, dialHeight)
{
    addAndMakeVisible (size);
    addAndMakeVisible (damping);
    addAndMakeVisible (stereoWidth);
    addAndMakeVisible (dry);
    addAndMakeVisible (wet);
    addAndMakeVisible (freeze);
    
    setCustomName ("Reverb");
}

ReverbComponent::~ReverbComponent()
{
    
}

void ReverbComponent::resized()
{
    FlexBox flexBox;
    flexBox.flexDirection = FlexBox::Direction::row;
    flexBox.justifyContent = FlexBox::JustifyContent::flexStart;
    flexBox.alignItems = FlexBox::AlignItems::stretch;
    flexBox.flexWrap = FlexBox::Wrap::noWrap;
    flexBox.alignContent = FlexBox::AlignContent::flexStart;

    // Define a lambda function to add items to the FlexBox with specific properties
    auto addItem = [&](Component& comp) {
        flexBox.items.add(FlexItem(comp).withWidth(67).withHeight(88));
    };

    // Add all the components to the FlexBox
    addItem(size);
    addItem(damping);
    addItem(stereoWidth);
    addItem(dry);
    addItem(wet);
    addItem(freeze);

    // Perform the layout within the local bounds of the ReverbComponent
    auto area = getLocalBounds().withTrimmedTop(40).withTrimmedLeft(10); // Adjust for yStart and initial x position
    flexBox.performLayout(area);
}
