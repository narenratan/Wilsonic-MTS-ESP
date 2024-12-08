/*
  ==============================================================================

    CPS_2_1.h
    Created: 31 Jul 2021 1:00:22pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_1_1.h"
#include "Seed2.h"

class CPS_2_1 
: public Seed2
{
public:
    // lifecycle
    CPS_2_1(Microtone_p A, Microtone_p B);
    CPS_2_1(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~CPS_2_1() override;

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

private:
    void _commonConstructorHelper(); // called only at construction

protected:
    void _allocateSubsets() override;

private:
    CPSMicrotone _mA;
    CPSMicrotone _mB;
    // subsets
    shared_ptr<CPS_1_1> _cps_1_1_0;
    shared_ptr<CPS_1_1> _cps_1_1_1;
};
