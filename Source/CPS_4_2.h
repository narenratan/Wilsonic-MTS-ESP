/*
  ==============================================================================

    CPS_4_2.h
    Created: 13 Aug 2021 8:10:44pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_3_1.h"
#include "CPS_3_2.h"
#include "Seed4.h"

class CPS_4_2 
: public Seed4
{
public:
    // lifecycle
    CPS_4_2(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D);
    CPS_4_2(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~CPS_4_2() override;

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

private:
    void _allocateSubsets() override;

    // microtones + points for drawing
    CPSMicrotone _mAB;
    CPSMicrotone _mAC;
    CPSMicrotone _mAD;
    CPSMicrotone _mBC;
    CPSMicrotone _mBD;
    CPSMicrotone _mCD;

    // subsets
    shared_ptr<CPS_3_1> _cps_3_1_0;
    shared_ptr<CPS_3_1> _cps_3_1_1;
    shared_ptr<CPS_3_1> _cps_3_1_2;
    shared_ptr<CPS_3_1> _cps_3_1_3;
    shared_ptr<CPS_3_2> _cps_3_2_0;
    shared_ptr<CPS_3_2> _cps_3_2_1;
    shared_ptr<CPS_3_2> _cps_3_2_2;
    shared_ptr<CPS_3_2> _cps_3_2_3;
    void _commonConstructorHelper(); // called only at construction
};
