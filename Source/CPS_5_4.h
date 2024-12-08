/*
  ==============================================================================

    CPS_5_4.h
    Created: 13 Aug 2021 8:35:04pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_4_3.h"
#include "CPS_4_4.h"
#include "Seed5.h"

class CPS_5_4 
: public Seed5
{
public:
    // lifecycle
    CPS_5_4(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E);
    CPS_5_4(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~CPS_5_4() override;

    // update
    void update() override;
    bool canPaintTuning() override;

public:
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
    CPSMicrotone _mABDE;
    CPSMicrotone _mACDE;
    CPSMicrotone _mBCDE;

    // subsets
    shared_ptr<CPS_4_3> _cps_4_3_0;
    shared_ptr<CPS_4_3> _cps_4_3_1;
    shared_ptr<CPS_4_3> _cps_4_3_2;
    shared_ptr<CPS_4_3> _cps_4_3_3;
    shared_ptr<CPS_4_3> _cps_4_3_4;
    shared_ptr<CPS_4_4> _cps_4_4_0;
    shared_ptr<CPS_4_4> _cps_4_4_1;
    shared_ptr<CPS_4_4> _cps_4_4_2;
    shared_ptr<CPS_4_4> _cps_4_4_3;
    shared_ptr<CPS_4_4> _cps_4_4_4;
    
    void _commonConstructorHelper(); // called only at construction
};
