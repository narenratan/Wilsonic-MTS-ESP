/*
  ==============================================================================

    Mandala.h
    Created: 23 May 2022 1:05:34pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_4_1.h"
#include "Seed4.h"

// Mandala
// D'Alessandro, Like A Hurricane, Erv Wilson, (c) 1989

class Mandala 
: public Seed4
{
public:
    // lifecycle
    Mandala(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D);
    Mandala(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~Mandala() noexcept override = default;

    // drawing
    void update() override;
    bool canPaintTuning() override;
    const string getShortDescriptionText();
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

private:
    CPSMicrotone _C_squared;
    CPSMicrotone _B2;
    CPSMicrotone _ABD_C;
    CPSMicrotone _BD;
    CPSMicrotone _BCD_A;
    CPSMicrotone _AB;
    CPSMicrotone _BC;
    CPSMicrotone _D2;
    CPSMicrotone _ABC_D;
    CPSMicrotone _AD;
    CPSMicrotone _CD;
    CPSMicrotone _A2;
    CPSMicrotone _AC;
    CPSMicrotone _ACD_B;
    CPSMicrotone _ptCenter; // not part of scale, used for drawing
    shared_ptr<CPS_4_1> _harmonic_subset_0;
    shared_ptr<CPS_4_1> _harmonic_subset_1;
    shared_ptr<CPS_4_1> _harmonic_subset_2;
    shared_ptr<CPS_4_1> _harmonic_subset_3;
    shared_ptr<CPS_4_1> _subharmonic_subset_0;
    shared_ptr<CPS_4_1> _subharmonic_subset_1;
    shared_ptr<CPS_4_1> _subharmonic_subset_2;
    shared_ptr<CPS_4_1> _subharmonic_subset_3;
    void _allocateSubsets() override;
    void _commonConstructorHelper(); // called only at construction
};
