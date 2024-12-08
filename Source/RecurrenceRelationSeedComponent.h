/*
  ==============================================================================

    RecurrenceRelationSeedComponent.h
    Created: 23 Mar 2022 7:57:21pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SeedSlider.h"
#include "RecurrenceRelation.h"
#include "Tuning_Include.h"
#include "WilsonicAppTuningComponent.h"

// forward
class WilsonicProcessor;

//
class RecurrenceRelationSeedComponent
: public Component
{

    // lifecycle
public:
    RecurrenceRelationSeedComponent(WilsonicProcessor&);
    ~RecurrenceRelationSeedComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RecurrenceRelationSeedComponent)

public:

    // drawing
    void paint(Graphics&) override;
    void resized() override;

    // public methods
    void setH_1_9(float, float, float, float, float, float, float, float, float, NotificationType);
    void selectIJ(unsigned long i, unsigned long j); // also deselects terms not equal to i,j

private:
    WilsonicProcessor& _processor;
    vector<shared_ptr<SeedSlider>> _sliderArray {};
    shared_ptr<SeedSlider> _Hn_1;
    shared_ptr<SeedSlider> _Hn_2;
    shared_ptr<SeedSlider> _Hn_3;
    shared_ptr<SeedSlider> _Hn_4;
    shared_ptr<SeedSlider> _Hn_5;
    shared_ptr<SeedSlider> _Hn_6;
    shared_ptr<SeedSlider> _Hn_7;
    shared_ptr<SeedSlider> _Hn_8;
    shared_ptr<SeedSlider> _Hn_9;
    CriticalSection _lock;
    void _setXHelper(float, unsigned long, NotificationType);
};
