/*
 ==============================================================================

 CPS_5_1.cpp
 Created: 13 Aug 2021 8:21:13pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "CPS_5_1.h"
#include "CPS.h"
#include "EulerGenusModel.h"

#pragma mark - lifecycle

CPS_5_1::CPS_5_1(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E)
: Seed5(A, B, C, D, E)
{
    // basename
    _tuningType = CPS_Class::CPS_5_1;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_5_1::CPS_5_1(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed5(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_5_1;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_5_1::canPaintTuning()
{
    return true;
}

void CPS_5_1::_commonConstructorHelper()
{
    auto const x01 = 0.185f;
    auto const x02 = 0.300f;
    auto const x04 = 0.5f;
    auto const x06 = 1.f - x02;
    auto const x07 = 1.f - x01;

    auto const y02 = 0.185f;
    auto const y03 = 0.235f;
    auto const y06 = 0.415f;
    auto const y10 = 1.f - y03;

    auto hpc = [] (float x, float y)
    {
        auto const sr3 = 1.f;
        auto xx = -(0.5f - x);
        xx *= sr3;
        auto yy = -(0.5f - y);
        auto s = 0.55708f; // magic
        xx *= s;
        yy *= s;
        return Point<float> (xx, yy);
    };

    _mA = CPSMicrotone_t::create(_A, hpc(x02, y10));
    _mB = CPSMicrotone_t::create(_B, hpc(x01, y06));
    _mC = CPSMicrotone_t::create(_C, hpc(x04, y02));
    _mD = CPSMicrotone_t::create(_D, hpc(x07, y06));
    _mE = CPSMicrotone_t::create(_E, hpc(x06, y10));
    _p0 = CPSMicrotone_t::create_center(hpc(0.5f, 0.5f));

    _lineArray.push_back(CPSMicrotone_t::create_line(_mA, _mB));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mB, _mC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mC, _mD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mD, _mE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mE, _mA));

    _labelArray.push_back(_mA);
    _labelArray.push_back(_mB);
    _labelArray.push_back(_mC);
    _labelArray.push_back(_mD);
    _labelArray.push_back(_mE);

    _masterPtArray.push_back(_mA);
    _masterPtArray.push_back(_mB);
    _masterPtArray.push_back(_mC);
    _masterPtArray.push_back(_mD);
    _masterPtArray.push_back(_mE);
    _masterPtArray.push_back(_p0);
}

CPS_5_1::~CPS_5_1()
{

}

#pragma mark - update

void CPS_5_1::update()
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

    _mA->mt = multiplyByCommonTones(vector<Microtone_p> {_A} );
    _mB->mt = multiplyByCommonTones(vector<Microtone_p> {_B} );
    _mC->mt = multiplyByCommonTones(vector<Microtone_p> {_C} );
    _mD->mt = multiplyByCommonTones(vector<Microtone_p> {_D} );
    _mE->mt = multiplyByCommonTones(vector<Microtone_p> {_E} );

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mA->mt);
    ma.addMicrotone(_mB->mt);
    ma.addMicrotone(_mC->mt);
    ma.addMicrotone(_mD->mt);
    ma.addMicrotone(_mE->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()

    // SUBSETS

    /*
     ------------------------------------------------------
     CPS SUBSETS AT PASCALS TRIANGLE AT ROW: 5
     (n,k):( 5 , 1 )
     // _A _B _C _D
     // _A _B _C    _E
     // _A _B    _D _E
     // _A    _C _D _E
     //    _B _C _D _E
     */
    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        _cps_4_1_0->setCommonTones(nullptr, getCommonTones());
        _cps_4_1_0->setABCD(_A, _B, _C, _D);

        _cps_4_1_1->setCommonTones(nullptr, getCommonTones());
        _cps_4_1_1->setABCD(_A, _B, _C, _E);

        _cps_4_1_2->setCommonTones(nullptr, getCommonTones());
        _cps_4_1_2->setABCD(_A, _B, _D, _E);

        _cps_4_1_3->setCommonTones(nullptr, getCommonTones());
        _cps_4_1_3->setABCD(_A, _C, _D, _E);

        _cps_4_1_4->setCommonTones(nullptr, getCommonTones());
        _cps_4_1_4->setABCD(_B, _C, _D, _E);
    }
}

#pragma mark - subsets

void CPS_5_1::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _cps_4_1_0 = make_shared<CPS_4_1> (_A, _B, _C, _D);
    _cps_4_1_1 = make_shared<CPS_4_1> (_A, _B, _C, _D);
    _cps_4_1_2 = make_shared<CPS_4_1> (_A, _B, _C, _D);
    _cps_4_1_3 = make_shared<CPS_4_1> (_A, _B, _C, _D);
    _cps_4_1_4 = make_shared<CPS_4_1> (_A, _B, _C, _D);

    // subsets0
    _subsets0.push_back(_cps_4_1_0);
    _subsets0.push_back(_cps_4_1_1);
    _subsets0.push_back(_cps_4_1_2);
    _subsets0.push_back(_cps_4_1_3);
    _subsets0.push_back(_cps_4_1_4);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_5_1::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void CPS_5_1::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void CPS_5_1::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void CPS_5_1::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void CPS_5_1::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void CPS_5_1::selectS0_5()
{
    jassertfalse;
}

void CPS_5_1::selectS0_6()
{
    jassertfalse;
}

void CPS_5_1::selectS0_7()
{
    jassertfalse;
}

void CPS_5_1::selectS1_0()
{
    jassertfalse;
}

void CPS_5_1::selectS1_1()
{
    jassertfalse;
}

void CPS_5_1::selectS1_2()
{
    jassertfalse;
}

void CPS_5_1::selectS1_3()
{
    jassertfalse;
}

void CPS_5_1::selectS1_4()
{
    jassertfalse;
}

void CPS_5_1::selectS1_5()
{
    jassertfalse;
}

void CPS_5_1::selectS1_6()
{
    jassertfalse;
}

void CPS_5_1::selectS1_7()
{
    jassertfalse;
}

bool CPS_5_1::isEulerGenusTuningType()
{
    return false;
}

