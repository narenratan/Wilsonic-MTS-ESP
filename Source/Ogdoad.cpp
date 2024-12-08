/*
  ==============================================================================

    Ogdoad.cpp
    Created: 20 Jun 2023 8:22:07pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "Ogdoad.h"
#include "CPS.h"
#include "EulerGenusModel.h"

#pragma mark - lifecycle

Ogdoad::Ogdoad(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F, Microtone_p G, Microtone_p H, bool isHarmonic)
: Seed8(A, B, C, D, E, F, G, H)
, _isHarmonic(isHarmonic) {
    setCanNPOOverride(true); // redundant, for clarity
    
    // basename
    _tuningType = CPS_Class::Ogdoad;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

Ogdoad::Ogdoad(vector<Microtone_p> master_set, vector<Microtone_p> common_tones, bool isHarmonic)
: Seed8(master_set, common_tones)
, _isHarmonic(isHarmonic) {
    // basename
    _tuningType = CPS_Class::Ogdoad;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

Ogdoad::~Ogdoad() {

}

bool Ogdoad::canPaintTuning() {
    return true;
}

#pragma mark - drawing

void Ogdoad::_commonConstructorHelper() {
    // custom geometry on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [this](auto x, auto y) {
        auto xx = 0.5f - x;
        xx *= -1.f;
        auto yy = 0.5f - y;
        yy *= -1.f;
        auto const s = (0.8f + 0.1f + 0.1f);
        xx *= s;
        yy *= s;
        if (!_isHarmonic) {
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
    _mH = CPSMicrotone_t::create(_H, hpc(x12, y10));
    _p0 = CPSMicrotone_t::create_center(hpc(x12, y10));

    // F and G are the centers, so always make them the last points
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
    _labelArray.push_back(_mH);

    _masterPtArray.push_back(_mA);
    _masterPtArray.push_back(_mB);
    _masterPtArray.push_back(_mC);
    _masterPtArray.push_back(_mD);
    _masterPtArray.push_back(_mE);
    _masterPtArray.push_back(_mF);
    _masterPtArray.push_back(_mG);
    _masterPtArray.push_back(_mH);
    _masterPtArray.push_back(_p0);
}

#pragma mark - update

void Ogdoad::update() {
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
    if(getShouldComputeSubsets() == true) {
        if(_getDidAllocateSubsets() == false) {
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

        _heptad_0->setCommonTones(nullptr, getCommonTones());
        _heptad_0->setABCDEFG(_A, _B, _C, _D, _E, _F, _G);

        _heptad_1->setCommonTones(nullptr, getCommonTones());
        _heptad_1->setABCDEFG(_A, _B, _C, _D, _E, _F, _H);

        _heptad_2->setCommonTones(nullptr, getCommonTones());
        _heptad_2->setABCDEFG(_A, _B, _C, _D, _E, _G, _H);

        _heptad_3->setCommonTones(nullptr, getCommonTones());
        _heptad_3->setABCDEFG(_A, _B, _C, _D, _F, _G, _H);

        _heptad_4->setCommonTones(nullptr, getCommonTones());
        _heptad_4->setABCDEFG(_A, _B, _C, _E, _F, _G, _H);

        _heptad_5->setCommonTones(nullptr, getCommonTones());
        _heptad_5->setABCDEFG(_A, _B, _D, _E, _F, _G, _H);

        _heptad_6->setCommonTones(nullptr, getCommonTones());
        _heptad_6->setABCDEFG(_A, _C, _D, _E, _F, _G, _H);

        _heptad_7->setCommonTones(nullptr, getCommonTones());
        _heptad_7->setABCDEFG(_B, _C, _D, _E, _F, _G, _H);
    }
}

#pragma mark - subsets

void Ogdoad::_allocateSubsets() {
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    // clobbered in update()
    _heptad_0 = make_shared<Heptad>(_A, _B, _C, _D, _E, _F, _G, true);
    _heptad_1 = make_shared<Heptad>(_A, _B, _C, _D, _E, _F, _H, true);
    _heptad_2 = make_shared<Heptad>(_A, _B, _C, _D, _E, _G, _H, true);
    _heptad_3 = make_shared<Heptad>(_A, _B, _C, _D, _F, _G, _H, true);
    _heptad_4 = make_shared<Heptad>(_A, _B, _C, _E, _F, _G, _H, true);
    _heptad_5 = make_shared<Heptad>(_A, _B, _D, _E, _F, _G, _H, true);
    _heptad_6 = make_shared<Heptad>(_A, _C, _D, _E, _F, _G, _H, true);
    _heptad_7 = make_shared<Heptad>(_B, _C, _D, _E, _F, _G, _H, true);

    // subsets0
    _subsets0.push_back(_heptad_0);
    _subsets0.push_back(_heptad_1);
    _subsets0.push_back(_heptad_2);
    _subsets0.push_back(_heptad_3);
    _subsets0.push_back(_heptad_4);
    _subsets0.push_back(_heptad_5);
    _subsets0.push_back(_heptad_6);
    _subsets0.push_back(_heptad_7);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void Ogdoad::selectS0_0() {
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void Ogdoad::selectS0_1() {
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void Ogdoad::selectS0_2() {
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void Ogdoad::selectS0_3() {
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void Ogdoad::selectS0_4() {
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void Ogdoad::selectS0_5() {
    _clearSelection();
    _subsets0[5]->setIsSelected(true);
}

void Ogdoad::selectS0_6() {
    _clearSelection();
    _subsets0[6]->setIsSelected(true);
}

void Ogdoad::selectS0_7() {
    _clearSelection();
    _subsets0[7]->setIsSelected(true);
}

void Ogdoad::selectS1_0() {
    jassertfalse;
}

void Ogdoad::selectS1_1() {
    jassertfalse;
}

void Ogdoad::selectS1_2() {
    jassertfalse;
}

void Ogdoad::selectS1_3() {
    jassertfalse;
}

void Ogdoad::selectS1_4() {
    jassertfalse;
}

void Ogdoad::selectS1_5() {
    jassertfalse;
}

void Ogdoad::selectS1_6() {
    jassertfalse;
}

void Ogdoad::selectS1_7() {
    jassertfalse;
}

bool Ogdoad::isEulerGenusTuningType() {
    return false;
}
