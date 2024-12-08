/*
  ==============================================================================

    AdsrComponent.h
    Created: 7 Feb 2021 2:28:49pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomComponent.h"

class AdsrComponent : public CustomComponent
{
    // lifecycle

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)

public:
    
    AdsrComponent (shared_ptr<AudioProcessorValueTreeState> apvts, String attackId, String decayId, String sustainId, String releaseId);

    ~AdsrComponent() override;

    // public methods

    void resized() override;

private:

    // private static members

    static constexpr int sliderWidth = 50;

    static constexpr int sliderHeight = 260;

    // private members

    SliderWithLabel attack;

    SliderWithLabel decay;

    SliderWithLabel sustain;

    SliderWithLabel release;
};
