/*
 ==============================================================================

 TriadicDiamond.h
 Created: 6 Jun 2023 4:31:06pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#pragma once


#include "Seed3.h"
#include "Triad.h"

// Triadic Diamond
// D'Alessandro, Like A Hurricane, Erv Wilson, (c) 1989

class TriadicDiamond 
: public Seed3
{
public:
    // lifecycle
    TriadicDiamond(Microtone_p A, Microtone_p B, Microtone_p C);
    TriadicDiamond(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~TriadicDiamond() override;

    // public member functions
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
    CPSMicrotone _C_B;
    CPSMicrotone _C_A;
    CPSMicrotone _A_B;
    CPSMicrotone _one;
    CPSMicrotone _B_A;
    CPSMicrotone _A_C;
    CPSMicrotone _B_C;
    shared_ptr<Triad> _harmonic_subset_0;
    shared_ptr<Triad> _harmonic_subset_1;
    shared_ptr<Triad> _harmonic_subset_2;
    shared_ptr<Triad> _subharmonic_subset_0;
    shared_ptr<Triad> _subharmonic_subset_1;
    shared_ptr<Triad> _subharmonic_subset_2;
    
    // private member functions
    void _allocateSubsets() override; // unused in EulerGenus
    void _commonConstructorHelper(); // called only at construction
};
