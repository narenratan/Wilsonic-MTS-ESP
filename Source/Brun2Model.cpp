/*
 ==============================================================================

 Brun2Model.cpp
 Created: 3 Nov 2021 8:26:41pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "Brun2Model.h"
#include "DesignsModel.h"
#include "WilsonicProcessor.h"

#pragma mark - lifecycle

/**
 * @brief Default constructor for the Brun2Model class.
 * Initializes the Brun object with default values and sets up the tuning update callback.
 */
Brun2Model::Brun2Model()
: ModelBase() {
    _brun = make_shared<Brun>();
    _brun->setLevel(Brun::defaultLevel);
    _brun->setLevelGral(Brun::defaultLevel);
    _brun->setGenerator(Brun::defaultGenerator);
    _brun->setOctave(TuningConstants::defaultPeriod);
    _brun->setMurchana(Brun::defaultMurchana);
    _brun->setAutoMurchana(false);
    _brun->setDisplayMode(Brun::DisplayMode::Cartesian);
    _brun->setOnTuningUpdate([this](){uiNeedsUpdate();});
}

Brun2Model::~Brun2Model() {
    removeAllActionListeners();
    detachParameterListeners();
}

#pragma mark - public methods

shared_ptr<Tuning> Brun2Model::getTuning() {
    return _brun;
}

/**
 * @brief Creates a group of parameters for the Brun2Model.
 * This function is called only once during the construction of the processor.
 * @return A unique pointer to a group of AudioProcessorParameterGroup.
 */
unique_ptr<AudioProcessorParameterGroup> Brun2Model::createParams() {
    // Create a group of parameters with the group ID, name, and subgroup separator
    auto paramGroup = make_unique<AudioProcessorParameterGroup>
    (getGroupID(), getGroupName(), getSubgroupSeparator(),

     // Create a generator parameter with its ID, name, range, default value, and conversion functions
     make_unique<AudioParameterFloat>
     (Brun2Model::getBrun2GeneratorParameterID(),
      Brun2Model::getBrun2GeneratorParameterName(),
      NormalisableRange<float>(Brun::minGenerator, Brun::maxGenerator, 0.f),
      Brun::defaultGenerator,
      Brun2Model::getBrun2GeneratorParameterName(),
      AudioProcessorParameter::genericParameter,
      [](float value, int maxLength) { return String(value).substring(0, maxLength); },
      [](const String& text) { return text.getFloatValue(); }),

     // Create a period parameter with its ID, name, range, default value, and conversion functions
     make_unique<AudioParameterFloat>
     (Brun2Model::getBrun2PeriodParameterID(),
      Brun2Model::getBrun2PeriodParameterName(),
      NormalisableRange<float>(TuningConstants::minPeriod, TuningConstants::maxPeriod, 0.f),
      TuningConstants::defaultPeriod,
      Brun2Model::getBrun2PeriodParameterName(),
      AudioProcessorParameter::genericParameter,
      [](float value, int maxLength) { return String(value).substring(0, maxLength); },
      [](const String& text) { return text.getFloatValue(); }),

     // Create a level parameter with its ID, name, range, and default value
     make_unique<AudioParameterInt>
     (Brun2Model::getBrun2LevelParameterID(),
      Brun2Model::getBrun2LevelParameterName(),
      Brun::absoluteMinLevel,
      Brun::absoluteMaxLevel,
      Brun::defaultLevel),

     // Create a level gral parameter with its ID, name, range, and default value
     make_unique<AudioParameterInt>
     (Brun2Model::getBrun2LevelGralParameterID(),
      Brun2Model::getBrun2LevelGralParameterName(),
      Brun::absoluteMinLevel,
      Brun::absoluteMaxLevel,
      Brun::defaultLevel),

     // Create a murchana parameter with its ID, name, range, and default value
     make_unique<AudioParameterInt>
     (Brun2Model::getBrun2MurchanaParameterID(),
      Brun2Model::getBrun2MurchanaParameterName(),
      Brun::minMurchana,
      Brun::maxMurchana,
      Brun::defaultMurchana),

     // Create an auto murchana parameter with its ID, name, and default value
     make_unique<AudioParameterBool>
     (Brun2Model::getBrun2AutoMurchanaParameterID(),
      Brun2Model::getBrun2AutoMurchanaParameterName(),
      false)
     );

    // Return the group of parameters
    return paramGroup;
}

