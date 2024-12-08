/*
 ==============================================================================

 DiamondsModel.cpp
 Created: 6 Jun 2023 4:30:03pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "DiamondsModel.h"
#include "DesignsModel.h"

#pragma mark - static members

const StringArray DiamondsModel::__DAWKeys {
    "TRIADIC DIAMOND", // 0
    ">  Harmonic Triad 0",
    ">  Subharmonic Triad 0",
    ">  Harmonic Triad 1",
    ">  Subharmonic Triad 1",
    ">  Harmonic Triad 2",
    ">  Subharmonic Triad 2",
    "TETRADIC DIAMOND", // 7
    ">  Harmonic Tetrad 0",
    ">  Subharmonic Tetrad 0",
    ">  Harmonic Tetrad 1",
    ">  Subharmonic Tetrad 1",
    ">  Harmonic Tetrad 2",
    ">  Subharmonic Tetrad 2",
    ">  Harmonic Tetrad 3",
    ">  Subharmonic Tetrad 3",
    "PENTADIC DIAMOND", // 16
    ">  Harmonic Pentad 0",
    ">  Subharmonic Pentad 0",
    ">  Harmonic Pentad 1",
    ">  Subharmonic Pentad 1",
    ">  Harmonic Pentad 2",
    ">  Subharmonic Pentad 2",
    ">  Harmonic Pentad 3",
    ">  Subharmonic Pentad 3",
    ">  Harmonic Pentad 4",
    ">  Subharmonic Pentad 4",
    "HEXADIC DIAMOND", // 27
    ">  Harmonic Hexad 0",
    ">  Subharmonic Hexad 0",
    ">  Harmonic Hexad 1",
    ">  Subharmonic Hexad 1",
    ">  Harmonic Hexad 2",
    ">  Subharmonic Hexad 2",
    ">  Harmonic Hexad 3",
    ">  Subharmonic Hexad 3",
    ">  Harmonic Hexad 4",
    ">  Subharmonic Hexad 4",
    ">  Harmonic Hexad 5",
    ">  Subharmonic Hexad 5",
    "HEPTADIC DIAMOND", // 40
    ">  Harmonic Heptad 0",
    ">  Subharmonic Heptad 0",
    ">  Harmonic Heptad 1",
    ">  Subharmonic Heptad 1",
    ">  Harmonic Heptad 2",
    ">  Subharmonic Heptad 2",
    ">  Harmonic Heptad 3",
    ">  Subharmonic Heptad 3",
    ">  Harmonic Heptad 4",
    ">  Subharmonic Heptad 4",
    ">  Harmonic Heptad 5",
    ">  Subharmonic Heptad 5",
    ">  Harmonic Heptad 6",
    ">  Subharmonic Heptad 6",
    "OGDOADIC DIAMOND", // 55
    ">  Harmonic Ogdoad 0",
    ">  Subharmonic Ogdoad 0",
    ">  Harmonic Ogdoad 1",
    ">  Subharmonic Ogdoad 1",
    ">  Harmonic Ogdoad 2",
    ">  Subharmonic Ogdoad 2",
    ">  Harmonic Ogdoad 3",
    ">  Subharmonic Ogdoad 3",
    ">  Harmonic Ogdoad 4",
    ">  Subharmonic Ogdoad 4",
    ">  Harmonic Ogdoad 5",
    ">  Subharmonic Ogdoad 5",
    ">  Harmonic Ogdoad 6",
    ">  Subharmonic Ogdoad 6",
    ">  Harmonic Ogdoad 7",
    ">  Subharmonic Ogdoad 7"
};

#pragma mark - lifecycle

DiamondsModel::DiamondsModel()
: _A(CPS::A(1))
, _B(CPS::B(3))
, _C(CPS::C(5))
, _D(CPS::D(7))
, _E(CPS::E(9))
, _F(CPS::F(11))
, _G(CPS::G(13))
, _H(CPS::H(15))
{
    _selectedScaleIndex = 0;
    _updateScales(); // sets _numberOfSeeds, and scale
}

DiamondsModel::~DiamondsModel() {
    removeAllActionListeners();
    detachParameterListeners();
}

#pragma mark - processor processBlock

unique_ptr<AudioProcessorParameterGroup> DiamondsModel::createParams() {
    // Tuning Params
    auto scaleGroup = make_unique<AudioProcessorParameterGroup>(getGroupID(), getGroupName(), getSubgroupSeparator(),

                                                                // Scale (combo box)
                                                                make_unique<AudioParameterChoice>
                                                                (DiamondsModel::getDiamondsParameterID(),
                                                                 DiamondsModel::getDiamondsParameterName(),
                                                                 DiamondsModel::getScaleNames(),
                                                                 0)
                                                                ,

                                                                // A
                                                                make_unique<AudioParameterFloat>
                                                                (getDiamonds_A_ParameterID(),
                                                                 getDiamonds_A_ParameterName(),
                                                                 NormalisableRange<float> (rangeMin, rangeMax, rangeStep),
                                                                 _A->getFrequencyValue(),
                                                                 getDiamonds_A_ParameterName(),
                                                                 AudioProcessorParameter::genericParameter,
[](float value, int maxLength) { return String(value).substring(0, maxLength); },
[](const String& text) { return text.getFloatValue(); })
                                                                ,

                                                                // B
                                                                make_unique<AudioParameterFloat>
                                                                (getDiamonds_B_ParameterID(),
                                                                 getDiamonds_B_ParameterName(),
                                                                 NormalisableRange<float> (rangeMin, rangeMax, rangeStep),
                                                                 _B->getFrequencyValue(),
                                                                 getDiamonds_B_ParameterName(),
                                                                 AudioProcessorParameter::genericParameter,
[](float value, int maxLength) { return String(value).substring(0, maxLength); },
[](const String& text) { return text.getFloatValue(); })
                                                                ,

                                                                // C
                                                                make_unique<AudioParameterFloat>
                                                                (getDiamonds_C_ParameterID(),
                                                                 getDiamonds_C_ParameterName(),
                                                                 NormalisableRange<float> (rangeMin, rangeMax, rangeStep),
                                                                 _C->getFrequencyValue(),
                                                                 getDiamonds_C_ParameterName(),
                                                                 AudioProcessorParameter::genericParameter,
[](float value, int maxLength) { return String(value).substring(0, maxLength); },
[](const String& text) { return text.getFloatValue(); })
                                                                ,

                                                                // D
                                                                make_unique<AudioParameterFloat>
                                                                (getDiamonds_D_ParameterID(),
                                                                 getDiamonds_D_ParameterName(),
                                                                 NormalisableRange<float> (rangeMin, rangeMax, rangeStep),
                                                                 _D->getFrequencyValue(),
                                                                 getDiamonds_D_ParameterName(),
                                                                 AudioProcessorParameter::genericParameter,
[](float value, int maxLength) { return String(value).substring(0, maxLength); },
[](const String& text) { return text.getFloatValue(); })
                                                                ,

                                                                // E
                                                                make_unique<AudioParameterFloat>
                                                                (getDiamonds_E_ParameterID(),
                                                                 getDiamonds_E_ParameterName(),
                                                                 NormalisableRange<float> (rangeMin, rangeMax, rangeStep),
                                                                 _E->getFrequencyValue(),
                                                                 getDiamonds_E_ParameterName(),
                                                                 AudioProcessorParameter::genericParameter,
[](float value, int maxLength) { return String(value).substring(0, maxLength); },
[](const String& text) { return text.getFloatValue(); })
                                                                ,

                                                                // F
                                                                make_unique<AudioParameterFloat>
                                                                (getDiamonds_F_ParameterID(),
                                                                 getDiamonds_F_ParameterName(),
                                                                 NormalisableRange<float> (rangeMin, rangeMax, rangeStep),
                                                                 _F->getFrequencyValue(),
                                                                 getDiamonds_F_ParameterName(),
                                                                 AudioProcessorParameter::genericParameter,
[](float value, int maxLength) { return String(value).substring(0, maxLength); },
[](const String& text) { return text.getFloatValue(); })
                                                                ,

                                                                // G
                                                                make_unique<AudioParameterFloat>
                                                                (getDiamonds_G_ParameterID(),
                                                                 getDiamonds_G_ParameterName(),
                                                                 NormalisableRange<float> (rangeMin, rangeMax, rangeStep),
                                                                 _G->getFrequencyValue(),
                                                                 getDiamonds_G_ParameterName(),
                                                                 AudioProcessorParameter::genericParameter,
[](float value, int maxLength) { return String(value).substring(0, maxLength); },
[](const String& text) { return text.getFloatValue(); })
                                                                ,

                                                                // H
                                                                make_unique<AudioParameterFloat>
                                                                (getDiamonds_H_ParameterID(),
                                                                 getDiamonds_H_ParameterName(),
                                                                 NormalisableRange<float> (rangeMin, rangeMax, rangeStep),
                                                                 _H->getFrequencyValue(),
                                                                 getDiamonds_H_ParameterName(),
                                                                 AudioProcessorParameter::genericParameter,
[](float value, int maxLength) { return String(value).substring(0, maxLength); },
[](const String& text) { return text.getFloatValue(); })
                                                                );

    return scaleGroup;
}

String DiamondsModel::getGroupID() {
    return "Diamonds";
}

String DiamondsModel::getGroupName() {
    return "Diamonds";
}

String DiamondsModel::getSubgroupSeparator() {
    return "|";
}

// key for this design's Favorites array
ParameterID DiamondsModel::getDesignParameterID() {
    return ParameterID ("DIAMONDS_PARAMETERID_DESIGNS", AppVersion::getVersionHint());
}

StringArray DiamondsModel::getFavoritesParameterIDs() {
    return StringArray
    (
     getDiamondsParameterID().getParamID(),
     getDiamonds_A_ParameterID().getParamID(),
     getDiamonds_B_ParameterID().getParamID(),
     getDiamonds_C_ParameterID().getParamID(),
     getDiamonds_D_ParameterID().getParamID(),
     getDiamonds_E_ParameterID().getParamID(),
     getDiamonds_F_ParameterID().getParamID(),
     getDiamonds_G_ParameterID().getParamID(),
     getDiamonds_H_ParameterID().getParamID()
     );
}

// called only once: after assigning _avpts
void DiamondsModel::attachParameterListeners() {
    jassert(_apvts != nullptr);
    for(auto pid : getFavoritesParameterIDs()) {
        _apvts->addParameterListener(pid, this);
    }
}

void DiamondsModel::detachParameterListeners() {
    jassert(_apvts != nullptr);
    for(auto pid : getFavoritesParameterIDs()) {
        _apvts->removeParameterListener(pid, this);
    }
}

// DAW callback when apvts changes
void DiamondsModel::parameterChanged(const String& parameterID, float newValue) {
    const ScopedLock sl(_lock);
    if(parameterID == getDiamondsParameterID().getParamID()) {
        _selectedScaleIndex = static_cast<unsigned long>(newValue);
    } else if(parameterID == getDiamonds_A_ParameterID().getParamID()) {
        _A->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _A->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _A->setFrequencyValue(newValue);
    } else if(parameterID == getDiamonds_B_ParameterID().getParamID()) {
        _B->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _B->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _B->setFrequencyValue(newValue);
    } else if(parameterID == getDiamonds_C_ParameterID().getParamID()) {
        _C->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _C->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _C->setFrequencyValue(newValue);
    } else if(parameterID == getDiamonds_D_ParameterID().getParamID()) {
        _D->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _D->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _D->setFrequencyValue(newValue);
    } else if(parameterID == getDiamonds_E_ParameterID().getParamID()) {
        _E->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _E->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _E->setFrequencyValue(newValue);
    } else if(parameterID == getDiamonds_F_ParameterID().getParamID()) {
        _F->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _F->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _F->setFrequencyValue(newValue);
    } else if(parameterID == getDiamonds_G_ParameterID().getParamID()) {
        _G->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _G->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _G->setFrequencyValue(newValue);
    } else if(parameterID == getDiamonds_H_ParameterID().getParamID()) {
        _H->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _H->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _H->setFrequencyValue(newValue);
    } else {
        jassertfalse;
    }

    _updateScales(); // update scales, sets _numberOfSeeds, and _diamond
}

void DiamondsModel::updateProperties() {
}

/**
 * @brief Updates the scales based on the selected scale index.
 * 
 * This function updates the scales based on the selected scale index. It creates or updates the diamond objects
 * for each scale type (triadic, tetradic, pentadic, hexadic, heptadic, ogdoadic) and sets the number of seeds
 * accordingly. It also selects the appropriate subset based on the selected scale index.
 
 * note that instead of adding a "tuning updated" completion block to call uiNeedsUpdate() we just
 * simply call uiNeedsUpdate() at the end of _updateScales()
 */
