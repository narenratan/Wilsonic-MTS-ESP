/*
 ==============================================================================
 
 CPS_1_1.cpp
 Created: 29 Jul 2021 9:11:39pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "CPS_1_1.h"
#include "EulerGenusModel.h"
#include "WilsonicProcessor.h"
#include "CPS.h"

#pragma mark - lifecycle

CPS_1_1::CPS_1_1(Microtone_p A)
: Seed1(A)
{
    // basename
    _tuningType = CPS_Class::CPS_1_1;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_1_1::CPS_1_1(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed1(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_1_1;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_1_1::canPaintTuning()
{
    return true;
}

CPS_1_1::~CPS_1_1()
{
    
}

void CPS_1_1::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    _mA = CPSMicrotone_t::create(CPS::A(_A->getFrequencyValue()), Point<float> (0, 0));

    // no line array for single points

    _labelArray.push_back(_mA);

    _masterPtArray.push_back(_mA);
}

#pragma mark - update

void CPS_1_1::update()
{
    //     ------------------------------------------------------
    //     CPS AT PASCALS TRIANGLE AT ROW: 1
    //     ------------------------------------------------------
    //     Master Set: ['A']
    //     (n,k):( 1 , 1 )
    //     [('A',)]
    //     count: 1
    //     ------------------------------------------------------
    _mA->mt = multiplyByCommonTones(vector<Microtone_p> {_A});
    auto ma = MicrotoneArray();
    ma.addMicrotone(_mA->mt);
    setMicrotoneArray(ma); // calls TuningImp::_update()

    // subsets

    // (no subsets)
    
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

void CPS_1_1::_allocateSubsets()
{
    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_1_1::selectS0_0()
{
    jassertfalse;
}

void CPS_1_1::selectS0_1()
{
    jassertfalse;
}

void CPS_1_1::selectS0_2()
{
    jassertfalse;
}

void CPS_1_1::selectS0_3()
{
    jassertfalse;
}

void CPS_1_1::selectS0_4()
{
    jassertfalse;
}

void CPS_1_1::selectS0_5()
{
    jassertfalse;
}

void CPS_1_1::selectS0_6()
{
    jassertfalse;
}

void CPS_1_1::selectS0_7()
{
    jassertfalse;
}

void CPS_1_1::selectS1_0()
{
    jassertfalse;
}

void CPS_1_1::selectS1_1()
{
    jassertfalse;
}

void CPS_1_1::selectS1_2()
{
    jassertfalse;
}

void CPS_1_1::selectS1_3()
{
    jassertfalse;
}

void CPS_1_1::selectS1_4()
{
    jassertfalse;
}

void CPS_1_1::selectS1_5()
{
    jassertfalse;
}

void CPS_1_1::selectS1_6()
{
    jassertfalse;
}

void CPS_1_1::selectS1_7()
{
    jassertfalse;
}

bool CPS_1_1::isEulerGenusTuningType()
{
    return false;
}

