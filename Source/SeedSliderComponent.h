/*
  ==============================================================================

    SeedSliderComponent.h
    Created: 19 Sep 2021 11:30:36am
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SeedSlider.h"
#include "Tuning_Include.h"
#include "WilsonicAppTuningComponent.h"

// forward
class WilsonicProcessor;

//
class SeedSliderComponent
: public Component
{
public:
    // public static members
    static constexpr float rangeMin = 1;
    static constexpr float rangeMax = 16384;
    static constexpr float rangeStep = 1;

    // lifecycle
    SeedSliderComponent(WilsonicProcessor&);
    ~SeedSliderComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SeedSliderComponent)

public:
    // drawing
    void paint(Graphics&) override;
    void resized() override;

    // public methods
    void setSliderAtIndex(unsigned long index, string label, float val, function<void(float)> onValueChange);

    // public slider methods: sets slider if it exists and calls it's callback
    void setA(float, NotificationType);
    void setAB(float, float, NotificationType);
    void setABC(float, float, float, NotificationType);
    void setABCD(float, float, float, float, NotificationType);
    void setABCDE(float, float, float, float, float, NotificationType);
    void setABCDEF(float, float, float, float, float, float, NotificationType);
    void setABCDEFG(float, float, float, float, float, float, float, NotificationType);
    void setABCDEFGH(float, float, float, float, float, float, float, float, NotificationType);
    void showNumberOfSliders(unsigned long number_of_sliders_to_show);

private:
    WilsonicProcessor& _processor;
    shared_ptr<SeedSlider> _A;
    shared_ptr<SeedSlider> _B;
    shared_ptr<SeedSlider> _C;
    shared_ptr<SeedSlider> _D;
    shared_ptr<SeedSlider> _E;
    shared_ptr<SeedSlider> _F;
    shared_ptr<SeedSlider> _G;
    shared_ptr<SeedSlider> _H;
    vector<shared_ptr<SeedSlider>> _sliderArray {};
    unsigned long _number_of_sliders_to_show = 0;
    CriticalSection _lock;
    void _setXHelper(float, unsigned long, NotificationType);
    void _tabReturnHelper(unsigned long sliderIndex);
};
