/**
  ==============================================================================

    TuningTable.cpp
    Created: 14 Feb 2021 3:11:49pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "TuningTableImp.h"

/**
 * @brief Lifecycle methods for TuningTableImp class.
 */
#pragma mark - Lifecycle

/**
 * @brief Default constructor for TuningTableImp class.
 * Initializes the tuning table to 12ET.
 */
TuningTableImp::TuningTableImp() {
    // default to 12ET
    for (unsigned long i = 0; i < WilsonicProcessorConstants::numMidiNotes; i++) {
        _tuningTable[i].store(static_cast<const float>(TuningConstants::defaultFrequencyA69 * exp2f((i - TuningConstants::defaultNoteNumberA69)/12.f)));
    }
}

/**
 * @brief Copy constructor for TuningTableImp class.
 * @param tt The TuningTableImp object to copy from.
 */
TuningTableImp::TuningTableImp(const TuningTableImp& tt) {
    // default to 12ET
    for (unsigned long i = 0; i < WilsonicProcessorConstants::numMidiNotes; i++ ) {
        _tuningTable[i].store(tt._tuningTable[i].load());
    }
}

/**
 * @brief Methods for TuningTableImp class.
 */
#pragma mark - methods

/**
 * @brief Get the sample rate.
 * @return The sample rate.
 */
const float TuningTableImp::getSampleRate() {
    return _sampleRate;
}

/**
 * @brief Set the sample rate.
 * @param sampleRate The new sample rate.
 */
void TuningTableImp::setSampleRate(float sampleRate) {
    jassert(sampleRate > 0);
    _sampleRate = sampleRate;
}

/**
 * @brief Set the tuning table frequency at a specific index.
 * @param frequency The new frequency.
 * @param index The index at which to set the frequency.
 */
void TuningTableImp::setTuningTable(float frequency, unsigned long index) {
    // how do we limit frequencies in the context of dsp and microtonality?
    jassert(!isnan(frequency));
    jassert(!isinf(frequency));
    jassert(frequency > 0);

    // TODO: Handle clamping based on nyquist, and dynamic sample rate
    //jassert( frequency <= 0.5f * _sampleRate);

    // fatal
    jassert(index >= 0);
    jassert(index < WilsonicProcessorConstants::numMidiNotes);

    // set
    _tuningTable[index].store(frequency);
}

/**
 * @brief Get the tuning table frequency at a specific index.
 * @param index The index from which to get the frequency.
 * @return The frequency at the specified index.
 */
const float TuningTableImp::getTuningTableFrequency(unsigned long index) {
    jassert(index < WilsonicProcessorConstants::numMidiNotes);

    return _tuningTable[index].load();
}

/**
 * @brief Print methods for TuningTableImp class.
 */
#pragma mark - print

/**
 * @brief Overload of the << operator for the TuningTableImp class.
 * @param os The ostream object to output to.
 * @param m The TuningTableImp object to output.
 * @return The ostream object.
 */
ostream& operator << (ostream& os, TuningTableImp& m) {
    for (unsigned long i = 0; i < WilsonicProcessorConstants::numMidiNotes; i++) {
        os << "i: " << i << ", " << m.getTuningTableFrequency(i) << "\n";
    }

    return os;
}
