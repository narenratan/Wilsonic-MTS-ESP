/*
  ==============================================================================

    CPSElementComponentV2.h
    Created: 8 Jan 2022 12:21:08pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

// used by CPSRootComponentV2, DiamondsComponent, and EulerGenusComponentV2

#pragma once

#include <JuceHeader.h>
#include "AppTuningModel.h"
#include "CPSTuningBase.h"
#include "EulerGenusModel.h"
#include "TuningRendererComponent.h"
#include "WilsonicAppSkin.h"
#include "WilsonicAppTuningComponent.h"
#include "WilsonicProcessor.h"

class CPSElementComponentV2 
: public WilsonicAppTuningComponent
, private ActionListener
{
    // lifecycle
public:
    CPSElementComponentV2(WilsonicProcessor&);
    ~CPSElementComponentV2() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CPSElementComponentV2)

public:
    // draw
    void paint(Graphics&) override;
    void resized() override;
    void setCustomFontScale(float scale01); // 1 = default logic
    void setHideNPOLabel(bool shouldHide);
    void setHideLabel(bool shouldHide);

    // tuning of this element
    void setTuning(shared_ptr<CPSTuningBase>);
    const shared_ptr<CPSTuningBase> getTuning();

    // EulerGenusComponentV2 manages title
    const string getAppTuningTitle() override;

    // EulerGenusComponentV2 manages selection state.
    // DiamondsComponent manages selection state.
    // CPSRootComponent does not use state.
    const bool getIsSelected();
    void setIsSelected(bool newValue);

    // shift-double-click mouse handler
    void setSingleClickCompletionBlock(function<void()>);

    // ctrl-double-click mouse handler
    void setControlClickCompletionBlock(function<void()>);

    // command-double-click mouse handler
    void setCommandClickCompletionBlock(function<void()>);

    // Component double-click override, calls completion handlers
    void mouseEnter(const MouseEvent&) override;
    void mouseDown(const MouseEvent&) override;
    void mouseDoubleClick(const MouseEvent&) override;

private:
    // private members
    shared_ptr<CPSTuningBase> _tuning {nullptr};
    unique_ptr<Label> _tuningNameLabel;
    unique_ptr<Label> _tuningNPOLabel;
    unique_ptr<TuningRendererComponent> _tuningRenderer;
    bool _isSelected = false;
    bool _npoLabelIsHidden = false;
    bool _labelIsHidden = false;

    // completion handlers
    function<void()> _singleClickCompletionBlock;
    function<void()> _controlClickCompletionBlock;
    function<void()> _commandClickCompletionBlock;

    // private helper
    void _mouseHelper(const MouseEvent& event);

    // ActionListener callback
    void actionListenerCallback(const String&) override;
};
