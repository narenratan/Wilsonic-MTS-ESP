/*
 ==============================================================================
 
 ScalaMorphModel.h
 Created: 17 Dec 2023 1:38:08pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "MorphModelBase.h"
#include "ScalaModel.h"
#include "Tuning_Include.h"

// forward
class ScalaTuningImp;
class Tuning;
class WilsonicProcessor;

//
class ScalaMorphModel final
: public MorphModelBase
{
    // lifecycle
public:
    ScalaMorphModel(WilsonicProcessor& processor);
    ~ScalaMorphModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScalaMorphModel)
    
public:
    void parameterChanged(const String& parameterID, float newValue) override;
    shared_ptr<Tuning> getTuning() override;
    
private:
    // private members
    WilsonicProcessor& _processor;
    shared_ptr<ScalaTuningImp> _scalaTuning;
    ScalaModel::Library _library = ScalaModel::Library::Bundled;
    int _bundle_id = ScalaModel::getScalaBundledMinID();
    int _user_id = ScalaModel::getScalaUserMinID();
    
    // app tuning model
    unsigned long _noteNumberMiddleC = Tuning::noteNumberMiddleCDefault;
    float _frequencyMiddleC = Tuning::frequencyMiddleCDefault;
    int _octaveMiddleC = Tuning::octaveMiddleCDefault;
};
