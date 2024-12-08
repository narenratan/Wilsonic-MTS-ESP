/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 7 Feb 2021 2:28:49pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

#pragma mark - lifecycle

AdsrComponent::AdsrComponent(shared_ptr<AudioProcessorValueTreeState> apvts, String attackId, String decayId, String sustainId, String releaseId)
: attack("A", attackId, apvts, sliderWidth, sliderHeight, Slider::SliderStyle::LinearVertical)
, decay("D", decayId, apvts, sliderWidth, sliderHeight, Slider::SliderStyle::LinearVertical)
, sustain("S", sustainId, apvts, sliderWidth, sliderHeight, Slider::SliderStyle::LinearVertical)
, release("R", releaseId, apvts, sliderWidth, sliderHeight, Slider::SliderStyle::LinearVertical)
{
    addAndMakeVisible(attack);
    addAndMakeVisible(decay);
    addAndMakeVisible(sustain);
    addAndMakeVisible(release);
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::resized()
{
    FlexBox flexBox;
    flexBox.flexDirection = FlexBox::Direction::row;
    flexBox.justifyContent = FlexBox::JustifyContent::flexStart;
    flexBox.alignItems = FlexBox::AlignItems::stretch;
    flexBox.flexWrap = FlexBox::Wrap::noWrap;
    flexBox.alignContent = FlexBox::AlignContent::flexStart;

    // Create a lambda function to add items to the FlexBox with uniform properties
    auto addItem = [&](Component& comp) {
        flexBox.items.add(FlexItem(comp).withFlex(1).withMinWidth(sliderWidth).withMinHeight(sliderHeight + 20).withMargin(FlexItem::Margin(0, 0, 0, 15)));
    };

    // Add the components to the FlexBox
    addItem(attack);
    addItem(decay);
    addItem(sustain);
    addItem(release);

    // Perform the layout within the local bounds of the AdsrComponent
    auto area = getLocalBounds().withTrimmedTop(55); // Adjust for startY
    flexBox.performLayout(area);
}
