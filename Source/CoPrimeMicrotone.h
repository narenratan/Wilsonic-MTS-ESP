/*
 ==============================================================================
 
 CoPrimeMicrotone.h
 Created: 23 Apr 2023 12:40:07pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"
#include "CoPrime.h"
#include "Microtone.h"

class CoPrimeMicrotone;
using CoPrimeMicrotone_p = shared_ptr<CoPrimeMicrotone>;

class CoPrimeMicrotone final : public Microtone
{
    
public:
    
    // lifecycle
    CoPrimeMicrotone(unsigned long numerator,
                     unsigned long denominator,
                     Microtone::Space space = Microtone::Space::Linear,
                     float period = TuningConstants::defaultOctave);
    ~CoPrimeMicrotone() noexcept override = default;
    
    // copy and assignment constructors
    CoPrimeMicrotone(const CoPrimeMicrotone& m); // do not use this outside of this class, use clone() instead
    virtual Microtone_p clone() const override;
    
    // public member functions
    
    bool isCoPrime();
    unsigned long getX(); // 0-based index into x of parent 2d array
    void setX(unsigned long x); // 0-based index into x of parent 2d array
    unsigned long getY(); // 0-based index into y of parent 2d array
    void setY(unsigned long y); // 0-based index into y of parent 2d array
    unsigned long getNoteNumber(); // 0-based note number
    void setNoteNumber(unsigned long note_number); // 0-based note number
    bool getIsClipped();
    void setIsClipped(bool is_clipped);
    
private:
    bool _isCoPrime = false;
    unsigned long _x = 0;
    unsigned long _y = 0;
    unsigned long _noteNumber = 0;
    bool _isClipped = false;
};
