/*
  ==============================================================================

    CPSMorphModel.cpp
    Created: 17 Dec 2023 1:33:11pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "CPSMorphModel.h"
#include "AppTuningModel.h"

CPSMorphModel::CPSMorphModel()
: _A(CPS::A(1))
, _B(CPS::B(3))
, _C(CPS::C(5))
, _D(CPS::D(7))
, _E(CPS::E(9))
, _F(CPS::F(11))
{
    _currentScale = CPSModel::Scale::CPS_4_2;
    _updateScales(); // clobbered on first update
}

CPSMorphModel::~CPSMorphModel() {
    
}

void CPSMorphModel::parameterChanged(const String& parameterID, float newValue) {
    if(parameterID == CPSModel::getCPSParameterID().getParamID()) {
        _currentScale = CPSModel::Scale(newValue);
    } else if(parameterID == CPSModel::getCPS_A_ParameterID().getParamID()) {
        _A->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _A->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _A->setFrequencyValue(newValue);
    } else if(parameterID == CPSModel::getCPS_B_ParameterID().getParamID()) {
        _B->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _B->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _B->setFrequencyValue(newValue);
    } else if(parameterID == CPSModel::getCPS_C_ParameterID().getParamID()) {
        _C->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _C->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _C->setFrequencyValue(newValue);
    } else if(parameterID == CPSModel::getCPS_D_ParameterID().getParamID()) {
        _D->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _D->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _D->setFrequencyValue(newValue);
    } else if(parameterID == CPSModel::getCPS_E_ParameterID().getParamID()) {
        _E->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _E->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _E->setFrequencyValue(newValue);
    } else if(parameterID == CPSModel::getCPS_F_ParameterID().getParamID()) {
        _F->setShortDescriptionText2(Microtone::getFrequencyValueDescription(newValue));
        _F->setShortDescriptionText3(Microtone::getFrequencyValueDescription(newValue));
        _F->setFrequencyValue(newValue);
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
    
    // update scales
    _updateScales();
}

shared_ptr<Tuning> CPSMorphModel::getTuning() {
    return _cps;
}

void CPSMorphModel::_updateScales() {
    switch(_currentScale) {
        case CPSModel::Scale::CPS_3_1:
            if(_cps_3_1 == nullptr) {
                _cps_3_1 = make_shared<CPS_3_1>(_A, _B, _C);
            } else {
                _cps_3_1->setABC(_A, _B, _C);
            }
            _cps = _cps_3_1;
            break;
            
        case CPSModel::Scale::CPS_3_2:
            if(_cps_3_2 == nullptr) {
                _cps_3_2 = make_shared<CPS_3_2>(_A, _B, _C);
            } else {
                _cps_3_2->setABC(_A, _B, _C);
            }
            _cps = _cps_3_2;
            break;
            
        case CPSModel::Scale::CPS_4_1:
            if(_cps_4_1 == nullptr) {
                _cps_4_1 = make_shared<CPS_4_1>(_A, _B, _C, _D);
            } else {
                _cps_4_1->setABCD(_A, _B, _C, _D);
            }
            _cps = _cps_4_1;
            break;
            
        case CPSModel::Scale::CPS_4_2:
            if(_cps_4_2 == nullptr) {
                _cps_4_2 = make_shared<CPS_4_2>(_A, _B, _C, _D);
            } else {
                _cps_4_2->setABCD(_A, _B, _C, _D);
            }
            _cps = _cps_4_2;
            break;
            
        case CPSModel::Scale::CPS_4_3:
            if(_cps_4_3 == nullptr) {
                _cps_4_3 = make_shared<CPS_4_3>(_A, _B, _C, _D);
            } else {
                _cps_4_3->setABCD(_A, _B, _C, _D);
            }
            _cps = _cps_4_3;
            break;
            
        case CPSModel::Scale::CPS_Stellated_Hexany: // Mandala
            if(_hexanyStellate == nullptr) {
                _hexanyStellate = make_shared<Mandala>(_A, _B, _C, _D);
            } else {
                _hexanyStellate->setABCD(_A, _B, _C, _D);
            }
            _cps = _hexanyStellate;
            break;
            
        case CPSModel::Scale::CPS_5_1:
            if(_cps_5_1 == nullptr) {
                _cps_5_1 = make_shared<CPS_5_1>(_A, _B, _C, _D, _E);
            } else {
                _cps_5_1->setABCDE(_A, _B, _C, _D, _E);
            }
            _cps = _cps_5_1;
            break;
            
        case CPSModel::Scale::CPS_5_2:
            if(_cps_5_2 == nullptr) {
                _cps_5_2 = make_shared<CPS_5_2>(_A, _B, _C, _D, _E);
            } else {
                _cps_5_2->setABCDE(_A, _B, _C, _D, _E);
            }
            _cps = _cps_5_2;
            break;
            
        case CPSModel::Scale::CPS_5_3:
            if(_cps_5_3 == nullptr) {
                _cps_5_3 = make_shared<CPS_5_3>(_A, _B, _C, _D, _E);
            } else {
                _cps_5_3->setABCDE(_A, _B, _C, _D, _E);
            }
            _cps = _cps_5_3;
            break;
            
        case CPSModel::Scale::CPS_5_4:
            if(_cps_5_4 == nullptr) {
                _cps_5_4 = make_shared<CPS_5_4>(_A, _B, _C, _D, _E);
            } else {
                _cps_5_4->setABCDE(_A, _B, _C, _D, _E);
            }
            _cps = _cps_5_4;
            break;
            
        case CPSModel::Scale::CPS_6_1:
            if(_cps_6_1 == nullptr) {
                _cps_6_1 = make_shared<CPS_6_1>(_A, _B, _C, _D, _E, _F);
            } else {
                _cps_6_1->setABCDEF(_A, _B, _C, _D, _E, _F);
            }
            _cps = _cps_6_1;
            break;
            
        case CPSModel::Scale::CPS_6_2:
            if(_cps_6_2 == nullptr) {
                _cps_6_2 = make_shared<CPS_6_2>(_A, _B, _C, _D, _E, _F);
            } else {
                _cps_6_2->setABCDEF(_A, _B, _C, _D, _E, _F);
            }
            _cps = _cps_6_2;
            break;
            
        case CPSModel::Scale::CPS_6_3:
            if(_cps_6_3 == nullptr) {
                _cps_6_3 = make_shared<CPS_6_3>(_A, _B, _C, _D, _E, _F);
            } else {
                _cps_6_3->setABCDEF(_A, _B, _C, _D, _E, _F);
            }
            _cps = _cps_6_3;
            break;
            
        case CPSModel::Scale::CPS_6_4:
            if(_cps_6_4 == nullptr) {
                _cps_6_4 = make_shared<CPS_6_4>(_A, _B, _C, _D, _E, _F);
            } else {
                _cps_6_4->setABCDEF(_A, _B, _C, _D, _E, _F);
            }
            _cps = _cps_6_4;
            break;
            
        case CPSModel::Scale::CPS_6_5:
            if(_cps_6_5 == nullptr) {
                _cps_6_5 = make_shared<CPS_6_5>(_A, _B, _C, _D, _E, _F);
            } else {
                _cps_6_5->setABCDEF(_A, _B, _C, _D, _E, _F);
            }
            _cps = _cps_6_5;
            break;
        default:
            jassertfalse;
            break;
    }
    
    // update app tuning model params
    _cps->setNoteNumberMiddleC(_noteNumberMiddleC);
    _cps->setOctaveMiddleC(_octaveMiddleC);
    _cps->setFrequencyMiddleC(_frequencyMiddleC);
    _cps->setNPOOverride(_npoOverride);
    _cps->setNPOOverrideEnable(_npoOverrideEnable);
}
