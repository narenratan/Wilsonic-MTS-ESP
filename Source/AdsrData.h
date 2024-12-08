/*
  ==============================================================================

    AdsrData.h
    Created: 7 Feb 2021 2:29:21pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public ADSR
{

public:

    void update (const float attack, const float decay, const float sustain, const float release);
    
private:
    
    ADSR::Parameters adsrParams;
};
