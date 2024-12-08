/*
  ==============================================================================

    CoPrimeComponent.h
    Created: 23 Apr 2023 12:41:21pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppTuningModel.h"
#include "BubbleDrawable.h"
#include "CoPrimeGridComponent.h"
#include "DeltaComboBox.h"
#include "SeedSlider.h"
#include "Tuning_Include.h"
#include "WilsonicProcessor.h"
#include "WilsonicAppTuningComponent.h"

class CoPrimeComponent
: public WilsonicAppTuningComponent
, private ActionListener
, private Timer
{
public:
    // lifecycle
    CoPrimeComponent(WilsonicProcessor& processor);
    ~CoPrimeComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CoPrimeComponent)

public:
    // UI
    void paint(Graphics&) override;
    void resized() override;
    const string getAppTuningTitle() override;

private:
    // private members
    unique_ptr<DeltaComboBox> _displayModeComboBox;
    CriticalSection _lock;
    unique_ptr<BubbleDrawable> _aBubble;
    unique_ptr<BubbleDrawable> _bBubble;
    unique_ptr<BubbleDrawable> _cBubble;
    unique_ptr<BubbleDrawable> _dBubble;
    unique_ptr<BubbleDrawable> _sBubble;
    unique_ptr<BubbleDrawable> _tBubble;
    unique_ptr<BubbleDrawable> _xBubble;
    unique_ptr<BubbleDrawable> _yBubble;
    unique_ptr<SeedSlider> _aSlider;
    unique_ptr<SeedSlider> _bSlider;
    unique_ptr<SeedSlider> _cSlider;
    unique_ptr<SeedSlider> _dSlider;
    unique_ptr<SeedSlider> _sSlider;
    unique_ptr<SeedSlider> _tSlider;
    unique_ptr<SeedSlider> _xSlider;
    unique_ptr<SeedSlider> _ySlider;
    unique_ptr<CoPrimeGridComponent> _coPrimeGrid;
    
    // private methods
    void actionListenerCallback(const String&) override;
    void _tuningChangedUpdateUI();
    void timerCallback() override;
    void _timerHelper();
};
