/*
  ==============================================================================

    TritriadicMorphModel.cpp
    Created: 17 Dec 2023 1:38:46pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "TritriadicMorphModel.h"
#include "TritriadicModel.h"
#include "TritriadicTuning.h"
#include "AppTuningModel.h"

TritriadicMorphModel::TritriadicMorphModel() {
    _tritriadicTuning = make_shared<TritriadicTuning>();
    _tritriadicTuning->setCanSort(true);
    _tritriadicTuning->setSort(true);
    _tritriadicTuning->setCanUniquify(false);
}

TritriadicMorphModel::~TritriadicMorphModel() {
    
}

void TritriadicMorphModel::parameterChanged(const String& parameterID, float newValue) {
    if(parameterID == TritriadicModel::getTritriadicDominantParameterID().getParamID()) {
        _tritriadicTuning->setDominant(newValue);
    } else if(parameterID == TritriadicModel::getTritriadicMediantParameterID().getParamID()) {
        _tritriadicTuning->setMediant(newValue);
    } else if (parameterID == AppTuningModel::getAppTuningNoteNumberMiddleCParameterID().getParamID()) {
        _tritriadicTuning->setNoteNumberMiddleC(static_cast<unsigned long>(newValue));
    } else if (parameterID == AppTuningModel::getAppTuningFrequencyMiddleCParameterID().getParamID()) {
        _tritriadicTuning->setFrequencyMiddleC(newValue);
    } else if (parameterID == AppTuningModel::getAppTuningOctaveMiddleCParameterID().getParamID()) {
        _tritriadicTuning->setOctaveMiddleC(static_cast<int>(newValue));
    } else if(parameterID == AppTuningModel::getAppTuningNPOOverrideParameterID().getParamID()) {
        _tritriadicTuning->setNPOOverride(static_cast<int>(newValue));
    } else if(parameterID == AppTuningModel::getAppTuningNPOOverrideEnableParameterID().getParamID()) {
        _tritriadicTuning->setNPOOverrideEnable(static_cast<bool>(newValue));
    } else {
        jassertfalse;
    }
}

shared_ptr<Tuning> TritriadicMorphModel::getTuning() 	{
    return _tritriadicTuning;
}
