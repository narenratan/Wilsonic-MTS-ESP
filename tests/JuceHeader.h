#pragma once
#include <cassert>
#include <cmath>
#include <limits>

#ifndef jassert
#define jassert(x) assert(x)
#endif

template <typename Type>
static constexpr const Type& jlimit(const Type& lower, const Type& upper, const Type& value)
{
    return value < lower ? lower : (value > upper ? upper : value);
}
