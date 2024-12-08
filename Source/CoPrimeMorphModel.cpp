/*
  ==============================================================================

    CoPrimeMorphModel.cpp
    Created: 17 Dec 2023 1:32:32pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "CoPrimeMorphModel.h"
#include "AppTuningModel.h"

CoPrimeMorphModel::CoPrimeMorphModel() {
    _coPrime = make_shared<CoPrime>();
}

CoPrimeMorphModel::~CoPrimeMorphModel() {}

void CoPrimeMorphModel::parameterChanged(const String& parameterID, float newValue) {
    if(parameterID == CoPrimeModel::getCoPrimeAParameterID().getParamID())
        _coPrime->setA(static_cast<unsigned long>(newValue));
    else if(parameterID == CoPrimeModel::getCoPrimeBParameterID().getParamID())
        _coPrime->setB(static_cast<unsigned long>(newValue));
    else if(parameterID == CoPrimeModel::getCoPrimeCParameterID().getParamID())
        _coPrime->setC(static_cast<unsigned long>(newValue));
    else if(parameterID == CoPrimeModel::getCoPrimeDParameterID().getParamID())
        _coPrime->setD(static_cast<unsigned long>(newValue));
    else if(parameterID == CoPrimeModel::getCoPrimeSParameterID().getParamID())
        _coPrime->setS(static_cast<unsigned long>(newValue));
    else if(parameterID == CoPrimeModel::getCoPrimeTParameterID().getParamID())
        _coPrime->setT(static_cast<unsigned long>(newValue));
    else if(parameterID == CoPrimeModel::getCoPrimeXParameterID().getParamID())
        _coPrime->setX(static_cast<unsigned long>(newValue));
    else if(parameterID == CoPrimeModel::getCoPrimeYParameterID().getParamID())
        _coPrime->setY(static_cast<unsigned long>(newValue));
    else if(parameterID == CoPrimeModel::getCoPrimeDisplayModeParameterID().getParamID())
        _coPrime->setDisplayMode(static_cast<CoPrime::DisplayMode>(newValue));
    else if (parameterID == AppTuningModel::getAppTuningNoteNumberMiddleCParameterID().getParamID())
        _coPrime->setNoteNumberMiddleC(static_cast<unsigned long>(newValue));
    else if (parameterID == AppTuningModel::getAppTuningFrequencyMiddleCParameterID().getParamID())
        _coPrime->setFrequencyMiddleC(newValue);
    else if (parameterID == AppTuningModel::getAppTuningOctaveMiddleCParameterID().getParamID())
        _coPrime->setOctaveMiddleC(static_cast<int>(newValue));
    else if(parameterID == AppTuningModel::getAppTuningNPOOverrideParameterID().getParamID())
        _coPrime->setNPOOverride(static_cast<int>(newValue));
    else if(parameterID == AppTuningModel::getAppTuningNPOOverrideEnableParameterID().getParamID())
        _coPrime->setNPOOverrideEnable(static_cast<bool>(newValue));

    else
        jassertfalse; // error
}

shared_ptr<Tuning> CoPrimeMorphModel::getTuning() {
    return _coPrime;
}
