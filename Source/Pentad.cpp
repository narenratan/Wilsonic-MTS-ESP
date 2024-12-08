/*
  ==============================================================================

    Pentad.cpp
    Created: 20 Jun 2023 8:21:12pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "Pentad.h"
#include "CPS.h"
#include "EulerGenusModel.h"

#pragma mark - lifecycle

Pentad::Pentad(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, bool isHarmonic)
: Seed5(A, B, C, D, E)
, _isHarmonic(isHarmonic)
{
    setCanNPOOverride(true); // redundant, for clarity
    
    // basename
    _tuningType = CPS_Class::Pentad;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

Pentad::Pentad(vector<Microtone_p> master_set, vector<Microtone_p> common_tones, bool isHarmonic)
: Seed5(master_set, common_tones)
, _isHarmonic(isHarmonic)
{
    // basename
    _tuningType = CPS_Class::Pentad;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

Pentad::~Pentad()
{

}

void Pentad::_commonConstructorHelper()
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

    auto hpc = [this] (float x, float y)
    {
        auto const sr3 = 1.f;
        auto xx = -(0.5f - x);
        xx *= sr3;
        auto yy = -(0.5f - y);
        auto s = 0.55708f; // magic
        xx *= s;
        yy *= s;
        if (!_isHarmonic)
        {
            yy *= -1.f;
        }

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

bool Pentad::canPaintTuning()
{
    return true;
}

#pragma mark - update

void Pentad::update()
{
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

    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        _tetrad_0->setCommonTones(nullptr, getCommonTones());
        _tetrad_0->setABCD(_A, _B, _C, _D);

        _tetrad_1->setCommonTones(nullptr, getCommonTones());
        _tetrad_1->setABCD(_A, _B, _C, _E);

        _tetrad_2->setCommonTones(nullptr, getCommonTones());
        _tetrad_2->setABCD(_A, _B, _D, _E);

        _tetrad_3->setCommonTones(nullptr, getCommonTones());
        _tetrad_3->setABCD(_A, _C, _D, _E);

        _tetrad_4->setCommonTones(nullptr, getCommonTones());
        _tetrad_4->setABCD(_B, _C, _D, _E);
    }
}

#pragma mark - subsets

void Pentad::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _tetrad_0 = make_shared<Tetrad> (_A, _B, _C, _D, true);
    _tetrad_1 = make_shared<Tetrad> (_A, _B, _C, _D, true);
    _tetrad_2 = make_shared<Tetrad> (_A, _B, _C, _D, true);
    _tetrad_3 = make_shared<Tetrad> (_A, _B, _C, _D, true);
    _tetrad_4 = make_shared<Tetrad> (_A, _B, _C, _D, true);

    // subsets0
    _subsets0.push_back(_tetrad_0);
    _subsets0.push_back(_tetrad_1);
    _subsets0.push_back(_tetrad_2);
    _subsets0.push_back(_tetrad_3);
    _subsets0.push_back(_tetrad_4);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void Pentad::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void Pentad::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void Pentad::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void Pentad::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void Pentad::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void Pentad::selectS0_5()
{
    jassertfalse;
}

void Pentad::selectS0_6()
{
    jassertfalse;
}

void Pentad::selectS0_7()
{
    jassertfalse;
}

void Pentad::selectS1_0()
{
    jassertfalse;
}

void Pentad::selectS1_1()
{
    jassertfalse;
}

void Pentad::selectS1_2()
{
    jassertfalse;
}

void Pentad::selectS1_3()
{
    jassertfalse;
}

void Pentad::selectS1_4()
{
    jassertfalse;
}

void Pentad::selectS1_5()
{
    jassertfalse;
}

void Pentad::selectS1_6()
{
    jassertfalse;
}

void Pentad::selectS1_7()
{
    jassertfalse;
}

bool Pentad::isEulerGenusTuningType()
{
    return false;
}
