/*
  ==============================================================================

    CPS_5_1.h
    Created: 13 Aug 2021 8:21:13pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_4_1.h"
#include "Seed5.h"

class CPS_5_1 
: public Seed5
{
public:
    CPS_5_1(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E);
    CPS_5_1(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~CPS_5_1() override;
    bool canPaintTuning() override;
    void update() override;
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
    CPSMicrotone _mA;
    CPSMicrotone _mB;
    CPSMicrotone _mC;
    CPSMicrotone _mD;
    CPSMicrotone _mE;
    shared_ptr<CPS_4_1> _cps_4_1_0;
    shared_ptr<CPS_4_1> _cps_4_1_1;
    shared_ptr<CPS_4_1> _cps_4_1_2;
    shared_ptr<CPS_4_1> _cps_4_1_3;
    shared_ptr<CPS_4_1> _cps_4_1_4;

    void _commonConstructorHelper(); // called only at construction
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

 ------------------------------------------------------
 CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 5
 (n,k):( 5 , 1 )
 (m,j):( 4 , 1 )
 count: 5
 [[{'D'}, {'B'}, {'C'}, {'A'}]],
 [[{'B'}, {'C'}, {'A'}, {'E'}]],
 [[{'D'}, {'B'}, {'A'}, {'E'}]],
 [[{'D'}, {'C'}, {'A'}, {'E'}]],
 [[{'D'}, {'B'}, {'C'}, {'E'}]]
 ------------------------------------------------------
 */
