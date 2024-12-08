/*
  ==============================================================================

    CPSMorphModel.h
    Created: 17 Dec 2023 1:33:11pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CPSModel.h"
#include "MorphModelBase.h"

class CPSMorphModel final
: public MorphModelBase
{
    // lifecycle
public:
    CPSMorphModel();
    ~CPSMorphModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CPSMorphModel)

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
    // master set
    Microtone_p _A = nullptr;
    Microtone_p _B = nullptr;
    Microtone_p _C = nullptr;
    Microtone_p _D = nullptr;
    Microtone_p _E = nullptr;
    Microtone_p _F = nullptr;

    // app tuning model
    unsigned long _noteNumberMiddleC = 60;
    float _frequencyMiddleC = 261.f;
    int _octaveMiddleC = 0.f;
    int _npoOverride = 12;
    bool _npoOverrideEnable = false;
    
    // current scale/tuning
    CPSModel::Scale _currentScale = CPSModel::Scale::CPS_4_2;
    shared_ptr<CPSTuningBase> _cps = nullptr;

    // tunings: lazy-load
    shared_ptr<CPS_3_1> _cps_3_1 = nullptr;
    shared_ptr<CPS_3_2> _cps_3_2 = nullptr;
    shared_ptr<CPS_4_1> _cps_4_1 = nullptr;
    shared_ptr<CPS_4_2> _cps_4_2 = nullptr;
    shared_ptr<CPS_4_3> _cps_4_3 = nullptr;
    shared_ptr<Mandala> _hexanyStellate = nullptr; // TODO: Fix me
    shared_ptr<CPS_5_1> _cps_5_1 = nullptr;
    shared_ptr<CPS_5_2> _cps_5_2 = nullptr;
    shared_ptr<CPS_5_3> _cps_5_3 = nullptr;
    shared_ptr<CPS_5_4> _cps_5_4 = nullptr;
    shared_ptr<CPS_6_1> _cps_6_1 = nullptr;
    shared_ptr<CPS_6_2> _cps_6_2 = nullptr;
    shared_ptr<CPS_6_3> _cps_6_3 = nullptr;
    shared_ptr<CPS_6_4> _cps_6_4 = nullptr;
    shared_ptr<CPS_6_5> _cps_6_5 = nullptr;

    // private methods
    void _updateScales(); // helper
};
