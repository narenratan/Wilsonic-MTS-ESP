///*
// ==============================================================================
//
// CPSElementComponent.h
// Created: 28 Aug 2021 10:43:13pm
// Author:  Marcus W. Hobbs
//
// ==============================================================================
// */
//
//#pragma once
//
//#include <JuceHeader.h>
//#include "AppTuningModel.h"
//#include "CPSTuningBase.h"
//#include "WilsonicAppSkin.h"
//#include "WilsonicAppTuningComponent.h"
//#include "WilsonicPitchWheelComponent.h"
//#include "WilsonicProcessor.h"
//
//class CPSElementComponent
//: public WilsonicAppTuningComponent
//{
//    // lifecycle
//
//private:
//
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CPSElementComponent)
//
//public:
//    
//    CPSElementComponent (WilsonicProcessor&);
//
//    ~CPSElementComponent() override;
//
//    // draw
//
//    void paint (Graphics&) override;
//
//    void resized() override;
//
//    void setCustomFontScale (float scale01); // 1 = default logic
//
//    // tuning of this element
//
//    void setTuning (shared_ptr<CPSTuningBase>);
//
//    const shared_ptr<CPSTuningBase> getTuning();
//
//    // cpsrootcomponent manages app tuning title
//
//    const string getAppTuningTitle() override;
//    
//    // CPSRootComponent manages selection state
//
//    const bool getIsSelected();
//
//    void setIsSelected (bool newValue);
//
//    // shift-double-click mouse handler
//
//    void setSingleClickCompletionBlock (function<void(String)>);
//
//    // ctrl-double-click mouse handler
//
//    void setDoubleClickCompletionBlock (function<void(String)>);
//
//    // command-double-click mouse handler
//
//    void setCommandClickCompletionBlock (function<void(String)>);
//
//    // Component double-click override, calls completion handlers
//
//    void mouseEnter (const MouseEvent&) override;
//
//    void mouseDown (const MouseEvent&) override;
//
//    void mouseDoubleClick (const MouseEvent&) override;
//
//    void updateAppTuning();
//
//private:
//
//    // Tuning
//
//    shared_ptr<CPSTuningBase> _tuning {nullptr};
//
//    // Broadcast to listeners that the tuning changed
//
//    void _cpsTuningChanged();
//
//    // owner
//
//    unique_ptr<Label> _tuningNameLabel;
//
//    unique_ptr<Label> _tuningNPOLabel;
//
//    unique_ptr<WilsonicPitchWheelComponent> _pitchWheel;
//
//    // selection state managed by CPSRootComponent
//
//    bool _isSelected {false};
//
//    // completion handlers
//
//    function<void(String)> _singleClickCompletionBlock;
//
//    function<void(String)> _controlClickCompletionBlock;
//
//    function<void(String)> _commandClickCompletionBlock;
//
//    // private helper
//
//    void _mouseHelper (const MouseEvent& event);
//};
