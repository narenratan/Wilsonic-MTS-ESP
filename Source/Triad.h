/*
  ==============================================================================

    Triad.h
    Created: 20 Jun 2023 8:20:29pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "Seed3.h"
#include "CPS_2_1.h"

class Triad 
: public Seed3
{
public:
    // lifecycle
    Triad(Microtone_p A, Microtone_p B, Microtone_p C, bool isHarmonic);
    Triad(vector<Microtone_p> master_set, vector<Microtone_p> common_tones, bool isHarmonic);
    ~Triad() override;

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

protected:
    void _allocateSubsets() override;

private:
    CPSMicrotone _mA;
    CPSMicrotone _mB;
    CPSMicrotone _mC;
    bool _isHarmonic = true;
    void _commonConstructorHelper(); // called only at construction

    // subsets
    shared_ptr<CPS_2_1> _cps_2_1_0;
    shared_ptr<CPS_2_1> _cps_2_1_1;
    shared_ptr<CPS_2_1> _cps_2_1_2;
};
