/*
  ==============================================================================

    EulerGenus_2.h
    Created: 31 Jul 2021 12:59:50pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_1_1.h"
#include "CPS_2_1.h"
#include "CPS_2_2.h"
#include "Seed2.h"
#include "Microtone.h"

// Row 3 of Figure 19 "A Pascal Triangle of Combination Set Lattices"
// D'Alessandro, Like A Hurricane, Erv Wilson, (c) 1989

class EulerGenus_2 : public Seed2
{
public:
    // lifecycle
    EulerGenus_2(Microtone_p A, Microtone_p B);
    EulerGenus_2(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~EulerGenus_2() override;

    // every cps of row 2 resulting from the master set
    const shared_ptr<CPS_2_1> getCps_2_1();
    const shared_ptr<CPS_2_2> getCps_2_2();

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

    // every cps of row 3 resulting from the master set
    shared_ptr<CPS_2_1> _cps_2_1;
    shared_ptr<CPS_2_2> _cps_2_2;
};

/*
 
------------------------------------------------------
CPS AT PASCALS TRIANGLE AT ROW: 2
------------------------------------------------------
Master Set: ['A', 'B']
(n,k):( 2 , 1 )
[('A',), ('B',)]
count: 2

 shared_ptr<CPS_2_1> _cps_2_1;

------------------------------------------------------

CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 2
(n,k):( 2 , 1 )
(m,j):( 1 , 1 )
count: 2
[[[{'A'}]], [[{'B'}]]]

------------------------------------------------------
CPS AT PASCALS TRIANGLE AT ROW: 2
------------------------------------------------------
Master Set: ['A', 'B']
(n,k):( 2 , 2 )
[('A', 'B')]
count: 1

 shared_ptr<CPS_2_2> _cps_2_2;

 ------------------------------------------------------


 */

