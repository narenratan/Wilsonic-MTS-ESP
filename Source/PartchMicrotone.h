/*
 ==============================================================================
 
 PartchMicrotone.h
 Created: 30 Jun 2024 12:46:39pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"
#include "Partch.h"
#include "Microtone.h"

class PartchMicrotone;
using PartchMicrotone_p = shared_ptr<PartchMicrotone>;

class PartchMicrotone final : public Microtone
{
    
public:
    
    // lifecycle
    PartchMicrotone(float f,
                    string desc,
                    bool o1 = false,
                    bool u1 = false,
                    bool o3 = false,
                    bool u3 = false,
                    bool o5 = false,
                    bool u5 = false,
                    bool o7 = false,
                    bool u7 = false,
                    bool o9 = false,
                    bool u9 = false,
                    bool o11 = false,
                    bool u11 = false);
    ~PartchMicrotone() noexcept override = default;
    
    // copy and assignment constructors
    PartchMicrotone(const PartchMicrotone& m); // do not use this outside of this class, use clone() instead
    virtual Microtone_p clone() const override;
    
    // Public member functions
    
    // This is intended to darken tones that are not on a selected row/column of the diamand.
    // If no rows/columns are selected, then nothing is darkened.
    bool isOtonalUtonal(bool o1, bool u1, bool o3, bool u3, bool o5, bool u5, bool o7, bool u7, bool o9, bool u9, bool o11, bool u11);
    
private:
    bool _o1, _u1, _o3, _u3, _o5, _u5, _o7, _u7, _o9, _u9, _o11, _u11;
};
