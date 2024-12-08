/*
  ==============================================================================

    LfoComponent.cpp
    Created: 19 Feb 2021 8:12:35pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LfoComponent.h"

LfoComponent::LfoComponent (shared_ptr<AudioProcessorValueTreeState> apvts, String lfoFreqId, String lfoDepthId)
: lfoFreq ("LFO Freq", lfoFreqId, apvts, dialWidth, dialHeight)
, lfoDepth ("LFO Depth", lfoDepthId, apvts, dialWidth, dialHeight)
{
    addAndMakeVisible (lfoFreq);
    addAndMakeVisible (lfoDepth);
}

LfoComponent::~LfoComponent()
{

}

void LfoComponent::resized()
{
    // Create a FlexBox instance
    FlexBox flexBox;

    // Set its flexDirection property to arrange children in a row
    flexBox.flexDirection = FlexBox::Direction::row;

    // Set alignment and justification properties
    flexBox.justifyContent = FlexBox::JustifyContent::flexStart;
    flexBox.alignItems = FlexBox::AlignItems::flexStart;

    // Create a lambda function to add items to the FlexBox with uniform properties
    auto addItem = [&](Component& comp, int marginLeft) {
        FlexItem item(comp);
        item.withFlex(1).withMinWidth(70).withMinHeight(88).withMargin(FlexItem::Margin(40, 0, 0, marginLeft)); // startY adjusted as margin-top
        flexBox.items.add(std::move(item));
    };

    // Add the components to the FlexBox
    addItem(lfoFreq, 18);
    addItem(lfoDepth, 2); // 90 - 18 - 70 (previous component's width)

    // Perform the layout within the local bounds of the LfoComponent
    flexBox.performLayout(getLocalBounds());
}
