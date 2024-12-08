/*
  ==============================================================================

    AppRootComponent.h
    Created: 17 Mar 2021 8:23:57pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DeltaListener.h"
#include "DesignsProtocol.h"
#include "WilsonicComponentBase.h"
#include "WilsonicMidiKeyboardComponent.h"
#include "WilsonicKeyboardContainerComponent.h"
#include "WilsonicRootComponent.h"

// top-level component that owns the tuning and keyboard components

class AppRootComponent
: public WilsonicComponentBase
, public DesignsProtocol
, private DeltaListener
, private ActionListener
{
public:
    // lifecycle
    AppRootComponent(WilsonicProcessor&);
    ~AppRootComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppRootComponent)

public:
    // drawing
    void paint(Graphics&) override;
    void resized() override;

    // ADD NEW SCALE DESIGN HERE

    // DesignsProtocol
    void showBrunTuning() override;
    void showCoPrimeTuning() override;
    void showCPSTuning() override;
    void showDiamondsTuning() override;
    void showEqualTemperamentTuning() override;
    void showEulerGenusV2Tuning() override;
    void showMorphTuning() override;
    void showPartchTuning() override;
    void showPersian17NorthIndianTuning() override;
    void showPresetsTuning() override;
    void showRecurrenceRelationTuning() override;
    void showScalaTuning() override;
    void showTritriadicTuning() override;

    // Pages
    void showSynth();

private:
    // private members

    // Main Window
    WilsonicRootComponent _rootComponent; // OWNER

    // Keyboard ui container
    WilsonicKeyboardContainerComponent _keyboardContainerComponent; // OWNER
    float _keyboardHeight = 225.f;
    static constexpr float __keyboardHeightMinShowing = 225.f;
    static constexpr float __keyboardHeightMinNotShowing = 65.f;

    // private member functions
    void changeListenerCallback(ChangeBroadcaster* source) override;
    float _getKeyboardHeightMin(); // based on toggled keyboard
    void actionListenerCallback(const String& message) override;
};
