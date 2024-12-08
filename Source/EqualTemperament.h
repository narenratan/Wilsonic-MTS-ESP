/*
  ==============================================================================

    EqualTemperament.h
    Created: 25 May 2022 7:58:16pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "TuningImp.h"
#include "Tuning_Include.h"

class EqualTemperament 
: public TuningImp
{
public:
    // static
    static unsigned long constexpr minNPO = 1;
    static unsigned long constexpr maxNPO = 128;
    static unsigned long constexpr defaultNPO = 12;
    
    // lifecycle
    EqualTemperament();
    ~EqualTemperament() override;

    // public methods
    void setNPO(unsigned long npo);
    unsigned long getNPO();
    void setPeriod(float period);
    float getPeriod();
    const string getParameterDescription() override;

    // drawing
    bool canPaintTuning() override;
    void paint(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds) override;

    // scala
    String defaultScalaName() override;
    String scalaComments() override;

private:
    // private members
    unsigned long _npo = defaultNPO;

    // private methods
    void _updateET();
};
