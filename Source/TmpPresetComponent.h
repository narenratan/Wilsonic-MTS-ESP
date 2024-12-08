/*
  ==============================================================================

    TmpPresetComponent.h
    Created: 24 Apr 2021 4:51:49pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppTuningModel.h"
#include "BubbleDrawable.h"
#include "DeltaComboBox.h"
#include "WilsonicAppTuningComponent.h"
#include "WilsonicIntervalMatrixComponent.h"
#include "WilsonicPitchWheelComponent.h"
#include "WilsonicProcessor.h"

class TmpPresetComponent 
: public WilsonicAppTuningComponent
, private ActionListener
{
public:
    // Lifecycle
    TmpPresetComponent(WilsonicProcessor&);
    ~TmpPresetComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TmpPresetComponent)

public:
    // UI
    void paint(Graphics&) override;
    void resized() override;

    // tuning title
    const string getAppTuningTitle() override;

    // ActionListener callback
    void actionListenerCallback(const String&) override;

private:
    // Tuning Preset
    BubbleDrawable _presetBubble;
    unique_ptr<DeltaComboBox> _tuningPresetsComboBox;

    // UI
    WilsonicPitchWheelComponent _pitchWheelComponent;  // OWNER
};
