/*
  ==============================================================================

    EqualTemperamentMorphModel.cpp
    Created: 17 Dec 2023 1:34:17pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "EqualTemperamentMorphModel.h"
#include "EqualTemperament.h"
#include "EqualTemperamentModel.h"
#include "AppTuningModel.h"

EqualTemperamentMorphModel::EqualTemperamentMorphModel() {
    _scale = make_shared<EqualTemperament>(); // default is 12et
}

EqualTemperamentMorphModel::~EqualTemperamentMorphModel() {
    
}

void EqualTemperamentMorphModel::parameterChanged(const String& parameterID, float newValue) {
    if(parameterID == EqualTemperamentModel::getEqualTemperamentNPOParameterID().getParamID()) {
        _scale->setNPO(static_cast<unsigned long>(newValue));
    } else if(parameterID == EqualTemperamentModel::getEqualTemperamentPeriodParameterID().getParamID()) {
        _scale->setPeriod(newValue);
    } else if (parameterID == AppTuningModel::getAppTuningNoteNumberMiddleCParameterID().getParamID()) {
        _scale->setNoteNumberMiddleC(static_cast<unsigned long>(newValue));
    } else if (parameterID == AppTuningModel::getAppTuningFrequencyMiddleCParameterID().getParamID()) {
        _scale->setFrequencyMiddleC(newValue);
    } else if (parameterID == AppTuningModel::getAppTuningOctaveMiddleCParameterID().getParamID()) {
        _scale->setOctaveMiddleC(static_cast<int>(newValue));
    } else if(parameterID == AppTuningModel::getAppTuningNPOOverrideParameterID().getParamID()) {
        _scale->setNPOOverride(static_cast<int>(newValue));
    } else if(parameterID == AppTuningModel::getAppTuningNPOOverrideEnableParameterID().getParamID()) {
        _scale->setNPOOverrideEnable(static_cast<bool>(newValue));
    } else {
        jassertfalse;
    }
}

shared_ptr<Tuning> EqualTemperamentMorphModel::getTuning() {
    return _scale;
}
