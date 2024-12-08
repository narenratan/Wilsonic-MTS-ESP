/*
  ==============================================================================

    Tetrad.h
    Created: 20 Jun 2023 8:20:46pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "Seed4.h"
#include "Triad.h"

class Tetrad 
: public Seed4
{
public:
    // lifecycle
    Tetrad(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, bool isHarmonic);
    Tetrad(vector<Microtone_p> master_set, vector<Microtone_p> common_tones, bool isHarmonic);
    ~Tetrad() override;

    bool canPaintTuning() override;

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

private:
    CPSMicrotone _mA;
    CPSMicrotone _mB;
    CPSMicrotone _mC;
    CPSMicrotone _mD;
    bool _isHarmonic = true;
    shared_ptr<Triad> _triad_0;
    shared_ptr<Triad> _triad_1;
    shared_ptr<Triad> _triad_2;
    shared_ptr<Triad> _triad_3;
    void _commonConstructorHelper(); // called only at construction
};
