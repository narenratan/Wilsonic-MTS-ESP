/*
 ==============================================================================
 
 CPS_2_2.cpp
 Created: 8 Aug 2021 9:41:58am
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "CPS_2_2.h"
#include "EulerGenusModel.h"
#include "WilsonicProcessor.h"
#include "CPS.h"

#pragma mark - lifecycle

CPS_2_2::CPS_2_2(Microtone_p A, Microtone_p B)
: Seed2(A, B)
{
    // basename
    _tuningType = CPS_Class::CPS_2_2;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_2_2::CPS_2_2(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed2(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_2_2;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_2_2::canPaintTuning()
{
    return true;
}

CPS_2_2::~CPS_2_2()
{
    
}

void CPS_2_2::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    _mAB = CPSMicrotone_t::create(CPS::AB(_A,_B), Point<float> (0, 0));

    // no line array for single points

    _labelArray.push_back(_mAB);

    _masterPtArray.push_back(_mAB);
}

#pragma mark - update

void CPS_2_2::update()
{
    /*
     ------------------------------------------------------
     CPS AT PASCALS TRIANGLE AT ROW: 2
     ------------------------------------------------------
     Master Set: ['A', 'B']
     (n,k):( 2 , 2 )
     [('A', 'B')]
     count: 1
     ------------------------------------------------------
     */
    _mAB->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B} );
    auto ma = MicrotoneArray();
    ma.addMicrotone(_mAB->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()

    // subsets

    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        // compute subsets here
    }
}

#pragma mark - subsets

void CPS_2_2::_allocateSubsets()
{
    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_2_2::selectS0_0()
{
    jassertfalse;
}

void CPS_2_2::selectS0_1()
{
    jassertfalse;
}

void CPS_2_2::selectS0_2()
{
    jassertfalse;
}

void CPS_2_2::selectS0_3()
{
    jassertfalse;
}

void CPS_2_2::selectS0_4()
{
    jassertfalse;
}

void CPS_2_2::selectS0_5()
{
    jassertfalse;
}

void CPS_2_2::selectS0_6()
{
    jassertfalse;
}

void CPS_2_2::selectS0_7()
{
    jassertfalse;
}

void CPS_2_2::selectS1_0()
{
    jassertfalse;
}

void CPS_2_2::selectS1_1()
{
    jassertfalse;
}

void CPS_2_2::selectS1_2()
{
    jassertfalse;
}

void CPS_2_2::selectS1_3()
{
    jassertfalse;
}

void CPS_2_2::selectS1_4()
{
    jassertfalse;
}

void CPS_2_2::selectS1_5()
{
    jassertfalse;
}

void CPS_2_2::selectS1_6()
{
    jassertfalse;
}

void CPS_2_2::selectS1_7()
{
    jassertfalse;
}

bool CPS_2_2::isEulerGenusTuningType()
{
    return false;
}

