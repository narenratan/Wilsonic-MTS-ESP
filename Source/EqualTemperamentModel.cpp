/*
 ==============================================================================

 EqualTemperamentModel.cpp
 Created: 25 May 2022 7:58:51pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "DesignsModel.h"
#include "EqualTemperament.h"
#include "EqualTemperamentModel.h"

// public methods

EqualTemperamentModel::EqualTemperamentModel() {
    _scale = make_shared<EqualTemperament>(); // default is 12et
    _scale->setOnTuningUpdate([this]() {uiNeedsUpdate();});
}

EqualTemperamentModel::~EqualTemperamentModel() {
    removeAllActionListeners();
    detachParameterListeners();
}

shared_ptr<Tuning> EqualTemperamentModel::getTuning() {
    return _scale;
}

void EqualTemperamentModel::uiSetNPO(int npo) {
    jassert(npo >= static_cast<int>(EqualTemperament::minNPO));
    jassert(npo <= static_cast<int>(EqualTemperament::maxNPO));
    auto key = getEqualTemperamentNPOParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(npo);
    param->setValueNotifyingHost(value01);
}

int EqualTemperamentModel::uiGetNPO() {
    auto& param = *_apvts->getRawParameterValue(getEqualTemperamentNPOParameterID().getParamID());

    return static_cast<int>(param.load());
}

void EqualTemperamentModel::uiSetPeriod(float period) {
    jassert(period >= TuningConstants::minPeriod);
    jassert(period <= TuningConstants::maxPeriod);
    auto key = getEqualTemperamentPeriodParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(period);
    param->setValueNotifyingHost(value01);
}

float EqualTemperamentModel::uiGetPeriod() {
    auto& param = *_apvts->getRawParameterValue(getEqualTemperamentPeriodParameterID().getParamID());

    return static_cast<float>(param.load());
}


// called only once: on construction of processor

unique_ptr<AudioProcessorParameterGroup> EqualTemperamentModel::createParams() {
    // Tuning Params

    auto scaleGroup = make_unique<AudioProcessorParameterGroup>
    (getGroupID(), getGroupName(), getSubgroupSeparator(),

     // Scale

     make_unique<AudioParameterInt>
     (EqualTemperamentModel::getEqualTemperamentNPOParameterID(),
      EqualTemperamentModel::getEqualTemperamentNPOParameterName(),
      EqualTemperament::minNPO,
      EqualTemperament::maxNPO,
      EqualTemperament::defaultNPO
      ),

     make_unique<AudioParameterFloat>
     (EqualTemperamentModel::getEqualTemperamentPeriodParameterID(),
      EqualTemperamentModel::getEqualTemperamentPeriodParameterName(),
      NormalisableRange<float>
      (TuningConstants::minPeriod,
       TuningConstants::maxPeriod,
       0.f),
      TuningConstants::defaultPeriod,
      EqualTemperamentModel::getEqualTemperamentPeriodParameterName(),
      AudioProcessorParameter::genericParameter,
[](float value, int maxLength) { return String(value).substring(0, maxLength); },
[](const String& text) { return text.getFloatValue(); }
      )

     );

    return scaleGroup;
}

String EqualTemperamentModel::getGroupID() {
    return "Equal Temperament";
}

String EqualTemperamentModel::getGroupName() {
    return "Equal Temperament";
}

String EqualTemperamentModel::getSubgroupSeparator() {
    return " | ";
}

// key for this design's Favorites array
ParameterID EqualTemperamentModel::getDesignParameterID() {
    return ParameterID("EQUALTEMPERAMENT_PARAMETERID_DESIGNS", AppVersion::getVersionHint());
}

// used for Favorites
StringArray EqualTemperamentModel::getFavoritesParameterIDs() {
    
    return StringArray(getEqualTemperamentNPOParameterID().getParamID(),
                        getEqualTemperamentPeriodParameterID().getParamID());
}

// called only once: after assigning _avpts
void EqualTemperamentModel::attachParameterListeners() {
    jassert (_apvts != nullptr);
    for (auto pid : getFavoritesParameterIDs()) {
        _apvts->addParameterListener (pid, this);
    }
}

void EqualTemperamentModel::detachParameterListeners() {
    jassert (_apvts != nullptr);
    for (auto pid : getFavoritesParameterIDs()) {
        _apvts->removeParameterListener (pid, this);
    }
}

void EqualTemperamentModel::parameterChanged(const String& parameterID, float newValue) {
    if (parameterID == getEqualTemperamentNPOParameterID().getParamID())
        _scale->setNPO(static_cast<unsigned long>(newValue));
    else if (parameterID == getEqualTemperamentPeriodParameterID().getParamID())
        _scale->setPeriod(newValue);
    else
        jassertfalse;
}

void EqualTemperamentModel::updateProperties() {
}

void EqualTemperamentModel::_tuningChangedUpdateUI() {
    sendActionMessage(DesignsModel::getEqualTemperamentTuningChangedActionMessage());
}
