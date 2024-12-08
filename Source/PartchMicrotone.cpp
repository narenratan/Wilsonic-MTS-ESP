/*
 ==============================================================================
 
 PartchMicrotone.cpp
 Created: 30 Jun 2024 12:46:39pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "PartchMicrotone.h"

PartchMicrotone::PartchMicrotone(float f,
                                 string desc,
                                 bool o1,
                                 bool u1,
                                 bool o3,
                                 bool u3,
                                 bool o5,
                                 bool u5,
                                 bool o7,
                                 bool u7,
                                 bool o9,
                                 bool u9,
                                 bool o11,
                                 bool u11)
: Microtone(f, desc, Microtone::Space::Linear, TuningConstants::defaultOctave)
, _o1(o1)
, _u1(u1)
, _o3(o3)
, _u3(u3)
, _o5(o5)
, _u5(u5)
, _o7(o7)
, _u7(u7)
, _o9(o9)
, _u9(u9)
, _o11(o11)
, _u11(u11) {
}

PartchMicrotone::PartchMicrotone(const PartchMicrotone& other)
: Microtone(other)
, _o1(other._o1)
, _u1(other._u1)
, _o3(other._o3)
, _u3(other._u3)
, _o5(other._o5)
, _u5(other._u5)
, _o7(other._o7)
, _u7(other._u7)
, _o9(other._o9)
, _u9(other._u9)
, _o11(other._o11)
, _u11(other._u11) {
    
}

Microtone_p PartchMicrotone::clone() const {
    return make_shared<PartchMicrotone>(*this);
}

// This is intended to darken tones that are not on a selected row/column of the diamand.
// If no rows/columns are selected, then nothing is darkened.
bool PartchMicrotone::isOtonalUtonal(bool o1, bool u1, bool o3, bool u3, bool o5, bool u5, bool o7, bool u7, bool o9, bool u9, bool o11, bool u11) {
    auto const activeOtonalUtonal = o1 || u1 || o3 || u3 || o5 || u5 || o7 || u7 || o9 || u9 || o11 || u11;
    if(!activeOtonalUtonal)
        return true;
    
    auto const selectedTones =
    ((o1 == true) &&  (_o1 == true))||
    ((u1 == true) &&  (_u1 == true))||
    ((o3 == true) &&  (_o3 == true))||
    ((u3 == true) &&  (_u3 == true))||
    ((o5 == true) &&  (_o5 == true))||
    ((u5 == true) &&  (_u5 == true))||
    ((o7 == true) &&  (_o7 == true))||
    ((u7 == true) &&  (_u7 == true))||
    ((o9 == true) &&  (_o9 == true))||
    ((u9 == true) &&  (_u9 == true))||
    ((o11 == true) &&  (_o11== true)) ||
    ((u11 == true) &&  (_u11== true));
    
    return selectedTones;
}
