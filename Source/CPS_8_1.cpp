/*
  ==============================================================================

    CPS_8_1.cpp
    Created: 7 Jun 2023 3:55:55pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "CPS_8_1.h"
#include "CPS.h"
#include "EulerGenusModel.h"

#pragma mark - lifecycle

CPS_8_1::CPS_8_1(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F, Microtone_p G, Microtone_p H)
: Seed8(A, B, C, D, E, F, G, H)
{
    // basename
    _tuningType = CPS_Class::CPS_8_1;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_8_1::CPS_8_1(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed8(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_8_1;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_8_1::~CPS_8_1()
{

}

bool CPS_8_1::canPaintTuning()
{
    return true;
}

#pragma mark - drawing

// TODO: fix drawing code
void CPS_8_1::_commonConstructorHelper()
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

    auto hpc = [](auto x, auto y) {
        auto xx = -(0.5f - x);
        auto yy = -(0.5f - y);
        auto s = 0.733f;
        s *= 0.95f;
        xx *= s;
        yy *= s;
        return Point<float>(xx, yy);
    };

    _mA = CPSMicrotone_t::create(_A, hpc(x01, y03));
    _mB = CPSMicrotone_t::create(_B, hpc(x00, y01));
    _mC = CPSMicrotone_t::create(_C, hpc(x02, y00));
    _mD = CPSMicrotone_t::create(_D, hpc(x04, y01));
    _mE = CPSMicrotone_t::create(_E, hpc(x03, y03));
    _mF = CPSMicrotone_t::create(_F, hpc(x02, y02)); // F is the center
    _mG = CPSMicrotone_t::create(_G, hpc(x02, y02)); // Add G
    _mH = CPSMicrotone_t::create(_H, hpc(x02, y02)); // Add H

    _p0 = CPSMicrotone_t::create_center(hpc(x02, y02));

    // F, G, and H are the centers, so always make them the last points
    _lineArray.push_back(CPSMicrotone_t::create_line(_mA, _mF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mB, _mF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mC, _mF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mD, _mF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mE, _mF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mF, _mG)); // Add line for F to G
    _lineArray.push_back(CPSMicrotone_t::create_line(_mG, _mH)); // Add line for G to H

    _labelArray.push_back(_mA);
    _labelArray.push_back(_mB);
    _labelArray.push_back(_mC);
    _labelArray.push_back(_mD);
    _labelArray.push_back(_mE);
    _labelArray.push_back(_mF);
    _labelArray.push_back(_mG); // Add G to label array
    _labelArray.push_back(_mH); // Add H to label array

    _masterPtArray.push_back(_mA);
    _masterPtArray.push_back(_mB);
    _masterPtArray.push_back(_mC);
    _masterPtArray.push_back(_mD);
    _masterPtArray.push_back(_mE);
    _masterPtArray.push_back(_mF);
    _masterPtArray.push_back(_mG); // Add G to master point array
    _masterPtArray.push_back(_mH); // Add H to master point array
    _masterPtArray.push_back(_p0);
}

#pragma mark - update

void CPS_8_1::update()
{
    _mA->mt = multiplyByCommonTones(vector<Microtone_p>{_A});
    _mB->mt = multiplyByCommonTones(vector<Microtone_p>{_B});
    _mC->mt = multiplyByCommonTones(vector<Microtone_p>{_C});
    _mD->mt = multiplyByCommonTones(vector<Microtone_p>{_D});
    _mE->mt = multiplyByCommonTones(vector<Microtone_p>{_E});
    _mF->mt = multiplyByCommonTones(vector<Microtone_p>{_F});
    _mG->mt = multiplyByCommonTones(vector<Microtone_p>{_G});
    _mH->mt = multiplyByCommonTones(vector<Microtone_p>{_H});

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mA->mt);
    ma.addMicrotone(_mB->mt);
    ma.addMicrotone(_mC->mt);
    ma.addMicrotone(_mD->mt);
    ma.addMicrotone(_mE->mt);
    ma.addMicrotone(_mF->mt);
    ma.addMicrotone(_mG->mt);
    ma.addMicrotone(_mH->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()

    // SUBSETS
    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

         // CPS SUBSETS AT PASCALS TRIANGLE AT ROW: 8
         // _A _B _C _D _E _F _G
         // _A _B _C _D _E _F    _H
         // _A _B _C _D _E    _G _H
         // _A _B _C _D    _F _G _H
         // _A _B _C    _E _F _G _H
         // _A _B    _D _E _F _G _H
         // _A    _C _D _E _F _G _H
         //    _B _C _D _E _F _G _H

        _cps_7_1_0->setCommonTones(nullptr, getCommonTones());
        _cps_7_1_0->setABCDEFG(_A, _B, _C, _D, _E, _F, _G);

        _cps_7_1_1->setCommonTones(nullptr, getCommonTones());
        _cps_7_1_1->setABCDEFG(_A, _B, _C, _D, _E, _F, _H);

        _cps_7_1_2->setCommonTones(nullptr, getCommonTones());
        _cps_7_1_2->setABCDEFG(_A, _B, _C, _D, _E, _G, _H);

        _cps_7_1_3->setCommonTones(nullptr, getCommonTones());
        _cps_7_1_3->setABCDEFG(_A, _B, _C, _D, _F, _G, _H);

        _cps_7_1_4->setCommonTones(nullptr, getCommonTones());
        _cps_7_1_4->setABCDEFG(_A, _B, _C, _E, _F, _G, _H);

        _cps_7_1_5->setCommonTones(nullptr, getCommonTones());
        _cps_7_1_5->setABCDEFG(_A, _B, _D, _E, _F, _G, _H);

        _cps_7_1_6->setCommonTones(nullptr, getCommonTones());
        _cps_7_1_6->setABCDEFG(_A, _C, _D, _E, _F, _G, _H);

        _cps_7_1_7->setCommonTones(nullptr, getCommonTones());
        _cps_7_1_7->setABCDEFG(_B, _C, _D, _E, _F, _G, _H);
    }
}

#pragma mark - subsets

void CPS_8_1::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    // clobbered in update()
    _cps_7_1_0 = make_shared<CPS_7_1>(_A, _B, _C, _D, _E, _F, _G);
    _cps_7_1_1 = make_shared<CPS_7_1>(_A, _B, _C, _D, _E, _F, _H);
    _cps_7_1_2 = make_shared<CPS_7_1>(_A, _B, _C, _D, _E, _G, _H);
    _cps_7_1_3 = make_shared<CPS_7_1>(_A, _B, _C, _D, _F, _G, _H);
    _cps_7_1_4 = make_shared<CPS_7_1>(_A, _B, _C, _E, _F, _G, _H);
    _cps_7_1_5 = make_shared<CPS_7_1>(_A, _B, _D, _E, _F, _G, _H);
    _cps_7_1_6 = make_shared<CPS_7_1>(_A, _C, _D, _E, _F, _G, _H);
    _cps_7_1_7 = make_shared<CPS_7_1>(_B, _C, _D, _E, _F, _G, _H);

    // subsets0
    _subsets0.push_back(_cps_7_1_0);
    _subsets0.push_back(_cps_7_1_1);
    _subsets0.push_back(_cps_7_1_2);
    _subsets0.push_back(_cps_7_1_3);
    _subsets0.push_back(_cps_7_1_4);
    _subsets0.push_back(_cps_7_1_5);
    _subsets0.push_back(_cps_7_1_6);
    _subsets0.push_back(_cps_7_1_7);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_8_1::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void CPS_8_1::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void CPS_8_1::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void CPS_8_1::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void CPS_8_1::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void CPS_8_1::selectS0_5()
{
    _clearSelection();
    _subsets0[5]->setIsSelected(true);
}

void CPS_8_1::selectS0_6()
{
    _clearSelection();
    _subsets0[6]->setIsSelected(true);
}

void CPS_8_1::selectS0_7()
{
    _clearSelection();
    _subsets0[7]->setIsSelected(true);
}

void CPS_8_1::selectS1_0()
{
    jassertfalse;
}

void CPS_8_1::selectS1_1()
{
    jassertfalse;
}

void CPS_8_1::selectS1_2()
{
    jassertfalse;
}

void CPS_8_1::selectS1_3()
{
    jassertfalse;
}

void CPS_8_1::selectS1_4()
{
    jassertfalse;
}

void CPS_8_1::selectS1_5()
{
    jassertfalse;
}

void CPS_8_1::selectS1_6()
{
    jassertfalse;
}

void CPS_8_1::selectS1_7()
{
    jassertfalse;
}

bool CPS_8_1::isEulerGenusTuningType()
{
    return false;
}
