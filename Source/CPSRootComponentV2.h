/*
  ==============================================================================

    CPSRootComponentV2.h
    Created: 19 May 2022 4:43:52pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppTuningModel.h"
#include "CPSElementComponentV2.h"
#include "CPSModel.h"
#include "CPSTuningBase.h"
#include "DeltaComboBox.h"
#include "SeedSliderComponent.h"
#include "Tuning_Include.h"
#include "WilsonicAppSkin.h"
#include "WilsonicAppTuningComponent.h"
#include "WilsonicPitchWheelComponent.h"
#include "WilsonicProcessor.h"

class CPSRootComponentV2 
: public WilsonicAppTuningComponent
, private ActionListener
{
public:
    // lifecycle
    CPSRootComponentV2 (WilsonicProcessor&);
    ~CPSRootComponentV2() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CPSRootComponentV2)

public:
    // UI
    void paint (Graphics&) override;
    void resized() override;

    // app tuning title
    const string getAppTuningTitle() override;

    // ActionListener callback
    void actionListenerCallback (const String&) override;

private:
    CriticalSection _lock;
    unique_ptr<DeltaComboBox> _comboBox {nullptr};
    unique_ptr<SeedSliderComponent> _seedSliderComponent;
    unique_ptr<WilsonicPitchWheelComponent> _pitchWheel {nullptr};
    unique_ptr<CPSElementComponentV2> _mainElement {nullptr};

    // private member functions
    void _tuningChangedUpdateUI();
};
