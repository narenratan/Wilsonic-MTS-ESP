/*
 ==============================================================================
 
 CoPrimeMicrotone.cpp
 Created: 23 Apr 2023 12:40:07pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "CoPrimeMicrotone.h"

CoPrimeMicrotone::CoPrimeMicrotone(unsigned long numerator,
                                   unsigned long denominator,
                                   Microtone::Space space,
                                   float period)
: Microtone(numerator, denominator, "", space, period, false) // empty desc calls updateshortdesc
{
    // reduce so 2/2, 6/3, n/n, etc.,  is coprime
    auto f = Fraction(numerator, denominator, true); // reduce
    _isCoPrime = CoPrime::GCD(f.numerator(), f.denominator()) == 1;
    updateShortDescriptionText(); // sets "numerator/denominator"
}

CoPrimeMicrotone::CoPrimeMicrotone(const CoPrimeMicrotone& other)
: Microtone(other)
, _isCoPrime(other._isCoPrime)
, _x(other._x)
, _y(other._y)
, _noteNumber(other._noteNumber)
, _isClipped(other._isClipped)
{
    
}

Microtone_p CoPrimeMicrotone::clone() const
{
    return make_shared<CoPrimeMicrotone>(*this);
}

// Implementation of the isCoPrime method
bool CoPrimeMicrotone::isCoPrime()
{
    return _isCoPrime;
}

// Implementation of the getX method
unsigned long CoPrimeMicrotone::getX()
{
    return _x;
}

// Implementation of the setX method
void CoPrimeMicrotone::setX(unsigned long x)
{
    _x = x;
}

// Implementation of the getY method
unsigned long CoPrimeMicrotone::getY()
{
    return _y;
}

// Implementation of the setY method
void CoPrimeMicrotone::setY(unsigned long y)
{
    _y = y;
}

// Implementation of the getNoteNumber method
unsigned long CoPrimeMicrotone::getNoteNumber()
{
    return _noteNumber;
}

// Implementation of the setNoteNumber method
void CoPrimeMicrotone::setNoteNumber(unsigned long note_number)
{
    _noteNumber = note_number;
}

bool CoPrimeMicrotone::getIsClipped()
{
    return _isClipped;
}

void CoPrimeMicrotone::setIsClipped(bool is_clipped)
{
    _isClipped = is_clipped;
}

