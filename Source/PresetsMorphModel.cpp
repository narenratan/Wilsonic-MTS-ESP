/*
  ==============================================================================

    PresetsMorphModel.cpp
    Created: 17 Dec 2023 1:36:41pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "PresetsMorphModel.h"
#include "PresetsModel.h"
#include "TuningImp.h"
#include "AppTuningModel.h"

PresetsMorphModel::PresetsMorphModel() {
    // Initialize local tuning
    _preset = std::make_shared<TuningImp>();
    _preset->setOctaveMiddleC(0);
    _preset->setFrequencyMiddleC(TuningConstants::middleCFrequency);
    _preset->setNoteNumberMiddleC(60);
    _preset->setCanSort(true);
    _preset->setSort(true);
    _preset->setOctaveReduce(true);
    _preset->setOctave(2.f);
    _preset->setCanUniquify(false);
    _preset->setUniquify(false);
    _preset->setCanNPOOverride(true);
    _preset->setNPOOverrideEnable(false);
    _preset->setNPOOverride(12);
}

PresetsMorphModel::~PresetsMorphModel() {
    
}

void PresetsMorphModel::parameterChanged(const String& parameterID, float newValue) {
    if (parameterID == PresetsModel::getPresetsParameterID().getParamID()) {
        _selectTuningPreset(static_cast<unsigned long>(newValue));
    } else if (parameterID == AppTuningModel::getAppTuningNoteNumberMiddleCParameterID().getParamID()) {
        _preset->setNoteNumberMiddleC(static_cast<unsigned long>(newValue));
    } else if (parameterID == AppTuningModel::getAppTuningFrequencyMiddleCParameterID().getParamID()) {
        _preset->setFrequencyMiddleC(newValue);
    } else if (parameterID == AppTuningModel::getAppTuningOctaveMiddleCParameterID().getParamID()) {
        _preset->setOctaveMiddleC(static_cast<int>(newValue));
    } else if(parameterID == AppTuningModel::getAppTuningNPOOverrideParameterID().getParamID()) {
        _preset->setNPOOverride(static_cast<int>(newValue));
    } else if(parameterID == AppTuningModel::getAppTuningNPOOverrideEnableParameterID().getParamID()) {
        _preset->setNPOOverrideEnable(static_cast<bool>(newValue));
    } else {
        jassertfalse; // error
    }
}

shared_ptr<Tuning> PresetsMorphModel::getTuning() {
    return _preset;
}

/**
  * @brief Selects a tuning preset.
  * @param presetIndex The index of the preset to select.
  */
void PresetsMorphModel::_selectTuningPreset(unsigned long presetIndex) {
    jassert(presetIndex < PresetsModel::getNumPresets());
    auto presetHelper = PresetsModel::getPresetHelperForIndex(presetIndex);
    _preset->setTuningName(presetHelper.name.toStdString());
    auto ma = presetHelper.ma();
    _preset->setMicrotoneArray(ma);
}
