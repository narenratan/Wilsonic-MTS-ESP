/*
  ==============================================================================

    CPS_6_3.h
    Created: 13 Aug 2021 9:05:09pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_5_2.h"
#include "CPS_5_3.h"
#include "Seed6.h"
#include "Tuning_Include.h"

// EIKOSANY (6, 3) = 20 npo

class CPS_6_3 
: public Seed6
{
public:
    // lifecycle
    CPS_6_3(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F);
    CPS_6_3(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~CPS_6_3() override;

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
    CPSMicrotone _mABC;
    CPSMicrotone _mABD;
    CPSMicrotone _mABE;
    CPSMicrotone _mABF;
    CPSMicrotone _mACD;
    CPSMicrotone _mACE;
    CPSMicrotone _mACF;
    CPSMicrotone _mADE;
    CPSMicrotone _mADF;
    CPSMicrotone _mAEF;
    CPSMicrotone _mBCD;
    CPSMicrotone _mBCE;
    CPSMicrotone _mBCF;
    CPSMicrotone _mBDE;
    CPSMicrotone _mBDF;
    CPSMicrotone _mBEF;
    CPSMicrotone _mCDE;
    CPSMicrotone _mCDF;
    CPSMicrotone _mCEF;
    CPSMicrotone _mDEF;
    CPSMicrotone _half_ACF_CEF;
    void _commonConstructorHelper(); // called only at construction

    // subsets
    shared_ptr<CPS_5_2> _cps_5_2_0;
    shared_ptr<CPS_5_2> _cps_5_2_1;
    shared_ptr<CPS_5_2> _cps_5_2_2;
    shared_ptr<CPS_5_2> _cps_5_2_3;
    shared_ptr<CPS_5_2> _cps_5_2_4;
    shared_ptr<CPS_5_2> _cps_5_2_5;
    shared_ptr<CPS_5_3> _cps_5_3_0;
    shared_ptr<CPS_5_3> _cps_5_3_1;
    shared_ptr<CPS_5_3> _cps_5_3_2;
    shared_ptr<CPS_5_3> _cps_5_3_3;
    shared_ptr<CPS_5_3> _cps_5_3_4;
    shared_ptr<CPS_5_3> _cps_5_3_5;
};
