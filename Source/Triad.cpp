/*
  ==============================================================================

    Triad.cpp
    Created: 20 Jun 2023 8:20:29pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "Triad.h"
#include "CPS.h"
#include "EulerGenusModel.h"

#pragma mark - lifecycle

Triad::Triad(Microtone_p A, Microtone_p B, Microtone_p C, bool isHarmonic)
: Seed3(A, B, C)
, _isHarmonic(isHarmonic)
{
    setCanNPOOverride(true); // redundant, for clarity
    
    // basename
    _tuningType = CPS_Class::Triad;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

Triad::Triad(vector<Microtone_p> master_set, vector<Microtone_p> common_tones, bool isHarmonic)
:Seed3(master_set, common_tones)
, _isHarmonic(isHarmonic)
{
    // basename
    _tuningType = CPS_Class::Triad;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool Triad::canPaintTuning()
{
    return true;
}

void Triad::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    // custom geometry on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [this](auto x, auto y)
    {
        auto const sr3 = 1 / (0.5f * sqrtf(3));
        auto xx = 0.5f - x;
        xx *= sr3;
        auto yy = 0.5f - y;
        auto const s = 0.3f;
        xx *= s;
        yy *= s;
        if (!_isHarmonic)
        {
            yy *= -1.f;
        }

        return Point<float> (xx, yy);
    };

    _mA = CPSMicrotone_t::create(_A, hpc(0.5f , 1.f   ));
    _mB = CPSMicrotone_t::create(_B, hpc(1.f  , 0.f   ));
    _mC = CPSMicrotone_t::create(_C, hpc(0.f  , 0.f   ));
    _p0 = CPSMicrotone_t::create_center(hpc(0.5f, 0.5f));

    _lineArray.push_back(CPSMicrotone_t::create_line(_mA, _mB));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mB, _mC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mC, _mA));

    _labelArray.push_back(_mA);
    _labelArray.push_back(_mB);
    _labelArray.push_back(_mC);

    _masterPtArray.push_back(_mA);
    _masterPtArray.push_back(_mB);
    _masterPtArray.push_back(_mC);
    _masterPtArray.push_back(_p0);
}

Triad::~Triad()
{

}

#pragma mark - update

void Triad::update()
{
    /*
     ------------------------------------------------------
     CPS AT PASCALS TRIANGLE AT ROW: 3
     ------------------------------------------------------
     Master Set: ['A', 'B', 'C']
     Triad:
     (n,k):( 3 , 1 )
     [('A',), ('B',), ('C',)]
     count: 3
     */
    _mA->mt = multiplyByCommonTones(vector<Microtone_p> {_A} );
    _mB->mt = multiplyByCommonTones(vector<Microtone_p> {_B} );
    _mC->mt = multiplyByCommonTones(vector<Microtone_p> {_C} );

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mA->mt);
    ma.addMicrotone(_mB->mt);
    ma.addMicrotone(_mC->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()

    // SUBSETS

    /*
     ------------------------------------------------------
     CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 3
     ------------------------------------------------------
     Master Set: ['A', 'B', 'C']
     CPS_2_1:
     (n,k):( 3 , 1 )
     (m,j):( 2 , 1 )
     count: 3
     [[[{'B'}, {'A'}]], [[{'C'}, {'A'}]], [[{'B'}, {'C'}]]]
     */
    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        _cps_2_1_0->setCommonTones(nullptr, getCommonTones());
        _cps_2_1_0->setAB(_A, _B); // [{'B'}, {'A'}]

        _cps_2_1_1->setCommonTones(nullptr, getCommonTones());
        _cps_2_1_1->setAB(_A, _C); // [{'C'}, {'A'}]

        _cps_2_1_2->setCommonTones(nullptr, getCommonTones());
        _cps_2_1_2->setAB(_B, _C); // [{'B'}, {'C'}]
    }
}

#pragma mark - subsets

void Triad::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _cps_2_1_0 = make_shared<CPS_2_1> (_A, _B);
    _cps_2_1_1 = make_shared<CPS_2_1> (_A, _B);
    _cps_2_1_2 = make_shared<CPS_2_1> (_A, _B);

    // array of subsets
    _subsets0.push_back(_cps_2_1_0);
    _subsets0.push_back(_cps_2_1_1);
    _subsets0.push_back(_cps_2_1_2);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void Triad::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void Triad::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void Triad::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void Triad::selectS0_3()
{
    jassertfalse;
}

void Triad::selectS0_4()
{
    jassertfalse;
}

void Triad::selectS0_5()
{
    jassertfalse;
}

void Triad::selectS0_6()
{
    jassertfalse;
}

void Triad::selectS0_7()
{
    jassertfalse;
}

void Triad::selectS1_0()
{
    jassertfalse;
}

void Triad::selectS1_1()
{
    jassertfalse;
}

void Triad::selectS1_2()
{
    jassertfalse;
}

void Triad::selectS1_3()
{
    jassertfalse;
}

void Triad::selectS1_4()
{
    jassertfalse;
}

void Triad::selectS1_5()
{
    jassertfalse;
}

void Triad::selectS1_6()
{
    jassertfalse;
}

void Triad::selectS1_7()
{
    jassertfalse;
}

bool Triad::isEulerGenusTuningType()
{
    return false;
}
