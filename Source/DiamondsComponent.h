/*
  ==============================================================================

    DiamondsComponent.h
    Created: 6 Jun 2023 4:30:27pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppTuningModel.h"
#include "BubbleDrawable.h"
#include "CPSElementComponentV2.h"
#include "DiamondsModel.h"
#include "DeltaComboBox.h"
#include "SeedSliderComponent.h"
#include "Tuning_Include.h"
#include "WilsonicAppSkin.h"
#include "WilsonicPitchWheelComponent.h"
#include "WilsonicProcessor.h"

class DiamondsComponent 
: public WilsonicAppTuningComponent
, private ActionListener
{
public:
    // lifecycle
    DiamondsComponent (WilsonicProcessor&);
    ~DiamondsComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiamondsComponent)

    // UI
    void paint (Graphics&) override;
    void resized() override;

    // app tuning title
    const string getAppTuningTitle() override;

private:
    // private static members
    static String const __mainElementBubbleText;
    static String const __subsetsBubbleText;

    // private members
    CriticalSection _lock;
    unique_ptr<DeltaComboBox> _comboBox {nullptr};
    unique_ptr<SeedSliderComponent> _seedSliderComponent;
    BubbleDrawable _mainElementBubble;
    unique_ptr<CPSElementComponentV2> _mainElement {nullptr};
    BubbleDrawable _subsetsBubble;
    vector<shared_ptr<CPSElementComponentV2>> _subsets0 {};
    vector<shared_ptr<CPSElementComponentV2>> _subsets1 {};

    // private member functions
    void _tuningChangedUpdateUI();

    // ActionListener callback
    void actionListenerCallback (const String&) override;

    // KeyListener
    bool keyPressed (const KeyPress& key) override;
};
