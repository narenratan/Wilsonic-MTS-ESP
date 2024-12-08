/*
 ==============================================================================

 WilsonicMath.cpp
 Created: 28 Feb 2021 2:00:03pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "WilsonicMath.h"

float WilsonicMath::smoothstep(float edge0, float edge1, float x) {
    jassert(!isnan(edge0));
    jassert(!isnan(edge1));
    jassert(!isnan(x));
    jassert(!isinf(edge0));
    jassert(!isinf(edge1));
    jassert(!isinf(x));
    
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
    jassert(!isnan(valA));
    jassert(!isnan(valB));
    jassert(!isnan(fract));
    jassert(!isinf(valA));
    jassert(!isinf(valB));
    jassert(!isinf(fract));
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
