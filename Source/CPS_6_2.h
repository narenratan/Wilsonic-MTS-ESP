/*
  ==============================================================================

    CPS_6_2.h
    Created: 13 Aug 2021 8:37:35pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_5_1.h"
#include "CPS_5_2.h"
#include "Seed6.h"

class CPS_6_2 
: public Seed6
{
public:
    // lifecycle
    CPS_6_2(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F);
    CPS_6_2(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~CPS_6_2() override;

    // udpate
    void update() override;
    bool canPaintTuning() override;

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
    CPSMicrotone _mAF;
    CPSMicrotone _mBC;
    CPSMicrotone _mBD;
    CPSMicrotone _mBE;
    CPSMicrotone _mBF;
    CPSMicrotone _mCD;
    CPSMicrotone _mCE;
    CPSMicrotone _mCF;
    CPSMicrotone _mDE;
    CPSMicrotone _mDF;
    CPSMicrotone _mEF;
    void _commonConstructorHelper(); // called only at construction

    // subsets
    shared_ptr<CPS_5_1> _cps_5_1_0;
    shared_ptr<CPS_5_1> _cps_5_1_1;
    shared_ptr<CPS_5_1> _cps_5_1_2;
    shared_ptr<CPS_5_1> _cps_5_1_3;
    shared_ptr<CPS_5_1> _cps_5_1_4;
    shared_ptr<CPS_5_1> _cps_5_1_5;
    shared_ptr<CPS_5_2> _cps_5_2_0;
    shared_ptr<CPS_5_2> _cps_5_2_1;
    shared_ptr<CPS_5_2> _cps_5_2_2;
    shared_ptr<CPS_5_2> _cps_5_2_3;
    shared_ptr<CPS_5_2> _cps_5_2_4;
    shared_ptr<CPS_5_2> _cps_5_2_5;
};
