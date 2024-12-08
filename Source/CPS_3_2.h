/*
  ==============================================================================

    CPS_3_2.h
    Created: 10 Aug 2021 10:32:06pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_2_1.h"
#include "CPS_2_2.h"
#include "Seed3.h"

class CPS_3_2 
: public Seed3
{
public:
    // lifecycle
    CPS_3_2(Microtone_p A, Microtone_p B, Microtone_p C);
    CPS_3_2(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~CPS_3_2() override;

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
    CPSMicrotone _mAB;
    CPSMicrotone _mAC;
    CPSMicrotone _mBC;

    // subsets
    shared_ptr<CPS_2_1> _cps_2_1_0;
    shared_ptr<CPS_2_1> _cps_2_1_1;
    shared_ptr<CPS_2_1> _cps_2_1_2;
    shared_ptr<CPS_2_2> _cps_2_2_0;
    shared_ptr<CPS_2_2> _cps_2_2_1;
    shared_ptr<CPS_2_2> _cps_2_2_2;

    // private methods
    void _commonConstructorHelper(); // called only at construction
};
