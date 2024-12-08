/*
  ==============================================================================

    TritriadicModel.h
    Created: 3 Nov 2021 8:28:54pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppVersion.h"
#include "ModelBase.h"
#include "Tuning_Include.h"

// forward
class Tuning;
class TritriadicTuning;

//
class TritriadicModel final
: public ModelBase
, public ActionBroadcaster
{
public:
    // static methods
    static const ParameterID getTritriadicDominantParameterID() { return ParameterID ("TRITRIADICDOMINANT", AppVersion::getVersionHint()); }
    static const String getTritriadicDominantParameterName() { return "Tritriadic|Dominant"; }
    static const ParameterID getTritriadicMediantParameterID() { return ParameterID ("TRITRIADICMEDIANT", AppVersion::getVersionHint()); }
    static const String getTritriadicMediantParameterName() { return "Tritriadic|Mediant"; }

public:
    // lifecycle
    TritriadicModel();
    ~TritriadicModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TritriadicModel)

public:
    // public methods
    shared_ptr<Tuning> getTuning() override;
    unique_ptr<AudioProcessorParameterGroup> createParams() override;// called only once: on construction of processor
    String getGroupID() override;
    String getGroupName() override;
    String getSubgroupSeparator() override;
    ParameterID getDesignParameterID() override; // key for this design's Favorites array
    StringArray getFavoritesParameterIDs() override; // used for Favorites
    // called only once: when assigning _avpts
    void attachParameterListeners() override;
    void parameterChanged (const String& parameterID, float newValue) override;
    void updateProperties() override;

    void uiSetMediant (float newMediant);
    float uiGetMediant();
    void uiSetDominant (float newDominant);
    float uiGetDominant();
    float uiGetDominantAsPitch();
    float uiGetDominantAsFrequency();
    float uiGetDominantAsCents();
    float uiGetMediantAsPitch();
    float uiGetMediantAsFrequency();
    float uiGetMediantAsCents();

    
protected:
    void detachParameterListeners() override;

private:
    // private members
    shared_ptr<TritriadicTuning> _tritriadicTuning;

    // private methods
    void _tuningChangedUpdateUI() override;
};
