/*
  ==============================================================================

    Heptad.h
    Created: 20 Jun 2023 8:21:47pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "Seed7.h"
#include "Hexad.h"

class Heptad 
: public Seed7
{
public:
    // lifecycle
    Heptad(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F, Microtone_p G, bool isHarmonic);
    Heptad(vector<Microtone_p> master_set, vector<Microtone_p> common_tones, bool isHarmonic);
    ~Heptad() override;

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
    bool _isHarmonic = true;

    // subsets
    shared_ptr<Hexad> _hexad_0;
    shared_ptr<Hexad> _hexad_1;
    shared_ptr<Hexad> _hexad_2;
    shared_ptr<Hexad> _hexad_3;
    shared_ptr<Hexad> _hexad_4;
    shared_ptr<Hexad> _hexad_5;
    shared_ptr<Hexad> _hexad_6;

    // called only at construction
    void _commonConstructorHelper();
};
