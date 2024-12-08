/*
  ==============================================================================

    EulerGenus_3.h
    Created: 10 Aug 2021 10:33:53pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_3_1.h"
#include "CPS_3_2.h"
#include "CPS_3_3.h"
#include "Seed3.h"
#include "Microtone.h"

// Row 4 of Figure 19 "A Pascal Triangle of Combination Set Lattices"
// D'Alessandro, Like A Hurricane, Erv Wilson, (c) 1989

class EulerGenus_3 : public Seed3
{
public:
    // lifecycle
    EulerGenus_3(Microtone_p A, Microtone_p B, Microtone_p C);
    EulerGenus_3(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~EulerGenus_3() override;

    // the 3 cps of row 4
    const shared_ptr<CPS_3_1> getCps_3_1();
    const shared_ptr<CPS_3_2> getCps_3_2();
    const shared_ptr<CPS_3_3> getCps_3_3();

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

    // every cps of row 4 resulting from the master set
    shared_ptr<CPS_3_1> _cps_3_1;
    shared_ptr<CPS_3_2> _cps_3_2;
    shared_ptr<CPS_3_3> _cps_3_3;
};



/*
------------------------------------------------------
CPS AT PASCALS TRIANGLE AT ROW: 3
------------------------------------------------------
Master Set: ['A', 'B', 'C']
(n,k):( 3 , 1 )
[('A',), ('B',), ('C',)]
count: 3
------------------------------------------------------

CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 3
(n,k):( 3 , 1 )
(m,j):( 2 , 1 )
count: 3
[[[{'B'}, {'A'}]], [[{'C'}, {'A'}]], [[{'B'}, {'C'}]]]

------------------------------------------------------
CPS AT PASCALS TRIANGLE AT ROW: 3
------------------------------------------------------
Master Set: ['A', 'B', 'C']
(n,k):( 3 , 2 )
[('A', 'B'), ('A', 'C'), ('B', 'C')]
count: 3
------------------------------------------------------

CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 3
(n,k):( 3 , 2 )
(m,j):( 2 , 1 )
count: 3
[[[{'B', 'C'}, {'C', 'A'}]], [[{'B', 'C'}, {'B', 'A'}]], [[{'B', 'A'}, {'C', 'A'}]]]
CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 3
(n,k):( 3 , 2 )
(m,j):( 2 , 2 )
count: 3
[[[{'B', 'A'}]], [[{'C', 'A'}]], [[{'B', 'C'}]]]

------------------------------------------------------
CPS AT PASCALS TRIANGLE AT ROW: 3
------------------------------------------------------
Master Set: ['A', 'B', 'C']
(n,k):( 3 , 3 )
[('A', 'B', 'C')]
count: 1
------------------------------------------------------

*/
