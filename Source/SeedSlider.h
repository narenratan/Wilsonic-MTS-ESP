/*
  ==============================================================================

    SeedSlider.h
    Created: 20 Sep 2021 3:48:56pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"

// forward
class WilsonicProcessor;

// Slider with a label

class SeedSlider 
: public Component
, private KeyListener
{
    // lifecycle
public:
    SeedSlider(WilsonicProcessor& processor,
               string label,
               float min,
               float val, // default
               float max,
               float step,
               function<void(float)> onValueChange);
    ~SeedSlider() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SeedSlider)

public:
    // drawing
    void paint(Graphics&) override;
    void resized() override;

    // public methods
    void setValue(float, NotificationType);
    void setOnValueChangedF(function<void(float)> callback);
    void setSliderAttachment(shared_ptr<AudioProcessorValueTreeState> stateToUse, const String& parameterID);
    void setText(string newText);
    void setIsSelected(bool isSelected); // true ==> paints blue outline
    bool getIsSelected();
    void grabFocus();
    void setOnTabReturnCallback(function<void(void)> callback);

    // KeyListener
    bool keyPressed(const KeyPress& key, Component* originatingComponent) override;
    bool keyPressed(const juce::KeyPress& key) override {return keyPressed(key, this);}

private:
    WilsonicProcessor& _processor;
    unique_ptr<Slider> _A;
    unique_ptr<AudioProcessorValueTreeState::SliderAttachment> _sliderAttachment;
    unique_ptr<Label> _ALabel;
    bool _isSelected {false};
    function<void(void)> _onTabReturnCallback;
};
