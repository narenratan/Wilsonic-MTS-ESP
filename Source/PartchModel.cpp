/*
  ==============================================================================

    PartchModel.cpp
    Created: 27 May 2024 1:53:38pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "PartchModel.h"
#include "DesignsModel.h"
#include "WilsonicProcessor.h"

#pragma mark - lifecycle

PartchModel::PartchModel(WilsonicProcessor& processor)
: ModelBase()
, _processor(processor) {
    _partch = make_shared<Partch>();
    _partch->setScale(Partch::Scale::Partch43);
    _partch->setOnTuningUpdate([this](){uiNeedsUpdate();});
}

PartchModel::~PartchModel() {
    removeAllActionListeners();
    detachParameterListeners();
}

#pragma mark - public methods

shared_ptr<Tuning> PartchModel::getTuning() {
    return _partch;
}

int PartchModel::getNumScales() {
    return Partch::num_scales;
}

StringArray PartchModel::getScaleNames() {
    return Partch::__scaleNames;
}

unique_ptr<AudioProcessorParameterGroup> PartchModel::createParams() {
    auto scaleGroup = make_unique<AudioProcessorParameterGroup>
    (getGroupID(), getGroupName(), getSubgroupSeparator(),
     make_unique<AudioParameterChoice>
     (PartchModel::getPartchScaleParameterID(),
      PartchModel::getPartchScaleParameterName(),
      PartchModel::getScaleNames(),
      0)
     );
    
    return scaleGroup;
}

String PartchModel::getGroupID() {
    return "Partch";
}

String PartchModel::getGroupName() {
    // Return the group name
    return "Partch";
}

String PartchModel::getSubgroupSeparator() {
    // Return the subgroup separator
    return " | ";
}

// key for this design's Favorites array
ParameterID PartchModel::getDesignParameterID() {
    // Return the design parameter ID
    return ParameterID("PARTCH_PARAMETERID_DESIGNS", AppVersion::getVersionHint());
}

// used for Favorites
StringArray PartchModel::getFavoritesParameterIDs() {
    return StringArray(getPartchScaleParameterID().getParamID());
}

// called only once: after assigning _avpts
void PartchModel::attachParameterListeners() {
    jassert (_apvts != nullptr);
    for (auto pid : getFavoritesParameterIDs())  {
        _apvts->addParameterListener (pid, this);
    }
}

void PartchModel::detachParameterListeners() {
    jassert (_apvts != nullptr);
    for (auto pid : getFavoritesParameterIDs())  {
        _apvts->removeParameterListener (pid, this);
    }
}

void PartchModel::parameterChanged(const String& parameterID, float newValue) {
    if(parameterID == getPartchScaleParameterID().getParamID()) {
        auto scale = static_cast<Partch::Scale>(newValue);
        _partch->setScale(scale);
    } else {
        // Assert false if the parameter ID does not match
        jassertfalse;
    }
}

void PartchModel::updateProperties() {
    _partch->setO1(_processor.restorePartchO1());
    _partch->setO3(_processor.restorePartchO3());
    _partch->setO5(_processor.restorePartchO5());
    _partch->setO7(_processor.restorePartchO7());
    _partch->setO9(_processor.restorePartchO9());
    _partch->setO11(_processor.restorePartchO11());
    _partch->setU1(_processor.restorePartchU1());
    _partch->setU3(_processor.restorePartchU3());
    _partch->setU5(_processor.restorePartchU5());
    _partch->setU7(_processor.restorePartchU7());
    _partch->setU9(_processor.restorePartchU9());
    _partch->setU11(_processor.restorePartchU11());
}
/** @section update Designs model */

void PartchModel::_tuningChangedUpdateUI() {
    sendActionMessage(DesignsModel::getPartchTuningChangedActionMessage());
}

#pragma mark - UI methods

void PartchModel::uiSetScale(int index) {
    jassert(index >= 0 && index < Partch::num_scales);
    auto key = getPartchScaleParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(index);
    param->setValueNotifyingHost(value01);
}

int PartchModel::uiGetSelectedScaleIndex() {
    auto paramID = getPartchScaleParameterID().getParamID();
    
    if (auto* param = _apvts->getRawParameterValue(paramID)) {
        return static_cast<int>(param->load());
    } else {
        // this actually might not be neccessary.
        DBG("Parameter not found: " << paramID);
        return static_cast<int>(Partch::default_scale);
    }
}

