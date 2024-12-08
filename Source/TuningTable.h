/**
 * @file TuningTable.h
 * @author Marcus W. Hobbs
 * @date 21 Feb 2021
 * @brief This file contains the TuningTable class.
 */

#pragma once

#include "Tuning_Include.h"

/**
 * @class TuningTable
 * @brief This class represents a tuning table.
 */
class TuningTable
{
public:
    /**
     * @brief Destructor.
     */
    virtual ~TuningTable() noexcept = default;

    /**
     * @brief Get the sample rate.
     * @return The sample rate.
     */
    virtual const float getSampleRate() = 0;

    /**
     * @brief Set the sample rate.
     * @param nyquist The new sample rate.
     */
    virtual void setSampleRate (float nyquist) = 0;

    /**
     * @brief Set the tuning table.
     * @param frequency The frequency.
     * @param index The index.
     */
    virtual void setTuningTable (float frequency, unsigned long index) = 0;

    /**
     * @brief Get the tuning table frequency.
     * @param index The index.
     * @return The frequency at the given index.
     */
    virtual const float getTuningTableFrequency (unsigned long index) = 0;
};


