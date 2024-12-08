/*
  ==============================================================================

    CPS_4_4.cpp
    Created: 13 Aug 2021 8:11:12pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "CPS_4_4.h"
#include "EulerGenusModel.h"
#include "WilsonicProcessor.h"
#include "CPS.h"

#pragma mark - lifecycle

CPS_4_4::CPS_4_4(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D)
: Seed4(A, B, C, D)
// these placeholder terms will be corrected in update()
{
    // basename
    _tuningType = CPS_Class::CPS_4_4;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_4_4::CPS_4_4(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed4(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_4_4;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_4_4::canPaintTuning()
{
    return true;
}

CPS_4_4::~CPS_4_4()
{

}

void CPS_4_4::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    _mABCD = CPSMicrotone_t::create(CPS::ABCD(_A,_B,_C,_D), Point<float> (0, 0));

    // no line array for single points

    _labelArray.push_back(_mABCD);

    _masterPtArray.push_back(_mABCD);
}

#pragma mark - update

void CPS_4_4::update()
{
    /*
     ------------------------------------------------------
     CPS AT PASCALS TRIANGLE AT ROW: 4
     ------------------------------------------------------
     Master Set: ['A', 'B', 'C', 'D']
     (n,k):( 4 , 1 )
     [('A',), ('B',), ('C',), ('D',)]
     count: 4
     ------------------------------------------------------
     */
    _mABCD->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _C, _D} );

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mABCD->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()
}

#pragma mark - subsets

void CPS_4_4::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_4_4::selectS0_0()
{
    jassertfalse;
}

void CPS_4_4::selectS0_1()
{
    jassertfalse;
}

void CPS_4_4::selectS0_2()
{
    jassertfalse;
}

void CPS_4_4::selectS0_3()
{
    jassertfalse;
}

void CPS_4_4::selectS0_4()
{
    jassertfalse;
}

void CPS_4_4::selectS0_5()
{
    jassertfalse;
}

void CPS_4_4::selectS0_6()
{
    jassertfalse;
}

void CPS_4_4::selectS0_7()
{
    jassertfalse;
}

void CPS_4_4::selectS1_0()
{
    jassertfalse;
}

void CPS_4_4::selectS1_1()
{
    jassertfalse;
}

void CPS_4_4::selectS1_2()
{
    jassertfalse;
}

void CPS_4_4::selectS1_3()
{
    jassertfalse;
}

void CPS_4_4::selectS1_4()
{
    jassertfalse;
}

void CPS_4_4::selectS1_5()
{
    jassertfalse;
}

void CPS_4_4::selectS1_6()
{
    jassertfalse;
}

void CPS_4_4::selectS1_7()
{
    jassertfalse;
}

bool CPS_4_4::isEulerGenusTuningType()
{
    return false;
}

