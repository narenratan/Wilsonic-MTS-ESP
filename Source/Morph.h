/*
  ==============================================================================

    Morph.h
    Created: 17 Dec 2023 1:41:35pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "TuningImp.h"
#include "Tuning_Include.h"

class WilsonicProcessor;

class Morph
: public TuningImp
{
public:
    enum class InterpolationType {
        Linear = 0,
        Log2 = 1
    };
    static constexpr int num_interpolation_types = 2;
    static StringArray getInterpolationTypeNames() { return __interpolationTypes; }
    static const StringArray __interpolationTypes;
    static int constexpr getInterpolationTypeDefault() {return 0;}
    static float constexpr getInterpolationMin() {return 0.f;}
    static float constexpr getInterpolationMax() {return 1.f;}

public:
    Morph();
    ~Morph() noexcept override = default;
    
    void setA(shared_ptr<Tuning> A);
    void setB(shared_ptr<Tuning> B);
    
    float getInterpolationValue();
    void setInterpolationValue(float);
    
    Morph::InterpolationType getInterpolationType();
    void setInterpolationType(Morph::InterpolationType type);
    
    // Drawing
    bool canPaintTuning() override; ///< Check if the tuning can be painted.
    void paint(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds) override; ///< Paint the tuning.

    // overrides TuningImp::update, modifies the tuningtable directly.
    void _update() override;
    void setNoteNumberMiddleC(unsigned long nn) override;
    void setFrequencyMiddleC(float f) override;
    void setOctaveMiddleC(int o) override;
    
private:
    // members
    shared_ptr<Tuning> _A;
    shared_ptr<Tuning> _B;
    float _interpolationValue = 0.f;
    Morph::InterpolationType _interpolationType = Morph::InterpolationType::Linear;

    // methods
    void paint01(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds); // both A and B are normalized, not very revealing
    void paint02(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds); // normalize A and B by some useful range
    void paint03(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds); // normalize A and B by some useful range, plus cool rendering
    void paint04(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds); // normalize A and B by some useful range, gradient rendering as paths
    void paint05(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds); // normalize A and B by some useful range, gradient rendering as paths
};
