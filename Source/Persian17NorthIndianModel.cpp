/*
  ==============================================================================

    Persian17NorthIndianModel.cpp
    Created: 18 Mar 2022 7:27:53pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

/** 
 * @file Persian17NorthIndianModel.cpp
 * @brief Implementation of the Persian17NorthIndianModel class.
 */

#include "Persian17NorthIndianModel.h"
#include "DesignsModel.h"
#include "Persian17NorthIndian.h"

#pragma mark - lifecycle

Persian17NorthIndianModel::Persian17NorthIndianModel() {
    _persian17NorthIndian = make_shared<Persian17NorthIndian>();
    _persian17NorthIndian->setScale(Persian17NorthIndian::Scale::Marwa); // clobbered when params are attached to host
    _persian17NorthIndian->setOnTuningUpdate([this]() {uiNeedsUpdate();});
}

Persian17NorthIndianModel::~Persian17NorthIndianModel() {
    removeAllActionListeners();
    detachParameterListeners();
}

/** @section public methods */

shared_ptr<Tuning> Persian17NorthIndianModel::getTuning() {
    return _persian17NorthIndian;
}

int Persian17NorthIndianModel::getNumScales() {
    return Persian17NorthIndian::num_scales;
}

StringArray Persian17NorthIndianModel::getScaleNames() {
    return Persian17NorthIndian::__scaleNames;
}

void Persian17NorthIndianModel::uiSetScale(int value) {
    jassert(value >= 0 && value < Persian17NorthIndian::num_scales);
    auto key = getPersian17NorthIndianScaleParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(value);
    param->setValueNotifyingHost(value01);
}

int Persian17NorthIndianModel::uiGetSelectedScaleIndex() {
    auto& param = *_apvts->getRawParameterValue(getPersian17NorthIndianScaleParameterID().getParamID());

    return static_cast<int>(param.load());
}

/** @section processor processBlock */

// called only once: on construction of processor
unique_ptr<AudioProcessorParameterGroup> Persian17NorthIndianModel::createParams() {

    auto scaleGroup = make_unique<AudioProcessorParameterGroup>
    (getGroupID(), getGroupName(), getSubgroupSeparator(),

     // Scale

     // Create a new AudioParameterChoice object
     make_unique<AudioParameterChoice>
     (Persian17NorthIndianModel::getPersian17NorthIndianScaleParameterID(),
      Persian17NorthIndianModel::getPersian17NorthIndianScaleParameterName(),
      Persian17NorthIndianModel::getScaleNames(),
      0)
     );

    return scaleGroup;
}

String Persian17NorthIndianModel::getGroupID() {
    return "Persian 17 North Indian";
}

String Persian17NorthIndianModel::getGroupName() {
    return "Persian 17 North Indian";
}

String Persian17NorthIndianModel::getSubgroupSeparator() {
    // Return the subgroup separator
    return " | ";
}

// key for this design's Favorites array
ParameterID Persian17NorthIndianModel::getDesignParameterID() {
    // Return the design parameter ID
    return ParameterID("PERSIAN17NORTHINDIAN_PARAMETERID_DESIGNS", AppVersion::getVersionHint());
}

// used for Favorites
StringArray Persian17NorthIndianModel::getFavoritesParameterIDs() {
    return StringArray(getPersian17NorthIndianScaleParameterID().getParamID());
}

// called only once: after assigning _avpts
void Persian17NorthIndianModel::attachParameterListeners() {
    jassert (_apvts != nullptr);
    for (auto pid : getFavoritesParameterIDs())  {
        _apvts->addParameterListener (pid, this);
    }
}

void Persian17NorthIndianModel::detachParameterListeners() {
    jassert (_apvts != nullptr);
    for (auto pid : getFavoritesParameterIDs())  {
        _apvts->removeParameterListener (pid, this);
    }
}

void Persian17NorthIndianModel::parameterChanged(const String& parameterID, float newValue) {
    if(parameterID == getPersian17NorthIndianScaleParameterID().getParamID()) {
        auto scale = static_cast<Persian17NorthIndian::Scale>(newValue);
        _persian17NorthIndian->setScale(scale);
    } else {
        // Assert false if the parameter ID does not match
        jassertfalse;
    }
}

void Persian17NorthIndianModel::updateProperties() {
}

/** @section update Designs model */

void Persian17NorthIndianModel::_tuningChangedUpdateUI() {
    sendActionMessage(DesignsModel::getPersian17NorthIndianTuningChangedActionMessage());
}
