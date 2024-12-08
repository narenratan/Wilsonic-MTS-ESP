/**
  * @file PythagoreanMeans.cpp
  * @author Marcus W. Hobbs
  * @date 13 Jul 2021
  * @brief This file contains the implementation of the PythagoreanMeans struct.
  */

#include "PythagoreanMeans.h"

/**
  * @brief Constructor for the PythagoreanMeans struct.
  * @param root The root of the Pythagorean mean.
  * @param third The third of the Pythagorean mean.
  * @param fifth The fifth of the Pythagorean mean.
  * @param type The type of the Pythagorean mean.
  */
PythagoreanMeans::PythagoreanMeans(unsigned long const root, unsigned long const third, unsigned long const fifth, PythagoreanMeans::Type const type)
: _scaleDegree{root, third, fifth}
, _type(type)
{
    jassert(root >= 0);
    jassert(third > 0);
    jassert(fifth > 0);
    jassert(root < third);
    jassert(third < fifth);
    jassert(type == PythagoreanMeans::Type::Proportional || type == PythagoreanMeans::Type::Geometric || type == PythagoreanMeans::Type::Subcontrary);
}

/**
  * @brief Getter for the root of the Pythagorean mean.
  * @return The root of the Pythagorean mean.
  */
unsigned long const PythagoreanMeans::getRoot() {
    return _scaleDegree[0];
}

/**
  * @brief Getter for the third of the Pythagorean mean.
  * @return The third of the Pythagorean mean.
  */
unsigned long const PythagoreanMeans::getThird() {
    return _scaleDegree[1];
}

/**
  * @brief Getter for the fifth of the Pythagorean mean.
  * @return The fifth of the Pythagorean mean.
  */
unsigned long const PythagoreanMeans::getFifth() {
    return _scaleDegree[2];
}

/**
  * @brief Getter for the type of the Pythagorean mean.
  * @return The type of the Pythagorean mean.
  */
PythagoreanMeans::Type const PythagoreanMeans::getType() {
    return _type;
}

/**
  * @brief Overloaded operator for outputting the Pythagorean mean to an ostream.
  * @param os The ostream to output to.
  * @param m The Pythagorean mean to output.
  * @return The ostream after outputting the Pythagorean mean.
  */
ostream& operator << (ostream& os, PythagoreanMeans& m) {
    string type = "";
    switch (m.getType()) {
        case PythagoreanMeans::Type::Proportional:
            type = "Proportional";
            break;
        case PythagoreanMeans::Type::Geometric:
            type = "Geometric";
            break;
        case PythagoreanMeans::Type::Subcontrary:
            type = "Subcontrary";
            break;
        default:
            jassertfalse;
            break;
    }
    os << type << "(";
    os << to_string (m.getRoot()) << ", ";
    os << to_string (m.getThird()) << ", ";
    os << to_string (m.getFifth()) << ")" << endl;

    return os;
}
