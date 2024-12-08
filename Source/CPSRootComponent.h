///*
// ==============================================================================
//
// CPSRootComponent.h
// Created: 25 Aug 2021 3:31:57pm
// Author:  Marcus W. Hobbs
//
// ==============================================================================
// */
//
//// TODO: Deprecate in favor of EulerGenus6Component
//
//#pragma once
//
//#include <JuceHeader.h>
//#include "AppTuningModel.h"
//#include "CPSElementComponent.h"
//#include "CPSTuningBase.h"
//#include "Tuning_Include.h"
//#include "WilsonicAppSkin.h"
//#include "WilsonicAppTuningComponent.h"
//#include "WilsonicPitchWheelComponent.h"
//#include "WilsonicProcessor.h"
//
//class CPSRootComponent
//: public WilsonicAppTuningComponent
//{
//    // lifecycle
//
//private:
//
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CPSRootComponent)
//
//public:
//    
//    CPSRootComponent (WilsonicProcessor&);
//
//    CPSRootComponent (WilsonicProcessor&, shared_ptr<CPSTuningBase>);
//
//    ~CPSRootComponent() override;
//
//    // draw
//
//    void paint (Graphics&) override;
//
//    void resized() override;
//
//    // app tuning title
//
//    const string getAppTuningTitle() override;
//
//
//    // click...elements call this method passing in their component ID
//
//    void singleClickElementID (String stringID);
//
//    void doubleClickElementID (String stringID);
//
//    void commandClickElement (String stringID); // "back button"
//
//    // elements call this when they want this, the parent, to dismiss itself
//
//    void setDismissCompletionBlock (function<void()>);
//
//    // TODO: refactor
//
//    void updateAppTuning();
//
//private:
//
//    // private properties
//
//    // has a main element
//
//    shared_ptr<CPSElementComponent> _mainElement {nullptr};
//
//    // 2 columns of the main element's subsets, or the euler genus
//
//    vector<shared_ptr<CPSElementComponent>> _subsets0 {};
//
//    vector<shared_ptr<CPSElementComponent>> _subsets1 {};
//
//    // the selected main/subset element
//
//    String _selectedElementID {""};
//
//    // navigation stack
//
//    stack<shared_ptr<CPSTuningBase>> _tuningStack {};
//
//    // lock
//
//    CriticalSection _lock;
//
//    // parent sets this to dismiss
//    
//    function<void()> _dismissCompletionBlock;
//
//    // private methods
//
//    void _addHexanyElement();
//
//    void _addDekanyElement();
//
//    void _addPentadekanyElement();
//
//    void _addEikosanyElement();
//
//    // tears down and rebuilds root component with new CPS Base tuning
//
//    void _setCPSComponent (shared_ptr<CPSTuningBase>);
//};
