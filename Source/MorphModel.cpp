/*
 ==============================================================================
 
 MorphModel.cpp
 Created: 17 Dec 2023 1:41:54pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "MorphModel.h"
#include "DesignsModel.h"
#include "FavoritesModelV2.h"
#include "Morph.h"
#include "MorphABModel.h"
#include "MorphComponentMessageBus.h"
#include "WilsonicProcessor.h"

#pragma mark - static members

#pragma mark - lifecycle

MorphModel::MorphModel(WilsonicProcessor& processor)
: ModelBase()
, _processor(processor)
, _A(make_shared<MorphABModel>(_processor))
, _B(make_shared<MorphABModel>(_processor))
, _morph(make_shared<Morph>())
{
    // TODO: add a helper that updates _morph from _A and _B, and use it everywhere
    // TODO: Add error checking for source/target deleted
    
#if 0
    // this is causing a race condition where favorites are accessed before DesignsModel is completely constructed
    // default is first favorite
    _morph->setA(_A->getTuningForFavoritesID(0));
    _morph->setB(_B->getTuningForFavoritesID(0));
#endif

    // tuning update callback
    _morph->setOnTuningUpdate([this]() {uiNeedsUpdate();});
}

MorphModel::~MorphModel() {
    removeAllActionListeners();
    detachParameterListeners();
}

#pragma mark -

const int MorphModel::getMorphDefaultID()  {
    return FavoritesModelV2::getFavoritesMinID();
}

shared_ptr<Tuning> MorphModel::getTuning() {
    return _morph;
}

// called only once: on construction of processor
unique_ptr<AudioProcessorParameterGroup> MorphModel::createParams() {
    // Tuning Params
    
    // Create a new AudioProcessorParameterGroup object
    auto scaleGroup = std::make_unique<AudioProcessorParameterGroup>
    (getGroupID(), getGroupName(), getSubgroupSeparator(),
     
     // Scale
     
     // Favorites A ID
     make_unique<AudioParameterInt>
     (getMorphFavoriteAParameterID(),
      getMorphFavoriteAParameterName(),
      FavoritesModelV2::getFavoritesMinID(),
      FavoritesModelV2::getFavoritesMaxID(),
      getMorphDefaultID()
      ),
     
     // Favorites B ID
     make_unique<AudioParameterInt>
     (getMorphFavoriteBParameterID(),
      getMorphFavoriteBParameterName(),
      FavoritesModelV2::getFavoritesMinID(),
      FavoritesModelV2::getFavoritesMaxID(),
      getMorphDefaultID()
      ),
     
     // Morph Interpolation
     make_unique<AudioParameterFloat>
     (getMorphInterpolationParameterID(),
      getMorphInterpolationParameterName(),
      NormalisableRange<float> (morphInterpolationParameterMin, morphInterpolationParameterMax, 0.f),
      _morph->getInterpolationValue(),
      getMorphInterpolationParameterName(),
      AudioProcessorParameter::genericParameter,
[](float value, int maxLength) { return String (value).substring (0, maxLength); },
[](const String& text) { return text.getFloatValue(); }
      ),
     
     // Morph Freq/Log choice
     make_unique<AudioParameterChoice>
     (getMorphInterpolationTypeParameterID(),
      getMorphInterpolationTypeParameterName(),
      Morph::getInterpolationTypeNames(),
      Morph::getInterpolationTypeDefault()
      )
     );
    
    // Return the AudioProcessorParameterGroup object
    return scaleGroup;
}

String MorphModel::getGroupID() {
    return "Morph";
}

String MorphModel::getGroupName() {
    return "Morph";
}

String MorphModel::getSubgroupSeparator() {
    return " | ";
}

ParameterID MorphModel::getDesignParameterID() {
    return ParameterID("MORPH_PARAMETERID_DESIGNS", AppVersion::getVersionHint());
}

StringArray MorphModel::getFavoritesParameterIDs() {
    return StringArray(getMorphFavoriteAParameterID().getParamID(),
                       getMorphFavoriteBParameterID().getParamID(),
                       getMorphInterpolationParameterID().getParamID(),
                       getMorphInterpolationTypeParameterID().getParamID()
                       );
}

// called only once: after assigning _avpts
void MorphModel::attachParameterListeners() {
    jassert(_apvts != nullptr);
    for(auto pid : getFavoritesParameterIDs()) {
        _apvts->addParameterListener(pid, this);
    }
}

void MorphModel::detachParameterListeners() {
    jassert(_apvts != nullptr);
    for (auto pid : getFavoritesParameterIDs()) {
        _apvts->removeParameterListener(pid, this);
    }
}

void MorphModel::parameterChanged(const String& parameterID, float newValue) {
    auto const fm = _processor.getFavoritesModelV2();
    
    // If the parameter ID matches the Morph scale parameter ID
    if(parameterID == getMorphFavoriteAParameterID().getParamID()) {
        auto A = static_cast<int>(newValue);
        auto selectedRow = fm->_rowNumberForID(A, FavoritesModelV2::DataList::FavoritesA);
        if(selectedRow == -1) {
            selectedRow = 0;
            DBG("MorphModel::parameterChanged: getMorphFavoriteAParameterID: Can not find row for ID: " + String(A) + ", defaulting to 12ET.");
            MorphComponentMessageBus::getInstance().broadcastMessage("Morph can NOT find Favorite A with ID: " + String(A) + ", defaulting to 12ET");
            shared_ptr<TuningImp> twelveET = make_shared<TuningImp>();
            _morph->setA(twelveET);
        } else {
            auto tuningA = _A->getTuningForFavoritesID(A);
            _morph->setA(tuningA);
            fm->setSelection(selectedRow, 1, FavoritesModelV2::DataList::FavoritesB);
        }
    } else if(parameterID == getMorphFavoriteBParameterID().getParamID()) {
        auto B = static_cast<int>(newValue);
        auto selectedRow = fm->_rowNumberForID(B, FavoritesModelV2::DataList::FavoritesB);
        if(selectedRow == -1) {
            selectedRow = 0;
            DBG("MorphModel::parameterChanged: getMorphFavoriteBParameterID: Can not find row for ID: " + String(B) + ", defaulting to 12ET.");
            MorphComponentMessageBus::getInstance().broadcastMessage("Morph can NOT find Favorite B with ID: " + String(B) + ", defaulting to 12ET");
            shared_ptr<TuningImp> twelveET = make_shared<TuningImp>();
            _morph->setB(twelveET);
        } else {
            auto tuningB = _B->getTuningForFavoritesID(B);
            _morph->setB(tuningB);
            fm->setSelection(selectedRow, 1, FavoritesModelV2::DataList::FavoritesB);
        }
    } else if(parameterID == getMorphInterpolationParameterID().getParamID()) {
        _morph->setInterpolationValue(newValue);
    } else if(parameterID == getMorphInterpolationTypeParameterID().getParamID()) {
        auto interpType = static_cast<Morph::InterpolationType>(newValue);
        _morph->setInterpolationType(interpType);
    } else {
        // Assert false if the parameter ID does not match
        jassertfalse;
    }
}

void MorphModel::updateProperties() {
}

/** @section update Designs model */

