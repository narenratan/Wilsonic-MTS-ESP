/*
  ==============================================================================

    Fraction.h
    Created: 14 Feb 2021 5:08:10pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

// from: https://github.com/harrylewis/fractionClass/blob/master/fractionClass.h

// dependencies
#include <JuceHeader.h>
#include "Tuning_Include.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// Fraction Class definition
class Fraction final
{
public:
    Fraction();
    Fraction(unsigned long);
    Fraction(unsigned long, unsigned long, bool should_reduce = true);

    // getters
    unsigned long numerator() const { return _num; }
    unsigned long denominator() const { return _den; }
    float floatValue() const { return float (_num) / float (_den) ;}

    // modifiers
    unsigned long greatestCommonFactor(unsigned long, unsigned long);

    // overloaded binary operators
    Fraction operator ++ ();
    Fraction operator += (const Fraction&);
    bool operator <= (const Fraction&);
    bool operator == (const Fraction&);
    bool operator >= (const Fraction&);

    // operator overloads
    friend bool operator > (const Fraction&, const Fraction&);
    friend bool operator < (const Fraction&, const Fraction&);
    friend Fraction operator + (const Fraction&, const Fraction&);
    friend Fraction operator - (const Fraction&, const Fraction&);
    friend Fraction operator * (const Fraction&, const Fraction&);
    friend Fraction operator / (const Fraction&, const Fraction&);
    friend bool operator != (const Fraction&, const Fraction&);
    friend istream& operator >> (istream&, Fraction&);
    friend ostream& operator << (ostream&, const Fraction&);

private:
    unsigned long _num;
    unsigned long _den;
};
