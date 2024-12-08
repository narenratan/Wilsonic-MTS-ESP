/*
  ==============================================================================

    BrunRootComponent.h
    Created: 7 Mar 2021 1:36:51pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppTuningModel.h"
#include "Brun.h"
#include "BrunGraphComponent.h"
#include "BrunIntervalMatrix.h"
#include "BrunLevelComponent.h"
#include "BrunPitchWheel.h"
#include "BubbleDrawable.h"
#include "ParameterListeners.h"
#include "WilsonicAppSkin.h"
#include "WilsonicAppTuningComponent.h"
#include "WilsonicProcessor.h"

class BrunRootComponent
: public WilsonicAppTuningComponent
, private ActionListener
, private Label::Listener
, private Timer
{
    // lifecycle
public:
    BrunRootComponent (WilsonicProcessor&);
    ~BrunRootComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrunRootComponent)

public:
    // drawing
    void paint(Graphics&) override;
    void resized() override;

    // app tuning title
    const string getAppTuningTitle() override;

    // ActionListener callback
    void actionListenerCallback(const String&) override;

private:
    // private members
    BubbleDrawable _frequencyBubble;
    Label _frequencyGLabel {"frequencyGLabel", "0"};
    BubbleDrawable _centsBubble;
    Label _centsGLabel {"centsGLabel", "0"};
    BubbleDrawable _generatorBubble;
    Slider _generatorSlider {Slider::SliderStyle::LinearHorizontal, Slider::TextEntryBoxPosition::TextBoxLeft};
    BubbleDrawable _periodBubble;
    Slider _periodSlider {Slider::SliderStyle::LinearHorizontal, Slider::TextEntryBoxPosition::TextBoxLeft};
    unique_ptr<ComboBox> _displayModeComboBox;
    BubbleDrawable _murchanaBubble;
    Slider _murchanaSlider {Slider::SliderStyle::LinearHorizontal, Slider::TextEntryBoxPosition::TextBoxLeft};
    BubbleDrawable _levelBubble;
    unique_ptr<BrunLevelComponent> _levelComponent;
    BubbleDrawable _levelGralBubble;
    unique_ptr<BrunLevelComponent> _levelGralComponent;
    ToggleButton _autoMurchanaToggle {""};
    Slider _gralHexAngleSlider {Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::NoTextBox};
    Slider _gralHexScaleSlider {Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::NoTextBox};
    Slider _gralHexShearXSlider {Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::NoTextBox};
    Slider _gralHexOriginOffsetFactorXSlider {Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::NoTextBox};
    Slider _gralHexOriginOffsetFactorYSlider {Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::NoTextBox};
    unique_ptr<BrunGraphComponent> _brunGraph;

    // private methods
    void _tuningChangedUpdateUI();
    void labelTextChanged(Label* labelThatHasChanged) override;
    void timerCallback() override;
    void _timerHelper();
};
