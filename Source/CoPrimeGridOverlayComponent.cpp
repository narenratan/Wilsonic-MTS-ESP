///*
//  ==============================================================================
//
//    CoPrimeGridOverlayComponent.cpp
//    Created: 1 May 2023 8:19:06pm
//    Author:  Marcus W. Hobbs
//
//  ==============================================================================
//*/
//
//#include "CoPrimeGridOverlayComponent.h"
//
//CoPrimeGridOverlayComponent::CoPrimeGridOverlayComponent(WilsonicProcessor& processor)
//: WilsonicComponentBase(processor)
//{
//    // this is a transparent overlay (child component)
//    setOpaque(false);
//
//    // pass mouse clicks to the parent
//    setInterceptsMouseClicks(false, false);
//    
//    //
//    _timerHelper();
//}
//
//CoPrimeGridOverlayComponent::~CoPrimeGridOverlayComponent()
//{
//    stopTimer();
//}
//
//#pragma mark - drawing
//
//void CoPrimeGridOverlayComponent::paint(Graphics& g)
//{
//    // this is an overlay...erasing means transparent black
//    g.fillAll(Colours::transparentBlack);
//
//    // debug
//    if (AppExperiments::showDebugBoundingBox)
//    {
//        // DEBUG
//        g.setColour(Colours::cyan);
//        g.drawRect(getLocalBounds().expanded (-5), 2);
//
//        // counter
//        g.drawText(String(_debug_paint_counter++), getLocalBounds().expanded (-10), Justification::topRight);
//    }
//
//    // paint
//    _processor.getCoPrimeModel()->getTuning()->paintOverlay(_processor, g, getLocalBounds());
//}
//
//#pragma mark - Timer
//
//void CoPrimeGridOverlayComponent::coPrimeTuningChanged()
//{
//    _timerHelper(); // update timer rate based on npo
//}
//
//void CoPrimeGridOverlayComponent::timerCallback()
//{
//    if(isShowing())
//    {
//        repaint();
//    }
//}
//
//void CoPrimeGridOverlayComponent::_timerHelper()
//{
//    stopTimer();
//
//    if(!_updateBasedOnAppTuningSynthNotes)
//    {
//        return;
//    }
//
//    if(_updateBasedOnAppTuningSynthNotes)
//    {
//        auto const npo = _processor.getAppTuningModel()->getTuning()->getProcessedArray().count();
//        auto const hz = AppExperiments::getFrameRateForNPO(npo);
//        if (hz > 0)
//        {
//            DBG("CoPrimeGridOverlayComponent timer STARTED for npo:" << npo << ", hz: " << hz);
//            startTimerHz(hz);
//        }
//        else
//        {
//            DBG("CoPrimeGridOverlayComponent timer STOPPED for npo:" << npo << ", hz: " << hz);
//            stopTimer();
//        }
//    }
//}
