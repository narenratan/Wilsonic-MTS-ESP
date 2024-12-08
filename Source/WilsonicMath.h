/*
  ==============================================================================

    WilsonicMath.h
    Created: 28 Feb 2021 2:00:03pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct WilsonicMath
{
public:
    static float smoothstep(float edge0, float edge1, float x);
    static float linearInterp(float valA, float valB, float fract);
    
    // float comparisons
    enum class Epsilon {
        UI,
        CALC
    };
    static float getEpsilon(WilsonicMath::Epsilon type);
    static bool floatsAreNotEqual(float a, float b, WilsonicMath::Epsilon epsilon=Epsilon::CALC);
    static bool floatsAreEqual(float a, float b, WilsonicMath::Epsilon epsilon=Epsilon::CALC);
};
