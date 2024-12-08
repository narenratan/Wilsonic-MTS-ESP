/*
 ==============================================================================
 
 RecurrenceRelationMorphModel.cpp
 Created: 17 Dec 2023 1:37:13pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "RecurrenceRelationMorphModel.h"
#include "RecurrenceRelation.h"
#include "RecurrenceRelationModel.h"
#include "AppTuningModel.h"

RecurrenceRelationMorphModel::RecurrenceRelationMorphModel() {
    // rr has good defaults
    _recurrenceRelation = make_shared<RecurrenceRelation>();
}

RecurrenceRelationMorphModel::~RecurrenceRelationMorphModel() {
    
}

void RecurrenceRelationMorphModel::parameterChanged(const String& parameterID, float newValue) {
    // indices
    if(parameterID == RecurrenceRelationModel::getRecurrenceRelationIndexParameterID().getParamID()) {
        _recurrenceRelation->setIndices(static_cast<unsigned long>(newValue));
        return;
    }
    
    // number of terms
    else if(parameterID == RecurrenceRelationModel::getRecurrenceRelationNumTermsParameterID().getParamID())
    {
        _recurrenceRelation->setNumberOfTerms(static_cast<unsigned long>(newValue));
        return;
    }
    
    // offset
    else if(parameterID == RecurrenceRelationModel::getRecurrenceRelationOffsetParameterID().getParamID())
    {
        _recurrenceRelation->setOffset(static_cast<unsigned long>(newValue));
        return;
    }
    
    // Seeds
    unsigned long i = 1;
    for(auto pid : RecurrenceRelationModel::__HnParameterIDs) {
        if(parameterID == pid) {
            _recurrenceRelation->setSeed(newValue, i);
            return;
        }
        i++;
    }
    
    // Coefficients
    i = 1;
    for(auto cid : RecurrenceRelationModel::__CnParameterIDs) {
        if(parameterID == cid) {
            _recurrenceRelation->setCoefficientByIndex(static_cast<unsigned long>(newValue), i);
            return;
        }
        i++;
    }
    
    // app tuning model
    if (parameterID == AppTuningModel::getAppTuningNoteNumberMiddleCParameterID().getParamID()) {
        _recurrenceRelation->setNoteNumberMiddleC(static_cast<unsigned long>(newValue));
        return;
    } else if (parameterID == AppTuningModel::getAppTuningFrequencyMiddleCParameterID().getParamID()) {
        _recurrenceRelation->setFrequencyMiddleC(newValue);
        return;
    } else if (parameterID == AppTuningModel::getAppTuningOctaveMiddleCParameterID().getParamID()) {
        _recurrenceRelation->setOctaveMiddleC(static_cast<int>(newValue));
        return;
    } else if(parameterID == AppTuningModel::getAppTuningNPOOverrideParameterID().getParamID()) {
        _recurrenceRelation->setNPOOverride(static_cast<int>(newValue));
    } else if(parameterID == AppTuningModel::getAppTuningNPOOverrideEnableParameterID().getParamID()) {
        _recurrenceRelation->setNPOOverrideEnable(static_cast<bool>(newValue));
    } else {
        jassertfalse;
    }
}

shared_ptr<Tuning> RecurrenceRelationMorphModel::getTuning() {
    return _recurrenceRelation;
}
