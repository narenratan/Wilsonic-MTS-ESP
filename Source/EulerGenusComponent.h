///*
//  ==============================================================================
//
//    EulerGenusComponent.h
//    Created: 2 Sep 2021 8:28:54pm
//    Author:  Marcus W. Hobbs
//
// // TODO: Deprecate in favor of EulerGenus6Component
// // this is a complicated view controller...expect a learning curve
// 
//  ==============================================================================
//*/
//
//
//#pragma once
//
//#include <JuceHeader.h>
//#include "AppTuningModel.h"
//#include "CPSElementComponent.h"
//#include "CPSRootComponent.h"
//#include "CPSTuningBase.h"
//#include "DeltaComboBox.h"
//#include "SeedSliderComponent.h"
//#include "Tuning_Include.h"
//#include "WilsonicAppSkin.h"
//#include "WilsonicAppTuningComponent.h"
//#include "WilsonicPitchWheelComponent.h"
//#include "WilsonicProcessor.h"
//
//class EulerGenusComponent : public WilsonicAppTuningComponent
//{
//    // lifecycle
//private:
//
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EulerGenusComponent)
//
//public:
//
//    EulerGenusComponent (WilsonicProcessor&);
//
//    ~EulerGenusComponent() override;
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
//    // click...elements call this method passing in their component ID
//
//    void singleClickElementID (String stringID);
//
//    void doubleClickElementID (String stringID);
//
//    void dismissCPSRootComponent();
//
//    void updateAppTuning();
//
//private:
//
//    // private members
//
//    shared_ptr<CPSTuningBase> _currentEulerGenus {nullptr};
//
//    unique_ptr<DeltaComboBox> _eulerGenusComboBox;
//
//    unique_ptr<DeltaComboBox> _presetsComboBox; // presets of seeds custom for each EG
//
//    unique_ptr<SeedSliderComponent> _seedSliderComponent;
//
//    vector<shared_ptr<CPSElementComponent>> _subsets0 {};
//
//    String _selectedElementID {""};
//
//    shared_ptr<CPSRootComponent> _cpsComponent {nullptr};
//
//    CriticalSection _lock;
//
//    // private methods
//
//    void _addEulerGenus6Component();
//
//    void _addEulerGenus5Component();
//
//    void _addEulerGenus4Component();
//
//    void _addEulerGenus3Component();
//
//    void _addEulerGenus2Component();
//
//    void _addEulerGenus1Component();
//
//    // tears down and rebuilds root component with new EulerGenus tuning
//
//    void _setEulerGenus (shared_ptr<CPSTuningBase>);
//
//    const shared_ptr<CPSTuningBase> _getEulerGenus();
//
//    // helper class for preset combo box selection
//
//    class EGPresetHelper
//    {
//    public:
//
//        EGPresetHelper(string t, int i, function<void()> c)
//        {
//            title=t; index=i; callback=c;
//        }
//
//        ~EGPresetHelper() {}
//
//        string title {""};
//
//        int index {0};
//
//        function<void()> callback {[](){}};
//    };
//};
