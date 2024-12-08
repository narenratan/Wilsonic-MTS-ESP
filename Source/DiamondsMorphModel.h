/*
  ==============================================================================

    DiamondsMorphModel.h
    Created: 17 Dec 2023 1:33:40pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "TriadicDiamond.h"
#include "TetradicDiamond.h"
#include "PentadicDiamond.h"
#include "HexadicDiamond.h"
#include "HeptadicDiamond.h"
#include "OgdoadicDiamond.h"
#include "MorphModelBase.h"

class DiamondsMorphModel final
: public MorphModelBase
{
public:
    DiamondsMorphModel();
    ~DiamondsMorphModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DiamondsMorphModel)

public:
    /**
     * @brief Public methods.
     */
    void parameterChanged(const String& parameterID, float newValue) override;
    shared_ptr<Tuning> getTuning() override;


private:
    Microtone_p _A = nullptr;
    Microtone_p _B = nullptr;
    Microtone_p _C = nullptr;
    Microtone_p _D = nullptr;
    Microtone_p _E = nullptr;
    Microtone_p _F = nullptr;
    Microtone_p _G = nullptr;
    Microtone_p _H = nullptr;
    unsigned long _selectedScaleIndex = 0;
    shared_ptr<Tuning> _diamond = nullptr;

    // app tuning model
    unsigned long _noteNumberMiddleC = 60;
    float _frequencyMiddleC = 261.f;
    int _octaveMiddleC = 0.f;
    int _npoOverride = 12;
    bool _npoOverrideEnable = false;

    // tunings: lazy load
    shared_ptr<TriadicDiamond> _triadicDiamond = nullptr;
    shared_ptr<TetradicDiamond> _tetradicDiamond = nullptr;
    shared_ptr<PentadicDiamond> _pentadicDiamond = nullptr;
    shared_ptr<HexadicDiamond> _hexadicDiamond = nullptr;
    shared_ptr<HeptadicDiamond> _heptadicDiamond = nullptr;
    shared_ptr<OgdoadicDiamond> _ogdoadicDiamond = nullptr;

    void _updateScales();
};
