/*
  ==============================================================================

    TritriadicTuning.h
    Created: 22 Sep 2021 4:33:39pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"
#include "Microtone.h"
#include "Tuning.h"
#include "TuningImp.h"

class TritriadicTuning 
: public TuningImp
{
public:
    // public static
    static constexpr float mediantMin {0};
    static constexpr float mediantMax {1};
    static constexpr float mediantDefault {0.3219280949f};
    static constexpr float dominantMin {0};
    static constexpr float dominantMax {1};
    static constexpr float dominantDefault {0.5849625007f};
    static constexpr unsigned long numTerms {7};

    // lifecycle
    TritriadicTuning();
    ~TritriadicTuning() override;

    // public methods
    void setMD(float m, float d); // calls _update by setting microtone array
    void setMediant(float m);
    void setDominant(float d);
    const float getDominantAsPitch();
    const float getDominantAsFrequency();
    const float getDominantAsCents();
    const float getMediantAsPitch();
    const float getMediantAsFrequency();
    const float getMediantAsCents();

    // scala
    String defaultScalaName() override;
    String scalaComments() override;

private:
    float _dominant {0.580f}; // stored as pitch
    float _mediant {0.320f}; // stored as pitch
    void _helper();
    vector<Microtone_p> _ttMicrotoneArray;
};


