/**
 * @file PythagoreanMeans.h
 * @author Marcus W. Hobbs
 * @date 12 Jul 2021
 * @brief This file contains the PythagoreanMeans struct.
 */

#pragma once

#include "Tuning_Include.h"

/**
 * @brief This struct represents the Pythagorean means.
 */
struct PythagoreanMeans final
{
    /**
     * @brief Enum class for the types of Pythagorean means.
     */
    enum class Type
    {
        Proportional = 0, /**< Proportional type */
        Geometric = 1, /**< Geometric type */
        Subcontrary = 2 /**< Subcontrary type */
    };

    /**
     * @brief Constructor for PythagoreanMeans.
     * @param root The root of the Pythagorean means.
     * @param third The third of the Pythagorean means.
     * @param fifth The fifth of the Pythagorean means.
     * @param type The type of the Pythagorean means.
     */
    PythagoreanMeans(unsigned long const, unsigned long const, unsigned long const, Type const);

    /**
     * @brief Get the root of the Pythagorean means.
     * @return The root of the Pythagorean means.
     */
    unsigned long const getRoot();

    /**
     * @brief Get the third of the Pythagorean means.
     * @return The third of the Pythagorean means.
     */
    unsigned long const getThird();

    /**
     * @brief Get the fifth of the Pythagorean means.
     * @return The fifth of the Pythagorean means.
     */
    unsigned long const getFifth();

    /**
     * @brief Get the type of the Pythagorean means.
     * @return The type of the Pythagorean means.
     */
    Type const getType();

    /**
     * @brief Overload of the << operator for PythagoreanMeans.
     * @param os The ostream object.
     * @param means The PythagoreanMeans object.
     * @return The ostream object.
     */
    friend ostream& operator << (ostream&, PythagoreanMeans&);

private:
    unsigned long const _scaleDegree[3]; /**< The scale degree of the Pythagorean means. */
    Type const _type; /**< The type of the Pythagorean means. */
};

