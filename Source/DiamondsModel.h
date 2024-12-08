/**
 * @file DiamondsModel.h
 * @brief Header file for the DiamondsModel class.
 * @details This file contains the declarations of the DiamondsModel class and its member functions.
 * @date Created: 6 Jun 2023 4:30:03pm
 * @author Marcus W. Hobbs
 */

#pragma once

#include <JuceHeader.h>
#include "ModelBase.h"
#include "TriadicDiamond.h"
#include "TetradicDiamond.h"
#include "PentadicDiamond.h"
#include "HexadicDiamond.h"
#include "HeptadicDiamond.h"
#include "OgdoadicDiamond.h"
#include "Tuning.h"
#include "TuningImp.h"
#include "Tuning_Include.h"

/**
 * @class DiamondsModel
 * @brief A class that models the behavior of diamonds.
 * @details This class is responsible for managing the behavior of diamonds. It inherits from ModelBase and ActionBroadcaster.
 */
class DiamondsModel final 
: public ModelBase
, public ActionBroadcaster
{
public:

    // static public members
    static constexpr float rangeMin = 1.f; ///< Minimum range for A,B,C,D,E,F,G,H
    static constexpr float rangeMax = 16384.f; ///< Maximum range for A,B,C,D,E,F,G,H
    static constexpr float rangeStep = 1.f; ///< Step size for A,B,C,D,E,F,G,H
    static const ParameterID getDiamondsParameterID() { return ParameterID ("DiamondsPRESET", AppVersion::getVersionHint()); } ///< Returns the ParameterID for DiamondsPRESET
    static const String getDiamondsParameterName() { return "Diamonds|Preset"; } ///< Returns the ParameterName for DiamondsPRESET
    static const ParameterID getDiamonds_A_ParameterID() { return ParameterID ("DiamondsA", AppVersion::getVersionHint()); } ///< Returns the ParameterID for DiamondsA
    static const String getDiamonds_A_ParameterName() { return "Diamonds|A"; } ///< Returns the ParameterName for DiamondsA
    static const ParameterID getDiamonds_B_ParameterID() { return ParameterID ("DiamondsB", AppVersion::getVersionHint()); } ///< Returns the ParameterID for DiamondsB
    static const String getDiamonds_B_ParameterName() { return "Diamonds|B"; } ///< Returns the ParameterName for DiamondsB
    static const ParameterID getDiamonds_C_ParameterID() { return ParameterID ("DiamondsC", AppVersion::getVersionHint()); } ///< Returns the ParameterID for DiamondsC
    static const String getDiamonds_C_ParameterName() { return "Diamonds|C"; } ///< Returns the ParameterName for DiamondsC
    static const ParameterID getDiamonds_D_ParameterID() { return ParameterID ("DiamondsD", AppVersion::getVersionHint()); } ///< Returns the ParameterID for DiamondsD
    static const String getDiamonds_D_ParameterName() { return "Diamonds|D"; } ///< Returns the ParameterName for DiamondsD
    static const ParameterID getDiamonds_E_ParameterID() { return ParameterID ("DiamondsE", AppVersion::getVersionHint()); } ///< Returns the ParameterID for DiamondsE
    static const String getDiamonds_E_ParameterName() { return "Diamonds|E"; } ///< Returns the ParameterName for DiamondsE
    static const ParameterID getDiamonds_F_ParameterID() { return ParameterID ("DiamondsF", AppVersion::getVersionHint()); } ///< Returns the ParameterID for DiamondsF
    static const String getDiamonds_F_ParameterName() { return "Diamonds|F"; } ///< Returns the ParameterName for DiamondsF
    static const ParameterID getDiamonds_G_ParameterID() { return ParameterID ("DiamondsG", AppVersion::getVersionHint()); } ///< Returns the ParameterID for DiamondsG
    static const String getDiamonds_G_ParameterName() { return "Diamonds|G"; } ///< Returns the ParameterName for DiamondsG
    static const ParameterID getDiamonds_H_ParameterID() { return ParameterID ("DiamondsH", AppVersion::getVersionHint()); } ///< Returns the ParameterID for DiamondsH
    static const String getDiamonds_H_ParameterName() { return "Diamonds|H"; } ///< Returns the ParameterName for DiamondsH

    // lifecycle
public:
    DiamondsModel(); ///< Constructor for DiamondsModel
    ~DiamondsModel() override; ///< Destructor for DiamondsModel
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiamondsModel) ///< Macro to declare that DiamondsModel objects should not be copied or assigned and leak-detection is enabled

