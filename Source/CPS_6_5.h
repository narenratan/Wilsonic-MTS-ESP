/*
  ==============================================================================

    CPS_6_5.h
    Created: 13 Aug 2021 9:06:00pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_5_5.h"
#include "CPS_5_4.h"
#include "Seed6.h"

// HEXANY (6, 5) = 6 npo

class CPS_6_5 
: public Seed6
{
public:
    // lifecycle
    CPS_6_5 (Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F);
    CPS_6_5 (vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~CPS_6_5() override;

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
    CPSMicrotone _mABCDE;
    CPSMicrotone _mABCDF;
    CPSMicrotone _mABCEF;
    CPSMicrotone _mABDEF;
    CPSMicrotone _mACDEF;
    CPSMicrotone _mBCDEF;

    // subsets
    shared_ptr<CPS_5_4> _cps_5_4_0;
    shared_ptr<CPS_5_4> _cps_5_4_1;
    shared_ptr<CPS_5_4> _cps_5_4_2;
    shared_ptr<CPS_5_4> _cps_5_4_3;
    shared_ptr<CPS_5_4> _cps_5_4_4;
    shared_ptr<CPS_5_4> _cps_5_4_5;
    shared_ptr<CPS_5_5> _cps_5_5_0;
    shared_ptr<CPS_5_5> _cps_5_5_1;
    shared_ptr<CPS_5_5> _cps_5_5_2;
    shared_ptr<CPS_5_5> _cps_5_5_3;
    shared_ptr<CPS_5_5> _cps_5_5_4;
    shared_ptr<CPS_5_5> _cps_5_5_5;
    
    void _commonConstructorHelper(); // called only at construction
};