void DiamondsModel::_updateScales() {
    const ScopedLock sl(_lock); // Lock to prevent concurrent access

    // Switch based on the selected scale index
    switch(_selectedScaleIndex) {
        // Triadic
        case 0:
        case 1: case 2:
        case 3: case 4:
        case 5: case 6:
            // If the triadic diamond doesn't exist, create it
            if(_triadicDiamond == nullptr) {
                _triadicDiamond = make_shared<TriadicDiamond> (_A, _B, _C);
                _triadicDiamond->setShouldComputeSubsets(true);
                _triadicDiamond->update();
                _triadicDiamond->setDAWKey(String(0));
                _triadicDiamond->getSubsets0()[0]->setDAWKey(String(1));
                _triadicDiamond->getSubsets1()[0]->setDAWKey(String(2));
                _triadicDiamond->getSubsets0()[1]->setDAWKey(String(3));
                _triadicDiamond->getSubsets1()[1]->setDAWKey(String(4));
                _triadicDiamond->getSubsets0()[2]->setDAWKey(String(5));
                _triadicDiamond->getSubsets1()[2]->setDAWKey(String(6));
            } else {
                // If it exists, update the ABC values
                _triadicDiamond->setABC(_A, _B, _C);
            }
            _parent = _triadicDiamond;
            _numberOfSeeds = 3;
            break;

        // Tetradic
        case 7:
        case 8: case 9:
        case 10: case 11:
        case 12: case 13:
        case 14: case 15:
            // If the tetradic diamond doesn't exist, create it
            if(_tetradicDiamond == nullptr) {
                _tetradicDiamond = make_shared<TetradicDiamond> (_A, _B, _C, _D);
                _tetradicDiamond->setShouldComputeSubsets(true);
                _tetradicDiamond->update();
                _tetradicDiamond->setDAWKey(String(7));
                _tetradicDiamond->getSubsets0()[0]->setDAWKey(String(8));
                _tetradicDiamond->getSubsets1()[0]->setDAWKey(String(9));
                _tetradicDiamond->getSubsets0()[1]->setDAWKey(String(10));
                _tetradicDiamond->getSubsets1()[1]->setDAWKey(String(11));
                _tetradicDiamond->getSubsets0()[2]->setDAWKey(String(12));
                _tetradicDiamond->getSubsets1()[2]->setDAWKey(String(13));
                _tetradicDiamond->getSubsets0()[3]->setDAWKey(String(14));
                _tetradicDiamond->getSubsets1()[3]->setDAWKey(String(15));
            } else {
                // If it exists, update the ABCD values
                _tetradicDiamond->setABCD(_A, _B, _C, _D);
            }
            _parent = _tetradicDiamond;
            _numberOfSeeds = 4;
            break;

        // Pentadic
        case 16:
        case 17: case 18:
        case 19: case 20:
        case 21: case 22:
        case 23: case 24:
        case 25: case 26:
            // If the pentadic diamond doesn't exist, create it
            if(_pentadicDiamond == nullptr) {
                _pentadicDiamond = make_shared<PentadicDiamond>(_A, _B, _C, _D, _E);
                _pentadicDiamond->setShouldComputeSubsets(true);
                _pentadicDiamond->update();
                _pentadicDiamond->setDAWKey(String(16));
                _pentadicDiamond->getSubsets0()[0]->setDAWKey(String(17));
                _pentadicDiamond->getSubsets1()[0]->setDAWKey(String(18));
                _pentadicDiamond->getSubsets0()[1]->setDAWKey(String(19));
                _pentadicDiamond->getSubsets1()[1]->setDAWKey(String(20));
                _pentadicDiamond->getSubsets0()[2]->setDAWKey(String(21));
                _pentadicDiamond->getSubsets1()[2]->setDAWKey(String(22));
                _pentadicDiamond->getSubsets0()[3]->setDAWKey(String(23));
                _pentadicDiamond->getSubsets1()[3]->setDAWKey(String(24));
                _pentadicDiamond->getSubsets0()[4]->setDAWKey(String(25));
                _pentadicDiamond->getSubsets1()[4]->setDAWKey(String(26));
            } else {
                // If it exists, update the ABCDE values
                _pentadicDiamond->setABCDE(_A, _B, _C, _D, _E);
            }
            _parent = _pentadicDiamond;
            _numberOfSeeds = 5;
            break;

        // Hexadic
        case 27:
        case 28: case 29:
        case 30: case 31:
        case 32: case 33:
        case 34: case 35:
        case 36: case 37:
        case 38: case 39:
            // If the hexadic diamond doesn't exist, create it
            if(_hexadicDiamond == nullptr) {
                _hexadicDiamond = make_shared<HexadicDiamond> (_A, _B, _C, _D, _E, _F);
                _hexadicDiamond->setShouldComputeSubsets(true);
                _hexadicDiamond->update();
                _hexadicDiamond->setDAWKey(String(27));
                _hexadicDiamond->getSubsets0()[0]->setDAWKey(String(28));
                _hexadicDiamond->getSubsets1()[0]->setDAWKey(String(29));
                _hexadicDiamond->getSubsets0()[1]->setDAWKey(String(30));
                _hexadicDiamond->getSubsets1()[1]->setDAWKey(String(31));
                _hexadicDiamond->getSubsets0()[2]->setDAWKey(String(32));
                _hexadicDiamond->getSubsets1()[2]->setDAWKey(String(33));
                _hexadicDiamond->getSubsets0()[3]->setDAWKey(String(34));
                _hexadicDiamond->getSubsets1()[3]->setDAWKey(String(35));
                _hexadicDiamond->getSubsets0()[4]->setDAWKey(String(36));
                _hexadicDiamond->getSubsets1()[4]->setDAWKey(String(37));
                _hexadicDiamond->getSubsets0()[5]->setDAWKey(String(38));
                _hexadicDiamond->getSubsets1()[5]->setDAWKey(String(39));
            } else {
                // If it exists, update the ABCDEF values
                _hexadicDiamond->setABCDEF(_A, _B, _C, _D, _E, _F);
            }
            _parent = _hexadicDiamond;
            _numberOfSeeds = 6;
            break;

        // Heptadic
        case 40:
        case 41: case 42:
        case 43: case 44:
        case 45: case 46:
        case 47: case 48:
        case 49: case 50:
        case 51: case 52:
        case 53: case 54:
            /** 
             * If the heptadic diamond doesn't exist, create it
             * and set its properties.
             */
            if(_heptadicDiamond == nullptr) {
                _heptadicDiamond = make_shared<HeptadicDiamond> (_A, _B, _C, _D, _E, _F, _G); // Create a new HeptadicDiamond with the given parameters
                _heptadicDiamond->setShouldComputeSubsets(true); // Set the diamond to compute subsets
                _heptadicDiamond->update(); // Update the diamond
                _heptadicDiamond->setDAWKey(String(40)); // Set the DAW key for the diamond
                // Set the DAW keys for the subsets of the diamond
                _heptadicDiamond->getSubsets0()[0]->setDAWKey(String(41));
                _heptadicDiamond->getSubsets1()[0]->setDAWKey(String(42));
                _heptadicDiamond->getSubsets0()[1]->setDAWKey(String(43));
                _heptadicDiamond->getSubsets1()[1]->setDAWKey(String(44));
                _heptadicDiamond->getSubsets0()[2]->setDAWKey(String(45));
                _heptadicDiamond->getSubsets1()[2]->setDAWKey(String(46));
                _heptadicDiamond->getSubsets0()[3]->setDAWKey(String(47));
                _heptadicDiamond->getSubsets1()[3]->setDAWKey(String(48));
                _heptadicDiamond->getSubsets0()[4]->setDAWKey(String(49));
                _heptadicDiamond->getSubsets1()[4]->setDAWKey(String(50));
                _heptadicDiamond->getSubsets0()[5]->setDAWKey(String(51));
                _heptadicDiamond->getSubsets1()[5]->setDAWKey(String(52));
                _heptadicDiamond->getSubsets0()[6]->setDAWKey(String(53));
                _heptadicDiamond->getSubsets1()[6]->setDAWKey(String(54));
            } else {
                // If the heptadic diamond already exists, just update its parameters
                _heptadicDiamond->setABCDEFG(_A, _B, _C, _D, _E, _F, _G);
            }
            _parent = _heptadicDiamond; // Set the parent diamond
            _numberOfSeeds = 7; // Set the number of seeds
            break;

            /** 
             * If the ogdoadic diamond doesn't exist, create it
             * and set its properties.
             */
        case 55:
        case 56: case 57:
        case 58: case 59:
        case 60: case 61:
        case 62: case 63:
        case 64: case 65:
        case 66: case 67:
        case 68: case 69:
        case 70: case 71:
            if(_ogdoadicDiamond == nullptr) {
                _ogdoadicDiamond = make_shared<OgdoadicDiamond> (_A, _B, _C, _D, _E, _F, _G, _H); // Create a new OgdoadicDiamond with the given parameters
                _ogdoadicDiamond->setShouldComputeSubsets(true); // Set the diamond to compute subsets
                _ogdoadicDiamond->update(); // Update the diamond
                _ogdoadicDiamond->setDAWKey(String(55)); // Set the DAW key for the diamond
                // Set the DAW keys for the subsets of the diamond
                _ogdoadicDiamond->getSubsets0()[0]->setDAWKey(String(56));
                _ogdoadicDiamond->getSubsets1()[0]->setDAWKey(String(57));
                _ogdoadicDiamond->getSubsets0()[1]->setDAWKey(String(58));
                _ogdoadicDiamond->getSubsets1()[1]->setDAWKey(String(59));
                _ogdoadicDiamond->getSubsets0()[2]->setDAWKey(String(60));
                _ogdoadicDiamond->getSubsets1()[2]->setDAWKey(String(61));
                _ogdoadicDiamond->getSubsets0()[3]->setDAWKey(String(62));
                _ogdoadicDiamond->getSubsets1()[3]->setDAWKey(String(63));
                _ogdoadicDiamond->getSubsets0()[4]->setDAWKey(String(64));
                _ogdoadicDiamond->getSubsets1()[4]->setDAWKey(String(65));
                _ogdoadicDiamond->getSubsets0()[5]->setDAWKey(String(66));
                _ogdoadicDiamond->getSubsets1()[5]->setDAWKey(String(67));
                _ogdoadicDiamond->getSubsets0()[6]->setDAWKey(String(68));
                _ogdoadicDiamond->getSubsets1()[6]->setDAWKey(String(69));
                _ogdoadicDiamond->getSubsets0()[7]->setDAWKey(String(70));
                _ogdoadicDiamond->getSubsets1()[7]->setDAWKey(String(71));
            } else {
                // If the ogdoadic diamond already exists, just update its parameters
                _ogdoadicDiamond->setABCDEFGH(_A, _B, _C, _D, _E, _F, _G, _H);
            }
            _parent = _ogdoadicDiamond; // Set the parent diamond
            _numberOfSeeds = 8; // Set the number of seeds
            break;
        default:
            jassertfalse;
            break;
    }

    switch(_selectedScaleIndex)
    {
            // Triadic
        case 0:
            _triadicDiamond->selectParent();
            _diamond = _triadicDiamond;
            break;
        case 1:
            _triadicDiamond->selectS0_0();
            _diamond = _triadicDiamond->getSelectedSubset();
            break;
        case 2:
            _triadicDiamond->selectS1_0();
            _diamond = _triadicDiamond->getSelectedSubset();
            break;
        case 3:
            _triadicDiamond->selectS0_1();
            _diamond = _triadicDiamond->getSelectedSubset();
            break;
        case 4:
            _triadicDiamond->selectS1_1();
            _diamond = _triadicDiamond->getSelectedSubset();
            break;
        case 5:
            _triadicDiamond->selectS0_2();
            _diamond = _triadicDiamond->getSelectedSubset();
            break;
        case 6:
            _triadicDiamond->selectS1_2();
            _diamond = _triadicDiamond->getSelectedSubset();
            break;

            // Tetradic
        case 7:
            _tetradicDiamond->selectParent();
            _diamond = _tetradicDiamond;
            break;
        case 8:
            _tetradicDiamond->selectS0_0();
            _diamond = _tetradicDiamond->getSelectedSubset();
            break;
        case 9:
            _tetradicDiamond->selectS1_0();
            _diamond = _tetradicDiamond->getSelectedSubset();
            break;
        case 10:
            _tetradicDiamond->selectS0_1();
            _diamond = _tetradicDiamond->getSelectedSubset();
            break;
        case 11:
            _tetradicDiamond->selectS1_1();
            _diamond = _tetradicDiamond->getSelectedSubset();
            break;
        case 12:
            _tetradicDiamond->selectS0_2();
            _diamond = _tetradicDiamond->getSelectedSubset();
            break;
        case 13:
            _tetradicDiamond->selectS1_2();
            _diamond = _tetradicDiamond->getSelectedSubset();
            break;
        case 14:
            _tetradicDiamond->selectS0_3();
            _diamond = _tetradicDiamond->getSelectedSubset();
            break;
        case 15:
            _tetradicDiamond->selectS1_3();
            _diamond = _tetradicDiamond->getSelectedSubset();
            break;

            // Pentadic
        case 16:
            _pentadicDiamond->selectParent();
            _diamond = _pentadicDiamond;
            break;
        case 17:
            _pentadicDiamond->selectS0_0();
            _diamond = _pentadicDiamond->getSelectedSubset();
            break;
        case 18:
            _pentadicDiamond->selectS1_0();
            _diamond = _pentadicDiamond->getSelectedSubset();
            break;
        case 19:
            _pentadicDiamond->selectS0_1();
            _diamond = _pentadicDiamond->getSelectedSubset();
            break;
        case 20:
            _pentadicDiamond->selectS1_1();
            _diamond = _pentadicDiamond->getSelectedSubset();
            break;
        case 21:
            _pentadicDiamond->selectS0_2();
            _diamond = _pentadicDiamond->getSelectedSubset();
            break;
        case 22:
            _pentadicDiamond->selectS1_2();
            _diamond = _pentadicDiamond->getSelectedSubset();
            break;
        case 23:
            _pentadicDiamond->selectS0_3();
            _diamond = _pentadicDiamond->getSelectedSubset();
            break;
        case 24:
            _pentadicDiamond->selectS1_3();
            _diamond = _pentadicDiamond->getSelectedSubset();
            break;
        case 25:
            _pentadicDiamond->selectS0_4();
            _diamond = _pentadicDiamond->getSelectedSubset();
            break;
        case 26:
            _pentadicDiamond->selectS1_4();
            _diamond = _pentadicDiamond->getSelectedSubset();
            break;

            // Hexadic
        case 27:
            _hexadicDiamond->selectParent();
            _diamond = _hexadicDiamond;
            break;
        case 28:
            _hexadicDiamond->selectS0_0();
            _diamond = _hexadicDiamond->getSelectedSubset();
            break;
        case 29:
            _hexadicDiamond->selectS1_0();
            _diamond = _hexadicDiamond->getSelectedSubset();
            break;
        case 30:
            _hexadicDiamond->selectS0_1();
            _diamond = _hexadicDiamond->getSelectedSubset();
            break;
        case 31:
            _hexadicDiamond->selectS1_1();
            _diamond = _hexadicDiamond->getSelectedSubset();
            break;
        case 32:
            _hexadicDiamond->selectS0_2();
            _diamond = _hexadicDiamond->getSelectedSubset();
            break;
        case 33:
            _hexadicDiamond->selectS1_2();
            _diamond = _hexadicDiamond->getSelectedSubset();
            break;
        case 34:
            _hexadicDiamond->selectS0_3();
            _diamond = _hexadicDiamond->getSelectedSubset();
            break;
        case 35:
            _hexadicDiamond->selectS1_3();
            _diamond = _hexadicDiamond->getSelectedSubset();
            break;
        case 36:
            _hexadicDiamond->selectS0_4();
            _diamond = _hexadicDiamond->getSelectedSubset();
            break;
        case 37:
            _hexadicDiamond->selectS1_4();
            _diamond = _hexadicDiamond->getSelectedSubset();
            break;
        case 38:
            _hexadicDiamond->selectS0_5();
            _diamond = _hexadicDiamond->getSelectedSubset();
            break;
        case 39:
            _hexadicDiamond->selectS1_5();
            _diamond = _hexadicDiamond->getSelectedSubset();
            break;

            // Heptadic
        case 40:
            _heptadicDiamond->selectParent();
            _diamond = _heptadicDiamond;
            break;
        case 41:
            _heptadicDiamond->selectS0_0();
            _diamond = _heptadicDiamond->getSelectedSubset();
            break;
        case 42:
            _heptadicDiamond->selectS1_0();
            _diamond = _heptadicDiamond->getSelectedSubset();
            break;
        case 43:
            _heptadicDiamond->selectS0_1();
            _diamond = _heptadicDiamond->getSelectedSubset();
            break;
        case 44:
            _heptadicDiamond->selectS1_1();
            _diamond = _heptadicDiamond->getSelectedSubset();
            break;
        case 45:
            _heptadicDiamond->selectS0_2();
            _diamond = _heptadicDiamond->getSelectedSubset();
            break;
        case 46:
            _heptadicDiamond->selectS1_2();
            _diamond = _heptadicDiamond->getSelectedSubset();
            break;
        case 47:
            _heptadicDiamond->selectS0_3();
            _diamond = _heptadicDiamond->getSelectedSubset();
            break;
        case 48:
            _heptadicDiamond->selectS1_3();
            _diamond = _heptadicDiamond->getSelectedSubset();
            break;
        case 49:
            _heptadicDiamond->selectS0_4();
            _diamond = _heptadicDiamond->getSelectedSubset();
            break;
        case 50:
            _heptadicDiamond->selectS1_4();
            _diamond = _heptadicDiamond->getSelectedSubset();
            break;
        case 51:
            _heptadicDiamond->selectS0_5();
            _diamond = _heptadicDiamond->getSelectedSubset();
            break;
        case 52:
            _heptadicDiamond->selectS1_5();
            _diamond = _heptadicDiamond->getSelectedSubset();
            break;
        case 53:
            _heptadicDiamond->selectS0_6();
            _diamond = _heptadicDiamond->getSelectedSubset();
            break;
        case 54:
            _heptadicDiamond->selectS1_6();
            _diamond = _heptadicDiamond->getSelectedSubset();
            break;

            // Ogdoadic
        case 55:
            _ogdoadicDiamond->selectParent();
            _diamond = _ogdoadicDiamond;
            break;
        case 56:
            _ogdoadicDiamond->selectS0_0();
            _diamond = _ogdoadicDiamond->getSelectedSubset();
            break;
        case 57:
            _ogdoadicDiamond->selectS1_0();
            _diamond = _ogdoadicDiamond->getSelectedSubset();
            break;
        case 58:
            _ogdoadicDiamond->selectS0_1();
            _diamond = _ogdoadicDiamond->getSelectedSubset();
            break;
        case 59:
            _ogdoadicDiamond->selectS1_1();
            _diamond = _ogdoadicDiamond->getSelectedSubset();
            break;
        case 60:
            _ogdoadicDiamond->selectS0_2();
            _diamond = _ogdoadicDiamond->getSelectedSubset();
            break;
        case 61:
            _ogdoadicDiamond->selectS1_2();
            _diamond = _ogdoadicDiamond->getSelectedSubset();
            break;
        case 62:
            _ogdoadicDiamond->selectS0_3();
            _diamond = _ogdoadicDiamond->getSelectedSubset();
            break;
        case 63:
            _ogdoadicDiamond->selectS1_3();
            _diamond = _ogdoadicDiamond->getSelectedSubset();
            break;
        case 64:
            _ogdoadicDiamond->selectS0_4();
            _diamond = _ogdoadicDiamond->getSelectedSubset();
            break;
        case 65:
            _ogdoadicDiamond->selectS1_4();
            _diamond = _ogdoadicDiamond->getSelectedSubset();
            break;
        case 66:
            _ogdoadicDiamond->selectS0_5();
            _diamond = _ogdoadicDiamond->getSelectedSubset();
            break;
        case 67:
            _ogdoadicDiamond->selectS1_5();
            _diamond = _ogdoadicDiamond->getSelectedSubset();
            break;
        case 68:
            _ogdoadicDiamond->selectS0_6();
            _diamond = _ogdoadicDiamond->getSelectedSubset();
            break;
        case 69:
            _ogdoadicDiamond->selectS1_6();
            _diamond = _ogdoadicDiamond->getSelectedSubset();
            break;
        case 70:
            _ogdoadicDiamond->selectS0_7();
            _diamond = _ogdoadicDiamond->getSelectedSubset();
            break;
        case 71:
            _ogdoadicDiamond->selectS1_7();
            _diamond = _ogdoadicDiamond->getSelectedSubset();
            break;

        default:
            jassertfalse;
            break;
    }
    
    //
    uiNeedsUpdate();
}

