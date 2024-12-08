/*
  ==============================================================================

    CPS_6_6.h
    Created: 13 Aug 2021 9:06:12pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "Seed6.h"

class CPS_6_6 
: public Seed6
{
public:
    // lifecycle
    CPS_6_6(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F);
    CPS_6_6(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~CPS_6_6() override;

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
    CPSMicrotone _mABCDEF;
    void _commonConstructorHelper(); // called only at construction
};
