/*
  ==============================================================================

    BrunLevelComponent.h
    Created: 1 Apr 2021 8:29:50pm
    Author:  Marcus W. Hobbs

    This component draws the UI element that is the level of the current generator
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Brun.h"
#include "Tuning_Include.h"
#include "WilsonicComponentBase.h"
#include "WilsonicProcessor.h"

class BrunLevelComponent 
: public WilsonicComponentBase
, public SettableTooltipClient
{
public:
    BrunLevelComponent(WilsonicProcessor&, function<unsigned long()> getSelectedIndex, function<void(float)> setLevel01);
    ~BrunLevelComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrunLevelComponent)

public:
    void paint(Graphics&) override;
    void resized() override;

    // event handler

private:
    // private members
    function<unsigned long()> _getSelectedIndex;
    function<void(float l01)> _setLevel01;

    // private methods
    // MouseListener
    void mouseDown(const MouseEvent&) override;
    void mouseUp(const MouseEvent&) override;
    void mouseDrag(const MouseEvent&) override;
    void mouseEnter(const MouseEvent&) override;
    void mouseExit(const MouseEvent&) override;
    void mouseMove(const MouseEvent&) override;
    void _mouseHelper(const MouseEvent&);
};
