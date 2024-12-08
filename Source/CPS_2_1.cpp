/*
 ==============================================================================

 CPS_2_1.cpp
 Created: 31 Jul 2021 1:00:22pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "CPS_2_1.h"
#include "CPS.h"
#include "EulerGenusModel.h"

#pragma mark - lifecycle

CPS_2_1::CPS_2_1(Microtone_p A, Microtone_p B)
: Seed2(A, B)
{
    // basename
    _tuningType = CPS_Class::CPS_2_1;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_2_1::CPS_2_1(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed2(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_2_1;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_2_1::canPaintTuning()
{
    return true;
}

void CPS_2_1::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    // scaling func for coords...on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [] (auto x, auto y)
    {
        auto xx = 0.5f - x;
        xx *= 960.f / 530;
        auto yy = 0.5f - y;
        auto const s = 1.f;
        xx *= s;
        yy *= s;
        return Point<float> (xx, yy);
    };

    _mA = CPSMicrotone_t::create(_A, hpc(0.25f, 0.5f));
    _mB = CPSMicrotone_t::create(_B, hpc(0.75f, 0.5f));
    _p0 = CPSMicrotone_t::create_center(Point<float> (0.5f, 0.5f));

    _lineArray.push_back(CPSMicrotone_t::create_line(_mA, _mB));

    _labelArray.push_back(_mA);
    _labelArray.push_back(_mB);

    _masterPtArray.push_back(_mA);
    _masterPtArray.push_back(_mB);
    _masterPtArray.push_back(_p0  );
}

CPS_2_1::~CPS_2_1()
{

}

#pragma mark - update

void CPS_2_1::update()
{
    //
    //    Master Set: ['A', 'B']
    //    (n,k):( 2 , 1 )
    //    [('A',), ('B',)]
    //    count: 2
    _mA->mt = multiplyByCommonTones(vector<Microtone_p> {_A});
    _mB->mt = multiplyByCommonTones(vector<Microtone_p> {_B});

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mA->mt);
    ma.addMicrotone(_mB->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()

    // subsets

    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        //    CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 2
        //    (n,k):( 2 , 1 )
        //    (m,j):( 1 , 1 )
        //    count: 2
        //    [[[{'A'}]], [[{'B'}]]]
        _cps_1_1_0->setCommonTones(nullptr, getCommonTones());
        _cps_1_1_0->setA(_A); // [[{'A'}]]

        _cps_1_1_1->setCommonTones(nullptr, getCommonTones());
        _cps_1_1_1->setA(_B); // [[{'B'}]]
    }
}

#pragma mark - subsets

void CPS_2_1::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _cps_1_1_0 = make_shared<CPS_1_1> (_A);
    _cps_1_1_1 = make_shared<CPS_1_1> (_B);

    // subsets
    _subsets0.push_back(_cps_1_1_0);
    _subsets0.push_back(_cps_1_1_1);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_2_1::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void CPS_2_1::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void CPS_2_1::selectS0_2()
{
    jassertfalse;
}

void CPS_2_1::selectS0_3()
{
    jassertfalse;
}

void CPS_2_1::selectS0_4()
{
    jassertfalse;
}

void CPS_2_1::selectS0_5()
{
    jassertfalse;
}

void CPS_2_1::selectS0_6()
{
    jassertfalse;
}

void CPS_2_1::selectS0_7()
{
    jassertfalse;
}

void CPS_2_1::selectS1_0()
{
    jassertfalse;
}

void CPS_2_1::selectS1_1()
{
    jassertfalse;
}

void CPS_2_1::selectS1_2()
{
    jassertfalse;
}

void CPS_2_1::selectS1_3()
{
    jassertfalse;
}

void CPS_2_1::selectS1_4()
{
    jassertfalse;
}

void CPS_2_1::selectS1_5()
{
    jassertfalse;
}

void CPS_2_1::selectS1_6()
{
    jassertfalse;
}

void CPS_2_1::selectS1_7()
{
    jassertfalse;
}

bool CPS_2_1::isEulerGenusTuningType()
{
    return false;
}

