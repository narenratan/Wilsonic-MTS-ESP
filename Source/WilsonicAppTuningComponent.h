/*
  ==============================================================================

    WilsonicAppTuningComponent.h
    Created: 26 Aug 2021 7:43:40pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "WilsonicComponentBase.h"
#include "Tuning_Include.h"

// abstract component whose subclasses can update the global app tuning table and tuning title, i.e., a page

class WilsonicAppTuningComponent 
: public WilsonicComponentBase
{
    // lifecycle

public:
    WilsonicAppTuningComponent(WilsonicProcessor&);
    ~WilsonicAppTuningComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WilsonicAppTuningComponent)

public:
    // drawing
    void paint(Graphics&) override;
    void resized() override;
    int getFirstComboBoxInset(); // x position common to all pages

    // title for designs menu bar
    virtual const string getAppTuningTitle() = 0; // page title
};
