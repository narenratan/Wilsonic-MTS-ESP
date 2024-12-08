/*
  ==============================================================================

    OscComponent.h
    Created: 14 Feb 2021 6:51:39pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include "Tuning_Include.h"
#include "CustomComponent.h"
#include <JuceHeader.h>

class OscComponent : public CustomComponent
{
    // lifecycle

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)

public:
    
    OscComponent (shared_ptr<AudioProcessorValueTreeState> apvts, String oscId, String gainId, String pitchId, String fmPitchId, String fmFreqId);

    ~OscComponent() override;

    // public methods

    void resized() override;

private:

    // private static members

    static constexpr int dialWidth = 70;

    static constexpr int dialHeight = 70;

    // private members

    ComboBox oscSelector;

    unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;
    
    SliderWithLabel gain;

    SliderWithLabel pitch;

    SliderWithLabel fmFreq;

    SliderWithLabel fmDepth;
};