#pragma mark - public methods

void DiamondsModel::uiSelectScale(unsigned long value)
{
    auto key = getDiamondsParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(value);
    param->setValueNotifyingHost(value01);
}

void DiamondsModel::uiSetA(float value)
{
    auto key = getDiamonds_A_ParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(value);
    param->setValueNotifyingHost(value01);
}

void DiamondsModel::uiSetB(float value)
{
    auto key = getDiamonds_B_ParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(value);
    param->setValueNotifyingHost(value01);
}

void DiamondsModel::uiSetC(float value)
{
    auto key = getDiamonds_C_ParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(value);
    param->setValueNotifyingHost(value01);
}

void DiamondsModel::uiSetD(float value)
{
    auto key = getDiamonds_D_ParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(value);
    param->setValueNotifyingHost(value01);
}

void DiamondsModel::uiSetE(float value)
{
    auto key = getDiamonds_E_ParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(value);
    param->setValueNotifyingHost(value01);
}

void DiamondsModel::uiSetF(float value)
{
    auto key = getDiamonds_F_ParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(value);
    param->setValueNotifyingHost(value01);
}

void DiamondsModel::uiSetG(float value)
{
    auto key = getDiamonds_G_ParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(value);
    param->setValueNotifyingHost(value01);
} 

void DiamondsModel::uiSetH(float value)
{
    auto key = getDiamonds_H_ParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(value);
    param->setValueNotifyingHost(value01);
}

