/*
  ==============================================================================

    CustomComponent.h
    Created: 20 Feb 2021 9:51:27am
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"

static constexpr float fontHeight { 15.0f };

class SliderWithLabel : public Component
{
public:
    using SliderAttachment = AudioProcessorValueTreeState::SliderAttachment;
    using SliderStyle = Slider::SliderStyle;
    
    SliderWithLabel (String labelName, String paramId, shared_ptr<AudioProcessorValueTreeState> apvts, const int width, const int height, SliderStyle style = SliderStyle::RotaryHorizontalVerticalDrag);
        
    void resized() override;
    
private:
    static constexpr int textBoxWidth { 48 };
    static constexpr int textBoxHeight { 20 };
    int sliderWidth { 0 };
    int sliderHeight { 0 };
    Slider slider;
    Label label;
    unique_ptr<SliderAttachment> attachment;
};

class CustomComponent  : public Component
{
    // lifecycle

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomComponent)

public:

    CustomComponent();

    ~CustomComponent() override;

    // public methods

    void paint (Graphics&) override;

    void resized() override;
    
    void setCustomName (const String n) { _name = n; }

    void setBoundsColour (Colour c) { boundsColour = c; }

private:

    // private members

    String _name { "" };

    Colour boundsColour { Colours::white };
};
