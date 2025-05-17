#include <cassert>
#include <cmath>

#ifndef jassert
#define jassert(x) assert(x)
#endif

template <typename Type>
static Type jlimit(Type lower, Type upper, Type value)
{
    return value < lower ? lower : (value > upper ? upper : value);
}

#include "../Source/WilsonicMath.h"

int main() {
    using WM = WilsonicMath;

    // linear interpolation clamps fraction to [0,1]
    assert(WM::linearInterp(0.0f, 10.0f, 0.5f) == 5.0f);
    assert(WM::linearInterp(0.0f, 10.0f, -1.0f) == 0.0f);
    assert(WM::linearInterp(0.0f, 10.0f, 2.0f) == 10.0f);

    // smoothstep should return 0 at edge0 and 1 at edge1
    assert(WM::smoothstep(0.0f, 1.0f, 0.0f) == 0.0f);
    assert(WM::smoothstep(0.0f, 1.0f, 1.0f) == 1.0f);

    float mid = WM::smoothstep(0.0f, 1.0f, 0.5f);
    assert(std::fabs(mid - 0.5f) <= WM::getEpsilon(WM::Epsilon::CALC));

    // floating point comparisons
    assert(WM::floatsAreEqual(0.1f, 0.1f));
    assert(WM::floatsAreNotEqual(0.1f, 0.1002f, WM::Epsilon::UI));

    return 0;
}