unsigned long DiamondsModel::uiGetSelectedScaleIndex()
{
    auto& param = *_apvts->getRawParameterValue(getDiamondsParameterID().getParamID());
    return static_cast<unsigned long>(param.load());
}

float DiamondsModel::uiGetA()
{
    auto& param = *_apvts->getRawParameterValue(getDiamonds_A_ParameterID().getParamID());
    return param.load();
}

float DiamondsModel::uiGetB()
{
    auto& param = *_apvts->getRawParameterValue(getDiamonds_B_ParameterID().getParamID());
    return param.load();
}

float DiamondsModel::uiGetC()
{
    auto& param = *_apvts->getRawParameterValue(getDiamonds_C_ParameterID().getParamID());
    return param.load();
}

float DiamondsModel::uiGetD()
{
    auto& param = *_apvts->getRawParameterValue(getDiamonds_D_ParameterID().getParamID());
    return param.load();
}

float DiamondsModel::uiGetE()
{
    auto& param = *_apvts->getRawParameterValue(getDiamonds_E_ParameterID().getParamID());
    return param.load();
}

float DiamondsModel::uiGetF()
{
    auto& param = *_apvts->getRawParameterValue(getDiamonds_F_ParameterID().getParamID());
    return param.load();
}

float DiamondsModel::uiGetG()
{
    auto& param = *_apvts->getRawParameterValue(getDiamonds_G_ParameterID().getParamID());
    return param.load();
}

