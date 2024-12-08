/*
  ==============================================================================

    Pentad.h
    Created: 20 Jun 2023 8:21:12pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "Seed5.h"
#include "Tetrad.h"

class Pentad 
: public Seed5
{
    // lifecycle
public:
    Pentad(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, bool isHarmonic);
    Pentad(vector<Microtone_p> master_set, vector<Microtone_p> common_tones, bool isHarmonic);
    ~Pentad() override;

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
    CPSMicrotone _mD;
    CPSMicrotone _mE;
    bool _isHarmonic = true;
    shared_ptr<Tetrad> _tetrad_0;
    shared_ptr<Tetrad> _tetrad_1;
    shared_ptr<Tetrad> _tetrad_2;
    shared_ptr<Tetrad> _tetrad_3;
    shared_ptr<Tetrad> _tetrad_4;

    void _commonConstructorHelper(); // called only at construction
};
