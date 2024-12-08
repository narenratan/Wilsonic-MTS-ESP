/*
  ==============================================================================

    TritriadicModel.cpp
    Created: 3 Nov 2021 8:28:54pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "DesignsModel.h"
#include "TritriadicModel.h"
#include "TritriadicTuning.h"

#pragma mark - lifecycle

TritriadicModel::TritriadicModel() {
    _tritriadicTuning = make_shared<TritriadicTuning>();
    _tritriadicTuning->setCanSort(true);
    _tritriadicTuning->setSort(true);
    _tritriadicTuning->setCanUniquify(false);
    _tritriadicTuning->setOnTuningUpdate([this]() {uiNeedsUpdate();});
}

TritriadicModel::~TritriadicModel() {
    removeAllActionListeners();
    detachParameterListeners();
}

#pragma mark - public methods

shared_ptr<Tuning> TritriadicModel::getTuning() {
    return _tritriadicTuning;
}


#pragma mark - processor processBlock

// called only once: on construction of processor

unique_ptr<AudioProcessorParameterGroup> TritriadicModel::createParams() {
    // Tuning Params
    auto paramGroup = make_unique<AudioProcessorParameterGroup>(getGroupID(), getGroupName(), getSubgroupSeparator(),

     // Dominant
     make_unique<AudioParameterFloat>(getTritriadicDominantParameterID(), getTritriadicDominantParameterName(), NormalisableRange<float> { 0.f, 1.f, 0.f}, 0.58333333f, ""),

     // mediant
     make_unique<AudioParameterFloat>(getTritriadicMediantParameterID(), getTritriadicMediantParameterName(), NormalisableRange<float> { 0.f, 1.f, 0.f}, 0.58333333f, "")
     );

    return paramGroup;
}

String TritriadicModel::getGroupID() {
    return "Tritriadic";
}

String TritriadicModel::getGroupName() {
    return "Tritriadic";
}

String TritriadicModel::getSubgroupSeparator() {
    return " | ";
}

// key for this design's Favorites array
ParameterID TritriadicModel::getDesignParameterID() {
    return ParameterID("TRITRIADIC_PARAMETERID_DESIGNS", AppVersion::getVersionHint());
}

// used for Favorites
StringArray TritriadicModel::getFavoritesParameterIDs() {
    return StringArray(getTritriadicDominantParameterID().getParamID(), getTritriadicMediantParameterID().getParamID());
}

// called only once: after assigning _avpts
void TritriadicModel::attachParameterListeners() {
    jassert(_apvts != nullptr);
    for(auto pid : getFavoritesParameterIDs()) {
        _apvts->addParameterListener(pid, this);
    }
}

void TritriadicModel::detachParameterListeners() {
    jassert(_apvts != nullptr);
    for(auto pid : getFavoritesParameterIDs()) {
        _apvts->removeParameterListener(pid, this);
    }
}

void TritriadicModel::parameterChanged(const String& parameterID, float newValue) {
    if(parameterID == getTritriadicDominantParameterID().getParamID())
        _tritriadicTuning->setDominant(newValue);
    else if(parameterID == getTritriadicMediantParameterID().getParamID())
        _tritriadicTuning->setMediant(newValue);
    else
        jassertfalse; // error
}

void TritriadicModel::updateProperties() {
}

void TritriadicModel::uiSetMediant(float value) {
    auto key = getTritriadicMediantParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(value);
    param->setValueNotifyingHost(value01);
}

float TritriadicModel::uiGetMediant() {
    auto id = getTritriadicMediantParameterID().getParamID();
    auto& param = *_apvts->getRawParameterValue(id);

    return param.load();
}

void TritriadicModel::uiSetDominant(float value) {
    auto key = getTritriadicDominantParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(value);
    param->setValueNotifyingHost(value01);
}

float TritriadicModel::uiGetDominant() {
    auto id = getTritriadicDominantParameterID().getParamID();
    auto& param = *_apvts->getRawParameterValue(id);

    return param.load();
}

float TritriadicModel::uiGetDominantAsPitch() {
    return _tritriadicTuning->getDominantAsPitch();
}

float TritriadicModel::uiGetDominantAsFrequency() {
    return _tritriadicTuning->getDominantAsFrequency();
}

float TritriadicModel::uiGetDominantAsCents() {
    return _tritriadicTuning->getDominantAsCents();
}

float TritriadicModel::uiGetMediantAsPitch() {
    return _tritriadicTuning->getMediantAsPitch();
}

float TritriadicModel::uiGetMediantAsFrequency() {
    return _tritriadicTuning->getMediantAsFrequency();
}

float TritriadicModel::uiGetMediantAsCents() {
    return _tritriadicTuning->getMediantAsCents();
}

#pragma mark - update Designs model

void TritriadicModel::_tuningChangedUpdateUI() {
    sendActionMessage(DesignsModel::getTritriadicTuningChangedActionMessage());
}
