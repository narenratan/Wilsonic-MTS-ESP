/*
  ==============================================================================

    ScalaMorphModel.cpp
    Created: 17 Dec 2023 1:38:08pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "ScalaMorphModel.h"
#include "ScalaModel.h"
#include "ScalaTuningImp.h"
#include "WilsonicProcessor.h"

ScalaMorphModel::ScalaMorphModel(WilsonicProcessor& processor)
: _processor(processor)
, _scalaTuning(make_shared<ScalaTuningImp>())
{
    
}

ScalaMorphModel::~ScalaMorphModel()
{
    
}

void ScalaMorphModel::parameterChanged(const String& parameterID, float newValue)
{
    auto const newValueC = static_cast<int>(newValue);
    
    if(parameterID == ScalaModel::getScalaLibraryParameterID().getParamID())
    {
        _library = static_cast<ScalaModel::Library>(newValue);
    }
    else if(parameterID == ScalaModel::getScalaBundledTuningIDParameterID().getParamID())
    {
        auto val = jlimit(ScalaModel::getScalaBundledMinID(), ScalaModel::getScalaBundledMaxID(), newValueC);
        if(val != newValueC)
        {
            DBG("ScalaMorphModel::parameterChanged: host did not clamp bundled ID:" + String(newValueC) + ", clamping to:" + String(val));
        }
        _bundle_id = val;
    }
    else if(parameterID == ScalaModel::getScalaUserTuningIDParameterID().getParamID())
    {
        auto val = jlimit(ScalaModel::getScalaUserMinID(), ScalaModel::getScalaUserMaxID(), newValueC);
        if(val != newValueC)
        {
            DBG("ScalaMorphModel::parameterChanged: host did not clamp user ID:" + String(newValueC) + ", clamping to:" + String(val));
        }
        _user_id = val;
    }
    else if(parameterID == AppTuningModel::getAppTuningNoteNumberMiddleCParameterID().getParamID())
    {
        _noteNumberMiddleC = static_cast<unsigned long>(newValue);
    }
    else if(parameterID == AppTuningModel::getAppTuningFrequencyMiddleCParameterID().getParamID())
    {
        _frequencyMiddleC = newValue;
    }
    else if(parameterID == AppTuningModel::getAppTuningOctaveMiddleCParameterID().getParamID())
    {
        _octaveMiddleC = static_cast<int>(newValue);
    }
    else
    {
        DBG("Unexpected parameter");
        jassertfalse;
    }
    
    // Final tuning
    auto tuning = (_library == ScalaModel::Library::Bundled) ?
    (_processor.getScalaModel()->getMorphFor(_library, _bundle_id)) :
    (_processor.getScalaModel()->getMorphFor(_library, _user_id));
    if(tuning != nullptr) // there must always be a non-nullptr _scalaTuning
    {
        _scalaTuning = tuning;
    }
    
    // update app tuning model params
    _scalaTuning->setNoteNumberMiddleC(_noteNumberMiddleC);
    _scalaTuning->setOctaveMiddleC(_octaveMiddleC);
    _scalaTuning->setFrequencyMiddleC(_frequencyMiddleC);
}

shared_ptr<Tuning> ScalaMorphModel::getTuning()
{
    return _scalaTuning;
}
