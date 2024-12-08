/**
 * @file MicrotoneArray.h
 * @author Marcus W. Hobbs
 * @date 14 Feb 2021
 * @brief This file contains the MicrotoneArray class.
 */

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"
#include "Microtone.h"

class MicrotoneArray;

/**
 * @class MicrotoneArray
 * @brief This class represents an array of microtones.
 */
class MicrotoneArray final
{
public:
    // lifecycle
    MicrotoneArray();
    ~MicrotoneArray();
    MicrotoneArray(const MicrotoneArray& m); ///< Deep copy constructor
    MicrotoneArray& operator=(const MicrotoneArray& other);
    /*
    MicrotoneArray(MicrotoneArray&& other) noexcept;
    MicrotoneArray& operator=(MicrotoneArray&& other) noexcept;
*/
    
    // Constructors that create a MicrotoneArray from various inputs
    MicrotoneArray(vector<Microtone_p> a ); ///< Deep copy constructor from a vector of Microtone pointers
    MicrotoneArray(vector<float> harmonics); ///< Constructor from a vector of harmonics
    MicrotoneArray(vector<unsigned long> numeratorDenominatorPairs); ///< Constructor from a vector of numerator/denominator pairs. Starts with 1/1, then adds rational DELTAS: MicrotoneArray (vector<int> {3, 2}) --> 1/1, 3/2

    // static factory methods
    static MicrotoneArray microtoneArray();
    static MicrotoneArray microtoneArrayHarmonicLimit(int limit, float period);
    static MicrotoneArray microtoneArrayFromArray(vector<Microtone_p> inputArray); ///< Deep copy factory method from a vector of Microtone pointers
    static MicrotoneArray microtoneArrayFromArrayOfFloats(vector<float> inputArray); ///< Factory method from a vector of floats

    // this is different than the above...it builds the array as degrees, not as deltas.
    static MicrotoneArray microtoneArrayFromArrayOfNumDenPairs(vector<int> numeratorDenominatorPairs); ///< Factory method from a vector of numerator/denominator pairs

    // instance methods
    // TODO: container is a vector--return pass-through iterators
    void addMicrotone(Microtone_p microtone); ///< Adds a Microtone to the array
    void insertMicrotone(Microtone_p microtone, unsigned long index); ///< Inserts a Microtone at a specific index in the array
    void addMicrotoneDelta(Microtone_p delta); ///< Adds a Microtone delta to the array
    bool containsMicrotone(Microtone_p microtone); ///< Checks if the array contains a specific Microtone
    void removeAllMicrotones(); ///< Removes all Microtones from the array
    unsigned long const count(); ///< Returns the count of Microtones in the array
    Microtone_p microtoneAtIndex(unsigned long index); ///< Returns the Microtone at a specific index
    void setMicrotone(Microtone_p m, unsigned long index); ///< Sets a Microtone at a specific index
    Microtone_p firstMicrotone(); ///< Returns the first Microtone in the array
    Microtone_p lastMicrotone(); ///< Returns the last Microtone in the array
    MicrotoneArray subarrayWithRange(unsigned long offset, unsigned long num_terms); ///< Returns a subarray of Microtones within a specific range
    MicrotoneArray octaveReduce(float period); ///< Returns an octave-reduced MicrotoneArray
    MicrotoneArray sort(); ///< Returns a sorted MicrotoneArray
    MicrotoneArray sortByShortDescription(); ///< Returns a MicrotoneArray sorted by short description
    MicrotoneArray uniquify(); ///< Returns a MicrotoneArray with unique Microtones
    MicrotoneArray removePowersOf2(); ///< Returns a MicrotoneArray with powers of 2 removed. Useful for both octave and non-octave use cases
    tuple<MicrotoneArray, map<int, int>> npoOverride(int newNPO); /// duplicates/removes items as neccessary to return a microtone array of size newNPO
    
    // print
    friend ostream& operator << (ostream& os, MicrotoneArray& m); ///< Overloaded output stream operator for printing
    string const getDebugDescription(); ///< Returns a debug description of the MicrotoneArray

private:
    vector<Microtone_p> _array {}; // Vector of Microtone pointers
    float _period = TuningConstants::defaultPeriod; // Period of the MicrotoneArray
    CriticalSection _lock;     // lock
};

