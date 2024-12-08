/*
  ==============================================================================

    CPS_4_1.h
    Created: 13 Aug 2021 8:10:12pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_3_1.h"
#include "Seed4.h"

class CPS_4_1 
: public Seed4
{
public:
    // lifecycle
    CPS_4_1(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D);
    CPS_4_1(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~CPS_4_1() override;
    
public:
    void update() override;
    bool canPaintTuning() override;
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
    CPSMicrotone _mA;
    CPSMicrotone _mB;
    CPSMicrotone _mC;
    CPSMicrotone _mD;
    shared_ptr<CPS_3_1> _cps_3_1_0;
    shared_ptr<CPS_3_1> _cps_3_1_1;
    shared_ptr<CPS_3_1> _cps_3_1_2;
    shared_ptr<CPS_3_1> _cps_3_1_3;
    void _commonConstructorHelper(); // called only at construction
};
