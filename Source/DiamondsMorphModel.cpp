/*
  ==============================================================================

    DiamondsMorphModel.cpp
    Created: 17 Dec 2023 1:33:40pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "DiamondsMorphModel.h"
#include "DiamondsModel.h"

DiamondsMorphModel::DiamondsMorphModel()
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

DiamondsMorphModel::~DiamondsMorphModel() {
    
}

void DiamondsMorphModel::parameterChanged(const String& parameterID, float newValue) {
    if(parameterID == DiamondsModel::getDiamondsParameterID().getParamID()) {
        _selectedScaleIndex = static_cast<unsigned long>(newValue);
    } else if(parameterID == DiamondsModel::getDiamonds_A_ParameterID().getParamID()) {
        _A->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _A->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _A->setFrequencyValue(newValue);
    } else if(parameterID == DiamondsModel::getDiamonds_B_ParameterID().getParamID()) {
        _B->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _B->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _B->setFrequencyValue(newValue);
    } else if(parameterID == DiamondsModel::getDiamonds_C_ParameterID().getParamID()) {
        _C->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _C->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _C->setFrequencyValue(newValue);
    } else if(parameterID == DiamondsModel::getDiamonds_D_ParameterID().getParamID()) {
        _D->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _D->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _D->setFrequencyValue(newValue);
    } else if(parameterID == DiamondsModel::getDiamonds_E_ParameterID().getParamID()) {
        _E->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _E->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _E->setFrequencyValue(newValue);
    } else if(parameterID == DiamondsModel::getDiamonds_F_ParameterID().getParamID()) {
        _F->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _F->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _F->setFrequencyValue(newValue);
    } else if(parameterID == DiamondsModel::getDiamonds_G_ParameterID().getParamID()) {
        _G->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _G->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _G->setFrequencyValue(newValue);
    } else if(parameterID == DiamondsModel::getDiamonds_H_ParameterID().getParamID()) {
        _H->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _H->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _H->setFrequencyValue(newValue);
    } else if (parameterID == AppTuningModel::getAppTuningNoteNumberMiddleCParameterID().getParamID()) {
        _noteNumberMiddleC = static_cast<unsigned long>(newValue);
    } else if (parameterID == AppTuningModel::getAppTuningFrequencyMiddleCParameterID().getParamID()) {
        _frequencyMiddleC = newValue;
    } else if (parameterID == AppTuningModel::getAppTuningOctaveMiddleCParameterID().getParamID()) {
        _octaveMiddleC = static_cast<int>(newValue);
    } else if(parameterID == AppTuningModel::getAppTuningNPOOverrideParameterID().getParamID()) {
        _npoOverride = static_cast<int>(newValue);
    } else if(parameterID == AppTuningModel::getAppTuningNPOOverrideEnableParameterID().getParamID()) {
        _npoOverrideEnable = static_cast<bool>(newValue);
    } else {
        jassertfalse;
    }

    // update scales, _diamond
    _updateScales();
}

/**
 * @brief Updates the scales based on the selected scale index.
 *
 * This function updates the scales based on the selected scale index. It creates or updates the diamond objects
 * for each scale type (triadic, tetradic, pentadic, hexadic, heptadic, ogdoadic) and sets the number of seeds
 * accordingly. It also selects the appropriate subset based on the selected scale index.
 */
void DiamondsMorphModel::_updateScales()
{
    // Switch based on the selected scale index
    switch(_selectedScaleIndex)
    {
        // Triadic
        case 0:
        case 1: case 2:
        case 3: case 4:
        case 5: case 6:
            // If the triadic diamond doesn't exist, create it
            if(_triadicDiamond == nullptr) {
                _triadicDiamond = make_shared<TriadicDiamond>(_A, _B, _C);
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
            break;

        // Tetradic
        case 7:
        case 8: case 9:
        case 10: case 11:
        case 12: case 13:
        case 14: case 15:
            // If the tetradic diamond doesn't exist, create it
            if(_tetradicDiamond == nullptr) {
                _tetradicDiamond = make_shared<TetradicDiamond>(_A, _B, _C, _D);
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
                _hexadicDiamond = make_shared<HexadicDiamond>(_A, _B, _C, _D, _E, _F);
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
                _heptadicDiamond = make_shared<HeptadicDiamond>(_A, _B, _C, _D, _E, _F, _G); // Create a new HeptadicDiamond with the given parameters
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
                _ogdoadicDiamond = make_shared<OgdoadicDiamond>(_A, _B, _C, _D, _E, _F, _G, _H); // Create a new OgdoadicDiamond with the given parameters
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
    
    // update app tuning model params
    _diamond->setNoteNumberMiddleC(_noteNumberMiddleC);
    _diamond->setOctaveMiddleC(_octaveMiddleC);
    _diamond->setFrequencyMiddleC(_frequencyMiddleC);
    _diamond->setNPOOverride(_npoOverride);
    _diamond->setNPOOverrideEnable(_npoOverrideEnable);
}

shared_ptr<Tuning> DiamondsMorphModel::getTuning()
{
    return _diamond;
}
