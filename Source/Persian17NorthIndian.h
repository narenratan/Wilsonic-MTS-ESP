/**
 * @file Persian17NorthIndian.h
 * @brief Declaration of the Persian17NorthIndian class.
 * @author Marcus W. Hobbs
 * @date Created: 18 Mar 2022 7:42:43pm
 * 
 * This file contains the declaration of the Persian17NorthIndian class, which is a subclass of the TuningImp class.
 * It adds additional properties and methods specific to the Persian17NorthIndian.
 * 
 * ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"
#include "Microtone.h"
#include "MicrotoneArray.h"
#include "TuningImp.h"

/**
 * @brief The Persian17NorthIndian class.
 * 
 * This class represents a Persian 17 North Indian tuning system.
 */
class Persian17NorthIndian : public TuningImp
{
public:

    /**
     * @brief Enumeration of the scales used in the Persian 17 North Indian tuning system.
     * 
     * These scales must never change.
     */
    enum class Scale {
        Master        = 0 ,
        Kalyan        = 1 ,
        Bilawal       = 2 ,
        Khamaj        = 3 ,
        KhafiOld      = 4 ,
        Kafi          = 5 ,
        Asawari       = 6 ,
        Bhairavi      = 7 ,
        Marwa         = 8 ,
        Purvi         = 9 ,
        Lalit2        = 10,
        Todi          = 11,
        Lalit         = 12,
        NoName        = 13,
        AnandBhairav  = 14,
        Bhairav       = 15,
        JogiyaTodi    = 16,
        Madhubanti    = 17,
        NatBhairav    = 18,
        AhirBhairav   = 19,
        ChandraKanada = 20,
        BasantMukhari = 21,
        Champakali    = 22,
        Patdeep       = 23,
        MohanKanuns   = 24,
        Parameswari   = 25
    };

    // These must be indexed by Scale, and the order should never change
    static const StringArray __scaleNames; ///< Names of the scales.
    static const vector<Persian17NorthIndian::Scale> all_scales; ///< All scales.
    static constexpr int num_scales = 26; ///< Number of scales.

    // Lifecycle
    Persian17NorthIndian(); ///< Constructor.
    ~Persian17NorthIndian() override; ///< Destructor.

    // Public methods
    void setScale (Scale mode); ///< Set the scale.
    int const getScale(); ///< Get the scale. Returns int instead of Scale enum.
    
    // Drawing
    bool canPaintTuning() override; ///< Check if the tuning can be painted.
    void paint(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds) override; ///< Paint the tuning.

    // Scala
    String defaultScalaName() override; ///< Get the default Scala name.
    String scalaComments() override; ///< Get the Scala comments.

private:
    // Private methods
    MicrotoneArray _mt_scale(vector<unsigned long> degrees); ///< Get the microtone array for the given degrees.

    // Paint variants

    // Original...too busy
    void paint00(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds); ///< Paint the tuning (original version).

    // Super-simple version
    void paint01(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds); ///< Paint the tuning (simplified version).

    // Private members
    Scale _scale = Scale::Master; ///< The current scale.
    static MicrotoneArray __persian17; ///< The Persian 17 microtone array.
    static const vector<float> __pitch_array[num_scales]; ///< Array of pitches for drawing.
    static const vector<String> __interval_array[num_scales]; ///< Array of intervals for drawing.
};
