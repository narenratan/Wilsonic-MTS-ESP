/*
  ==============================================================================

    CPS_6_4.h
    Created: 13 Aug 2021 9:05:38pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_5_3.h"
#include "CPS_5_4.h"
#include "Seed6.h"

class CPS_6_4 
: public Seed6
{
public:
    // lifecycle
    CPS_6_4 (Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F);
    CPS_6_4 (vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~CPS_6_4() override;

    // update
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
    CPSMicrotone _mABCD;
    CPSMicrotone _mABCE;
    CPSMicrotone _mABCF;
    CPSMicrotone _mABDE;
    CPSMicrotone _mABDF;
    CPSMicrotone _mABEF;
    CPSMicrotone _mACDE;
    CPSMicrotone _mACDF;
    CPSMicrotone _mACEF;
    CPSMicrotone _mADEF;
    CPSMicrotone _mBCDE;
    CPSMicrotone _mBCDF;
    CPSMicrotone _mBCEF;
    CPSMicrotone _mBDEF;
    CPSMicrotone _mCDEF;

    // subsets
    shared_ptr<CPS_5_3> _cps_5_3_0;
    shared_ptr<CPS_5_3> _cps_5_3_1;
    shared_ptr<CPS_5_3> _cps_5_3_2;
    shared_ptr<CPS_5_3> _cps_5_3_3;
    shared_ptr<CPS_5_3> _cps_5_3_4;
    shared_ptr<CPS_5_3> _cps_5_3_5;
    shared_ptr<CPS_5_4> _cps_5_4_0;
    shared_ptr<CPS_5_4> _cps_5_4_1;
    shared_ptr<CPS_5_4> _cps_5_4_2;
    shared_ptr<CPS_5_4> _cps_5_4_3;
    shared_ptr<CPS_5_4> _cps_5_4_4;
    shared_ptr<CPS_5_4> _cps_5_4_5;
    
    void _commonConstructorHelper(); // called only at construction
};
