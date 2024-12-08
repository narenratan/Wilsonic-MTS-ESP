/*
  ==============================================================================

    Tetrad.cpp
    Created: 20 Jun 2023 8:20:46pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "Tetrad.h"
#include "CPS.h"
#include "EulerGenusModel.h"
#include "WilsonicProcessor.h"

#pragma mark - lifecycle

Tetrad::Tetrad(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, bool isHarmonic)
: Seed4(A, B, C, D)
, _isHarmonic(isHarmonic)
{
    setCanNPOOverride(true); // redundant, for clarity
    
    // basename
    _tuningType = CPS_Class::Tetrad;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

Tetrad::Tetrad(vector<Microtone_p> master_set, vector<Microtone_p> common_tones, bool isHarmonic)
: Seed4(master_set, common_tones)
, _isHarmonic(isHarmonic)
{
    // basename
    _tuningType = CPS_Class::Tetrad;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool Tetrad::canPaintTuning()
{
    return true;
}

void Tetrad::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    // custom geometry on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [this](auto x, auto y)
    {
        auto const sr3 = 1.f / (0.5f * sqrtf(3.f));
        auto xx = 0.5f - x;
        xx *= sr3;
        auto yy = 0.5f - y;
        auto const s = 0.4f;
        xx *= s;
        yy *= s;
        if (!_isHarmonic)
        {
            yy *= -1.f;
        }
        
        return Point<float> (xx, yy);
    };

    auto const ysr3 = 1 - (1.f / sqrtf(3));
    _mA = CPSMicrotone_t::create(_A, hpc(0.5f, ysr3));
    _mB = CPSMicrotone_t::create(_B, hpc(0.5f, 1.0f));
    _mC = CPSMicrotone_t::create(_C, hpc(1.0f, 0.0f));
    _mD = CPSMicrotone_t::create(_D, hpc(0.0f, 0.0f));
    _p0 = CPSMicrotone_t::create_center(hpc(0.5f, 0.5f));

    _lineArray.push_back(CPSMicrotone_t::create_line(_mA, _mB));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mB, _mC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mC, _mD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mD, _mB));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mD, _mA));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mC, _mA));

    _labelArray.push_back(_mA);
    _labelArray.push_back(_mB);
    _labelArray.push_back(_mC);
    _labelArray.push_back(_mD);

    _masterPtArray.push_back(_mA);
    _masterPtArray.push_back(_mB);
    _masterPtArray.push_back(_mC);
    _masterPtArray.push_back(_mD);
    _masterPtArray.push_back(_p0);
}

Tetrad::~Tetrad()
{

}

#pragma mark - update

void Tetrad::update()
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
    _mA->mt = multiplyByCommonTones(vector<Microtone_p> {_A} );
    _mB->mt = multiplyByCommonTones(vector<Microtone_p> {_B} );
    _mC->mt = multiplyByCommonTones(vector<Microtone_p> {_C} );
    _mD->mt = multiplyByCommonTones(vector<Microtone_p> {_D} );

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mA->mt);
    ma.addMicrotone(_mB->mt);
    ma.addMicrotone(_mC->mt);
    ma.addMicrotone(_mD->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()

    // SUBSETS

    /*
     ------------------------------------------------------
     CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 4
     (n,k):( 4 , 1 )
     (m,j):( 3 , 1 )
     count: 4
     [[[{'B'}, {'C'}, {'A'}]],
     [[{'D'}, {'B'}, {'A'}]],
     [[{'D'}, {'C'}, {'A'}]],
     [[{'D'}, {'B'}, {'C'}]]]
     ------------------------------------------------------
     */
    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        _triad_0->setCommonTones(nullptr, getCommonTones());
        _triad_0->setABC(_A, _B, _C);

        _triad_1->setCommonTones(nullptr, getCommonTones());
        _triad_1->setABC(_A, _B, _D);

        _triad_2->setCommonTones(nullptr, getCommonTones());
        _triad_2->setABC(_A, _C, _D);

        _triad_3->setCommonTones(nullptr, getCommonTones());
        _triad_3->setABC(_B, _C, _D);
    }
}

#pragma mark - subsets

void Tetrad::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _triad_0 = make_shared<Triad> (_A, _B, _C, true);
    _triad_1 = make_shared<Triad> (_A, _B, _C, true);
    _triad_2 = make_shared<Triad> (_A, _B, _C, true);
    _triad_3 = make_shared<Triad> (_A, _B, _C, true);

    // array of subsets
    _subsets0.push_back(_triad_0);
    _subsets0.push_back(_triad_1);
    _subsets0.push_back(_triad_2);
    _subsets0.push_back(_triad_3);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void Tetrad::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void Tetrad::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void Tetrad::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void Tetrad::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void Tetrad::selectS0_4()
{
    jassertfalse;
}

void Tetrad::selectS0_5()
{
    jassertfalse;
}

void Tetrad::selectS0_6()
{
    jassertfalse;
}

void Tetrad::selectS0_7()
{
    jassertfalse;
}

void Tetrad::selectS1_0()
{
    jassertfalse;
}

void Tetrad::selectS1_1()
{
    jassertfalse;
}

void Tetrad::selectS1_2()
{
    jassertfalse;
}

void Tetrad::selectS1_3()
{
    jassertfalse;
}

void Tetrad::selectS1_4()
{
    jassertfalse;
}

void Tetrad::selectS1_5()
{
    jassertfalse;
}

void Tetrad::selectS1_6()
{
    jassertfalse;
}

void Tetrad::selectS1_7()
{
    jassertfalse;
}

bool Tetrad::isEulerGenusTuningType()
{
    return false;
}
