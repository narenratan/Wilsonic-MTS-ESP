/*
  ==============================================================================

    CoPrimeMorphModel.h
    Created: 17 Dec 2023 1:32:32pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CoPrimeModel.h"
#include "MorphModelBase.h"

class CoPrimeMorphModel final
: public MorphModelBase
{
public:
    CoPrimeMorphModel();
    ~CoPrimeMorphModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CoPrimeMorphModel)
    
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
    shared_ptr<CoPrime> _coPrime;
};
