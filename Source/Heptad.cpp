/*
  ==============================================================================

    Heptad.cpp
    Created: 20 Jun 2023 8:21:47pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "Heptad.h"
#include "CPS.h"
#include "EulerGenusModel.h"
#include "Hexad.h"

#pragma mark - lifecycle

Heptad::Heptad(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F, Microtone_p G, bool isHarmonic)
: Seed7(A, B, C, D, E, F, G)
, _isHarmonic(isHarmonic)
{
    setCanNPOOverride(true); // redundant, for clarity
    
    // basename
    _tuningType = CPS_Class::Heptad;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

Heptad::Heptad(vector<Microtone_p> master_set, vector<Microtone_p> common_tones, bool isHarmonic)
: Seed7(master_set, common_tones)
, _isHarmonic(isHarmonic)
{
    // basename
    _tuningType = CPS_Class::Heptad;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

Heptad::~Heptad()
{

}

bool Heptad::canPaintTuning()
{
    return true;
}

void Heptad::_commonConstructorHelper()
{
    // custom geometry on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [this](auto x, auto y)
    {
        auto xx = 0.5f - x;
        xx *= -1.f;
        auto yy = 0.5f - y;
        yy *= -1.f;
        auto const s = (0.8f + 0.1f + 0.1f);
        xx *= s;
        yy *= s;
        if (!_isHarmonic)
        {
            yy *= -1.f;
        }

        return Point<float>(xx, yy);
    };

    // xfm
    auto const x5 = 0.30f;
    auto const x7 = 0.34f;
    auto const x9 = 0.40f;
    auto const x12 = 0.5f;
    auto const x15 = 1.0f - x9;
    auto const x17 = 1.0f - x7;
    auto const x19 = 1.0f - x5;
    auto const y3 = 0.29f;
    auto const y4 = 0.315f;
    auto const y7 = 0.371f;
    auto const y9 = 0.456f;
    auto const y10 = 0.5f;
    auto const y11 = 1.0f - y9;
    auto const y16 = 1.0f - y4;

    _mA = CPSMicrotone_t::create(_A, hpc(x12, y3));
    _mB = CPSMicrotone_t::create(_B, hpc(x17, y7));
    _mC = CPSMicrotone_t::create(_C, hpc(x19, y11));
    _mD = CPSMicrotone_t::create(_D, hpc(x15, y16));
    _mE = CPSMicrotone_t::create(_E, hpc(x9, y16));
    _mF = CPSMicrotone_t::create(_F, hpc(x5, y11));
    _mG = CPSMicrotone_t::create(_G, hpc(x7, y7));
    _p0 = CPSMicrotone_t::create_center(hpc(x12, y10));

    _lineArray.push_back(CPSMicrotone_t::create_line(_mA, _mB));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mB, _mC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mC, _mD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mD, _mE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mE, _mF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mF, _mG));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mG, _mA));

    _labelArray.push_back(_mA);
    _labelArray.push_back(_mB);
    _labelArray.push_back(_mC);
    _labelArray.push_back(_mD);
    _labelArray.push_back(_mE);
    _labelArray.push_back(_mF);
    _labelArray.push_back(_mG);

    _masterPtArray.push_back(_mA);
    _masterPtArray.push_back(_mB);
    _masterPtArray.push_back(_mC);
    _masterPtArray.push_back(_mD);
    _masterPtArray.push_back(_mE);
    _masterPtArray.push_back(_mF);
    _masterPtArray.push_back(_mG);
    _masterPtArray.push_back(_p0);
}

#pragma mark - update

void Heptad::update()
{
    _mA->mt = multiplyByCommonTones(vector<Microtone_p>{_A});
    _mB->mt = multiplyByCommonTones(vector<Microtone_p>{_B});
    _mC->mt = multiplyByCommonTones(vector<Microtone_p>{_C});
    _mD->mt = multiplyByCommonTones(vector<Microtone_p>{_D});
    _mE->mt = multiplyByCommonTones(vector<Microtone_p>{_E});
    _mF->mt = multiplyByCommonTones(vector<Microtone_p>{_F});
    _mG->mt = multiplyByCommonTones(vector<Microtone_p>{_G});

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mA->mt);
    ma.addMicrotone(_mB->mt);
    ma.addMicrotone(_mC->mt);
    ma.addMicrotone(_mD->mt);
    ma.addMicrotone(_mE->mt);
    ma.addMicrotone(_mF->mt);
    ma.addMicrotone(_mG->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()

    // SUBSETS
    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        //CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 7
        // A B C D E F
        // A B C D E   G
        // A B C D   F G
        // A B C   E F G
        // A B   D E F G
        // A   C D E F G
        //   B C D E F G

        _hexad_0->setCommonTones(nullptr, getCommonTones());
        _hexad_0->setABCDEF(_A, _B, _C, _D, _E, _F);

        _hexad_1->setCommonTones(nullptr, getCommonTones());
        _hexad_1->setABCDEF(_A, _B, _C, _D, _E, _G);

        _hexad_2->setCommonTones(nullptr, getCommonTones());
        _hexad_2->setABCDEF(_A, _B, _C, _E, _F, _G);

        _hexad_3->setCommonTones(nullptr, getCommonTones());
        _hexad_3->setABCDEF(_A, _B, _D, _E, _F, _G);

        _hexad_4->setCommonTones(nullptr, getCommonTones());
        _hexad_4->setABCDEF(_A, _B, _D, _E, _F, _G);

        _hexad_5->setCommonTones(nullptr, getCommonTones());
        _hexad_5->setABCDEF(_A, _C, _D, _E, _F, _G);

        _hexad_6->setCommonTones(nullptr, getCommonTones());
        _hexad_6->setABCDEF(_B, _C, _D, _E, _F, _G);
    }
}

#pragma mark - subsets

void Heptad::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    // clobbered in update()
    _hexad_0 = make_shared<Hexad>(_A, _B, _C, _D, _E, _F, true);
    _hexad_1 = make_shared<Hexad>(_A, _B, _C, _D, _E, _F, true);
    _hexad_2 = make_shared<Hexad>(_A, _B, _C, _D, _E, _F, true);
    _hexad_3 = make_shared<Hexad>(_A, _B, _C, _D, _E, _F, true);
    _hexad_4 = make_shared<Hexad>(_A, _B, _C, _D, _E, _F, true);
    _hexad_5 = make_shared<Hexad>(_A, _B, _C, _D, _E, _F, true);
    _hexad_6 = make_shared<Hexad>(_A, _B, _C, _D, _E, _F, true);

    // subsets0
    _subsets0.push_back(_hexad_0);
    _subsets0.push_back(_hexad_1);
    _subsets0.push_back(_hexad_2);
    _subsets0.push_back(_hexad_3);
    _subsets0.push_back(_hexad_4);
    _subsets0.push_back(_hexad_5);
    _subsets0.push_back(_hexad_6);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void Heptad::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void Heptad::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void Heptad::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void Heptad::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void Heptad::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void Heptad::selectS0_5()
{
    _clearSelection();
    _subsets0[5]->setIsSelected(true);
}

void Heptad::selectS0_6()
{
    _clearSelection();
    _subsets0[6]->setIsSelected(true);
}

void Heptad::selectS0_7()
{
    jassertfalse;
}

void Heptad::selectS1_0()
{
    jassertfalse;
}

void Heptad::selectS1_1()
{
    jassertfalse;
}

void Heptad::selectS1_2()
{
    jassertfalse;
}

void Heptad::selectS1_3()
{
    jassertfalse;
}

void Heptad::selectS1_4()
{
    jassertfalse;
}

void Heptad::selectS1_5()
{
    jassertfalse;
}

void Heptad::selectS1_6()
{
    jassertfalse;
}

void Heptad::selectS1_7()
{
    jassertfalse;
}

bool Heptad::isEulerGenusTuningType()
{
    return false;
}
