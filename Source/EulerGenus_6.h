/*
  ==============================================================================

    EulerGenus_6.h
    Created: 10 Aug 2021 10:35:56pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_6_1.h"
#include "CPS_6_2.h"
#include "CPS_6_3.h"
#include "CPS_6_4.h"
#include "CPS_6_5.h"
#include "CPS_6_6.h"
#include "Seed6.h"
#include "Microtone.h"
#include "Tuning_Include.h"

// Row 7 of Figure 19 "A Pascal Triangle of Combination Set Lattices"
// D'Alessandro, Like A Hurricane, Erv Wilson, (c) 1989

class EulerGenus_6 : public Seed6
{
public:
    // lifecycle
    EulerGenus_6(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F);
    EulerGenus_6(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~EulerGenus_6() override;

    // every cps of row 7 resulting from the master set
    const shared_ptr<CPS_6_1> getCps_6_1();
    const shared_ptr<CPS_6_2> getCps_6_2();
    const shared_ptr<CPS_6_3> getCps_6_3();
    const shared_ptr<CPS_6_4> getCps_6_4();
    const shared_ptr<CPS_6_5> getCps_6_5();
    const shared_ptr<CPS_6_6> getCps_6_6();

    // member functions
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

    // every cps of row 7 resulting from the master set
    shared_ptr<CPS_6_1> _cps_6_1;
    shared_ptr<CPS_6_2> _cps_6_2;
    shared_ptr<CPS_6_3> _cps_6_3;
    shared_ptr<CPS_6_4> _cps_6_4;
    shared_ptr<CPS_6_5> _cps_6_5;
    shared_ptr<CPS_6_6> _cps_6_6;
};








/*

 ------------------------------------------------------
 CPS AT PASCALS TRIANGLE AT ROW: 6
 ------------------------------------------------------
 Master Set: ['A', 'B', 'C', 'D', 'E', 'F']
 (n,k):( 6 , 1 )
 [('A',), ('B',), ('C',), ('D',), ('E',), ('F',)]
 count: 6
 ------------------------------------------------------

 CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
 (n,k):( 6 , 1 )
 (m,j):( 5 , 1 )
 count: 6
 [[[{'D'}, {'B'}, {'C'}, {'A'}, {'E'}]], [[{'D'}, {'B'}, {'C'}, {'A'}, {'F'}]], [[{'B'}, {'C'}, {'A'}, {'F'}, {'E'}]], [[{'D'}, {'B'}, {'A'}, {'F'}, {'E'}]], [[{'D'}, {'C'}, {'A'}, {'F'}, {'E'}]], [[{'D'}, {'B'}, {'C'}, {'F'}, {'E'}]]]





 ------------------------------------------------------
 CPS AT PASCALS TRIANGLE AT ROW: 6
 ------------------------------------------------------
 Master Set: ['A', 'B', 'C', 'D', 'E', 'F']
 (n,k):( 6 , 2 )
 [('A', 'B'), ('A', 'C'), ('A', 'D'), ('A', 'E'), ('A', 'F'), ('B', 'C'), ('B', 'D'), ('B', 'E'), ('B', 'F'), ('C', 'D'), ('C', 'E'), ('C', 'F'), ('D', 'E'), ('D', 'F'), ('E', 'F')]
 count: 15
 ------------------------------------------------------

 CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
 (n,k):( 6 , 2 )
 (m,j):( 5 , 1 )
 count: 6
 [[[{'D', 'F'}, {'B', 'F'}, {'C', 'F'}, {'F', 'A'}, {'F', 'E'}]], [[{'D', 'E'}, {'B', 'E'}, {'C', 'E'}, {'A', 'E'}, {'F', 'E'}]], [[{'D', 'B'}, {'D', 'C'}, {'D', 'A'}, {'D', 'F'}, {'D', 'E'}]], [[{'D', 'C'}, {'B', 'C'}, {'C', 'A'}, {'C', 'F'}, {'C', 'E'}]], [[{'D', 'B'}, {'B', 'C'}, {'B', 'A'}, {'B', 'F'}, {'B', 'E'}]], [[{'D', 'A'}, {'B', 'A'}, {'C', 'A'}, {'F', 'A'}, {'A', 'E'}]]]
 CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
 (n,k):( 6 , 2 )
 (m,j):( 5 , 2 )
 count: 6
 [[[{'D', 'B'}, {'D', 'C'}, {'D', 'A'}, {'D', 'E'}, {'B', 'C'}, {'B', 'A'}, {'B', 'E'}, {'C', 'A'}, {'C', 'E'}, {'A', 'E'}]], [[{'D', 'B'}, {'D', 'C'}, {'D', 'A'}, {'D', 'F'}, {'B', 'C'}, {'B', 'A'}, {'B', 'F'}, {'C', 'A'}, {'C', 'F'}, {'F', 'A'}]], [[{'B', 'C'}, {'B', 'A'}, {'B', 'F'}, {'B', 'E'}, {'C', 'A'}, {'C', 'F'}, {'C', 'E'}, {'F', 'A'}, {'A', 'E'}, {'F', 'E'}]], [[{'D', 'B'}, {'D', 'A'}, {'D', 'F'}, {'D', 'E'}, {'B', 'A'}, {'B', 'F'}, {'B', 'E'}, {'F', 'A'}, {'A', 'E'}, {'F', 'E'}]], [[{'D', 'C'}, {'D', 'A'}, {'D', 'F'}, {'D', 'E'}, {'C', 'A'}, {'C', 'F'}, {'C', 'E'}, {'F', 'A'}, {'A', 'E'}, {'F', 'E'}]], [[{'D', 'B'}, {'D', 'C'}, {'D', 'F'}, {'D', 'E'}, {'B', 'C'}, {'B', 'F'}, {'B', 'E'}, {'C', 'F'}, {'C', 'E'}, {'F', 'E'}]]]







 ------------------------------------------------------
 CPS AT PASCALS TRIANGLE AT ROW: 6
 ------------------------------------------------------
 Master Set: ['A', 'B', 'C', 'D', 'E', 'F']
 (n,k):( 6 , 3 )
 [('A', 'B', 'C'), ('A', 'B', 'D'), ('A', 'B', 'E'), ('A', 'B', 'F'), ('A', 'C', 'D'), ('A', 'C', 'E'), ('A', 'C', 'F'), ('A', 'D', 'E'), ('A', 'D', 'F'), ('A', 'E', 'F'), ('B', 'C', 'D'), ('B', 'C', 'E'), ('B', 'C', 'F'), ('B', 'D', 'E'), ('B', 'D', 'F'), ('B', 'E', 'F'), ('C', 'D', 'E'), ('C', 'D', 'F'), ('C', 'E', 'F'), ('D', 'E', 'F')]
 count: 20
 ------------------------------------------------------

 CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
 (n,k):( 6 , 3 )
 (m,j):( 5 , 1 )
 CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
 (n,k):( 6 , 3 )
 (m,j):( 5 , 2 )
 count: 6
 [[[{'D', 'B', 'F'}, {'D', 'C', 'F'}, {'D', 'F', 'A'}, {'D', 'F', 'E'}, {'B', 'C', 'F'}, {'B', 'F', 'A'}, {'B', 'F', 'E'}, {'F', 'C', 'A'}, {'C', 'F', 'E'}, {'F', 'A', 'E'}]], [[{'D', 'B', 'E'}, {'D', 'C', 'E'}, {'D', 'A', 'E'}, {'D', 'F', 'E'}, {'B', 'C', 'E'}, {'B', 'A', 'E'}, {'B', 'F', 'E'}, {'C', 'A', 'E'}, {'C', 'F', 'E'}, {'F', 'A', 'E'}]], [[{'D', 'B', 'C'}, {'D', 'B', 'A'}, {'D', 'B', 'F'}, {'D', 'B', 'E'}, {'D', 'C', 'A'}, {'D', 'C', 'F'}, {'D', 'C', 'E'}, {'D', 'F', 'A'}, {'D', 'A', 'E'}, {'D', 'F', 'E'}]], [[{'D', 'B', 'C'}, {'D', 'C', 'A'}, {'D', 'C', 'F'}, {'D', 'C', 'E'}, {'B', 'C', 'A'}, {'B', 'C', 'F'}, {'B', 'C', 'E'}, {'C', 'F', 'A'}, {'C', 'A', 'E'}, {'C', 'F', 'E'}]], [[{'D', 'B', 'C'}, {'D', 'B', 'A'}, {'D', 'B', 'F'}, {'D', 'B', 'E'}, {'B', 'C', 'A'}, {'B', 'C', 'F'}, {'B', 'C', 'E'}, {'B', 'F', 'A'}, {'B', 'A', 'E'}, {'B', 'F', 'E'}]], [[{'D', 'B', 'A'}, {'D', 'C', 'A'}, {'D', 'F', 'A'}, {'D', 'A', 'E'}, {'B', 'C', 'A'}, {'B', 'F', 'A'}, {'B', 'A', 'E'}, {'C', 'F', 'A'}, {'C', 'A', 'E'}, {'F', 'E', 'A'}]]]
 CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
 (n,k):( 6 , 3 )
 (m,j):( 5 , 3 )
 count: 6
 [[[{'D', 'B', 'C'}, {'D', 'B', 'A'}, {'D', 'B', 'E'}, {'D', 'C', 'A'}, {'D', 'C', 'E'}, {'D', 'A', 'E'}, {'B', 'C', 'A'}, {'B', 'C', 'E'}, {'B', 'A', 'E'}, {'C', 'A', 'E'}]], [[{'D', 'B', 'C'}, {'D', 'B', 'A'}, {'D', 'B', 'F'}, {'D', 'C', 'A'}, {'D', 'C', 'F'}, {'D', 'F', 'A'}, {'B', 'C', 'A'}, {'B', 'C', 'F'}, {'B', 'F', 'A'}, {'F', 'C', 'A'}]], [[{'B', 'C', 'A'}, {'B', 'C', 'F'}, {'B', 'C', 'E'}, {'B', 'F', 'A'}, {'B', 'A', 'E'}, {'B', 'F', 'E'}, {'F', 'C', 'A'}, {'C', 'A', 'E'}, {'C', 'F', 'E'}, {'F', 'A', 'E'}]], [[{'D', 'B', 'A'}, {'D', 'B', 'F'}, {'D', 'B', 'E'}, {'D', 'F', 'A'}, {'D', 'A', 'E'}, {'D', 'F', 'E'}, {'B', 'F', 'A'}, {'B', 'A', 'E'}, {'B', 'F', 'E'}, {'F', 'A', 'E'}]], [[{'D', 'C', 'A'}, {'D', 'C', 'F'}, {'D', 'C', 'E'}, {'D', 'F', 'A'}, {'D', 'A', 'E'}, {'D', 'F', 'E'}, {'F', 'C', 'A'}, {'C', 'A', 'E'}, {'C', 'F', 'E'}, {'F', 'A', 'E'}]], [[{'D', 'B', 'C'}, {'D', 'B', 'F'}, {'D', 'B', 'E'}, {'D', 'C', 'F'}, {'D', 'C', 'E'}, {'D', 'F', 'E'}, {'B', 'C', 'F'}, {'B', 'C', 'E'}, {'B', 'F', 'E'}, {'C', 'F', 'E'}]]]





 ------------------------------------------------------
 CPS AT PASCALS TRIANGLE AT ROW: 6
 ------------------------------------------------------
 Master Set: ['A', 'B', 'C', 'D', 'E', 'F']
 (n,k):( 6 , 4 )
 [('A', 'B', 'C', 'D'), ('A', 'B', 'C', 'E'), ('A', 'B', 'C', 'F'), ('A', 'B', 'D', 'E'), ('A', 'B', 'D', 'F'), ('A', 'B', 'E', 'F'), ('A', 'C', 'D', 'E'), ('A', 'C', 'D', 'F'), ('A', 'C', 'E', 'F'), ('A', 'D', 'E', 'F'), ('B', 'C', 'D', 'E'), ('B', 'C', 'D', 'F'), ('B', 'C', 'E', 'F'), ('B', 'D', 'E', 'F'), ('C', 'D', 'E', 'F')]
 count: 15
 ------------------------------------------------------

 CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
 (n,k):( 6 , 4 )
 (m,j):( 5 , 1 )
 CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
 (n,k):( 6 , 4 )
 (m,j):( 5 , 2 )
 CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
 (n,k):( 6 , 4 )
 (m,j):( 5 , 3 )
 count: 6
 [[[{'D', 'B', 'C', 'F'}, {'D', 'B', 'F', 'A'}, {'D', 'B', 'F', 'E'}, {'D', 'C', 'A', 'F'}, {'D', 'C', 'F', 'E'}, {'D', 'F', 'A', 'E'}, {'F', 'B', 'C', 'A'}, {'B', 'C', 'F', 'E'}, {'B', 'F', 'A', 'E'}, {'F', 'C', 'A', 'E'}]], [[{'D', 'B', 'C', 'E'}, {'D', 'B', 'A', 'E'}, {'D', 'B', 'F', 'E'}, {'D', 'C', 'A', 'E'}, {'D', 'C', 'F', 'E'}, {'D', 'F', 'A', 'E'}, {'B', 'C', 'A', 'E'}, {'B', 'C', 'F', 'E'}, {'B', 'F', 'A', 'E'}, {'F', 'C', 'A', 'E'}]], [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'C', 'F'}, {'D', 'B', 'C', 'E'}, {'D', 'B', 'F', 'A'}, {'D', 'B', 'A', 'E'}, {'D', 'B', 'F', 'E'}, {'F', 'C', 'A', 'D'}, {'D', 'C', 'A', 'E'}, {'D', 'C', 'F', 'E'}, {'D', 'F', 'A', 'E'}]], [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'C', 'F'}, {'D', 'B', 'C', 'E'}, {'D', 'C', 'F', 'A'}, {'D', 'C', 'A', 'E'}, {'D', 'C', 'F', 'E'}, {'B', 'F', 'C', 'A'}, {'B', 'C', 'A', 'E'}, {'B', 'C', 'F', 'E'}, {'C', 'F', 'A', 'E'}]], [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'C', 'F'}, {'D', 'B', 'C', 'E'}, {'D', 'B', 'F', 'A'}, {'D', 'B', 'A', 'E'}, {'D', 'B', 'F', 'E'}, {'F', 'B', 'C', 'A'}, {'B', 'C', 'A', 'E'}, {'B', 'C', 'F', 'E'}, {'B', 'F', 'A', 'E'}]], [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'F', 'A'}, {'D', 'B', 'A', 'E'}, {'D', 'C', 'F', 'A'}, {'D', 'C', 'A', 'E'}, {'D', 'F', 'E', 'A'}, {'B', 'C', 'F', 'A'}, {'B', 'C', 'A', 'E'}, {'B', 'F', 'E', 'A'}, {'C', 'F', 'E', 'A'}]]]
 CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
 (n,k):( 6 , 4 )
 (m,j):( 5 , 4 )
 count: 6
 [[[{'D', 'B', 'C', 'A'}, {'D', 'B', 'C', 'E'}, {'D', 'B', 'A', 'E'}, {'D', 'C', 'A', 'E'}, {'B', 'C', 'A', 'E'}]], [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'C', 'F'}, {'D', 'B', 'F', 'A'}, {'D', 'C', 'A', 'F'}, {'F', 'B', 'C', 'A'}]], [[{'F', 'B', 'C', 'A'}, {'B', 'C', 'A', 'E'}, {'B', 'C', 'F', 'E'}, {'B', 'F', 'A', 'E'}, {'F', 'C', 'A', 'E'}]], [[{'D', 'B', 'F', 'A'}, {'D', 'B', 'A', 'E'}, {'D', 'B', 'F', 'E'}, {'D', 'F', 'A', 'E'}, {'B', 'F', 'A', 'E'}]], [[{'D', 'C', 'A', 'F'}, {'D', 'C', 'A', 'E'}, {'D', 'C', 'F', 'E'}, {'D', 'F', 'A', 'E'}, {'F', 'C', 'A', 'E'}]], [[{'D', 'B', 'C', 'F'}, {'D', 'B', 'C', 'E'}, {'D', 'B', 'F', 'E'}, {'D', 'C', 'F', 'E'}, {'B', 'C', 'F', 'E'}]]]

 ------------------------------------------------------
 CPS AT PASCALS TRIANGLE AT ROW: 6
 ------------------------------------------------------
 Master Set: ['A', 'B', 'C', 'D', 'E', 'F']
 (n,k):( 6 , 5 )
 [('A', 'B', 'C', 'D', 'E'), ('A', 'B', 'C', 'D', 'F'), ('A', 'B', 'C', 'E', 'F'), ('A', 'B', 'D', 'E', 'F'), ('A', 'C', 'D', 'E', 'F'), ('B', 'C', 'D', 'E', 'F')]
 count: 6
 ------------------------------------------------------

 CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
 (n,k):( 6 , 5 )
 (m,j):( 5 , 1 )
 CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
 (n,k):( 6 , 5 )
 (m,j):( 5 , 2 )
 CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
 (n,k):( 6 , 5 )
 (m,j):( 5 , 3 )
 CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
 (n,k):( 6 , 5 )
 (m,j):( 5 , 4 )
 count: 6
 [[[{'D', 'B', 'C', 'A', 'F'}, {'D', 'B', 'C', 'F', 'E'}, {'D', 'B', 'A', 'F', 'E'}, {'D', 'C', 'A', 'F', 'E'}, {'B', 'C', 'A', 'F', 'E'}]], [[{'D', 'B', 'C', 'A', 'E'}, {'D', 'B', 'C', 'F', 'E'}, {'D', 'B', 'A', 'F', 'E'}, {'D', 'C', 'A', 'F', 'E'}, {'B', 'C', 'A', 'F', 'E'}]], [[{'D', 'B', 'C', 'A', 'F'}, {'D', 'B', 'C', 'A', 'E'}, {'D', 'B', 'C', 'F', 'E'}, {'D', 'B', 'A', 'F', 'E'}, {'D', 'C', 'A', 'F', 'E'}]], [[{'D', 'B', 'C', 'A', 'F'}, {'D', 'B', 'C', 'A', 'E'}, {'D', 'B', 'C', 'F', 'E'}, {'D', 'C', 'A', 'F', 'E'}, {'B', 'C', 'A', 'F', 'E'}]], [[{'D', 'B', 'C', 'A', 'F'}, {'D', 'B', 'C', 'A', 'E'}, {'D', 'B', 'C', 'F', 'E'}, {'D', 'B', 'A', 'F', 'E'}, {'B', 'C', 'A', 'F', 'E'}]], [[{'D', 'B', 'C', 'A', 'F'}, {'D', 'B', 'C', 'A', 'E'}, {'D', 'B', 'A', 'F', 'E'}, {'D', 'C', 'A', 'F', 'E'}, {'B', 'C', 'A', 'F', 'E'}]]]
 CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
 (n,k):( 6 , 5 )
 (m,j):( 5 , 5 )
 count: 6
 [[[{'D', 'B', 'C', 'A', 'E'}]], [[{'D', 'B', 'C', 'F', 'A'}]], [[{'B', 'C', 'F', 'A', 'E'}]], [[{'D', 'B', 'F', 'A', 'E'}]], [[{'D', 'C', 'F', 'A', 'E'}]], [[{'D', 'B', 'C', 'F', 'E'}]]]


 
 ------------------------------------------------------
 CPS AT PASCALS TRIANGLE AT ROW: 6
 ------------------------------------------------------
 Master Set: ['A', 'B', 'C', 'D', 'E', 'F']
 (n,k):( 6 , 6 )
 [('A', 'B', 'C', 'D', 'E', 'F')]
 count: 1
 ------------------------------------------------------


 */
