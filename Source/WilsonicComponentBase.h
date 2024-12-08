/*
  ==============================================================================

    WilsonicComponentBase.h
    Created: 10 Jul 2021 1:46:26pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// forward
class WilsonicProcessor;

// base class for components: provides references to Processor, which unlocks Skin, Designs, etc.
class WilsonicComponentBase 
: public Component
{
    // lifecycle
public:
    WilsonicComponentBase(WilsonicProcessor&);
    ~WilsonicComponentBase() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WilsonicComponentBase)

public:
    // drawing
    void paint(Graphics&) override;
    void resized() override;

protected:
    WilsonicProcessor& _processor;
    unsigned long _debug_paint_counter = 0;
};
