/*
 ==============================================================================

 WilsonicMath.cpp
 Created: 28 Feb 2021 2:00:03pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "WilsonicMath.h"

float WilsonicMath::smoothstep(float edge0, float edge1, float x) {
    jassert(!std::isnan(edge0));
    jassert(!std::isnan(edge1));
    jassert(!std::isnan(x));
    jassert(!std::isinf(edge0));
    jassert(!std::isinf(edge1));
    jassert(!std::isinf(x));
    
    // same = return edge0
    if(floatsAreEqual(edge0, edge1, Epsilon::CALC)) {
        return edge0;
    }

    float t = (x - edge0) / (edge1 - edge0);
    t = (t < 0.0f ? 0.0f : (t > 1.0f ? 1.0f : t));

    return(t * t * (3.0f - 2.0f * t));
}

float WilsonicMath::linearInterp(float valA, float valB, float fract)
{
    jassert(!std::isnan(valA));
    jassert(!std::isnan(valB));
    jassert(!std::isnan(fract));
    jassert(!std::isinf(valA));
    jassert(!std::isinf(valB));
    jassert(!std::isinf(fract));
    float const fract01 = jlimit(0.f, 1.f, fract);

    return valA + ((valB - valA) * fract01);
}

float WilsonicMath::getEpsilon(Epsilon type) 
{
    switch (type) {
        case Epsilon::UI: return 1e-4f;
        case Epsilon::CALC: return std::numeric_limits<float>::epsilon();
    }
    
    // Default case, if needed
    return std::numeric_limits<float>::epsilon();
}

bool WilsonicMath::floatsAreNotEqual(float a, float b, WilsonicMath::Epsilon epsilonType) {
    float const epsilon = getEpsilon(epsilonType);
    
    return fabs(a - b) > epsilon;
}

bool WilsonicMath::floatsAreEqual(float a, float b, WilsonicMath::Epsilon epsilonType) {
    float const epsilon = getEpsilon(epsilonType);
    
    return fabs(a - b) <= epsilon;
}