float DiamondsModel::uiGetH()
{
    auto& param = *_apvts->getRawParameterValue(getDiamonds_H_ParameterID().getParamID());
    return param.load();
}

shared_ptr<Tuning> DiamondsModel::getTuning()
{
    return _diamond;
}

const shared_ptr<CPSTuningBase> DiamondsModel::getParentTuning()
{
    return _parent;
}

unsigned long DiamondsModel::getNumScales()
{
    return static_cast<unsigned long>(__DAWKeys.size());
}

const StringArray DiamondsModel::getScaleNames()
{
    return __DAWKeys;
}

unsigned long DiamondsModel::getNumberOfSeeds()
{
    return _numberOfSeeds;
}

#pragma mark - update Designs model

void DiamondsModel::_tuningChangedUpdateUI() {
    sendActionMessage(DesignsModel::getDiamondsTuningChangedActionMessage());
}

/**
 * @brief Handles the event of the left arrow key being pressed.
 * @details Calls the helper function _arrowKeyPressedHelper with parameters indicating a leftward movement.
 */
void DiamondsModel::uiLeftArrowKeyPressed()
{
    _arrowKeyPressedHelper (-1, 0); // -1 in x direction, 0 in y direction
}

/**
 * @brief Handles the event of the right arrow key being pressed.
 * @details Calls the helper function _arrowKeyPressedHelper with parameters indicating a rightward movement.
 */
