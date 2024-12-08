/*
  ==============================================================================

    PartchComponent.h
    Created: 27 May 2024 1:53:49pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppTuningModel.h"
#include "BubbleDrawable.h"
#include "DeltaComboBox.h"
#include "PartchGraphComponent.h"
#include "WilsonicAppTuningComponent.h"
#include "WilsonicPitchWheelComponent.h"
#include "WilsonicProcessor.h"

class PartchComponent
: public WilsonicAppTuningComponent
, private ActionListener
, private Button::Listener
, private Timer
{
public:
    PartchComponent(WilsonicProcessor& processor);
    ~PartchComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PartchComponent)

public:
    // UI
    void paint(Graphics& g) override;
    void resized() override;
    const string getAppTuningTitle() override;

private:
    BubbleDrawable _scaleBubble;
    unique_ptr<DeltaComboBox> _scaleComboBox;
    Slider _gralHexAngleSlider {Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::NoTextBox};
    Slider _gralHexScaleSlider {Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::NoTextBox};
    Slider _gralHexShearXSlider {Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::NoTextBox};
    Slider _gralHexOriginOffsetFactorXSlider {Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::NoTextBox};
    Slider _gralHexOriginOffsetFactorYSlider {Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::NoTextBox};
    unique_ptr<ToggleButton> _o1, _u1, _o3, _u3, _o5, _u5, _o7, _u7, _o9, _u9, _o11, _u11;
    unique_ptr<PartchGraphComponent> _partchGraph;

    // private methods
    void actionListenerCallback(const String& actionName) override;
    void _tuningChangedUpdateUI();
    void timerCallback() override;
    void _timerHelper();
    void buttonClicked(Button* button) override;
};
