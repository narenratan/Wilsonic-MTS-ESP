/*
  ==============================================================================

    CPS_1_1.h
    Created: 29 Jul 2021 9:11:39pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "Seed1.h"

class CPS_1_1 
: public Seed1
{
public:
    // lifecycle
    CPS_1_1(Microtone_p A);
    CPS_1_1(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    bool canPaintTuning() override;

private:
    CPSMicrotone _mA;
    void _commonConstructorHelper(); // called only at construction

public:
    ~CPS_1_1() override;

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

protected:
    void _allocateSubsets() override;
};
