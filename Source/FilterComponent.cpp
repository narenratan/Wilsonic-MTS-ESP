/*
 ==============================================================================

 FilterComponent.cpp
 Created: 18 Feb 2021 10:00:39pm
 Author:  Joshua Hodge

 ==============================================================================
 */

#include <JuceHeader.h>
#include "FilterComponent.h"

#pragma mark - lifecycle

FilterComponent::FilterComponent (shared_ptr<AudioProcessorValueTreeState> apvts, String filterTypeId, String cutoffId, String resonanceId)
: cutoff ("Cutoff", cutoffId, apvts, dialWidth, dialHeight)
, resonance ("Resonance", resonanceId, apvts, dialWidth, dialHeight)
{
    StringArray filterTypeChoices { "Low Pass", "Band Pass", "High Pass" };
    filterTypeSelector.addItemList (filterTypeChoices, 1);
    filterTypeSelector.setSelectedItemIndex (0);
    addAndMakeVisible (filterTypeSelector);
    
    filterTypeAttachment = make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(*apvts, filterTypeId, filterTypeSelector);
    
    addAndMakeVisible (cutoff);
    addAndMakeVisible (resonance);
}

FilterComponent::~FilterComponent()
{

}

#pragma mark - drawing

void FilterComponent::resized()
{
    FlexBox flexBox;
    flexBox.flexDirection = FlexBox::Direction::row;
    flexBox.justifyContent = FlexBox::JustifyContent::flexStart;
    flexBox.alignItems = FlexBox::AlignItems::stretch;
    flexBox.flexWrap = FlexBox::Wrap::noWrap;
    flexBox.alignContent = FlexBox::AlignContent::flexStart;

    // Add the filterTypeSelector with custom bounds
    FlexItem filterItem(filterTypeSelector);
    filterItem.withFlex(0).withWidth(145).withHeight(25).withMargin(FlexItem::Margin(40, 0, 0, 18)); // Custom positioning
    flexBox.items.add(filterItem);

    // Create a lambda function to add the rest of the items to the FlexBox with uniform properties
    auto addItem = [&](Component& comp) {
        FlexItem item(comp);
        item.withFlex(1).withMinWidth(70).withMinHeight(88).withMargin(FlexItem::Margin(0, 0, 0, 10)); // 10 units margin to separate components
        flexBox.items.add(item);
    };

    // Add the other components to the FlexBox
    addItem(cutoff);
    addItem(resonance);

    // Perform the layout within the local bounds of the FilterComponent
    auto area = getLocalBounds().withTrimmedTop(40); // Adjust for startY
    flexBox.performLayout(area);
}
