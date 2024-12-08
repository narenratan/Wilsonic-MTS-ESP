/*
  ==============================================================================

    EulerGenus_5.h
    Created: 10 Aug 2021 10:35:40pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_5_1.h"
#include "CPS_5_2.h"
#include "CPS_5_3.h"
#include "CPS_5_4.h"
#include "CPS_5_5.h"
#include "Seed5.h"
#include "Microtone.h"

// Row 6 of Figure 19 "A Pascal Triangle of Combination Set Lattices"
// D'Alessandro, Like A Hurricane, Erv Wilson, (c) 1989

class EulerGenus_5 : public Seed5
{
public:
    // lifecycle
    EulerGenus_5(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E);
    EulerGenus_5(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~EulerGenus_5() override;

    // every cps of row 6 resulting from the master set
    const shared_ptr<CPS_5_1> getCps_5_1();
    const shared_ptr<CPS_5_2> getCps_5_2();
    const shared_ptr<CPS_5_3> getCps_5_3();
    const shared_ptr<CPS_5_4> getCps_5_4();
    const shared_ptr<CPS_5_5> getCps_5_5();

    //
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

    // every cps of row 6 resulting from the master set
    shared_ptr<CPS_5_1> _cps_5_1;
    shared_ptr<CPS_5_2> _cps_5_2;
    shared_ptr<CPS_5_3> _cps_5_3;
    shared_ptr<CPS_5_4> _cps_5_4;
    shared_ptr<CPS_5_5> _cps_5_5;
};


/*

------------------------------------------------------
CPS AT PASCALS TRIANGLE AT ROW: 5
------------------------------------------------------
Master Set: ['A', 'B', 'C', 'D', 'E']
(n,k):( 5 , 1 )
[('A',), ('B',), ('C',), ('D',), ('E',)]
count: 5
------------------------------------------------------

CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 5
(n,k):( 5 , 1 )
(m,j):( 4 , 1 )
count: 5
[[[{'D'}, {'B'}, {'C'}, {'A'}]], [[{'B'}, {'C'}, {'A'}, {'E'}]], [[{'D'}, {'B'}, {'A'}, {'E'}]], [[{'D'}, {'C'}, {'A'}, {'E'}]], [[{'D'}, {'B'}, {'C'}, {'E'}]]]




------------------------------------------------------
CPS AT PASCALS TRIANGLE AT ROW: 5
------------------------------------------------------
Master Set: ['A', 'B', 'C', 'D', 'E']
(n,k):( 5 , 2 )
[('A', 'B'), ('A', 'C'), ('A', 'D'), ('A', 'E'), ('B', 'C'), ('B', 'D'), ('B', 'E'), ('C', 'D'), ('C', 'E'), ('D', 'E')]
count: 10
------------------------------------------------------

CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 5
(n,k):( 5 , 2 )
(m,j):( 4 , 1 )
count: 5
[[[{'D', 'E'}, {'B', 'E'}, {'C', 'E'}, {'A', 'E'}]], [[{'D', 'B'}, {'D', 'C'}, {'D', 'A'}, {'D', 'E'}]], [[{'D', 'C'}, {'B', 'C'}, {'C', 'A'}, {'C', 'E'}]], [[{'D', 'B'}, {'B', 'C'}, {'B', 'A'}, {'B', 'E'}]], [[{'D', 'A'}, {'B', 'A'}, {'C', 'A'}, {'A', 'E'}]]]
CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 5
(n,k):( 5 , 2 )
(m,j):( 4 , 2 )
count: 5
[[[{'D', 'B'}, {'D', 'C'}, {'D', 'A'}, {'B', 'C'}, {'B', 'A'}, {'C', 'A'}]], [[{'B', 'C'}, {'B', 'A'}, {'B', 'E'}, {'C', 'A'}, {'C', 'E'}, {'A', 'E'}]], [[{'D', 'B'}, {'D', 'A'}, {'D', 'E'}, {'B', 'A'}, {'B', 'E'}, {'A', 'E'}]], [[{'D', 'C'}, {'D', 'A'}, {'D', 'E'}, {'C', 'A'}, {'C', 'E'}, {'A', 'E'}]], [[{'D', 'B'}, {'D', 'C'}, {'D', 'E'}, {'B', 'C'}, {'B', 'E'}, {'C', 'E'}]]]






------------------------------------------------------
CPS AT PASCALS TRIANGLE AT ROW: 5
------------------------------------------------------
Master Set: ['A', 'B', 'C', 'D', 'E']
(n,k):( 5 , 3 )
[('A', 'B', 'C'), ('A', 'B', 'D'), ('A', 'B', 'E'), ('A', 'C', 'D'), ('A', 'C', 'E'), ('A', 'D', 'E'), ('B', 'C', 'D'), ('B', 'C', 'E'), ('B', 'D', 'E'), ('C', 'D', 'E')]
count: 10
------------------------------------------------------

CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 5
(n,k):( 5 , 3 )
(m,j):( 4 , 1 )
CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 5
(n,k):( 5 , 3 )
(m,j):( 4 , 2 )
count: 5
[[[{'D', 'B', 'E'}, {'D', 'C', 'E'}, {'D', 'A', 'E'}, {'B', 'C', 'E'}, {'B', 'A', 'E'}, {'C', 'A', 'E'}]], [[{'D', 'B', 'C'}, {'D', 'B', 'A'}, {'D', 'B', 'E'}, {'D', 'C', 'A'}, {'D', 'C', 'E'}, {'D', 'A', 'E'}]], [[{'D', 'B', 'C'}, {'D', 'C', 'A'}, {'D', 'C', 'E'}, {'B', 'C', 'A'}, {'B', 'C', 'E'}, {'C', 'A', 'E'}]], [[{'D', 'B', 'C'}, {'D', 'B', 'A'}, {'D', 'B', 'E'}, {'B', 'C', 'A'}, {'B', 'C', 'E'}, {'B', 'A', 'E'}]], [[{'D', 'B', 'A'}, {'D', 'C', 'A'}, {'D', 'A', 'E'}, {'B', 'C', 'A'}, {'B', 'A', 'E'}, {'C', 'A', 'E'}]]]
CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 5
(n,k):( 5 , 3 )
(m,j):( 4 , 3 )
count: 5
[[[{'D', 'B', 'C'}, {'D', 'B', 'A'}, {'D', 'C', 'A'}, {'B', 'C', 'A'}]], [[{'B', 'C', 'A'}, {'B', 'C', 'E'}, {'B', 'A', 'E'}, {'C', 'A', 'E'}]], [[{'D', 'B', 'A'}, {'D', 'B', 'E'}, {'D', 'A', 'E'}, {'B', 'A', 'E'}]], [[{'D', 'C', 'A'}, {'D', 'C', 'E'}, {'D', 'A', 'E'}, {'C', 'A', 'E'}]], [[{'D', 'B', 'C'}, {'D', 'B', 'E'}, {'D', 'C', 'E'}, {'B', 'C', 'E'}]]]






 
------------------------------------------------------
CPS AT PASCALS TRIANGLE AT ROW: 5
------------------------------------------------------
Master Set: ['A', 'B', 'C', 'D', 'E']
(n,k):( 5 , 4 )
[('A', 'B', 'C', 'D'), ('A', 'B', 'C', 'E'), ('A', 'B', 'D', 'E'), ('A', 'C', 'D', 'E'), ('B', 'C', 'D', 'E')]
count: 5
------------------------------------------------------

CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 5
(n,k):( 5 , 4 )
(m,j):( 4 , 1 )
CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 5
(n,k):( 5 , 4 )
(m,j):( 4 , 2 )
CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 5
(n,k):( 5 , 4 )
(m,j):( 4 , 3 )
count: 5
[[[{'D', 'B', 'C', 'E'}, {'D', 'B', 'A', 'E'}, {'D', 'C', 'A', 'E'}, {'B', 'C', 'A', 'E'}]], [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'C', 'E'}, {'D', 'B', 'A', 'E'}, {'D', 'C', 'A', 'E'}]], [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'C', 'E'}, {'D', 'C', 'A', 'E'}, {'B', 'C', 'A', 'E'}]], [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'C', 'E'}, {'D', 'B', 'A', 'E'}, {'B', 'C', 'A', 'E'}]], [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'A', 'E'}, {'D', 'C', 'A', 'E'}, {'B', 'C', 'A', 'E'}]]]
CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 5
(n,k):( 5 , 4 )
(m,j):( 4 , 4 )
count: 5
[[[{'D', 'B', 'C', 'A'}]], [[{'B', 'C', 'A', 'E'}]], [[{'D', 'B', 'A', 'E'}]], [[{'D', 'C', 'A', 'E'}]], [[{'D', 'B', 'C', 'E'}]]]







------------------------------------------------------
CPS AT PASCALS TRIANGLE AT ROW: 5
------------------------------------------------------
Master Set: ['A', 'B', 'C', 'D', 'E']
(n,k):( 5 , 5 )
[('A', 'B', 'C', 'D', 'E')]
count: 1
------------------------------------------------------

*/
