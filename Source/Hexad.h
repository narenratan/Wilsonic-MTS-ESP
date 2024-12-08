/*
  ==============================================================================

    Hexad.h
    Created: 20 Jun 2023 8:21:29pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "Seed6.h"
#include "Pentad.h"

class Hexad 
: public Seed6
{

public:
    // lifecycle
    Hexad (Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F, bool isHarmonic);
    Hexad (vector<Microtone_p> master_set, vector<Microtone_p> common_tones, bool isHarmonic);
    ~Hexad() override;

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
    // Microtones
    CPSMicrotone _mA;
    CPSMicrotone _mB;
    CPSMicrotone _mC;
    CPSMicrotone _mD;
    CPSMicrotone _mE;
    CPSMicrotone _mF;
    bool _isHarmonic = true;

    // subsets
    shared_ptr<Pentad> _pentad_0;
    shared_ptr<Pentad> _pentad_1;
    shared_ptr<Pentad> _pentad_2;
    shared_ptr<Pentad> _pentad_3;
    shared_ptr<Pentad> _pentad_4;
    shared_ptr<Pentad> _pentad_5;
    
    // called only at construction
    void _commonConstructorHelper();
};
