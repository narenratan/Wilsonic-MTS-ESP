/**
  * @file PresetsModel.h
  * @author Marcus W. Hobbs
  * @date 31 Oct 2021
  * @brief This file contains the PresetsModel class and the PresetHelper struct.
  */

#pragma once

#include <JuceHeader.h>
#include "AppVersion.h"
#include "Microtone.h"
#include "ModelBase.h"
#include "TuningImp.h"

// Helper struct

// Presets Helper Microtone Array Lambda
using Phmal = function<MicrotoneArray(void)>; 

/**
  * @brief This struct is a helper for the PresetsModel class.
  */
struct PresetHelper
{
    String name; ///< The name of the preset
    Phmal ma; ///< The MicrotoneArray lambda function
    String description; ///< The description of the preset

    /**
      * @brief Constructor for the PresetHelper struct.
      * @param n The name of the preset.
      * @param in_ma The MicrotoneArray lambda function.
      * @param d The description of the preset. Defaults to "No Description".
      */
    PresetHelper(String n, Phmal in_ma, String d = "No Description")
    {
        name = n;
        ma = in_ma;
        description = d; // Corrected assignment to description
    }
};

/**
  * @brief This class represents the model for presets.
  */
class PresetsModel final 
: public ModelBase
, public ActionBroadcaster
{

public:
    // Static methods
    static const ParameterID getPresetsParameterID() { return ParameterID("TUNINGPRESET", AppVersion::getVersionHint()); }
    static const String getPresetsParameterName() { return "Wilson's Garden|Presets"; }
    static unsigned long constexpr getPresetsDefault() {return 0;}
    static MicrotoneArray MAF(vector<float> float_array);
    static MicrotoneArray MAD(vector<int> num_den_pairs);
    static unsigned long getNumPresets();
    static PresetHelper getPresetHelperForIndex(unsigned long index);

    // Lifecycle
    PresetsModel();
    ~PresetsModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetsModel)

public:
    // Public methods
    shared_ptr<Tuning> getTuning() override;
    StringArray getTuningPresetNames();
    unsigned long uiGetSelectedPresetIndex();
    void uiSetPreset(unsigned long index = 0);

    // Called only once: on construction of processor
    unique_ptr<AudioProcessorParameterGroup> createParams() override;

    String getGroupID() override;
    String getGroupName() override;
    String getSubgroupSeparator() override;
    ParameterID getDesignParameterID() override; // Key for this design's Favorites array
    StringArray getFavoritesParameterIDs() override; // Used for Favorites
    // Called only once: when assigning _avpts
    void attachParameterListeners() override;
    void parameterChanged(const String& parameterID, float newValue) override;
    void updateProperties() override;

protected:
    void detachParameterListeners() override;

private:
    // Private static members
    static vector<PresetHelper> __presetsHelpers; // Defined in "PresetsModel+Presets.cpp"

    // Private members
    shared_ptr<TuningImp> _preset;

    // Private methods
    void _selectTuningPreset(unsigned long index);
    void _tuningChangedUpdateUI() override;
};

