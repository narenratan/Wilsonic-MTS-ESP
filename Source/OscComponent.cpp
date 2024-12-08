/*
  ==============================================================================

    OscComponent.cpp
    Created: 14 Feb 2021 6:51:39pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

OscComponent::OscComponent (shared_ptr<AudioProcessorValueTreeState> apvts, String oscId, String gainId, String pitchId, String fmFreqId, String fmDepthId)
: gain ("Gain", gainId, apvts, dialWidth, dialHeight)
, pitch ("Pitch", pitchId, apvts, dialWidth, dialHeight)
, fmFreq ("FM Freq", fmFreqId, apvts, dialWidth, dialHeight)
, fmDepth ("FM Depth", fmDepthId, apvts, dialWidth, dialHeight)
{
    StringArray oscChoices { "Sine", "Saw", "Square" };
    oscSelector.addItemList (oscChoices, 1);
    oscSelector.setSelectedItemIndex (0);
    addAndMakeVisible (oscSelector);
    
    oscSelAttachment = make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(*apvts, oscId, oscSelector);
    
    addAndMakeVisible (gain);
    addAndMakeVisible (pitch);
    addAndMakeVisible (fmFreq);
    addAndMakeVisible (fmDepth);
}

OscComponent::~OscComponent()
{

}


void OscComponent::resized()
{
    FlexBox flexBox;
    flexBox.flexDirection = FlexBox::Direction::row;
    flexBox.justifyContent = FlexBox::JustifyContent::flexStart;
    flexBox.alignItems = FlexBox::AlignItems::stretch;
    flexBox.flexWrap = FlexBox::Wrap::noWrap;
    flexBox.alignContent = FlexBox::AlignContent::flexStart;

    // Define a lambda function to add items to the FlexBox with specific properties
    auto addItem = [&](Component& comp) {
        flexBox.items.add(FlexItem(comp).withWidth(70).withHeight(88));
    };

    // Add the oscSelector with custom bounds
    FlexItem oscItem(oscSelector);
    oscItem.withFlex(0).withWidth(100).withHeight(25).withMargin(FlexItem::Margin(40, 0, 0, 18)); // Custom positioning
    flexBox.items.add(oscItem);

    // Add all the components to the FlexBox
    addItem(gain);
    addItem(pitch);
    addItem(fmFreq);
    addItem(fmDepth);

    // Perform the layout within the local bounds of the OscComponent
    auto area = getLocalBounds().withPosition(0, 15); // Adjusted yStart
    flexBox.performLayout(area);
}
