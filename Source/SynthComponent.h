/*
  ==============================================================================

    SynthComponent.h
    Created: 13 Mar 2021 3:40:40pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AdsrComponent.h"
#include "AppTuningModel.h"
#include "Assets.h"
#include "FilterComponent.h"
#include "LfoComponent.h"
#include "MeterComponent.h"
#include "OscComponent.h"
#include "ReverbComponent.h"
#include "WilsonicAppSkin.h"
#include "WilsonicAppTuningComponent.h"
#include "WilsonicProcessor.h"

class SynthComponent
: public WilsonicAppTuningComponent
, public Timer
{
    // lifecycle
public:
    SynthComponent(WilsonicProcessor&);
    ~SynthComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthComponent)

public:
    // draw
    void paint(Graphics&) override;
    void resized() override;

    // page title
    const string getAppTuningTitle() override;

    // timer
    void timerCallback() override;

private:
    OscComponent _osc1;
    OscComponent _osc2;
    FilterComponent _filter;
    AdsrComponent _adsr;
    LfoComponent _lfo1;
    AdsrComponent _filterAdsr;
    ReverbComponent _reverb;
    MeterComponent _meter;
};
