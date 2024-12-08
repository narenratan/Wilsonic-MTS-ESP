/*
  ==============================================================================

    MeterData.h
    Created: 27 Feb 2021 9:37:46pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Tuning_Include.h"

class MeterData
{

public:

    void process (AudioBuffer<float>& buffer);

    const atomic<float>& getRMS();

    const atomic<float>& getPeak();
    
private:

    atomic<float> _rms {0.f};
    
    atomic<float> _peak {0.f};
};
