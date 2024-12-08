/*
  ==============================================================================

    CPS_5_2.h
    Created: 13 Aug 2021 8:33:14pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_4_1.h"
#include "CPS_4_2.h"
#include "Seed5.h"

class CPS_5_2 
: public Seed5
{
public:
    // lifecycle
    CPS_5_2(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E);
    CPS_5_2(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~CPS_5_2() override;

    // public
    bool canPaintTuning() override;
    void update() override;

    // select subsets
    void selectS0_0() override;
    void selectS0_1() override;
    void selectS0_2() override;
    void selectS0_3() override;
    void selectS0_4() override;
    void selectS0_5() override;
    void selectS0_6() override;
    void selectS0_7() override;
    void selectS1_0() override;
    void selectS1_1() override;
    void selectS1_2() override;
    void selectS1_3() override;
    void selectS1_4() override;
    void selectS1_5() override;
    void selectS1_6() override;
    void selectS1_7() override;
    bool isEulerGenusTuningType() override;

protected:
    void _allocateSubsets() override;

private:
    CPSMicrotone _mAB;
    CPSMicrotone _mAC;
    CPSMicrotone _mAD;
    CPSMicrotone _mAE;
    CPSMicrotone _mBC;
    CPSMicrotone _mBD;
    CPSMicrotone _mBE;
    CPSMicrotone _mCD;
    CPSMicrotone _mCE;
    CPSMicrotone _mDE;
    CPSMicrotone _half_CE_AC; // for drawing only, like _p0
    shared_ptr<CPS_4_1> _cps_4_1_0;
    shared_ptr<CPS_4_1> _cps_4_1_1;
    shared_ptr<CPS_4_1> _cps_4_1_2;
    shared_ptr<CPS_4_1> _cps_4_1_3;
    shared_ptr<CPS_4_1> _cps_4_1_4;
    shared_ptr<CPS_4_2> _cps_4_2_0;
    shared_ptr<CPS_4_2> _cps_4_2_1;
    shared_ptr<CPS_4_2> _cps_4_2_2;
    shared_ptr<CPS_4_2> _cps_4_2_3;
    shared_ptr<CPS_4_2> _cps_4_2_4;
    void _commonConstructorHelper(); // called only at construction
};
