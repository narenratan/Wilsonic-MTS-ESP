/*
  ==============================================================================

    EqualTemperamentModel.h
    Created: 25 May 2022 7:58:51pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppVersion.h"
#include "ModelBase.h"
#include "TuningImp.h"
#include "Tuning_Include.h"

// forward
class EqualTemperament;

//
class EqualTemperamentModel final
: public ModelBase
, public ActionBroadcaster
{
public:
    // static
    static const ParameterID getEqualTemperamentNPOParameterID() { return ParameterID ("EQUALTEMPERAMENTNPO", AppVersion::getVersionHint()); }
    static const String getEqualTemperamentNPOParameterName() { return "Equal Temperament|ET"; }
    static const ParameterID getEqualTemperamentPeriodParameterID() { return ParameterID ("EQUALTEMPERAMENTPERIOD", AppVersion::getVersionHint()); }
    static const String getEqualTemperamentPeriodParameterName() { return "Equal Temperament|Period"; }

    // lifecycle
public:
    EqualTemperamentModel();
    ~EqualTemperamentModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualTemperamentModel)

public:
    // public methods
    shared_ptr<Tuning> getTuning() override;
    void uiSetNPO (int npo);
    int uiGetNPO();
    void uiSetPeriod (float period);
    float uiGetPeriod();

    // called only once: on construction of processor
    unique_ptr<AudioProcessorParameterGroup> createParams() override;
    String getGroupID() override;
    String getGroupName() override;
    String getSubgroupSeparator() override;
    ParameterID getDesignParameterID() override; // key for this design's Favorites array
    StringArray getFavoritesParameterIDs() override; // used by processor to print apvts, and to store favorites
    void updateProperties() override;

    // called only once: when assigning _avpts
    void attachParameterListeners() override;
    void parameterChanged (const String& parameterID, float newValue) override;

protected:
    void detachParameterListeners() override;

private:
    // private members
    shared_ptr<EqualTemperament> _scale;

    // private methods
    void _tuningChangedUpdateUI() override;
};

