/*
  ==============================================================================

    ModelBase.cpp
    Created: 15 Nov 2021 6:41:14pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "ModelBase.h"
#include "WilsonicProcessorConstants.h"

#pragma mark - lifecycle

ModelBase::ModelBase() {}

ModelBase::~ModelBase() {
    stopTimer();
}

#pragma mark - public methods

void ModelBase::setApvts(shared_ptr<AudioProcessorValueTreeState> apvts) {
    // this should be called only once.
    // therefore _apvts = nullptr, and apvts is non-nullptr
    jassert (_apvts == nullptr);
    jassert (apvts != nullptr);
    _apvts = apvts;
    
    // now start the ui update timer
    startTimerHz(WilsonicProcessorConstants::defaultUIUpdateFrequencyHz);
}

void ModelBase::uiNeedsUpdate() {
    _uiNeedsUpdate = true;
}

void ModelBase::timerCallback() {
    if(_uiNeedsUpdate.exchange(false)) { // atomic
        _tuningChangedUpdateUI();
    }
}

void ModelBase::parameterChanged(const String& /* parameterID */, float /* newValue */) {
    //uiNeedsUpdate();
    jassertfalse;
}

void ModelBase::setDesignIndex(int index) {
    jassert(index >= 0);
    _designIndex = index;
}
int ModelBase::getDesignIndex() {
    jassert(_designIndex >= 0);
    return _designIndex;
}
