///*
//  ==============================================================================
//
// WilsonicComponent.cpp
//    Created: 6 Mar 2021 10:40:08pm
//    Author:  Marcus W. Hobbs
//
//  ==============================================================================
//*/
//
//#include "WilsonicComponent.h"
//
//#pragma mark - lifecycle
//
//WilsonicComponent::WilsonicComponent (
// WilsonicProcessor& processor,
// AppTuningModel& appTuning,
// WilsonicAppSkin& appSkin)
//: _processor (processor)
//, _appTuning (appTuning)
//, _appSkin (appSkin)
//, _rootMenu (_appSkin)
//, _rootArrowLeft (_appSkin)
//, _rootArrowRight (_appSkin)
//{
//    //
//    addAndMakeVisible (_rootMenu);
//    addAndMakeVisible (_rootArrowLeft);
//    addAndMakeVisible (_rootArrowRight);
//
//    //
//
//
//    _brunComponent = make_shared<BrunRootComponent>(_processor, _appTuning, _appSkin);
//    _currentTuningComponent = _brunComponent;
//    addAndMakeVisible (*_currentTuningComponent);
//
//    //
//    setSize (_appSkin.getWindowWidth(), _appSkin.getWindowHeight());
//}
//
//WilsonicComponent::~WilsonicComponent()
//{
//
//}
//
//#pragma mark - drawing
//
//void WilsonicComponent::paint (Graphics& g)
//{
//    g.fillAll (_appSkin.getBgColour());
//
//    // DEBUG
//    g.setColour (Colours::red);
//    g.drawRect (getLocalBounds(), 1);
//}
//
//void WilsonicComponent::resized()
//{
//    auto const minHitpointSize = 35.f;
//    auto area = getLocalBounds();
//
//    _rootMenu.setBounds (area.removeFromTop(minHitpointSize));
//    _rootArrowLeft.setBounds (area.removeFromLeft(minHitpointSize));
//    _rootArrowRight.setBounds (area.removeFromRight(minHitpointSize));
//
//    _currentTuningComponent->setBounds (area);
//}
