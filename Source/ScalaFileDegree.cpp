/*
  ==============================================================================

    ScalaFileDegree.cpp
    Created: 2 Dec 2022 6:31:14pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "ScalaFileDegree.h"

ScalaFileDegree::ScalaFileDegree(unsigned long long n, unsigned long long d)
{
    // Two inputs: a ratio
    _ratio  = static_cast<double>(n) / static_cast<double>(d);
    _desc = to_string(n);
    if(d != 1)
    {
        _desc += "/" + to_string(d);
    }
}

ScalaFileDegree::ScalaFileDegree(double cents)
{
    // One input: cents
    if(WilsonicMath::floatsAreEqual(static_cast<float>(cents), 0.f))
    {
        _ratio = 1;
        _desc = "1";
    }
    else
    {
        _ratio = pow(pow(2, 1.0 / 12.0), cents/100.0);
        _desc = to_string(_ratio);
    }
}

double ScalaFileDegree::get_ratio()
{
    return _ratio;
}

void ScalaFileDegree::set_desc (string desc)
{
    _desc = desc;
}

string ScalaFileDegree::get_desc()
{
    return _desc;
}
