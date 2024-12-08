/*
  ==============================================================================

    PresetsMorphModel.h
    Created: 17 Dec 2023 1:36:41pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MorphModelBase.h"
#include "Tuning_Include.h"

// Forward
class TuningImp;

//
class PresetsMorphModel final
: public MorphModelBase
{
public:
    PresetsMorphModel();
    ~PresetsMorphModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetsMorphModel)

public:
    /**
     * @brief Public methods.
     */
    void parameterChanged(const String& parameterID, float newValue) override;
    shared_ptr<Tuning> getTuning() override;

private:
    /**
     * @brief Private members and methods.
     */
    shared_ptr<TuningImp> _preset;
    void _selectTuningPreset(unsigned long presetIndex);
};
