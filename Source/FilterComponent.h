/*
  ==============================================================================

    FilterComponent.h
    Created: 18 Feb 2021 10:00:39pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomComponent.h"
#include "Tuning_Include.h"

class FilterComponent : public CustomComponent
{
    // lifecycle

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)

public:
    
    FilterComponent (shared_ptr<AudioProcessorValueTreeState> apvts, String filterTypeId, String cutoffId, String resonanceId);

    ~FilterComponent() override;

    // public methods

    void resized() override;

private:

    // private static members

    static constexpr int dialWidth = 70;

    static constexpr int dialHeight = 70;

    // private members

    ComboBox filterTypeSelector;

    unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
    
    SliderWithLabel cutoff;

    SliderWithLabel resonance;
};
