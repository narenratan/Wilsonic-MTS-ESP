/*
 ==============================================================================

 CPS_5_5.cpp
 Created: 13 Aug 2021 8:35:56pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "CPS_5_5.h"
#include "EulerGenusModel.h"
#include "WilsonicProcessor.h"
#include "CPS.h"

#pragma mark - lifecycle

CPS_5_5::CPS_5_5(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E)
: Seed5(A, B, C, D, E)
{
    // basename
    _tuningType = CPS_Class::CPS_5_5;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_5_5::CPS_5_5(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed5(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_5_5;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_5_5::canPaintTuning()
{
    return true;
}

CPS_5_5::~CPS_5_5()
{

}

void CPS_5_5::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    _mABCDE = CPSMicrotone_t::create(CPS::ABCDE(_A,_B,_C,_D,_E), Point<float> (0, 0));

    // no line array for single points

    _labelArray.push_back(_mABCDE);

    _masterPtArray.push_back(_mABCDE);
}

#pragma mark - update

void CPS_5_5::update()
{
    /*
     ------------------------------------------------------
     CPS AT PASCALS TRIANGLE AT ROW: 5
     ------------------------------------------------------
     Master Set: ['A', 'B', 'C', 'D', 'E']
     (n,k):( 5 , 1 )
     [('A',), ('B',), ('C',), ('D',), ('E',)]
     count: 5
     ------------------------------------------------------
     */
    _mABCDE->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _C, _D, _E} );

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mABCDE->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()
}

void CPS_5_5::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_5_5::selectS0_0()
{
    jassertfalse;
}

void CPS_5_5::selectS0_1()
{
    jassertfalse;
}

void CPS_5_5::selectS0_2()
{
    jassertfalse;
}

void CPS_5_5::selectS0_3()
{
    jassertfalse;
}

void CPS_5_5::selectS0_4()
{
    jassertfalse;
}

void CPS_5_5::selectS0_5()
{
    jassertfalse;
}

void CPS_5_5::selectS0_6()
{
    jassertfalse;
}

void CPS_5_5::selectS0_7()
{
    jassertfalse;
}

void CPS_5_5::selectS1_0()
{
    jassertfalse;
}

void CPS_5_5::selectS1_1()
{
    jassertfalse;
}

void CPS_5_5::selectS1_2()
{
    jassertfalse;
}

void CPS_5_5::selectS1_3()
{
    jassertfalse;
}

void CPS_5_5::selectS1_4()
{
    jassertfalse;
}

void CPS_5_5::selectS1_5()
{
    jassertfalse;
}

void CPS_5_5::selectS1_6()
{
    jassertfalse;
}

void CPS_5_5::selectS1_7()
{
    jassertfalse;
}

bool CPS_5_5::isEulerGenusTuningType()
{
    return false;
}

