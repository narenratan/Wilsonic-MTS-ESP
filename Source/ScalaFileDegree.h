/*
  ==============================================================================

    ScalaFileDegree.h
    Created: 2 Dec 2022 6:31:14pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"

// degree
class ScalaFileDegree
{
public:
    ScalaFileDegree(unsigned long long n, unsigned long long d);
    explicit ScalaFileDegree(double cents);
    double get_ratio();
    void set_desc(string desc);
    string get_desc();

private:
    double _ratio;
    string _desc;
};
