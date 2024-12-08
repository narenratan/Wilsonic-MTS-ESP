/*
 ==============================================================================
 
 Persian17NorthIndianMorphModel.cpp
 Created: 17 Dec 2023 1:36:03pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "Persian17NorthIndianMorphModel.h"
#include "Persian17NorthIndian.h"
#include "AppTuningModel.h"

Persian17NorthIndianMorphModel::Persian17NorthIndianMorphModel()
: _persian17NorthIndian(make_shared<Persian17NorthIndian>()) {
    // Set the scale of the Persian17NorthIndian object
    _persian17NorthIndian->setScale(Persian17NorthIndian::Scale::Marwa);
}

Persian17NorthIndianMorphModel::~Persian17NorthIndianMorphModel() {
    
}

void Persian17NorthIndianMorphModel::parameterChanged(const String& parameterID, float newValue) {
    if(parameterID == Persian17NorthIndianModel::getPersian17NorthIndianScaleParameterID().getParamID()) {
        auto scale = static_cast<Persian17NorthIndian::Scale>(newValue);
        _persian17NorthIndian->setScale(scale);
    } else if (parameterID == AppTuningModel::getAppTuningNoteNumberMiddleCParameterID().getParamID()) {
        _persian17NorthIndian->setNoteNumberMiddleC(static_cast<unsigned long>(newValue));
    } else if (parameterID == AppTuningModel::getAppTuningFrequencyMiddleCParameterID().getParamID()) {
        _persian17NorthIndian->setFrequencyMiddleC(newValue);
    } else if (parameterID == AppTuningModel::getAppTuningOctaveMiddleCParameterID().getParamID()) {
        _persian17NorthIndian->setOctaveMiddleC(static_cast<int>(newValue));
    } else if(parameterID == AppTuningModel::getAppTuningNPOOverrideParameterID().getParamID()) {
        _persian17NorthIndian->setNPOOverride(static_cast<int>(newValue));
    } else if(parameterID == AppTuningModel::getAppTuningNPOOverrideEnableParameterID().getParamID()) {
        _persian17NorthIndian->setNPOOverrideEnable(static_cast<bool>(newValue));
    } else {
        // Assert false if the parameter ID does not match
        jassertfalse;
    }
    
}

shared_ptr<Tuning> Persian17NorthIndianMorphModel::getTuning() {
    return _persian17NorthIndian;
}
