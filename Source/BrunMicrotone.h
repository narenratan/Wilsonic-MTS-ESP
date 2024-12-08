/**
 * @file BrunMicrotone.h
 * @brief Header file for the BrunMicrotone class.
 * @author Marcus W. Hobbs
 * @date Created: 24 Feb 2021 4:10:59pm
 *
 * This file contains the declaration of the BrunMicrotone class, which is a subclass of the Microtone class.
 * It adds additional properties and methods specific to the BrunMicrotone.
 *
 * ==============================================================================
 */

#pragma once

#include "Microtone.h"

class BrunMicrotone;
using BrunMicrotone_p = shared_ptr<BrunMicrotone>;

class BrunMicrotone final : public Microtone
{
public:
    BrunMicrotone(float f, int scaleDegree, unsigned long level); ///< Constructor.
    ~BrunMicrotone() noexcept override = default; ///< Destructor.
    virtual Microtone_p clone() const override; ///< Clones the microtone.
    BrunMicrotone(const BrunMicrotone& b); // Copy constructor
    
    int getScaleDegree(); ///< Returns the scale degree of the microtone.
    unsigned long getLevel(); ///< Returns the level of the microtone.
    friend ostream& operator << (ostream&, BrunMicrotone_p m); ///< Overloaded stream insertion operator.

private:
    int _scaleDegree = 0; ///< The scale degree of the microtone.
    unsigned long _level = 1; ///< The level of the microtone.
};

