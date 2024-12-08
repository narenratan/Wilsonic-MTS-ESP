/*
 ==============================================================================
 
 CPS_3_3.cpp
 Created: 10 Aug 2021 10:32:39pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "CPS_3_3.h"
#include "EulerGenusModel.h"
#include "WilsonicProcessor.h"
#include "CPS.h"

#pragma mark - lifecycle

CPS_3_3::CPS_3_3(Microtone_p A, Microtone_p B, Microtone_p C)
: Seed3(A, B, C)
{
    // basename
    _tuningType = CPS_Class::CPS_3_3;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // no subsets
    
    // update
    update();
}

CPS_3_3::CPS_3_3(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed3(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_3_3;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_3_3::canPaintTuning()
{
    return true;
}


CPS_3_3::~CPS_3_3()
{
    
}

void CPS_3_3::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    _mABC = CPSMicrotone_t::create(CPS::ABC(_A,_B,_C), Point<float> (0, 0));

    // no line array for single points

    _labelArray.push_back(_mABC);

    _masterPtArray.push_back(_mABC);
}

#pragma mark - update

void CPS_3_3::update()
{
    // no subsets
    
    //    ------------------------------------------------------
    //    CPS AT PASCALS TRIANGLE AT ROW: 3
    //    ------------------------------------------------------
    //    Master Set: ['A', 'B', 'C']
    //    (n,k):( 3 , 3 )
    //    [('A', 'B', 'C')]
    //    count: 1
    //    ------------------------------------------------------
    _mABC->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _C} );
    auto ma = MicrotoneArray();
    ma.addMicrotone(_mABC->mt);
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

void CPS_3_3::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_3_3::selectS0_0()
{
    jassertfalse;
}

void CPS_3_3::selectS0_1()
{
    jassertfalse;
}

void CPS_3_3::selectS0_2()
{
    jassertfalse;
}

void CPS_3_3::selectS0_3()
{
    jassertfalse;
}

void CPS_3_3::selectS0_4()
{
    jassertfalse;
}

void CPS_3_3::selectS0_5()
{
    jassertfalse;
}

void CPS_3_3::selectS0_6()
{
    jassertfalse;
}

void CPS_3_3::selectS0_7()
{
    jassertfalse;
}

void CPS_3_3::selectS1_0()
{
    jassertfalse;
}

void CPS_3_3::selectS1_1()
{
    jassertfalse;
}

void CPS_3_3::selectS1_2()
{
    jassertfalse;
}

void CPS_3_3::selectS1_3()
{
    jassertfalse;
}

void CPS_3_3::selectS1_4()
{
    jassertfalse;
}

void CPS_3_3::selectS1_5()
{
    jassertfalse;
}

void CPS_3_3::selectS1_6()
{
    jassertfalse;
}

void CPS_3_3::selectS1_7()
{
    jassertfalse;
}

bool CPS_3_3::isEulerGenusTuningType()
{
    return false;
}

