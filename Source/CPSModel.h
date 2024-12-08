/*
  ==============================================================================

    CPSModel.h
    Created: 19 May 2022 4:45:06pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CPSTuningBase.h"
#include "CPS_3_1.h"
#include "CPS_3_2.h"
#include "CPS_4_1.h"
#include "CPS_4_2.h"
#include "CPS_4_3.h"
#include "Mandala.h"
#include "CPS_5_1.h"
#include "CPS_5_2.h"
#include "CPS_5_3.h"
#include "CPS_5_4.h"
#include "CPS_6_1.h"
#include "CPS_6_2.h"
#include "CPS_6_3.h"
#include "CPS_6_4.h"
#include "CPS_6_5.h"
#include "ModelBase.h"
#include "Tuning.h"
#include "TuningImp.h"
#include "Tuning_Include.h"

class CPSModel final 
: public ModelBase
, public ActionBroadcaster
{
public:

    // types

    // this has to match 1:1 __scaleNames, num_scales
    enum class Scale {
        CPS_3_1 = 0,
        CPS_3_2 = 1,
        CPS_4_1 = 2,
        CPS_4_2 = 3,
        CPS_4_3 = 4,
        CPS_Stellated_Hexany = 5, // Mandala
        CPS_5_1 = 6,
        CPS_5_2 = 7,
        CPS_5_3 = 8,
        CPS_5_4 = 9,
        CPS_6_1 = 10,
        CPS_6_2 = 11,
        CPS_6_3 = 12,
        CPS_6_4 = 13,
        CPS_6_5 = 14
    };

    // static public members

    // these must be indexed by enum CPSScale, and the order should never change
    static const StringArray __scaleNames;
    static const vector<CPSModel::Scale> all_scales;
    static constexpr int num_scales = 15;
    static constexpr float rangeMin = 1.f; // A,B,C,D,E,F
    static constexpr float rangeMax = 16384.f; // A,B,C,D,E,F
    static constexpr float rangeStep = 1.f; // A,B,C,D,E,F
    static const ParameterID getCPSParameterID() { return ParameterID ("CPSCALE", AppVersion::getVersionHint()); }
    static const String getCPSSParameterName() { return "CPS|Scale"; }
    static const ParameterID getCPS_A_ParameterID() { return ParameterID ("CPSA", AppVersion::getVersionHint()); }
    static const String getCPS_A_ParameterName() { return "CPS|A"; }
    static const ParameterID getCPS_B_ParameterID() { return ParameterID ("CPSB", AppVersion::getVersionHint()); }
    static const String getCPS_B_ParameterName() { return "CPS|B"; }
    static const ParameterID getCPS_C_ParameterID() { return ParameterID ("CPSC", AppVersion::getVersionHint()); }
    static const String getCPS_C_ParameterName() { return "CPS|C"; }
    static const ParameterID getCPS_D_ParameterID() { return ParameterID ("CPSD", AppVersion::getVersionHint()); }
    static const String getCPS_D_ParameterName() { return "CPS|D"; }
    static const ParameterID getCPS_E_ParameterID() { return ParameterID ("CPSE", AppVersion::getVersionHint()); }
    static const String getCPS_E_ParameterName() { return "CPS|E"; }
    static const ParameterID getCPS_F_ParameterID() { return ParameterID ("CPSF", AppVersion::getVersionHint()); }
    static const String getCPS_F_ParameterName() { return "CPS|F"; }

    // lifecycle

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CPSModel)

public:
    // public methods
    CPSModel();
    ~CPSModel() override;
    shared_ptr<Tuning> getTuning() override;
    const shared_ptr<CPSTuningBase> getCPSTuning();
    unsigned long getNumScales();
    StringArray getScaleNames();
    unsigned long getNumberOfSeeds();

    // called only once: on construction of processor
    unique_ptr<AudioProcessorParameterGroup> createParams() override;

    String getGroupID() override;
    String getGroupName() override;
    String getSubgroupSeparator() override;
    ParameterID getDesignParameterID() override; // key for this design's Favorites array
    StringArray getFavoritesParameterIDs() override; // used for Favorites
    // called only once: when assigning _avpts
    void attachParameterListeners() override;
    void parameterChanged (const String& parameterID, float newValue) override;
    void updateProperties() override;

    // UI methods:
    // UI notifies host that param has changed, host updates state, host notifies model, model updates tuning, model sends notification to update UI.  This handles the cold start flow too.
    unsigned long uiGetSelectedScaleIndex();
    void uiSetScale (unsigned long index = 0);
    void uiSetA(float);
    void uiSetB(float);
    void uiSetC(float);
    void uiSetD(float);
    void uiSetE(float);
    void uiSetF(float);
    float uiGetA();
    float uiGetB();
    float uiGetC();
    float uiGetD();
    float uiGetE();
    float uiGetF();

protected:
    void detachParameterListeners() override;

private:
    // private members

    // master set
    Microtone_p _A = nullptr;
    Microtone_p _B = nullptr;
    Microtone_p _C = nullptr;
    Microtone_p _D = nullptr;
    Microtone_p _E = nullptr;
    Microtone_p _F = nullptr;
    unsigned long _numberOfSeeds {6};

    // current scale/tuning
    Scale _currentScale = Scale::CPS_4_2; // default hexany
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
    void _tuningChangedUpdateUI() override; // sends notification to UI Component to query current ViewModel
    void _updateScales(); // helper
};
