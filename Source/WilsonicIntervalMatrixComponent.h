/*
  ==============================================================================

    WilsonicIntervalMatrixComponent.h
    Created: 17 May 2021 9:28:26pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "TuningImp.h"
#include "WilsonicAppSkin.h"

// forward
class WilsonicProcessor;

//
class WilsonicIntervalMatrixComponent
: public Component
{
// public methods
public:
    WilsonicIntervalMatrixComponent (WilsonicProcessor&);
    ~WilsonicIntervalMatrixComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WilsonicIntervalMatrixComponent)

public:
    // drawing
    void paint(Graphics&) override;
    void resized() override;
    void setTuning(shared_ptr<Tuning>);

private:
    // private members
    WilsonicProcessor& _processor;
    shared_ptr<Tuning> _tuning; // frequently overwritten by app tuning model
    shared_ptr<TuningImp> _tuningInternalDefault; // 12 et as fallback
    CriticalSection _lock;
};
