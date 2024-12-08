/**
 * @file BrunMicrotone.cpp
 * @brief Implementation of the BrunMicrotone class.
 * @author Marcus W. Hobbs
 * @date Created: 24 Feb 2021 4:10:59pm
 * 
 * This file contains the implementation of the BrunMicrotone class, which is a subclass of the Microtone class.
 * It adds additional properties and methods specific to the BrunMicrotone.
 * 
 * ==============================================================================
 */

#include "BrunMicrotone.h"

/**
 * @brief Constructor for the BrunMicrotone class.
 * @param f The frequency of the microtone.
 * @param scaleDegree The scale degree of the microtone.
 * @param level The level of the microtone.
 */
BrunMicrotone::BrunMicrotone(float f, int scaleDegree, unsigned long level)
: Microtone(f, "", Space::LogPeriod, TuningConstants::defaultOctave)
, _scaleDegree(scaleDegree)
, _level(level)
{
    Microtone::_shortDescriptionText = to_string(scaleDegree);
}

/**
 * @brief Copy constructor for the BrunMicrotone class.
 * @param b The BrunMicrotone object to be copied.
 */
BrunMicrotone::BrunMicrotone(const BrunMicrotone& b)
: Microtone(b)
, _scaleDegree(b._scaleDegree)
, _level(b._level)
{
}

/**
 * @brief Clone method for the BrunMicrotone class.
 * @return A shared pointer to a copy of the BrunMicrotone object.
 */
Microtone_p BrunMicrotone::clone() const {
    return make_shared<BrunMicrotone>(*this);
}

/**
 * @brief Getter for the scale degree of the BrunMicrotone.
 * @return The scale degree of the BrunMicrotone.
 */
int BrunMicrotone::getScaleDegree() {
    return _scaleDegree;
}

/**
 * @brief Getter for the level of the BrunMicrotone.
 * @return The level of the BrunMicrotone.
 */
unsigned long BrunMicrotone::getLevel() {
    return _level;
}

/**
 * @brief Overloaded << operator for the BrunMicrotone class.
 * @param os The output stream.
 * @param m The BrunMicrotone object to be printed.
 * @return The output stream.
 */
ostream& operator << (ostream& os, BrunMicrotone_p m) {
    os
    << "Freq: " << m->getFrequencyValueDescription() 
    << ", Scale Degree:" << to_string(m->getScaleDegree()) 
    << ", Level:" << to_string(m->getLevel()) 
    << ", GralPoint:(" << m->getGralErvPoint().toString() 
    << "), HexPoint:(" << m->getGralHexPoint().toString() << ")";
    return os;
}

