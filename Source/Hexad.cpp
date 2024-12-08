/*
  ==============================================================================

    Hexad.cpp
    Created: 20 Jun 2023 8:21:29pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "Hexad.h"
#include "CPS.h"
#include "EulerGenusModel.h"

#pragma mark - lifecycle

Hexad::Hexad(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F, bool isHarmonic)
: Seed6(A, B, C, D, E, F)
, _isHarmonic(isHarmonic)
{
    setCanNPOOverride(true); // redundant, for clarity
    
    // basename
    _tuningType = CPS_Class::Hexad;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

Hexad::Hexad(vector<Microtone_p> master_set, vector<Microtone_p> common_tones, bool isHarmonic)
: Seed6(master_set, common_tones)
, _isHarmonic(isHarmonic)
{
    // basename
    _tuningType = CPS_Class::Hexad;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool Hexad::canPaintTuning()
{
    return true;
}

void Hexad::_commonConstructorHelper()
{
    auto const x00 = 0.085f;
    auto const x01 = 0.240f;
    auto const x02 = 0.500f;
    auto const x03 = 1 - x01;
    auto const x04 = 1 - x00;

    auto const y00 = 0.075f;
    auto const y01 = 0.355f;
    auto const y02 = 0.500f;
    auto const y03 = 0.850f;

    auto hpc = [this] (auto x, auto y)
    {
        auto xx = -(0.5f - x);
        auto yy = -(0.5f - y);
        auto s = 0.733f;
        s *= 0.95f;
        xx *= s;
        yy *= s;
        if (!_isHarmonic)
        {
            yy *= -1.f;
        }

        return Point<float> (xx, yy);
    };

    _mA = CPSMicrotone_t::create(_A, hpc(x01, y03));
    _mB = CPSMicrotone_t::create(_B, hpc(x00, y01));
    _mC = CPSMicrotone_t::create(_C, hpc(x02, y00));
    _mD = CPSMicrotone_t::create(_D, hpc(x04, y01));
    _mE = CPSMicrotone_t::create(_E, hpc(x03, y03));
    _mF = CPSMicrotone_t::create(_F, hpc(x02, y02)); // F is the center
    _p0 = CPSMicrotone_t::create_center(hpc(x02, y02));

    _lineArray.push_back(CPSMicrotone_t::create_line(_mB, _mC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mC, _mD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mD, _mE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mE, _mA));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mA, _mB));

    _labelArray.push_back(_mA);
    _labelArray.push_back(_mB);
    _labelArray.push_back(_mC);
    _labelArray.push_back(_mD);
    _labelArray.push_back(_mE);
    _labelArray.push_back(_mF); // draw F last

    _masterPtArray.push_back(_mA);
    _masterPtArray.push_back(_mB);
    _masterPtArray.push_back(_mC);
    _masterPtArray.push_back(_mD);
    _masterPtArray.push_back(_mE);
    _masterPtArray.push_back(_mF);
    _masterPtArray.push_back(_p0);
}

Hexad::~Hexad()
{

}

#pragma mark - update

void Hexad::update()
{
    _mA->mt = multiplyByCommonTones(vector<Microtone_p> {_A} );
    _mB->mt = multiplyByCommonTones(vector<Microtone_p> {_B} );
    _mC->mt = multiplyByCommonTones(vector<Microtone_p> {_C} );
    _mD->mt = multiplyByCommonTones(vector<Microtone_p> {_D} );
    _mE->mt = multiplyByCommonTones(vector<Microtone_p> {_E} );
    _mF->mt = multiplyByCommonTones(vector<Microtone_p> {_F} );

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mA->mt);
    ma.addMicrotone(_mB->mt);
    ma.addMicrotone(_mC->mt);
    ma.addMicrotone(_mD->mt);
    ma.addMicrotone(_mE->mt);
    ma.addMicrotone(_mF->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()

    // SUBSETS
    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        // CPS SUBSETS AT PASCALS TRIANGLE AT ROW: 6
        // A B C D E
        // A B C D   F
        // A B C   E F
        // A B   D E F
        // A   C D E F
        //   B C D E F
        _pentad_0->setCommonTones(nullptr, getCommonTones());
        _pentad_0->setABCDE(_A, _B, _C, _D, _E);

        _pentad_1->setCommonTones(nullptr, getCommonTones());
        _pentad_1->setABCDE(_A, _B, _C, _D, _F);

        _pentad_2->setCommonTones(nullptr, getCommonTones());
        _pentad_2->setABCDE(_A, _B, _C, _E, _F);

        _pentad_3->setCommonTones(nullptr, getCommonTones());
        _pentad_3->setABCDE(_A, _B, _D, _E, _F);

        _pentad_4->setCommonTones(nullptr, getCommonTones());
        _pentad_4->setABCDE(_A, _C, _D, _E, _F);

        _pentad_5->setCommonTones(nullptr, getCommonTones());
        _pentad_5->setABCDE(_B, _C, _D, _E, _F);
    }
}

#pragma mark - subsets

void Hexad::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    // clobbered in update()
    _pentad_0 = make_shared<Pentad> (_A, _B, _C, _D, _E, true);
    _pentad_1 = make_shared<Pentad> (_A, _B, _C, _D, _E, true);
    _pentad_2 = make_shared<Pentad> (_A, _B, _C, _D, _E, true);
    _pentad_3 = make_shared<Pentad> (_A, _B, _C, _D, _E, true);
    _pentad_4 = make_shared<Pentad> (_A, _B, _C, _D, _E, true);
    _pentad_5 = make_shared<Pentad> (_A, _B, _C, _D, _E, true);

    // subsets0
    _subsets0.push_back(_pentad_0);
    _subsets0.push_back(_pentad_1);
    _subsets0.push_back(_pentad_2);
    _subsets0.push_back(_pentad_3);
    _subsets0.push_back(_pentad_4);
    _subsets0.push_back(_pentad_5);
    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void Hexad::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void Hexad::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void Hexad::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void Hexad::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void Hexad::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void Hexad::selectS0_5()
{
    _clearSelection();
    _subsets0[5]->setIsSelected(true);
}

void Hexad::selectS0_6()
{
    jassertfalse;
}

void Hexad::selectS0_7()
{
    jassertfalse;
}

void Hexad::selectS1_0()
{
    jassertfalse;
}

void Hexad::selectS1_1()
{
    jassertfalse;
}

void Hexad::selectS1_2()
{
    jassertfalse;
}

void Hexad::selectS1_3()
{
    jassertfalse;
}

void Hexad::selectS1_4()
{
    jassertfalse;
}

void Hexad::selectS1_5()
{
    jassertfalse;
}

void Hexad::selectS1_6()
{
    jassertfalse;
}

void Hexad::selectS1_7()
{
    jassertfalse;
}

bool Hexad::isEulerGenusTuningType()
{
    return false;
}

