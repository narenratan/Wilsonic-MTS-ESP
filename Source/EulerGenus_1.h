/*
  ==============================================================================

    EulerGenus_1.h
    Created: 25 Jul 2021 5:23:19pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_1_1.h"
#include "Seed1.h"

// Row 2 of Figure 19 "A Pascal Triangle of Combination Set Lattices"
// D'Alessandro, Like A Hurricane, Erv Wilson, (c) 1989

class EulerGenus_1 : public Seed1
{
public:
    // lifecycle
    EulerGenus_1(Microtone_p A);
    EulerGenus_1(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~EulerGenus_1() override;

    // every cps of row 2 resulting from the master set
    const shared_ptr<CPS_1_1> getCps_1_1();

    // description
    const string getShortDescriptionText();

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

private:
    // update
    void update() override;
    void _allocateSubsets() override; // unused in EulerGenus

    // every cps of row 2 resulting from the master set
    shared_ptr<CPS_1_1> _cps_1_1;
};


/*

------------------------------------------------------
CPS AT PASCALS TRIANGLE AT ROW: 1
------------------------------------------------------
Master Set: ['A']
(n,k):( 1 , 1 )
[('A',)]
count: 1
------------------------------------------------------

*/
