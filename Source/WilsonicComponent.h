///*
//  ==============================================================================
//
// WilsonicComponent.h
//    Created: 6 Mar 2021 10:40:08pm
//    Author:  Marcus W. Hobbs
//
//  ==============================================================================
//*/
//
//#pragma once
//
//#include <JuceHeader.h>
//#include "WilsonicMenuComponent.h"
//#include "WilsonicArrowBaseComponent.h"
//#include "WilsonicTuningContainer.h"
//#include "WilsonicKeyboardContainerComponent.h"
//#include "../App/WilsonicProcessor.h"
//#include "../App/AppTuningModel.h"
//#include "../Synth/SynthComponent.h"
//#include "../WilsonicComponent/WilsonicComponentBase.h"
//#include "../TmpPresetComponent/TmpPresetComponent.h"
//#include "../../WilsonicSource/WilsonicJuce/BrunRootComponent.h"
//#include "../../WilsonicSource/WilsonicJuce/WilsonicAppSkin.h"
//
//class WilsonicComponent : public Component
//{
//
//public:
//
//    //
//    WilsonicComponent (WilsonicProcessor&, AppTuningModel&, WilsonicAppSkin&);
//    
//    ~WilsonicComponent();
//
//    //
//
//    void paint (Graphics&) override;
//
//    void resized() override;
//
//private:
//
//    WilsonicProcessor& _processor;
//
//    AppTuningModel& _appTuning;
//
//    WilsonicAppSkin& _appSkin;
//
//    WilsonicMenuComponent _rootMenu; // OWNER
//
//    WilsonicArrowBaseComponent _rootArrowLeft;  // OWNER
//
//    WilsonicArrowBaseComponent _rootArrowRight; // OWNER
//
//private:
//
//    shared_ptr<WilsonicComponentBase> _currentTuningComponent;
//
//    shared_ptr<BrunRootComponent> _brunComponent;
//
//    shared_ptr<TmpPresetComponent> _tmpPresetComponent;
//
//    shared_ptr<SynthComponent> _synthComponent;
//};
