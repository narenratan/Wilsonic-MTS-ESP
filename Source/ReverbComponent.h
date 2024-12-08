/*
  ==============================================================================

    ReverbComponent.h
    Created: 19 Feb 2021 9:18:11pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomComponent.h"

class ReverbComponent : public CustomComponent
{
    // lifecycle
public:
    ReverbComponent (shared_ptr<AudioProcessorValueTreeState> apvts, String sizeId, String dampingId, String widthId, String dryId, String wetId, String freezeId);
    ~ReverbComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)

public:
    // public methods
    void resized() override;

private:
    // private static members
    static constexpr int dialWidth = 67;
    static constexpr int dialHeight = 67;

    // private members
    SliderWithLabel size;
    SliderWithLabel damping;
    SliderWithLabel stereoWidth;
    SliderWithLabel dry;
    SliderWithLabel wet;
    SliderWithLabel freeze;
};
