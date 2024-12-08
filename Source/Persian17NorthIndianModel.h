/**
 * @file Persian17NorthIndianModel.h
 * @brief Declaration of the Persian17NorthIndianModel class.
 * @author Marcus W. Hobbs
 * @date Created: 18 Mar 2022 7:27:53pm
 * 
 * This file contains the declaration of the Persian17NorthIndianModel class, which is a subclass of the ModelBase class and implements the ActionBroadcaster interface.
 * It adds additional properties and methods specific to the Persian17NorthIndianModel.
 * 
 * ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "AppVersion.h"
#include "ModelBase.h"
#include "Tuning_Include.h"

class Tuning;
class Persian17NorthIndian;

/**
 * @brief The Persian17NorthIndianModel class.
 * 
 * This class represents the Persian 17 North Indian model of the application.
 * It inherits from the ModelBase class and implements the ActionBroadcaster interface.
 */
class Persian17NorthIndianModel final 
: public ModelBase
, public ActionBroadcaster
{

public:
    static const ParameterID getPersian17NorthIndianScaleParameterID() { return ParameterID("PERSIAN17NORTHINDIANSCALE", AppVersion::getVersionHint()); }
    static const String getPersian17NorthIndianScaleParameterName() { return "17-Persian N. Indian Raga|Scale"; }

    // lifecycle
    Persian17NorthIndianModel();
    ~Persian17NorthIndianModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Persian17NorthIndianModel)

public:
    // public methods
    shared_ptr<Tuning> getTuning() override;
    int getNumScales();
    StringArray getScaleNames();
    int uiGetSelectedScaleIndex();
    void uiSetScale(int index = 0);
    // called only once: on construction of processor
    unique_ptr<AudioProcessorParameterGroup> createParams() override;
    String getGroupID() override;
    String getGroupName() override;
    String getSubgroupSeparator() override;
    ParameterID getDesignParameterID() override;
    StringArray getFavoritesParameterIDs() override;
    void attachParameterListeners() override;
    void parameterChanged(const String& parameterID, float newValue) override;
    void updateProperties() override;

protected:
    void detachParameterListeners() override;

private:
    // private members
    shared_ptr<Persian17NorthIndian> _persian17NorthIndian;

    // private methods
    void _tuningChangedUpdateUI() override;
};