String Brun2Model::getGroupID() {
    return "Brun2";
}

String Brun2Model::getGroupName() {
    return "Brun2";
}

String Brun2Model::getSubgroupSeparator() {
    return " | ";
}

// key for this design's Favorites array
ParameterID Brun2Model::getDesignParameterID() {
    return ParameterID("BRUN2_PARAMETERID_DESIGNS", AppVersion::getVersionHint());
}

// used for Favorites
StringArray Brun2Model::getFavoritesParameterIDs() {
    
    return StringArray(getBrun2GeneratorParameterID().getParamID(),
                       getBrun2PeriodParameterID().getParamID(),
                       getBrun2LevelParameterID().getParamID(),
                       getBrun2LevelGralParameterID().getParamID(),
                       getBrun2MurchanaParameterID().getParamID(),
                       getBrun2AutoMurchanaParameterID().getParamID()
                       );
}

// called only once: after assigning _avpts
void Brun2Model::attachParameterListeners() {
    jassert(_apvts != nullptr);
    for(auto pid : getFavoritesParameterIDs()) {
        _apvts->addParameterListener (pid, this);
    }
}

void Brun2Model::detachParameterListeners() {
    jassert(_apvts != nullptr);
    for(auto pid : getFavoritesParameterIDs()) {
        _apvts->removeParameterListener (pid, this);
    }
}

/**
 * @brief Sync with _apvts
 * @param parameterID The ID of the parameter that has changed
 * @param newValue The new value of the parameter
 */
void Brun2Model::parameterChanged(const String& parameterID, float newValue) {
    if (parameterID == getBrun2GeneratorParameterID().getParamID())
        _brun->setGenerator(newValue);
    else if (parameterID == getBrun2PeriodParameterID().getParamID())
        _brun->setOctave(newValue); // octave is actually the period
    else if (parameterID == getBrun2LevelParameterID().getParamID())
        _brun->setLevel(static_cast<unsigned long>(newValue));
    else if (parameterID == getBrun2LevelGralParameterID().getParamID())
        _brun->setLevelGral(static_cast<unsigned long>(newValue));
    else if (parameterID == getBrun2MurchanaParameterID().getParamID())
        _brun->setMurchana(static_cast<unsigned long>(newValue));
    else if (parameterID == getBrun2AutoMurchanaParameterID().getParamID())
        _brun->setAutoMurchana(static_cast<bool>(newValue));
    else
        jassertfalse;
}

void Brun2Model::updateProperties() {
    // NOP
}

#pragma mark - BrunModel methods

void Brun2Model::uiSetGenerator(float newGenerator) {
    auto key = getBrun2GeneratorParameterID();
    auto param = _apvts->getParameter(key.getParamID());
    auto range = _apvts->getParameterRange(key.getParamID());
    auto const value01 = range.convertTo0to1(newGenerator);
    param->setValueNotifyingHost(value01);
}

// source of truth getter
float Brun2Model::uiGetGenerator() {
    auto const id = getBrun2GeneratorParameterID().getParamID();
    auto& param = *_apvts->getRawParameterValue(id);

    return param.load();
}

void Brun2Model::uiSetGeneratorAsFrequency(float frequency) {
    auto const g01 = _brun->getGeneratorGivenFrequency(frequency);
    uiSetGenerator(g01);
}

// this has to query the tuning itself instead of _avpts
float Brun2Model::uiGetGeneratorAsFrequency() {
    return _brun->getGeneratorWithFrequency();
}

void Brun2Model::uiSetGeneratorAsCents(float cents) {
    auto const g01 = _brun->getGeneratorGivenCents(cents);
    uiSetGenerator(g01);
}

// this has to query the tuning itself instead of _avpts
float Brun2Model::uiGetGeneratorAsCents() {
    return _brun->getGeneratorWithCents();
}

void Brun2Model::uiSetPeriod(float newPeriod) {
    auto key = getBrun2PeriodParameterID();
    auto param = _apvts->getParameter(key.getParamID());
    auto range = _apvts->getParameterRange(key.getParamID());
    auto const value01 = range.convertTo0to1(newPeriod);
    param->setValueNotifyingHost(value01);
}

float Brun2Model::uiGetPeriod() {
    auto id = getBrun2PeriodParameterID().getParamID();
    auto& param = *_apvts->getRawParameterValue(id);

    return param.load();
}

