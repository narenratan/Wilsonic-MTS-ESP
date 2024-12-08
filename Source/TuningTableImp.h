/**
 * @file TuningTableImp.h
 * @author Marcus W. Hobbs
 * @date 14 Feb 2021
 * @brief This file contains the TuningTableImp class.
 */

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"
#include "TuningConstants.h"
#include "TuningTable.h"
#include "WilsonicProcessorConstants.h"

/**
 * @class TuningTableImp
 * @brief This class is an implementation of the TuningTable interface.
 */
class TuningTableImp
: public TuningTable
{
public:
    TuningTableImp();
    TuningTableImp(const TuningTableImp& tt);
    ~TuningTableImp() noexcept override = default;

    const float getSampleRate() override;
    void setSampleRate(float sampleRate) override;
    void setTuningTable(float frequency, unsigned long index) override;
    const float getTuningTableFrequency(unsigned long index) override;
    
    friend ostream& operator << (ostream&, TuningTableImp& m);

private:
    /**
     * @brief The sample rate. Not used yet, need to decide how to clamp frequencies in a table.
     */
    float _sampleRate = 44100.f;

    /**
     * @brief The tuning table.
     */
    array<atomic<float>, WilsonicProcessorConstants::numMidiNotes> _tuningTable;
};