public:
    // called only once: on construction of processor
    unique_ptr<AudioProcessorParameterGroup> createParams() override; ///< Creates parameters for the audio processor
    String getGroupID() override; ///< Returns the group ID
    String getGroupName() override; ///< Returns the group name
    String getSubgroupSeparator() override; ///< Returns the subgroup separator
    ParameterID getDesignParameterID() override; ///< Returns the design parameter ID
    StringArray getFavoritesParameterIDs() override; ///< Returns the parameter IDs
    // called only once: when assigning _avpts
    void attachParameterListeners() override; ///< Attaches parameter listeners
    void parameterChanged (const String& parameterID, float newValue) override; ///< Called when a parameter changes
    void updateProperties() override;

    shared_ptr<Tuning> getTuning() override; ///< Returns the current tuning
    const shared_ptr<CPSTuningBase> getParentTuning(); ///< Returns the parent tuning
    unsigned long getNumScales(); ///< Returns the number of scales
    const StringArray getScaleNames(); ///< Returns the names of the scales
    unsigned long getNumberOfSeeds(); ///< Returns the number of seeds
    unsigned long uiGetSelectedScaleIndex(); ///< Returns the index of the selected scale
    void uiSelectScale (unsigned long index = 0); ///< Selects a scale by index
    void uiSetA(float); ///< Sets the value of A
    void uiSetB(float); ///< Sets the value of B
    void uiSetC(float); ///< Sets the value of C
    void uiSetD(float); ///< Sets the value of D
    void uiSetE(float); ///< Sets the value of E
    void uiSetF(float); ///< Sets the value of F
    void uiSetG(float); ///< Sets the value of G
    void uiSetH(float); ///< Sets the value of H
    float uiGetA(); ///< Returns the value of A
    float uiGetB(); ///< Returns the value of B
    float uiGetC(); ///< Returns the value of C
    float uiGetD(); ///< Returns the value of D
    float uiGetE(); ///< Returns the value of E
    float uiGetF(); ///< Returns the value of F
    float uiGetG(); ///< Returns the value of G
    float uiGetH(); ///< Returns the value of H
    void uiLeftArrowKeyPressed(); ///< Called when the left arrow key is pressed
    void uiRightArrowKeyPressed(); ///< Called when the right arrow key is pressed
    void uiUpArrowKeyPressed(); ///< Called when the up arrow key is pressed
    void uiDownArrowKeyPressed(); ///< Called when the down arrow key is pressed

protected:
    void detachParameterListeners() override; ///< Detaches parameter listeners

private:
    // private members
    static const StringArray __DAWKeys; ///< Array of DAW keys for selection of actual scale
    Microtone_p _A = nullptr; ///< Pointer to Microtone A
    Microtone_p _B = nullptr; ///< Pointer to Microtone B
    Microtone_p _C = nullptr; ///< Pointer to Microtone C
    Microtone_p _D = nullptr; ///< Pointer to Microtone D
    Microtone_p _E = nullptr; ///< Pointer to Microtone E
    Microtone_p _F = nullptr; ///< Pointer to Microtone F
    Microtone_p _G = nullptr; ///< Pointer to Microtone G
    Microtone_p _H = nullptr; ///< Pointer to Microtone H

    // current scale/tuning
    unsigned long _selectedScaleIndex = 0; ///< Index of the selected scale
    unsigned long _numberOfSeeds = 3; ///< Number of seeds
    shared_ptr<Tuning> _diamond = nullptr; ///< Pointer to the current diamond tuning
    shared_ptr<CPSTuningBase> _parent = nullptr; ///< Pointer to the parent tuning

    // tunings: lazy load
    shared_ptr<TriadicDiamond> _triadicDiamond = nullptr; ///< Pointer to the triadic diamond tuning
    shared_ptr<TetradicDiamond> _tetradicDiamond = nullptr; ///< Pointer to the tetradic diamond tuning
    shared_ptr<PentadicDiamond> _pentadicDiamond = nullptr; ///< Pointer to the pentadic diamond tuning
    shared_ptr<HexadicDiamond> _hexadicDiamond = nullptr; ///< Pointer to the hexadic diamond tuning
    shared_ptr<HeptadicDiamond> _heptadicDiamond = nullptr; ///< Pointer to the heptadic diamond tuning
    shared_ptr<OgdoadicDiamond> _ogdoadicDiamond = nullptr; ///< Pointer to the ogdoadic diamond tuning

    // private methods
    void _tuningChangedUpdateUI() override; ///< Sends notification to UI Component to query current ViewModel
    void _updateScales(); ///< Helper function to update scales
    void _arrowKeyPressedHelper(int x_delta, int y_delta); ///< Helper function for arrow key press
};

