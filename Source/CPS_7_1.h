/*
  ==============================================================================

    CPS_7_1.h
    Created: 7 Jun 2023 3:55:13pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_6_1.h"
#include "Seed7.h"

class CPS_7_1 
: public Seed7
{
public:
    // lifecycle
    CPS_7_1(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F, Microtone_p G);
    CPS_7_1(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~CPS_7_1() override;

    void update() override;
    bool canPaintTuning() override;
    bool isEulerGenusTuningType() override;

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

protected:
    void _allocateSubsets() override;

private:
    // Microtones
    CPSMicrotone _mA;
    CPSMicrotone _mB;
    CPSMicrotone _mC;
    CPSMicrotone _mD;
    CPSMicrotone _mE;
    CPSMicrotone _mF;
    CPSMicrotone _mG;

    // subsets
    shared_ptr<CPS_6_1> _cps_6_1_0;
    shared_ptr<CPS_6_1> _cps_6_1_1;
    shared_ptr<CPS_6_1> _cps_6_1_2;
    shared_ptr<CPS_6_1> _cps_6_1_3;
    shared_ptr<CPS_6_1> _cps_6_1_4;
    shared_ptr<CPS_6_1> _cps_6_1_5;
    shared_ptr<CPS_6_1> _cps_6_1_6;

    // called only at construction
    void _commonConstructorHelper();
};
