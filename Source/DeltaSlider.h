/*
  ==============================================================================

    DeltaSlider.h
    Created: 12 Sep 2021 3:17:18pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"
#include "WilsonicComponentBase.h"

// forward
class WilsonicProcessor;

//
class DeltaSlider
: public WilsonicComponentBase
{
    // lifecycle
public:
    DeltaSlider (WilsonicProcessor&);
    ~DeltaSlider() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeltaSlider)

public:
    // drawing
    void paint (Graphics&) override;
    void resized() override;

    // public methods
    function<void()> onValueIncremented;
    function<void()> onValueDecremented;

private:
    const int _minValue {0};
    const int _midValue {3};
    int _currentValue {3};
    const int _maxValue {5};
    Slider _slider { Slider::IncDecButtons, Slider::NoTextBox };

    // private methods
    void _reset();
};
