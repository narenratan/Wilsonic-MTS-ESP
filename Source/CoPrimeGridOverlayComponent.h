///*
//  ==============================================================================
//
//    CoPrimeGridOverlayComponent.h
//    Created: 1 May 2023 8:19:06pm
//    Author:  Marcus W. Hobbs
//
//  ==============================================================================
//*/
//
//#pragma once
//
//#include <JuceHeader.h>
//#include "Tuning_Include.h"
//#include "WilsonicComponentBase.h"
//#include "WilsonicProcessor.h"
//
//// transparent overlay, owned by CoPrimeGridComponent
//
//class CoPrimeGridOverlayComponent 
//: public WilsonicComponentBase
//, private Timer
//{
//    // lifecycle
//public:
//    CoPrimeGridOverlayComponent (WilsonicProcessor& processor);
//    ~CoPrimeGridOverlayComponent() override;
//private:
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CoPrimeGridOverlayComponent)
//
//public:
//    void paint(Graphics&) override;
//    void coPrimeTuningChanged();
//
//private:
//    // private members
//    bool _updateBasedOnAppTuningSynthNotes {true};
//
//    // private member functions
//    void timerCallback() override;
//    void _timerHelper();
//};
