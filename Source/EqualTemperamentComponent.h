/*
  ==============================================================================

    EqualTemperamentComponent.h
    Created: 25 May 2022 8:00:37pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppTuningModel.h"
#include "BubbleDrawable.h"
#include "DeltaComboBox.h"
#include "WilsonicAppTuningComponent.h"
#include "WilsonicPitchWheelComponent.h"
#include "WilsonicProcessor.h"

class EqualTemperamentComponent 
: public WilsonicAppTuningComponent
, private ActionListener
{
public:
    // Lifecycle
    EqualTemperamentComponent(WilsonicProcessor&);
    ~EqualTemperamentComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqualTemperamentComponent)

public:
    // UI
    void paint(Graphics&) override;
    void resized() override;
    
    // tuning title
    const string getAppTuningTitle() override;

private:
    BubbleDrawable _npoBubble;
    Slider _npoSlider {Slider::SliderStyle::LinearHorizontal, Slider::TextEntryBoxPosition::TextBoxLeft};
    BubbleDrawable _periodBubble;
    Slider _periodSlider {Slider::SliderStyle::LinearHorizontal, Slider::TextEntryBoxPosition::TextBoxLeft};

    // private methods
    void _tuningChangedUpdateUI();
    void actionListenerCallback (const String&) override;

    // private members
    unique_ptr<WilsonicPitchWheelComponent> _pitchWheelComponent;
    Rectangle<int> _paintBounds; // resize calculates this, paint draws in it
};
