/*
  ==============================================================================

    ModelBase.h
    Created: 15 Nov 2021 6:41:14pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"

// forward
class Tuning;

//
class ModelBase
: public AudioProcessorValueTreeState::Listener
, private Timer
{
    // lifecycle
public:
    ModelBase();
    ~ModelBase() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModelBase)

public:
    // public methods
    void setApvts(shared_ptr<AudioProcessorValueTreeState>);
    virtual String getGroupID() = 0;
    virtual String getGroupName() = 0;
    virtual String getSubgroupSeparator() = 0;
    virtual ParameterID getDesignParameterID() = 0; // key for this design's Favorites array
    virtual StringArray getFavoritesParameterIDs() = 0; // used for Favorites
    virtual void setDesignIndex(int index);
    virtual int getDesignIndex();
    
    // called only once: on construction of processor
    virtual unique_ptr<AudioProcessorParameterGroup> createParams() = 0;
    virtual void attachParameterListeners() = 0;
    virtual shared_ptr<Tuning> getTuning() = 0;
    virtual void updateProperties() = 0;

protected:
    // protected members
    CriticalSection _lock;
    shared_ptr<AudioProcessorValueTreeState> _apvts {nullptr};
    int _designIndex = -1;
    atomic<bool> _uiNeedsUpdate {false};
    
    // protected methods
    virtual void detachParameterListeners() = 0;
    virtual void _tuningChangedUpdateUI() = 0;
    void uiNeedsUpdate();
    void parameterChanged(const String &parameterID, float newValue) override;
    void timerCallback() override;
};
