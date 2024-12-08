/*
  ==============================================================================

    Ogdoad.h
    Created: 20 Jun 2023 8:22:07pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "Seed8.h"
#include "Heptad.h"

class Ogdoad 
: public Seed8
{
public:
    // lifecycle
    Ogdoad(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F, Microtone_p G, Microtone_p H, bool isHarmonic);
    Ogdoad(vector<Microtone_p> master_set, vector<Microtone_p> common_tones, bool isHarmonic);
    ~Ogdoad() override;

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
    // backing microtones
    CPSMicrotone _mA;
    CPSMicrotone _mB;
    CPSMicrotone _mC;
    CPSMicrotone _mD;
    CPSMicrotone _mE;
    CPSMicrotone _mF;
    CPSMicrotone _mG;
    CPSMicrotone _mH;
    bool _isHarmonic = true;

    // subsets
    shared_ptr<Heptad> _heptad_0;
    shared_ptr<Heptad> _heptad_1;
    shared_ptr<Heptad> _heptad_2;
    shared_ptr<Heptad> _heptad_3;
    shared_ptr<Heptad> _heptad_4;
    shared_ptr<Heptad> _heptad_5;
    shared_ptr<Heptad> _heptad_6;
    shared_ptr<Heptad> _heptad_7;

    // called only at construction
    void _commonConstructorHelper();
};
