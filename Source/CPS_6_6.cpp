/*
 ==============================================================================

 CPS_6_6.cpp
 Created: 13 Aug 2021 9:06:12pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "CPS_6_6.h"
#include "EulerGenusModel.h"
#include "WilsonicProcessor.h"
#include "CPS.h"

#pragma mark - lifecycle

CPS_6_6::CPS_6_6(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F)
: Seed6(A, B, C, D, E, F)
{
    // basename
    _tuningType = CPS_Class::CPS_6_6;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_6_6::CPS_6_6(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed6(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_6_6;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_6_6::canPaintTuning()
{
    return true;
}

CPS_6_6::~CPS_6_6()
{

}

void CPS_6_6::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    _mABCDEF = CPSMicrotone_t::create(CPS::ABCDEF(_A,_B,_C,_D,_E,_F), Point<float> (0, 0));

    // no line array for single points

    _labelArray.push_back(_mABCDEF);

    _masterPtArray.push_back(_mABCDEF);
}

#pragma mark - update

void CPS_6_6::update()
{
    /*
     ------------------------------------------------------
     CPS AT PASCALS TRIANGLE AT ROW: 6
     ------------------------------------------------------
     Master Set: ['A', 'B', 'C', 'D', 'E', 'F']
     (n,k):( 6 , 6 )
     [('A', 'B', 'C', 'D', 'E', 'F')]
     count: 1
     ------------------------------------------------------
     */
    _mABCDEF->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _C, _D, _E, _F});
    auto ma = MicrotoneArray();
    ma.addMicrotone(_mABCDEF->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()
}

#pragma mark - subsets

void CPS_6_6::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_6_6::selectS0_0()
{
    jassertfalse;
}

void CPS_6_6::selectS0_1()
{
    jassertfalse;
}

void CPS_6_6::selectS0_2()
{
    jassertfalse;
}

void CPS_6_6::selectS0_3()
{
    jassertfalse;
}

void CPS_6_6::selectS0_4()
{
    jassertfalse;
}

void CPS_6_6::selectS0_5()
{
    jassertfalse;
}

void CPS_6_6::selectS0_6()
{
    jassertfalse;
}

void CPS_6_6::selectS0_7()
{
    jassertfalse;
}

void CPS_6_6::selectS1_0()
{
    jassertfalse;
}

void CPS_6_6::selectS1_1()
{
    jassertfalse;
}

void CPS_6_6::selectS1_2()
{
    jassertfalse;
}

void CPS_6_6::selectS1_3()
{
    jassertfalse;
}

void CPS_6_6::selectS1_4()
{
    jassertfalse;
}

void CPS_6_6::selectS1_5()
{
    jassertfalse;
}

void CPS_6_6::selectS1_6()
{
    jassertfalse;
}

void CPS_6_6::selectS1_7()
{
    jassertfalse;
}

bool CPS_6_6::isEulerGenusTuningType()
{
    return false;
}