// gral sliders

void PartchModel::uiSetGralHexScale(float newScale) {
    _partch->setGralHexScale(newScale);
}

float PartchModel::uiGetGralHexScale() {
    return _partch->getGralHexScale();
}

void PartchModel::uiSetGralHexRotationRadians(float newRotationRadians) {
    _partch->setGralHexRotationRadians(newRotationRadians);
}

float PartchModel::uiGetGralHexRotationRadians() {
    return _partch->getGralHexRotationRadians();
}

void PartchModel::uiSetGralHexShearX(float newHexShearX) {
    _partch->setGralHexShearX(newHexShearX);
}

float PartchModel::uiGetGralHexShearX() {
    return _partch->getGralHexShearX();
}

void PartchModel::uiSetGralHexOriginOffsetFactorX(float newFactorX) {
    _partch->setGralHexOriginOffsetFactorX(newFactorX);
}

float PartchModel::uiGetGralHexOriginOffsetFactorX() {
    return _partch->getGralHexOriginOffsetFactorX();
}

void PartchModel::uiSetGralHexOriginOffsetFactorY(float newFactorY) {
    _partch->setGralHexOriginOffsetFactorY(newFactorY);
}

float PartchModel::uiGetGralHexOriginOffsetFactorY() {
    return _partch->getGralHexOriginOffsetFactorY();
}

void PartchModel::uiSetO1(bool o1) {
    _processor.savePartchO1(o1);
    _partch->setO1(o1);
}

bool PartchModel::uiGetO1() const {
    return _partch->getO1();
}

void PartchModel::uiSetU1(bool u1) {
    _processor.savePartchU1(u1);
    _partch->setU1(u1);
}

bool PartchModel::uiGetU1() const {
    return _partch->getU1();
}

void PartchModel::uiSetO3(bool o3) {
    _processor.savePartchO3(o3);
    _partch->setO3(o3);
}

bool PartchModel::uiGetO3() const {
    return _partch->getO3();
}

void PartchModel::uiSetU3(bool u3) {
    _processor.savePartchU3(u3);
    _partch->setU3(u3);
}

bool PartchModel::uiGetU3() const {
    return _partch->getU3();
}

void PartchModel::uiSetO5(bool o5) {
    _processor.savePartchO5(o5);
    _partch->setO5(o5);
}

bool PartchModel::uiGetO5() const {
    return _partch->getO5();
}

void PartchModel::uiSetU5(bool u5) {
    _processor.savePartchU5(u5);
    _partch->setU5(u5);
}

bool PartchModel::uiGetU5() const {
    return _partch->getU5();
}

void PartchModel::uiSetO7(bool o7) {
    _processor.savePartchO7(o7);
    _partch->setO7(o7);
}

bool PartchModel::uiGetO7() const {
    return _partch->getO7();
}

void PartchModel::uiSetU7(bool u7) {
    _processor.savePartchU7(u7);
    _partch->setU7(u7);
}

bool PartchModel::uiGetU7() const {
    return _partch->getU7();
}

void PartchModel::uiSetO9(bool o9) {
    _processor.savePartchO9(o9);
    _partch->setO9(o9);
}

bool PartchModel::uiGetO9() const {
    return _partch->getO9();
}

void PartchModel::uiSetU9(bool u9) {
    _processor.savePartchU9(u9);
    _partch->setU9(u9);
}

bool PartchModel::uiGetU9() const {
    return _partch->getU9();
}

void PartchModel::uiSetO11(bool o11) {
    _processor.savePartchO11(o11);
    _partch->setO11(o11);
}

bool PartchModel::uiGetO11() const {
    return _partch->getO11();
}

void PartchModel::uiSetU11(bool u11) {
    _processor.savePartchU11(u11);
    _partch->setU11(u11);
}

bool PartchModel::uiGetU11() const {
    return _partch->getU11();
}
#pragma mark - touch

int PartchModel::nnForDeviceSpace(Point<int> xy) {
    auto const nn = _partch->nnForDeviceSpace(xy);

    return nn;
}

