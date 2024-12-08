/*
  ==============================================================================

    Brun2MorphModel.cpp
    Created: 17 Dec 2023 1:32:01pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "Brun2MorphModel.h"
#include "AppTuningModel.h"

Brun2MorphModel::Brun2MorphModel() {
    _brun = make_shared<Brun>();
    _brun->setLevel(Brun::defaultLevel);
    _brun->setLevelGral(Brun::defaultLevel);
    _brun->setGenerator(Brun::defaultGenerator);
    _brun->setOctave(TuningConstants::defaultPeriod);
    _brun->setMurchana(Brun::defaultMurchana);
    _brun->setAutoMurchana(false);
    _brun->setDisplayMode(Brun::DisplayMode::Cartesian);
}

Brun2MorphModel::~Brun2MorphModel() {}

void Brun2MorphModel::parameterChanged(const String& parameterID, float newValue) {
    if (parameterID == Brun2Model::getBrun2GeneratorParameterID().getParamID()) {
        _brun->setGenerator(newValue);
    } else if (parameterID == Brun2Model::getBrun2PeriodParameterID().getParamID()) {
        _brun->setOctave(newValue); // octave is actually the period
    } else if (parameterID == Brun2Model::getBrun2LevelParameterID().getParamID()) {
        _brun->setLevel(static_cast<unsigned long>(newValue));
    } else if (parameterID == Brun2Model::getBrun2LevelGralParameterID().getParamID()) {
        _brun->setLevelGral(static_cast<unsigned long>(newValue));
    } else if (parameterID == Brun2Model::getBrun2MurchanaParameterID().getParamID()) {
        _brun->setMurchana(static_cast<unsigned long>(newValue));
    } else if (parameterID == Brun2Model::getBrun2AutoMurchanaParameterID().getParamID()) {
        _brun->setAutoMurchana(static_cast<bool>(newValue));
    }  else if (parameterID == AppTuningModel::getAppTuningNoteNumberMiddleCParameterID().getParamID()) {
        _brun->setNoteNumberMiddleC(static_cast<unsigned long>(newValue));
    } else if (parameterID == AppTuningModel::getAppTuningFrequencyMiddleCParameterID().getParamID()) {
        _brun->setFrequencyMiddleC(newValue);
    } else if (parameterID == AppTuningModel::getAppTuningOctaveMiddleCParameterID().getParamID()) {
        _brun->setOctaveMiddleC(static_cast<int>(newValue));
    } else if(parameterID == AppTuningModel::getAppTuningNPOOverrideParameterID().getParamID()) {
        _brun->setNPOOverride(static_cast<int>(newValue));
    } else if(parameterID == AppTuningModel::getAppTuningNPOOverrideEnableParameterID().getParamID()) {
        _brun->setNPOOverrideEnable(static_cast<bool>(newValue));
    } else {
        jassertfalse;
    }    
}

shared_ptr<Tuning> Brun2MorphModel::getTuning() {
    return _brun;
}
