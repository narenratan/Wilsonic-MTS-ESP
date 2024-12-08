/*
  ==============================================================================

    CPS_5_3.h
    Created: 13 Aug 2021 8:36:29pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_4_2.h"
#include "CPS_4_3.h"
#include "Seed5.h"

class CPS_5_3 
: public Seed5
{
public:
    // lifecycle
    CPS_5_3(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E);
    CPS_5_3 (vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~CPS_5_3() override;

    // update
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
    bool canPaintTuning() override;

private:
    CPSMicrotone _mABC;
    CPSMicrotone _mABD;
    CPSMicrotone _mABE;
    CPSMicrotone _mACE;
    CPSMicrotone _mADE;
    CPSMicrotone _mBDE;
    CPSMicrotone _mCDE;
    CPSMicrotone _mACD;
    CPSMicrotone _mBCD;
    CPSMicrotone _mBCE;
    CPSMicrotone _halfACD; // used for drawing only, like _p0
    void _commonConstructorHelper(); // called only at construction

protected:
    void _allocateSubsets() override;

private:
    // subsets
    shared_ptr<CPS_4_2> _cps_4_2_0;
    shared_ptr<CPS_4_2> _cps_4_2_1;
    shared_ptr<CPS_4_2> _cps_4_2_2;
    shared_ptr<CPS_4_2> _cps_4_2_3;
    shared_ptr<CPS_4_2> _cps_4_2_4;
    shared_ptr<CPS_4_3> _cps_4_3_0;
    shared_ptr<CPS_4_3> _cps_4_3_1;
    shared_ptr<CPS_4_3> _cps_4_3_2;
    shared_ptr<CPS_4_3> _cps_4_3_3;
    shared_ptr<CPS_4_3> _cps_4_3_4;
};
