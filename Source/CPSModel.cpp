/*
 ==============================================================================
 
 CPSModel.cpp
 Created: 19 May 2022 4:45:06pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "CPSModel.h"
#include "DesignsModel.h"

#pragma mark - static members

const StringArray CPSModel::__scaleNames {
    "3_1",      // 0
    "3_2",      // 1
    "4_1",      // 2
    "4_2",      // 3
    "4_3",      // 4
    "Mandala",  // 5
    "5_1",      // 6
    "5_2",      // 7
    "5_3",      // 8
    "5_4",      // 9
    "6_1",      // 10
    "6_2",      // 11
    "6_3",      // 12
    "6_4",      // 13
    "6_5"       // 14
};

const vector<CPSModel::Scale> all_scales {
    CPSModel::Scale::CPS_3_1             ,
    CPSModel::Scale::CPS_3_2             ,
    CPSModel::Scale::CPS_4_1             ,
    CPSModel::Scale::CPS_4_2             ,
    CPSModel::Scale::CPS_4_3             ,
    CPSModel::Scale::CPS_Stellated_Hexany, // Mandala
    CPSModel::Scale::CPS_5_1             ,
    CPSModel::Scale::CPS_5_2             ,
    CPSModel::Scale::CPS_5_3             ,
    CPSModel::Scale::CPS_5_4             ,
    CPSModel::Scale::CPS_6_1             ,
    CPSModel::Scale::CPS_6_2             ,
    CPSModel::Scale::CPS_6_3             ,
    CPSModel::Scale::CPS_6_4             ,
    CPSModel::Scale::CPS_6_5
};

#pragma mark - lifecycle

CPSModel::CPSModel()
: _A (CPS::A (1))
, _B (CPS::B (3))
, _C (CPS::C (5))
, _D (CPS::D (7))
, _E (CPS::E (9))
, _F (CPS::F (11))
{
    _currentScale = Scale::CPS_4_2;
    _updateScales(); // clobbered when parameters are hooked up
}

CPSModel::~CPSModel() {
    removeAllActionListeners();
    detachParameterListeners();
}

#pragma mark - processor processBlock

// called only once: after assigning _avpts

unique_ptr<AudioProcessorParameterGroup> CPSModel::createParams() {
    // Tuning Params
    
    auto scaleGroup = make_unique<AudioProcessorParameterGroup>
    (getGroupID(), getGroupName(), getSubgroupSeparator(),
     
     // Scale (combo box)
     make_unique<AudioParameterChoice>
     (CPSModel::getCPSParameterID(),
      CPSModel::getCPSSParameterName(),
      CPSModel::getScaleNames(),
      0)
     ,
     
     // A
     make_unique<AudioParameterFloat>
     (getCPS_A_ParameterID(),
      getCPS_A_ParameterName(),
      NormalisableRange<float> (rangeMin, rangeMax, rangeStep),
      _A->getFrequencyValue(),
      getCPS_A_ParameterName(),
      AudioProcessorParameter::genericParameter,
[](float value, int maxLength) { return String (value).substring (0, maxLength); },
[](const String& text) { return text.getFloatValue(); })
     ,
     
     // B
     make_unique<AudioParameterFloat>
     (getCPS_B_ParameterID(),
      getCPS_B_ParameterName(),
      NormalisableRange<float> (rangeMin, rangeMax, rangeStep),
      _B->getFrequencyValue(),
      getCPS_B_ParameterName(),
      AudioProcessorParameter::genericParameter,
[](float value, int maxLength) { return String (value).substring (0, maxLength); },
[](const String& text) { return text.getFloatValue(); })
     ,
     
     // C
     make_unique<AudioParameterFloat>
     (getCPS_C_ParameterID(),
      getCPS_C_ParameterName(),
      NormalisableRange<float> (rangeMin, rangeMax, rangeStep),
      _C->getFrequencyValue(),
      getCPS_C_ParameterName(),
      AudioProcessorParameter::genericParameter,
[](float value, int maxLength) { return String (value).substring (0, maxLength); },
[](const String& text) { return text.getFloatValue(); })
     ,
     
     // D
     make_unique<AudioParameterFloat>
     (getCPS_D_ParameterID(),
      getCPS_D_ParameterName(),
      NormalisableRange<float> (rangeMin, rangeMax, rangeStep),
      _D->getFrequencyValue(),
      getCPS_D_ParameterName(),
      AudioProcessorParameter::genericParameter,
[](float value, int maxLength) { return String (value).substring (0, maxLength); },
[](const String& text) { return text.getFloatValue(); })
     ,
     
     // E
     make_unique<AudioParameterFloat>
     (getCPS_E_ParameterID(),
      getCPS_E_ParameterName(),
      NormalisableRange<float> (rangeMin, rangeMax, rangeStep),
      _E->getFrequencyValue(),
      getCPS_E_ParameterName(),
      AudioProcessorParameter::genericParameter,
[](float value, int maxLength) { return String (value).substring (0, maxLength); },
[](const String& text) { return text.getFloatValue(); })
     ,
     
     // F
     make_unique<AudioParameterFloat>
     (getCPS_F_ParameterID(),
      getCPS_F_ParameterName(),
      NormalisableRange<float> (rangeMin, rangeMax, rangeStep),
      _F->getFrequencyValue(),
      getCPS_F_ParameterName(),
      AudioProcessorParameter::genericParameter,
[](float value, int maxLength) { return String (value).substring (0, maxLength); },
[](const String& text) { return text.getFloatValue(); })
     
     );
    
    return scaleGroup;
}

String CPSModel::getGroupID() {
    return "CPS";
}

String CPSModel::getGroupName() {
    return "CPS";
}

String CPSModel::getSubgroupSeparator() {
    return " | ";
}

// key for this design's Favorites array
ParameterID CPSModel::getDesignParameterID() {
    return ParameterID ("CPS_PARAMETERID_DESIGNS", AppVersion::getVersionHint());
}

// used by processor to print apvts
StringArray CPSModel::getFavoritesParameterIDs() {
    
    return StringArray(getCPSParameterID().getParamID(),
                       getCPS_A_ParameterID().getParamID(),
                       getCPS_B_ParameterID().getParamID(),
                       getCPS_C_ParameterID().getParamID(),
                       getCPS_D_ParameterID().getParamID(),
                       getCPS_E_ParameterID().getParamID(),
                       getCPS_F_ParameterID().getParamID()
                       );
}

// called only once: after assigning _avpts
void CPSModel::attachParameterListeners() {
    jassert(_apvts != nullptr);
    for(auto pid : getFavoritesParameterIDs()) {
        _apvts->addParameterListener(pid, this);
    }
}

void CPSModel::detachParameterListeners() {
    jassert(_apvts != nullptr);
    for(auto pid : getFavoritesParameterIDs()) {
        _apvts->removeParameterListener(pid, this);
    }
}


// DAW callback when apvts changes
void CPSModel::parameterChanged(const String& parameterID, float newValue) {
    const ScopedLock sl(_lock);
    if (parameterID == getCPSParameterID().getParamID()) {
        _currentScale = CPSModel::Scale(newValue);
        uiNeedsUpdate();
    } else if(parameterID == getCPS_A_ParameterID().getParamID()) {
        _A->setShortDescriptionText2 (Microtone::getFrequencyValueDescription(newValue));
        _A->setShortDescriptionText3 (Microtone::getFrequencyValueDescription(newValue));
        _A->setFrequencyValue(newValue);
    } else if(parameterID == getCPS_B_ParameterID().getParamID()) {
        _B->setShortDescriptionText2 (Microtone::getFrequencyValueDescription(newValue));
        _B->setShortDescriptionText3 (Microtone::getFrequencyValueDescription(newValue));
        _B->setFrequencyValue(newValue);
    } else if(parameterID == getCPS_C_ParameterID().getParamID()) {
        _C->setShortDescriptionText2 (Microtone::getFrequencyValueDescription(newValue));
        _C->setShortDescriptionText3 (Microtone::getFrequencyValueDescription(newValue));
        _C->setFrequencyValue(newValue);
    } else if(parameterID == getCPS_D_ParameterID().getParamID()) {
        _D->setShortDescriptionText2 (Microtone::getFrequencyValueDescription(newValue));
        _D->setShortDescriptionText3 (Microtone::getFrequencyValueDescription(newValue));
        _D->setFrequencyValue(newValue);
    } else if(parameterID == getCPS_E_ParameterID().getParamID()) {
        _E->setShortDescriptionText2 (Microtone::getFrequencyValueDescription(newValue));
        _E->setShortDescriptionText3 (Microtone::getFrequencyValueDescription(newValue));
        _E->setFrequencyValue(newValue);
    } else if(parameterID == getCPS_F_ParameterID().getParamID()) {
        _F->setShortDescriptionText2 (Microtone::getFrequencyValueDescription(newValue));
        _F->setShortDescriptionText3 (Microtone::getFrequencyValueDescription(newValue));
        _F->setFrequencyValue(newValue);
    } else {
        jassertfalse;
    }
    
    // update scales: scales loaded lazily: They all call uiNeedsUpdate()
    _updateScales();
}

void CPSModel::updateProperties() {
}

// helper for parameter changes

void CPSModel::_updateScales() {
    switch (_currentScale) {
        case Scale::CPS_3_1:
            if (_cps_3_1 == nullptr)
            {
                _cps_3_1 = make_shared<CPS_3_1>(_A, _B, _C);
                _cps_3_1->setOnTuningUpdate([this](){uiNeedsUpdate();});
            } else {
                _cps_3_1->setABC(_A, _B, _C);
            }
            _cps = _cps_3_1;
            _numberOfSeeds = 3;
            break;
            
        case Scale::CPS_3_2:
            if (_cps_3_2 == nullptr)
            {
                _cps_3_2 = make_shared<CPS_3_2>(_A, _B, _C);
                _cps_3_2->setOnTuningUpdate([this](){uiNeedsUpdate();});
            } else {
                _cps_3_2->setABC(_A, _B, _C);
            }
            _cps = _cps_3_2;
            _numberOfSeeds = 3;
            break;
            
        case Scale::CPS_4_1:
            if (_cps_4_1 == nullptr) {
                _cps_4_1 = make_shared<CPS_4_1>(_A, _B, _C, _D);
                _cps_4_1->setOnTuningUpdate([this](){uiNeedsUpdate();});
            } else {
                _cps_4_1->setABCD(_A, _B, _C, _D);
            }
            _cps = _cps_4_1;
            _numberOfSeeds = 4;
            break;
            
        case Scale::CPS_4_2:
            if (_cps_4_2 == nullptr) {
                _cps_4_2 = make_shared<CPS_4_2>(_A, _B, _C, _D);
                _cps_4_2->setOnTuningUpdate([this](){uiNeedsUpdate();});
            } else {
                _cps_4_2->setABCD(_A, _B, _C, _D);
            }
            _cps = _cps_4_2;
            _numberOfSeeds = 4;
            break;
            
        case Scale::CPS_4_3:
            if (_cps_4_3 == nullptr) {
                _cps_4_3 = make_shared<CPS_4_3>(_A, _B, _C, _D);
                _cps_4_3->setOnTuningUpdate([this](){uiNeedsUpdate();});
            } else {
                _cps_4_3->setABCD(_A, _B, _C, _D);
            }
            _cps = _cps_4_3;
            _numberOfSeeds = 4;
            break;
            
        case Scale::CPS_Stellated_Hexany: // Mandala
            if (_hexanyStellate == nullptr) {
                _hexanyStellate = make_shared<Mandala>(_A, _B, _C, _D);
                _hexanyStellate->setOnTuningUpdate([this](){uiNeedsUpdate();});
            } else {
                _hexanyStellate->setABCD(_A, _B, _C, _D);
            }
            _cps = _hexanyStellate;
            _numberOfSeeds = 4;
            break;
            
        case Scale::CPS_5_1:
            if (_cps_5_1 == nullptr) {
                _cps_5_1 = make_shared<CPS_5_1>(_A, _B, _C, _D, _E);
                _cps_5_1->setOnTuningUpdate([this](){uiNeedsUpdate();});
            } else {
                _cps_5_1->setABCDE(_A, _B, _C, _D, _E);
            }
            _cps = _cps_5_1;
            _numberOfSeeds = 5;
            break;
            
        case Scale::CPS_5_2:
            if (_cps_5_2 == nullptr) {
                _cps_5_2 = make_shared<CPS_5_2>(_A, _B, _C, _D, _E);
                _cps_5_2->setOnTuningUpdate([this](){uiNeedsUpdate();});
            } else {
                _cps_5_2->setABCDE(_A, _B, _C, _D, _E);
            }
            _cps = _cps_5_2;
            _numberOfSeeds = 5;
            break;
            
        case Scale::CPS_5_3:
            if (_cps_5_3 == nullptr) {
                _cps_5_3 = make_shared<CPS_5_3>(_A, _B, _C, _D, _E);
                _cps_5_3->setOnTuningUpdate([this](){uiNeedsUpdate();});
            } else {
                _cps_5_3->setABCDE(_A, _B, _C, _D, _E);
            }
            _cps = _cps_5_3;
            _numberOfSeeds = 5;
            break;
            
        case Scale::CPS_5_4:
            if (_cps_5_4 == nullptr) {
                _cps_5_4 = make_shared<CPS_5_4>(_A, _B, _C, _D, _E);
                _cps_5_4->setOnTuningUpdate([this](){uiNeedsUpdate();});
            } else {
                _cps_5_4->setABCDE(_A, _B, _C, _D, _E);
            }
            _cps = _cps_5_4;
            _numberOfSeeds = 5;
            break;
            
        case Scale::CPS_6_1:
            if (_cps_6_1 == nullptr) {
                _cps_6_1 = make_shared<CPS_6_1>(_A, _B, _C, _D, _E, _F);
                _cps_6_1->setOnTuningUpdate([this](){uiNeedsUpdate();});
            } else {
                _cps_6_1->setABCDEF(_A, _B, _C, _D, _E, _F);
            }
            _cps = _cps_6_1;
            _numberOfSeeds = 6;
            break;
            
        case Scale::CPS_6_2:
            if (_cps_6_2 == nullptr) {
                _cps_6_2 = make_shared<CPS_6_2>(_A, _B, _C, _D, _E, _F);
                _cps_6_2->setOnTuningUpdate([this](){uiNeedsUpdate();});
            } else {
                _cps_6_2->setABCDEF(_A, _B, _C, _D, _E, _F);
            }
            _cps = _cps_6_2;
            _numberOfSeeds = 6;
            break;
            
        case Scale::CPS_6_3:
            if (_cps_6_3 == nullptr) {
                _cps_6_3 = make_shared<CPS_6_3>(_A, _B, _C, _D, _E, _F);
                _cps_6_3->setOnTuningUpdate([this](){uiNeedsUpdate();});
            } else {
                _cps_6_3->setABCDEF(_A, _B, _C, _D, _E, _F);
            }
            _cps = _cps_6_3;
            _numberOfSeeds = 6;
            break;
            
        case Scale::CPS_6_4:
            if (_cps_6_4 == nullptr) {
                _cps_6_4 = make_shared<CPS_6_4>(_A, _B, _C, _D, _E, _F);
                _cps_6_4->setOnTuningUpdate([this](){uiNeedsUpdate();});
            } else {
                _cps_6_4->setABCDEF(_A, _B, _C, _D, _E, _F);
            }
            _cps = _cps_6_4;
            _numberOfSeeds = 6;
            break;
            
        case Scale::CPS_6_5:
            if (_cps_6_5 == nullptr) {
                _cps_6_5 = make_shared<CPS_6_5>(_A, _B, _C, _D, _E, _F);
                _cps_6_5->setOnTuningUpdate([this](){uiNeedsUpdate();});
            } else {
                _cps_6_5->setABCDEF(_A, _B, _C, _D, _E, _F);
            }
            _cps = _cps_6_5;
            _numberOfSeeds = 6;
            break;
            
        default:
            jassertfalse;
            break;
    }
}

#pragma mark - public methods

unsigned long CPSModel::uiGetSelectedScaleIndex() {
    return static_cast<unsigned long>(_currentScale);
}

void CPSModel::uiSetScale(unsigned long value) {
    auto key = getCPSParameterID().getParamID();
    auto param = _apvts->getParameter (key);
    auto range = _apvts->getParameterRange (key);
    auto const value01 = range.convertTo0to1 (value);
    param->setValueNotifyingHost (value01);
}

void CPSModel::uiSetA(float value) {
    auto key = getCPS_A_ParameterID().getParamID();
    auto param = _apvts->getParameter (key);
    auto range = _apvts->getParameterRange (key);
    auto const value01 = range.convertTo0to1 (value);
    param->setValueNotifyingHost (value01);
}

void CPSModel::uiSetB(float value) {
    auto key = getCPS_B_ParameterID().getParamID();
    auto param = _apvts->getParameter (key);
    auto range = _apvts->getParameterRange (key);
    auto const value01 = range.convertTo0to1 (value);
    param->setValueNotifyingHost (value01);
}

void CPSModel::uiSetC(float value) {
    auto key = getCPS_C_ParameterID().getParamID();
    auto param = _apvts->getParameter (key);
    auto range = _apvts->getParameterRange (key);
    auto const value01 = range.convertTo0to1 (value);
    param->setValueNotifyingHost (value01);
}

void CPSModel::uiSetD(float value) {
    auto key = getCPS_D_ParameterID().getParamID();
    auto param = _apvts->getParameter (key);
    auto range = _apvts->getParameterRange (key);
    auto const value01 = range.convertTo0to1 (value);
    param->setValueNotifyingHost (value01);
}

void CPSModel::uiSetE(float value) {
    auto key = getCPS_E_ParameterID().getParamID();
    auto param = _apvts->getParameter (key);
    auto range = _apvts->getParameterRange (key);
    auto const value01 = range.convertTo0to1 (value);
    param->setValueNotifyingHost (value01);
}

void CPSModel::uiSetF(float value) {
    auto key = getCPS_F_ParameterID().getParamID();
    auto param = _apvts->getParameter (key);
    auto range = _apvts->getParameterRange (key);
    auto const value01 = range.convertTo0to1 (value);
    param->setValueNotifyingHost (value01);
}

// param = atomic float

float CPSModel::uiGetA() {
    auto& param = *_apvts->getRawParameterValue (getCPS_A_ParameterID().getParamID());
    
    return param.load();
}

float CPSModel::uiGetB() {
    auto& param = *_apvts->getRawParameterValue (getCPS_B_ParameterID().getParamID());
    
    return param.load();
}

float CPSModel::uiGetC() {
    auto& param = *_apvts->getRawParameterValue (getCPS_C_ParameterID().getParamID());
    
    return param.load();
}

float CPSModel::uiGetD() {
    auto& param = *_apvts->getRawParameterValue (getCPS_D_ParameterID().getParamID());
    
    return param.load();
}

float CPSModel::uiGetE() {
    auto& param = *_apvts->getRawParameterValue (getCPS_E_ParameterID().getParamID());
    
    return param.load();
}

float CPSModel::uiGetF() {
    auto& param = *_apvts->getRawParameterValue (getCPS_F_ParameterID().getParamID());
    
    return param.load();
}

shared_ptr<Tuning> CPSModel::getTuning() {
    return _cps;
}

const shared_ptr<CPSTuningBase> CPSModel::getCPSTuning() {
    return _cps;
}

unsigned long CPSModel::getNumScales() {
    return num_scales;
}

StringArray CPSModel::getScaleNames() {
    return __scaleNames;
}

unsigned long CPSModel::getNumberOfSeeds() {
    return _numberOfSeeds;
}

#pragma mark - update Designs model

void CPSModel::_tuningChangedUpdateUI() {
    sendActionMessage(DesignsModel::getCPSTuningChangedActionMessage());
}
