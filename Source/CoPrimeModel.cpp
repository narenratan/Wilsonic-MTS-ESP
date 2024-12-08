/*
 ==============================================================================

 CoPrimeModel.cpp
 Created: 23 Apr 2023 12:40:48pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "CoPrimeModel.h"
#include "DesignsModel.h"

#pragma mark - lifecycle

CoPrimeModel::CoPrimeModel() {
    _coPrime = make_shared<CoPrime>();
    _coPrime->setOnTuningUpdate([this]() {uiNeedsUpdate();});
}

CoPrimeModel::~CoPrimeModel() {
    removeAllActionListeners();
    detachParameterListeners();
}

#pragma mark - public methods

shared_ptr<Tuning> CoPrimeModel::getTuning() {
    return _coPrime;
}

#pragma mark - processor processBlock

// called only once: on construction of processor

unique_ptr<AudioProcessorParameterGroup> CoPrimeModel::createParams() {
    // juce String macros for automation formatting
    auto str_max_length = [](float value, int ) { return String (value).substring (0, 6); };
    auto str_float_value = [](const String& text) { return text.getFloatValue(); };

    // Tuning Param Group
    auto paramGroup = make_unique<AudioProcessorParameterGroup>
    (getGroupID(), getGroupName(), getSubgroupSeparator(),

     // Tuning Params

     // A
     make_unique<AudioParameterFloat>
     (getCoPrimeAParameterID(),
      getCoPrimeAParameterName(),
      NormalisableRange<float>
      (CoPrime::getMinA(),
       CoPrime::getMaxA(),
       CoPrime::getIntervalValue()
       ),
      CoPrime::getDefaultA(),
      getCoPrimeAParameterName(),
      AudioProcessorParameter::genericParameter,
      str_max_length,
      str_float_value
      ),

     // B
     make_unique<AudioParameterFloat>
     (getCoPrimeBParameterID(),
      getCoPrimeBParameterName(),
      NormalisableRange<float>
      (CoPrime::getMinB(),
       CoPrime::getMaxB(),
       CoPrime::getIntervalValue()
       ),
      CoPrime::getDefaultB(),
      getCoPrimeBParameterName(),
      AudioProcessorParameter::genericParameter,
      str_max_length,
      str_float_value
      ),

     // C
     make_unique<AudioParameterFloat>
     (getCoPrimeCParameterID(),
      getCoPrimeCParameterName(),
      NormalisableRange<float>
      (CoPrime::getMinC(),
       CoPrime::getMaxC(),
       CoPrime::getIntervalValue()
       ),
      CoPrime::getDefaultC(),
      getCoPrimeCParameterName(),
      AudioProcessorParameter::genericParameter,
      str_max_length,
      str_float_value
      ),

     // D
     make_unique<AudioParameterFloat>
     (getCoPrimeDParameterID(),
      getCoPrimeDParameterName(),
      NormalisableRange<float>
      (CoPrime::getMinD(),
       CoPrime::getMaxD(),
       CoPrime::getIntervalValue()
       ),
      CoPrime::getDefaultD(),
      getCoPrimeDParameterName(),
      AudioProcessorParameter::genericParameter,
      str_max_length,
      str_float_value
      ),

     // S
     make_unique<AudioParameterFloat>
     (getCoPrimeSParameterID(),
      getCoPrimeSParameterName(),
      NormalisableRange<float>
      (CoPrime::getMinS(),
       CoPrime::getMaxS(),
       CoPrime::getIntervalValue()
       ),
      CoPrime::getDefaultS(),
      getCoPrimeSParameterName(),
      AudioProcessorParameter::genericParameter,
      str_max_length,
      str_float_value
      ),

     // T
     make_unique<AudioParameterFloat>
     (getCoPrimeTParameterID(),
      getCoPrimeTParameterName(),
      NormalisableRange<float>
      (CoPrime::getMinT(),
       CoPrime::getMaxT(),
       CoPrime::getIntervalValue()
       ),
      CoPrime::getDefaultT(),
      getCoPrimeTParameterName(),
      AudioProcessorParameter::genericParameter,
      str_max_length,
      str_float_value
      ),

     // X
     make_unique<AudioParameterFloat>
     (getCoPrimeXParameterID(),
      getCoPrimeXParameterName(),
      NormalisableRange<float>
      (CoPrime::getMinX(),
       CoPrime::getMaxX(),
       CoPrime::getIntervalValue()
       ),
      CoPrime::getDefaultX(),
      getCoPrimeXParameterName(),
      AudioProcessorParameter::genericParameter,
      str_max_length,
      str_float_value
      ),

     // Y
     make_unique<AudioParameterFloat>
     (getCoPrimeYParameterID(),
      getCoPrimeYParameterName(),
      NormalisableRange<float>
      (CoPrime::getMinY(),
       CoPrime::getMaxY(),
       CoPrime::getIntervalValue()
       ),
      CoPrime::getDefaultY(),
      getCoPrimeTParameterName(),
      AudioProcessorParameter::genericParameter,
      str_max_length,
      str_float_value
      ),

     // display mode
     make_unique<AudioParameterChoice>
     (getCoPrimeDisplayModeParameterID(),
      getCoPrimeDisplayModeParameterName(),
      CoPrime::getDisplayModeNames(),
      CoPrime::getDisplayModeDefault()
      )

     );

    return paramGroup;
}


String CoPrimeModel::getGroupID() {
    return "CoPrime";
}

String CoPrimeModel::getGroupName() {
    return "CoPrime Grid";
}

String CoPrimeModel::getSubgroupSeparator() {
    return " | ";
}

// key for this design's Favorites array
ParameterID CoPrimeModel::getDesignParameterID() {
    return ParameterID ("COPRIME_PARAMETERID_DESIGNS", AppVersion::getVersionHint());
}

// used for favorites
StringArray CoPrimeModel::getFavoritesParameterIDs() {
    
    return StringArray(getCoPrimeAParameterID().getParamID(),
                       getCoPrimeBParameterID().getParamID(),
                       getCoPrimeCParameterID().getParamID(),
                       getCoPrimeDParameterID().getParamID(),
                       getCoPrimeSParameterID().getParamID(),
                       getCoPrimeTParameterID().getParamID(),
                       getCoPrimeXParameterID().getParamID(),
                       getCoPrimeYParameterID().getParamID(),
                       getCoPrimeDisplayModeParameterID().getParamID()
                       );
}

// called only once: after assigning _avpts

void CoPrimeModel::attachParameterListeners() {
    jassert(_apvts != nullptr);
    for(auto pid : getFavoritesParameterIDs()) {
        _apvts->addParameterListener(pid, this);
    }
}

void CoPrimeModel::detachParameterListeners() {
    jassert(_apvts != nullptr);
    for(auto pid : getFavoritesParameterIDs()) {
        _apvts->removeParameterListener(pid, this);
    }
}

void CoPrimeModel::parameterChanged(const String& parameterID, float newValue) {
    if(parameterID == getCoPrimeAParameterID().getParamID())
        _coPrime->setA(static_cast<unsigned long>(newValue));
    else if(parameterID == getCoPrimeBParameterID().getParamID())
        _coPrime->setB(static_cast<unsigned long>(newValue));
    else if(parameterID == getCoPrimeCParameterID().getParamID())
        _coPrime->setC(static_cast<unsigned long>(newValue));
    else if(parameterID == getCoPrimeDParameterID().getParamID())
        _coPrime->setD(static_cast<unsigned long>(newValue));
    else if(parameterID == getCoPrimeSParameterID().getParamID())
        _coPrime->setS(static_cast<unsigned long>(newValue));
    else if(parameterID == getCoPrimeTParameterID().getParamID())
        _coPrime->setT(static_cast<unsigned long>(newValue));
    else if(parameterID == getCoPrimeXParameterID().getParamID())
        _coPrime->setX(static_cast<unsigned long>(newValue));
    else if(parameterID == getCoPrimeYParameterID().getParamID())
        _coPrime->setY(static_cast<unsigned long>(newValue));
    else if(parameterID == getCoPrimeDisplayModeParameterID().getParamID())
        _coPrime->setDisplayMode (static_cast<CoPrime::DisplayMode>(newValue));
    else
        jassertfalse; // error
}

void CoPrimeModel::updateProperties() {
}

#pragma mark - update Designs model

void CoPrimeModel::_tuningChangedUpdateUI() {
    sendActionMessage (DesignsModel::getCoPrimeTuningChangedActionMessage());
}

#pragma mark - UI methods

float CoPrimeModel::uiGetA() const {
    auto& param = *_apvts->getRawParameterValue(getCoPrimeAParameterID().getParamID());

    return param.load();
}

void CoPrimeModel::uiSetA(float value) {
    auto key = getCoPrimeAParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(value);
    param->setValueNotifyingHost(value01);
}

float CoPrimeModel::uiGetB() const {
    auto& param = *_apvts->getRawParameterValue(getCoPrimeBParameterID().getParamID());

    return param.load();
}

void CoPrimeModel::uiSetB(float value) {
    auto key = getCoPrimeBParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(value);
    param->setValueNotifyingHost(value01);
}

float CoPrimeModel::uiGetC() const {
    auto& param = *_apvts->getRawParameterValue(getCoPrimeCParameterID().getParamID());

    return param.load();
}

void CoPrimeModel::uiSetC(float value) {
    auto key = getCoPrimeCParameterID().getParamID();
    auto param = _apvts->getParameter (key);
    auto range = _apvts->getParameterRange (key);
    auto const value01 = range.convertTo0to1 (value);
    param->setValueNotifyingHost (value01);
}

float CoPrimeModel::uiGetD() const {
    auto& param = *_apvts->getRawParameterValue(getCoPrimeDParameterID().getParamID());

    return param.load();
}

void CoPrimeModel::uiSetD(float value) {
    auto key = getCoPrimeDParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(value);
    param->setValueNotifyingHost(value01);
}

float CoPrimeModel::uiGetS() const {
    auto& param = *_apvts->getRawParameterValue(getCoPrimeSParameterID().getParamID());

    return param.load();
}

void CoPrimeModel::uiSetS(float value) {
    auto key = getCoPrimeSParameterID().getParamID();
    auto param = _apvts->getParameter (key);
    auto range = _apvts->getParameterRange (key);
    auto const value01 = range.convertTo0to1 (value);
    param->setValueNotifyingHost (value01);
}

float CoPrimeModel::uiGetT() const {
    auto& param = *_apvts->getRawParameterValue(getCoPrimeTParameterID().getParamID());

    return param.load();
}

void CoPrimeModel::uiSetT(float value) {
    auto key = getCoPrimeTParameterID().getParamID();
    auto param = _apvts->getParameter (key);
    auto range = _apvts->getParameterRange (key);
    auto const value01 = range.convertTo0to1 (value);
    param->setValueNotifyingHost (value01);
}

float CoPrimeModel::uiGetX() const {
    auto& param = *_apvts->getRawParameterValue (getCoPrimeXParameterID().getParamID());

    return param.load();
}

void CoPrimeModel::uiSetX(float value) {
    auto key = getCoPrimeXParameterID().getParamID();
    auto param = _apvts->getParameter (key);
    auto range = _apvts->getParameterRange (key);
    auto const value01 = range.convertTo0to1 (value);
    param->setValueNotifyingHost (value01);
}

float CoPrimeModel::uiGetY() const {
    auto& param = *_apvts->getRawParameterValue(getCoPrimeYParameterID().getParamID());

    return param.load();
}

void CoPrimeModel::uiSetY(float value) {
    auto key = getCoPrimeYParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(value);
    param->setValueNotifyingHost(value01);
}

void CoPrimeModel::uiSetDisplayMode(CoPrime::DisplayMode value) {
    auto key = getCoPrimeDisplayModeParameterID().getParamID();
    auto param = _apvts->getParameter(key);
    auto range = _apvts->getParameterRange(key);
    auto const value01 = range.convertTo0to1(static_cast<int>(value));
    param->setValueNotifyingHost(value01);
}

// yes return int instead of DisplayMode
const int CoPrimeModel::uiGetDisplayMode() {
    auto& param = *_apvts->getRawParameterValue(getCoPrimeDisplayModeParameterID().getParamID());

    return static_cast<int>(param.load());
}

int CoPrimeModel::nnForMouseInViewBounds(Point<int> xy, Rectangle<int> viewBounds) {
    auto const nn = _coPrime->cpgnnForDeviceSpace(xy, viewBounds);

    return nn;
}
