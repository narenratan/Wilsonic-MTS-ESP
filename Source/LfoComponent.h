/*
  ==============================================================================

    LfoComponent.h
    Created: 19 Feb 2021 8:12:35pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomComponent.h"
#include "Tuning_Include.h"

class LfoComponent : public CustomComponent
{
    // lifecycle

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LfoComponent)

public:
    
    LfoComponent (shared_ptr<AudioProcessorValueTreeState> apvts, String lfoFreqId, String lfoDepthId);

    ~LfoComponent() override;

    // public static members

    static constexpr int dialWidth = 70;

    static constexpr int dialHeight = 70;

    // public methods

    void resized() override;

private:

    // private members

    using SliderAttachment = AudioProcessorValueTreeState::SliderAttachment;

    Slider lfoFreqSlider;

    Slider lfoDepthSlider;
    
    Label lfoFreqLabel { "Freq", "Freq" };

    Label lfoDepthLabel { "Depth", "Depth" };
    
    unique_ptr<SliderAttachment> lfoFreqAttachment;

    unique_ptr<SliderAttachment> lfoDepthAttachment;
    
    SliderWithLabel lfoFreq;

    SliderWithLabel lfoDepth;

    // private methods

    void setSliderParams (Slider& slider, Label& label, unique_ptr<SliderAttachment>& attachment, String paramId, shared_ptr<AudioProcessorValueTreeState> apvts);
};
