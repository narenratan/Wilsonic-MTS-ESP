/*
  ==============================================================================

    CPS_2_2.h
    Created: 8 Aug 2021 9:41:58am
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "Seed2.h"

class CPS_2_2 
: public Seed2
{
public:
    // lifecycle
    CPS_2_2(Microtone_p A, Microtone_p B);
    CPS_2_2(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~CPS_2_2() override;

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
    void _commonConstructorHelper(); // called only at construction
};
