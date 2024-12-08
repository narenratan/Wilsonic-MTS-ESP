/*
  ==============================================================================

    PresetsModel.cpp
    Created: 31 Oct 2021 2:30:19pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "PresetsModel.h"
#include "DesignsModel.h"
#include "TuningConstants.h"

#pragma mark - lifecycle

/**
  * @brief Constructor for the PresetsModel class.
  * Initializes local tuning and populates presets.
  */
PresetsModel::PresetsModel()
{
    // Initialize local tuning
    _preset = make_shared<TuningImp>();
    _preset->setCanNPOOverride(true);
    _preset->setOctaveMiddleC(0);
    _preset->setFrequencyMiddleC(TuningConstants::middleCFrequency);
    _preset->setNoteNumberMiddleC(60);
    _preset->setCanSort(true);
    _preset->setSort(true);
    _preset->setOctaveReduce(true);
    _preset->setOctave(2.f);
    _preset->setCanUniquify(false);
    _preset->setUniquify(false);
    _preset->setOnTuningUpdate([this](){uiNeedsUpdate();});

    // Initialize
    _selectTuningPreset(getPresetsDefault());
}

/**
  * @brief Destructor for the PresetsModel class.
  * Removes all action listeners and detaches parameter listeners.
  */
PresetsModel::~PresetsModel() {
    removeAllActionListeners();
    detachParameterListeners();
}

#pragma mark - Tuning Presets

/**
  * @brief Returns the number of presets.
  * @return The number of presets.
  */
unsigned long PresetsModel::getNumPresets() {
    return static_cast<unsigned long>(__presetsHelpers.size());
}

/**
  * @brief Returns the names of the tuning presets.
  * @return The names of the tuning presets.
  */
StringArray PresetsModel::getTuningPresetNames() {
    StringArray presetNames;
    for (const auto& preset : __presetsHelpers) {
        presetNames.add(preset.name);
    }
    
    return presetNames;
}

/**
  * @brief Sets the preset value from the UI.
  * @param value The preset value.
  */
void PresetsModel::uiSetPreset(unsigned long value) {
    jassert (value >= 0 && value < getNumPresets());
    auto key = getPresetsParameterID().getParamID();
    auto param = _apvts->getParameter (key);
    auto range = _apvts->getParameterRange (key);
    auto const value01 = range.convertTo0to1 (value);
    param->setValueNotifyingHost (value01);
}

/**
  * @brief Returns the index of the selected preset from the UI.
  * @return The index of the selected preset.
  */
unsigned long PresetsModel::uiGetSelectedPresetIndex() {
    auto& param = *_apvts->getRawParameterValue (getPresetsParameterID().getParamID());

    return static_cast<unsigned long>(param.load());
}

/**
  * @brief Returns the tuning.
  * @return The tuning.
  */
std::shared_ptr<Tuning> PresetsModel::getTuning() {
    return _preset;
}

/**
  * @brief Selects a tuning preset.
  * @param presetIndex The index of the preset to select.
  */
void PresetsModel::_selectTuningPreset(unsigned long presetIndex) {
    jassert(presetIndex < __presetsHelpers.size());
    const ScopedLock sl(_lock);
    auto preset = __presetsHelpers[presetIndex];
    _preset->setTuningName(preset.name.toStdString());
    auto ma = preset.ma();
    _preset->setMicrotoneArray(ma);
}

PresetHelper PresetsModel::getPresetHelperForIndex(unsigned long index) {
    jassert(index < __presetsHelpers.size());
    auto presetHelper = __presetsHelpers[index];
    
    return presetHelper;
}

#pragma mark - processor processBlock

/**
  * @brief Creates parameters for the PresetsModel.
  * @return The created parameters.
  */
unique_ptr<AudioProcessorParameterGroup> PresetsModel::createParams() {
    // Tuning Params
    auto presetNames = getTuningPresetNames();
    auto presetParamGroup = std::make_unique<AudioProcessorParameterGroup>
    (getGroupID(), getGroupName(), getSubgroupSeparator(),

     // combo box
     std::make_unique<AudioParameterChoice> (getPresetsParameterID(), getPresetsParameterName(), presetNames, getPresetsDefault())

     );

    return presetParamGroup;
}

/**
  * @brief Returns the group ID.
  * @return The group ID.
  */
String PresetsModel::getGroupID() {
    return "Presets";
}

/**
  * @brief Returns the group name.
  * @return The group name.
  */
String PresetsModel::getGroupName() {
    return "Presets";
}

/**
  * @brief Returns the subgroup separator.
  * @return The subgroup separator.
  */
String PresetsModel::getSubgroupSeparator() {
    return " | ";
}

/**
  * @brief Returns the design parameter ID.
  * @return The design parameter ID.
  */
ParameterID PresetsModel::getDesignParameterID() {
    return ParameterID("WILSONSGARDEN_PARAMETERID_DESIGNS", AppVersion::getVersionHint());
}

/**
  * @brief Returns the parameter IDs.
  * @return The parameter IDs.
  */
StringArray PresetsModel::getFavoritesParameterIDs() {
    return StringArray(getPresetsParameterID().getParamID());
}

// called only once: after assigning _avpts
void PresetsModel::attachParameterListeners() {
    jassert(_apvts != nullptr);
    for(auto pid : getFavoritesParameterIDs()) {
        _apvts->addParameterListener(pid, this);
    }
}

void PresetsModel::detachParameterListeners() {
    jassert(_apvts != nullptr);
    for(auto pid : getFavoritesParameterIDs()) {
        _apvts->removeParameterListener(pid, this);
    }
}

/**
  * @brief Called when a parameter changes.
  * @param parameterID The ID of the parameter that changed.
  * @param newValue The new value of the parameter.
  */
void PresetsModel::parameterChanged(const String& parameterID, float newValue) {
    if (parameterID == getPresetsParameterID().getParamID()) {
        _selectTuningPreset(static_cast<unsigned long>(newValue));
    } else {
        jassertfalse; //error
    }
}

void PresetsModel::updateProperties() {
}

#pragma mark - update Designs model

/**
  * @brief Updates the UI when the tuning changes.
  */
void PresetsModel::_tuningChangedUpdateUI() {
    sendActionMessage(DesignsModel::getPresetsTuningChangedActionMessage());
}