vector<string> Brun2Model::uiGetLabelArray() {
    return _brun->getLabelArray();
}

void Brun2Model::uiSetLevel01(float newLevel) {
    auto levelParam01 = _apvts->getParameter(getBrun2LevelParameterID().getParamID());
    levelParam01->setValueNotifyingHost(newLevel);
}

float Brun2Model::uiGetLevel01() {
    auto id = getBrun2LevelParameterID().getParamID();
    auto& param = *_apvts->getRawParameterValue(id);

    return param.load();
}

void Brun2Model::uiSetLevelGral01(float newLevelGral) {
    auto levelGralParam01 = _apvts->getParameter(getBrun2LevelGralParameterID().getParamID());
    levelGralParam01->setValueNotifyingHost(newLevelGral);
}

float Brun2Model::uiGetLevelGral01() {
    auto id = getBrun2LevelGralParameterID().getParamID();
    auto& param = *_apvts->getRawParameterValue(id);

    return param.load();
}

void Brun2Model::uiSetMurchana(float newMurchana) {
    auto key = getBrun2MurchanaParameterID();
    auto param = _apvts->getParameter(key.getParamID());
    auto range = _apvts->getParameterRange(key.getParamID());
    auto const value01 = range.convertTo0to1(newMurchana);
    param->setValueNotifyingHost(value01);
}

float Brun2Model::uiGetMurchana() {
    auto id = getBrun2MurchanaParameterID().getParamID();
    auto& param = *_apvts->getRawParameterValue(id);

    return param.load();
}

void Brun2Model::uiSetAutoMurchana(bool autoMurchana) {
    auto key = getBrun2AutoMurchanaParameterID();
    auto param = _apvts->getParameter(key.getParamID());
    auto range = _apvts->getParameterRange(key.getParamID());
    auto const value01 = range.convertTo0to1(autoMurchana);
    param->setValueNotifyingHost(value01);
}

bool Brun2Model::uiGetAutoMurchana() {
    auto id = getBrun2AutoMurchanaParameterID().getParamID();
    auto& param = *_apvts->getRawParameterValue(id);

    return static_cast<bool>(param.load());
}


// properties, not automation, are source of truth for DisplayMode

void Brun2Model::uiSetDisplayMode(WilsonicProcessor& processor, int displayMode) {
    processor.saveBrunDisplayMode(displayMode);
    auto dm = static_cast<Brun::DisplayMode>(displayMode);
    _brun->setDisplayMode(dm);// clamps to range, and updates tuning
}

int Brun2Model::uiGetDisplayMode(WilsonicProcessor& processor) {
    auto const dm = processor.restoreBrunDisplayMode();

    return dm;
}

// gral sliders

void Brun2Model::uiSetGralHexScale(float newScale) {
    _brun->setGralHexScale(newScale);
}

float Brun2Model::uiGetGralHexScale() {
    return _brun->getGralHexScale();
}

void Brun2Model::uiSetGralHexRotationRadians(float newRotationRadians) {
    _brun->setGralHexRotationRadians(newRotationRadians);
}

float Brun2Model::uiGetGralHexRotationRadians() {
    return _brun->getGralHexRotationRadians();
}

void Brun2Model::uiSetGralHexShearX(float newHexShearX) {
    _brun->setGralHexShearX(newHexShearX);
}

float Brun2Model::uiGetGralHexShearX() {
    return _brun->getGralHexShearX();
}

void Brun2Model::uiSetGralHexOriginOffsetFactorX(float newFactorX) {
    _brun->setGralHexOriginOffsetFactorX(newFactorX);
}

float Brun2Model::uiGetGralHexOriginOffsetFactorX() {
    return _brun->getGralHexOriginOffsetFactorX();
}

void Brun2Model::uiSetGralHexOriginOffsetFactorY(float newFactorY) {
    _brun->setGralHexOriginOffsetFactorY(newFactorY);
}

float Brun2Model::uiGetGralHexOriginOffsetFactorY() {
    return _brun->getGralHexOriginOffsetFactorY();
}

#pragma mark - update UI

void Brun2Model::_tuningChangedUpdateUI() {
    sendActionMessage(DesignsModel::getBrunTuningChangedActionMessage());
}

#pragma mark - touch

int Brun2Model::nnForDeviceSpace(Point<int> xy) {
    auto const nn = _brun->nnForDeviceSpace(xy);

    return nn;
}

