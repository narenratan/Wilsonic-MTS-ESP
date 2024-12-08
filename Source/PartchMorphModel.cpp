/*
  ==============================================================================

    PartchMorphModel.cpp
    Created: 6 Jun 2024 10:22:35pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "PartchMorphModel.h"
#include "Partch.h"
#include "AppTuningModel.h"

PartchMorphModel::PartchMorphModel(WilsonicProcessor& processor)
: _processor(processor)
, _partch(make_shared<Partch>()) {
    _partch->setScale(Partch::Scale::Partch43);
}

PartchMorphModel::~PartchMorphModel() {
}

void PartchMorphModel::parameterChanged(const String& parameterID, float newValue) {
    if(parameterID == PartchModel::getPartchScaleParameterID().getParamID()) {
        auto scale = static_cast<Partch::Scale>(newValue);
        _partch->setScale(scale);
    } else {
        // Assert false if the parameter ID does not match
        jassertfalse;
    }
}

shared_ptr<Tuning> PartchMorphModel::getTuning() {
    return _partch;
}