void DiamondsModel::uiRightArrowKeyPressed()
{
    _arrowKeyPressedHelper (+1, 0); // +1 in x direction, 0 in y direction
}

/**
 * @brief Handles the event of the up arrow key being pressed.
 * @details Calls the helper function _arrowKeyPressedHelper with parameters indicating an upward movement.
 */
void DiamondsModel::uiUpArrowKeyPressed()
{
    _arrowKeyPressedHelper(0, +1); // 0 in x direction, +1 in y direction
}

/**
 * @brief Handles the event of the down arrow key being pressed.
 * @details Calls the helper function _arrowKeyPressedHelper with parameters indicating a downward movement.
 */
void DiamondsModel::uiDownArrowKeyPressed()
{
    _arrowKeyPressedHelper(0, -1); // 0 in x direction, -1 in y direction
}

/**
 * @brief Helper function for handling arrow key press events.
 * @details This function takes in the x and y deltas(change in position) and performs the necessary operations to handle the key press event.
 * @param x_delta The change in x position.
 * @param y_delta The change in y position.
 */
void DiamondsModel::_arrowKeyPressedHelper(int x_delta, int y_delta)
{
    // Ensure that the deltas are valid(only one direction of movement is allowed at a time)
    jassert(abs(x_delta) + abs(y_delta) == 1); // (-1,0), (1,0), (0,-1), (0,1)
    // Ensure that the selected scale index is within the valid range
    jassert(_selectedScaleIndex < static_cast<unsigned long>(__DAWKeys.size()));
    // Ensure that the size of the DAWKeys array is as expected
    jassert(__DAWKeys.size() == 72);

    const ScopedLock sl(_lock); // Lock for thread safety

    // Determine the direction of movement based on the deltas
    int move = 0;
    if(x_delta == -1)
        move = 0; // left
    else if(x_delta == 1)
        move = 1; // right
    else if(y_delta == -1)
        move = 2; // down
    else if(y_delta == 1)
        move = 3; // up
    else
        jassertfalse; // Invalid deltas

    // Transition table for determining the new scale index based on the current index and direction of movement
    unsigned long transitions[72][4] = {
        // triadic
        //case 0:
        {0, 1, 0, 0},
        //case 1: case 2:
        {2,2,3,5}, {1,1,4,6},
        //case 3: case 4:
        {4,4,5,1}, {3,3,6,2},
        //case 5: case 6:
        {6,6,1,3}, {5,5,2,4},

        //tetradic
        //case 7:
        {7,8,7,7},
        //case 8:      case 9:
        {9,9,10,14},   {8,8,11,15},
        //case 10:     case 11:
        {11,11,12,8},  {10,10,13,9},
        //case 12:     case 13:
        {13,13,14,10}, {12,12,15,11},
        //case 14:     case 15:
        {15,15,8,12},  {14,14,9,13},

        // pentadic
        //case 16:
        {16,17,16,16},
        //case 17:     case 18:
        {18,18,19,25}, {17,17,20,26},
        //case 19:     case 20:
        {20,20,21,17}, {19,19,22,18},
        //case 21:     case 22:
        {22,22,23,19}, {21,21,24,20},
        //case 23:     case 24:
        {24,24,25,21}, {23,23,26,22},
        //case 25:     case 26:
        {26,26,17,23}, {25,25,18,24},

        // Hexadic
        //case 27:
        {27,28,27,27},
        //case 28:     case 29:
        {29,29,30,38}, {28,28,31,39},
        //case 30:     case 31:
        {31,31,32,28}, {30,30,33,29},
        //case 32:     case 33:
        {33,33,34,30}, {32,32,35,31},
        //case 34:     case 35:
        {35,35,36,32}, {34,34,37,33},
        //case 36:     case 37:
        {37,37,38,34}, {36,36,39,35},
        //case 38:     case 39:
        {39,39,28,36}, {38,38,29,37},

        // Heptadic
        //case 40:
        {40,41,40,40},
        //case 41:     case 42:
        {42,42,43,53}, {41,41,44,54},
        //case 43:     case 44:
        {44,44,45,41}, {43,43,46,42},
        //case 45:     case 46:
        {46,46,47,43}, {45,45,48,44},
        //case 47:     case 48:
        {48,48,49,45}, {47,47,50,46},
        //case 49:     case 50:
        {50,50,51,47}, {49,49,52,48},
        //case 51:     case 52:
        {52,52,53,49}, {51,51,54,50},
        //case 53:     case 54:
        {54,54,41,51}, {53,53,42,52},

        // Ogdoadic
        //case 55:
        {55,56,55,55},
        //case 56:     case 57:
        {57,57,58,70}, {56,56,59,71},
        //case 58:     case 59:
        {59,59,60,56}, {58,58,61,57},
        //case 60:     case 61:
        {61,61,62,58}, {60,60,63,59},
        //case 62:     case 63:
        {63,63,64,60}, {62,62,65,61},
        //case 64:     case 65:
        {65,65,66,62}, {64,64,67,63},
        //case 66:     case 67:
        {67,67,68,64}, {66,66,69,65},
        //case 68:     case 69:
        {69,69,70,66}, {68,68,71,67},
        //case 70:     case 71:
        {71,71,56,68}, {70,70,57,69}
    };

    // Determine the new scale index based on the current index and direction of movement
    auto const new_index = transitions[_selectedScaleIndex][move];
    uiSelectScale(new_index); // Select the new scale
}