void MorphModel::_tuningChangedUpdateUI() {
    sendActionMessage(DesignsModel::getMorphTuningChangedActionMessage());
}

void MorphModel::uiSetID_A(int ID_A) {
    jassert(ID_A >= static_cast<int>(FavoritesModelV2::getFavoritesMinID()));
    jassert(ID_A <= static_cast<int>(FavoritesModelV2::getFavoritesMaxID()));
    auto key = getMorphFavoriteAParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(ID_A);
    param->setValueNotifyingHost(value01);
}

int MorphModel::uiGetID_A() {
    auto& param = *_apvts->getRawParameterValue(getMorphFavoriteAParameterID().getParamID());

    return static_cast<int>(param.load());
}

void MorphModel::uiSetID_B(int ID_B) {
    jassert(ID_B >= static_cast<int>(FavoritesModelV2::getFavoritesMinID()));
    jassert(ID_B <= static_cast<int>(FavoritesModelV2::getFavoritesMaxID()));
    auto key = getMorphFavoriteBParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(ID_B);
    param->setValueNotifyingHost(value01);
}

int MorphModel::uiGetID_B() {
    auto& param = *_apvts->getRawParameterValue(getMorphFavoriteBParameterID().getParamID());

    return static_cast<int>(param.load());
}

void MorphModel::uiSetInterpolationValue(float x) {
    jassert(x >= morphInterpolationParameterMin);
    jassert(x <= morphInterpolationParameterMax);
    auto key = getMorphInterpolationParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(x);
    param->setValueNotifyingHost(value01);
}

float MorphModel::uiGetInterpolationValue() {
    auto& param = *_apvts->getRawParameterValue(getMorphInterpolationParameterID().getParamID());

    return static_cast<float>(param.load());
}

void MorphModel::uiSetInterpolationTypeIndex(int i) {
    jassert(i >= 0 && i < Morph::num_interpolation_types);
    auto key = getMorphInterpolationTypeParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(i);
    param->setValueNotifyingHost(value01);
}

int MorphModel::uiGetInterpolationTypeIndex() {
    auto& param = *_apvts->getRawParameterValue(getMorphInterpolationTypeParameterID().getParamID());

    return static_cast<int>(param.load());
}

// not automatable
void MorphModel::uiSwapTunings() {
    auto const a = uiGetID_A();
    auto const b = uiGetID_B();
    uiSetID_A(b);
    uiSetID_B(a);
}
