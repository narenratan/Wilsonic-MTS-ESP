/*
 ==============================================================================
 
 CPS_3_2.cpp
 Created: 10 Aug 2021 10:32:06pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "CPS_3_2.h"
#include "CPS.h"
#include "EulerGenusModel.h"

#pragma mark - lifecycle

CPS_3_2::CPS_3_2(Microtone_p A, Microtone_p B, Microtone_p C)
: Seed3(A, B, C)
{
    // basename
    _tuningType = CPS_Class::CPS_3_2;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_3_2::CPS_3_2(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed3(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_3_2;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_3_2::canPaintTuning()
{
    return true;
}

void CPS_3_2::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    // custom geometry on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [](auto x, auto y)
    {
        auto const sr3 = 1 / (0.5f * sqrtf(3));
        auto xx = 0.5f - x;
        xx *= sr3;
        auto yy = 0.5f - y;
        auto const s = 0.3f;
        xx *= s;
        yy *= s;
        return Point<float> (xx, yy);
    };

    _mAB = CPSMicrotone_t::create(CPS::AB(_A, _B), hpc(0.5f, 1 - 1   ));
    _mAC = CPSMicrotone_t::create(CPS::AB(_A, _C), hpc(1.f , 1 - 0   ));
    _mBC = CPSMicrotone_t::create(CPS::AB(_B, _C), hpc(0.f , 1 - 0   ));
    _p0 = CPSMicrotone_t::create_center(hpc(0.5f, 0.5f));

    _lineArray.push_back(CPSMicrotone_t::create_line(_mAB, _mAC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAB, _mBC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBC, _mAC));

    _labelArray.push_back(_mAB);
    _labelArray.push_back(_mAC);
    _labelArray.push_back(_mBC);

    _masterPtArray.push_back(_mAB);
    _masterPtArray.push_back(_mAC);
    _masterPtArray.push_back(_mBC);
    _masterPtArray.push_back(_p0);
}


CPS_3_2::~CPS_3_2()
{
    
}

#pragma mark - update

void CPS_3_2::update()
{
    //     ------------------------------------------------------
    //     CPS AT PASCALS TRIANGLE AT ROW: 3
    //     ------------------------------------------------------
    //     Master Set: ['A', 'B', 'C']
    //     (n,k):( 3 , 2 )
    //     [('A', 'B'), ('A', 'C'), ('B', 'C')]
    //     count: 3
    //     ------------------------------------------------------
    _mAB->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B} );
    _mAC->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _C} );
    _mBC->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _C} );

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mAB->mt);
    ma.addMicrotone(_mAC->mt);
    ma.addMicrotone(_mBC->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()
    
    //    CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 3
    //    (n,k):( 3 , 2 )
    //    (m,j):( 2 , 1 )
    //    count: 3
    //    [[{'B', 'C'}, {'C', 'A'}]],
    //    [[{'B', 'C'}, {'B', 'A'}]],
    //    [[{'B', 'A'}, {'C', 'A'}]]

    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        _cps_2_1_0->setCommonTones(_C, getCommonTones());
        _cps_2_1_0->setAB(_A, _B);

        _cps_2_1_1->setCommonTones(_B, getCommonTones());
        _cps_2_1_1->setAB(_A, _C);

        _cps_2_1_2->setCommonTones(_A, getCommonTones());
        _cps_2_1_2->setAB(_B, _C);

        //    CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 3
        //    (n,k):( 3 , 2 )
        //    (m,j):( 2 , 2 )
        //    count: 3
        //    [[[{'B', 'A'}]], [[{'C', 'A'}]], [[{'B', 'C'}]]]

        _cps_2_2_0->setCommonTones(nullptr, getCommonTones());
        _cps_2_2_0->setAB(_A, _B);

        _cps_2_2_1->setCommonTones(nullptr, getCommonTones());
        _cps_2_2_1->setAB(_A, _C);

        _cps_2_2_2->setCommonTones(nullptr, getCommonTones());
        _cps_2_2_2->setAB(_B, _C);
    }
}

#pragma mark - subsets

void CPS_3_2::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _cps_2_1_0 = make_shared<CPS_2_1> (_A, _B);
    _cps_2_1_1 = make_shared<CPS_2_1> (_A, _B);
    _cps_2_1_2 = make_shared<CPS_2_1> (_A, _B);
    _cps_2_2_0 = make_shared<CPS_2_2> (_A, _B);
    _cps_2_2_1 = make_shared<CPS_2_2> (_A, _B);
    _cps_2_2_2 = make_shared<CPS_2_2> (_A, _B);

    // subsets0
    _subsets0.push_back(_cps_2_1_0);
    _subsets0.push_back(_cps_2_1_1);
    _subsets0.push_back(_cps_2_1_2);

    // subsets1
    _subsets1.push_back(_cps_2_2_0);
    _subsets1.push_back(_cps_2_2_1);
    _subsets1.push_back(_cps_2_2_2);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_3_2::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void CPS_3_2::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void CPS_3_2::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void CPS_3_2::selectS0_3()
{
    jassertfalse;
}

void CPS_3_2::selectS0_4()
{
    jassertfalse;
}

void CPS_3_2::selectS0_5()
{
    jassertfalse;
}

void CPS_3_2::selectS0_6()
{
    jassertfalse;
}

void CPS_3_2::selectS0_7()
{
    jassertfalse;
}

void CPS_3_2::selectS1_0()
{
    _clearSelection();
    _subsets1[0]->setIsSelected(true);
}

void CPS_3_2::selectS1_1()
{
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void CPS_3_2::selectS1_2()
{
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void CPS_3_2::selectS1_3()
{
    jassertfalse;
}

void CPS_3_2::selectS1_4()
{
    jassertfalse;
}

void CPS_3_2::selectS1_5()
{
    jassertfalse;
}

void CPS_3_2::selectS1_6()
{
    jassertfalse;
}

void CPS_3_2::selectS1_7()
{
    jassertfalse;
}

bool CPS_3_2::isEulerGenusTuningType()
{
    return false;
}

