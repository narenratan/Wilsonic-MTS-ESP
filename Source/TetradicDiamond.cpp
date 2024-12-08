/*
 ==============================================================================

 TetradicDiamond.cpp
 Created: 30 Jan 2022 4:16:50pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "TetradicDiamond.h"
#include "CPS.h"

#pragma mark - lifecycle

TetradicDiamond::TetradicDiamond(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D)
: Seed4(A, B, C, D) {
    setCanNPOOverride(true); // redundant, for clarity
    
    // basename
    _tuningType = CPS_Class::TetradicDiamond;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

TetradicDiamond::TetradicDiamond(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed4(master_set, common_tones) {
    // no common tones for TetradicDiamond
    jassertfalse;

    // basename
    _tuningType = CPS_Class::TetradicDiamond;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

TetradicDiamond::~TetradicDiamond() {

}

void TetradicDiamond::_commonConstructorHelper() {
    // called at construction only, will be updated in update

    // custom geometry on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [](auto x, auto y) {
        auto xx = 0.5f - x;
        xx *= -1.f;
        auto yy = 0.5f - y;
        yy *= -1.f;
        auto const s = 0.743f + 0.04f;
        xx *= s;
        yy *= s;
        return Point<float> (xx, yy);
    };

    // xfm
    auto const x0 = 0.0f;
    auto const x1 = 0.25f;
    auto const x2 = 0.5f;
    auto const x3 = 1.0f - x1;
    auto const x4 = 1.0f;
    auto const y0 = 0.075f;
    auto const y1 = 0.225f;
    auto const y2 = 0.366f;
    auto const y3 = 0.5f;
    auto const y4 = 1.0f - y2;
    auto const y5 = 1.0f - y1;
    auto const y6 = 1.0f - y0;

    // helpers
    auto const Af = _A->getFrequencyValue();
    auto const Bf = _B->getFrequencyValue();
    auto const Cf = _C->getFrequencyValue();
    auto const Df = _D->getFrequencyValue();

    // tones and points
    _A_B = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::B(Bf)), hpc(x1, y6) );
    _A_C = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::C(Cf)), hpc(x0, y3) );
    _A_D = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::D(Df)), hpc(x1, y4) );
    _B_A = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::A(Af)), hpc(x3, y0) );
    _B_C = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::C(Cf)), hpc(x1, y0) );
    _B_D = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::D(Df)), hpc(x2, y1) );
    _C_A = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::A(Af)), hpc(x4, y3) );
    _C_B = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::B(Bf)), hpc(x3, y6) );
    _C_D = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::D(Df)), hpc(x3, y4) );
    _D_A = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::A(Af)), hpc(x3, y2) );
    _D_B = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::B(Bf)), hpc(x2, y5) );
    _D_C = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::C(Cf)), hpc(x1, y2) );
    _one = CPSMicrotone_t::create(CPS::one(), hpc(x2, y3) );

    // lines, order is important
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_B, _C_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_A, _D_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_A, _D_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_B, _C_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_B, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_A, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_B, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_A, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_C, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_C, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_C, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_B, _D_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_C, _D_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_A, _D_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_B, _A_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_A, _B_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_B, _C_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_A, _C_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_B, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_A, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_B, _A_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_A, _B_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_B, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_A, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_D, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_D, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_C, _D_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_C, _D_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_B, _A_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_B, _A_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_A, _B_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_D, _A_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_D, _B_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_C, _B_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_A, _B_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_D, _C_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_D, _B_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_D, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_D, _A_D));

    // labels
    _labelArray.push_back(_A_B);
    _labelArray.push_back(_A_C);
    _labelArray.push_back(_A_D);
    _labelArray.push_back(_B_A);
    _labelArray.push_back(_B_C);
    _labelArray.push_back(_B_D);
    _labelArray.push_back(_C_A);
    _labelArray.push_back(_C_B);
    _labelArray.push_back(_C_D);
    _labelArray.push_back(_D_A);
    _labelArray.push_back(_D_B);
    _labelArray.push_back(_D_C);
    _labelArray.push_back(_one);

    // all points for drawing
    _masterPtArray.push_back(_A_B);
    _masterPtArray.push_back(_A_C);
    _masterPtArray.push_back(_A_D);
    _masterPtArray.push_back(_B_A);
    _masterPtArray.push_back(_B_C);
    _masterPtArray.push_back(_B_D);
    _masterPtArray.push_back(_C_A);
    _masterPtArray.push_back(_C_B);
    _masterPtArray.push_back(_C_D);
    _masterPtArray.push_back(_D_A);
    _masterPtArray.push_back(_D_B);
    _masterPtArray.push_back(_D_C);
    _masterPtArray.push_back(_one);
}

bool TetradicDiamond::canPaintTuning() {
    return true;
}

#pragma mark - update

void TetradicDiamond::update() {
    auto const a_freq = _A->getFrequencyValue();
    auto const b_freq = _B->getFrequencyValue();
    auto const c_freq = _C->getFrequencyValue();
    auto const d_freq = _D->getFrequencyValue();
    _A_B->mt  = CPS::A_div_B(CPS::A(a_freq), CPS::B(b_freq));
    _A_C->mt  = CPS::A_div_B(CPS::A(a_freq), CPS::C(c_freq));
    _A_D->mt  = CPS::A_div_B(CPS::A(a_freq), CPS::D(d_freq));
    _B_A->mt  = CPS::A_div_B(CPS::B(b_freq), CPS::A(a_freq));
    _B_C->mt  = CPS::A_div_B(CPS::B(b_freq), CPS::C(c_freq));
    _B_D->mt  = CPS::A_div_B(CPS::B(b_freq), CPS::D(d_freq));
    _C_A->mt  = CPS::A_div_B(CPS::C(c_freq), CPS::A(a_freq));
    _C_B->mt  = CPS::A_div_B(CPS::C(c_freq), CPS::B(b_freq));
    _C_D->mt  = CPS::A_div_B(CPS::C(c_freq), CPS::D(d_freq));
    _D_A->mt  = CPS::A_div_B(CPS::D(d_freq), CPS::A(a_freq));
    _D_B->mt  = CPS::A_div_B(CPS::D(d_freq), CPS::B(b_freq));
    _D_C->mt  = CPS::A_div_B(CPS::D(d_freq), CPS::C(c_freq));
    //_one->mt  = CPS::A_div_B(CPS::A(1),                       CPS::A(1));

    auto ma = MicrotoneArray();
    ma.addMicrotone(_one->mt);
    ma.addMicrotone(_A_B->mt);
    ma.addMicrotone(_A_C->mt);
    ma.addMicrotone(_A_D->mt);
    ma.addMicrotone(_B_A->mt);
    ma.addMicrotone(_B_C->mt);
    ma.addMicrotone(_B_D->mt);
    ma.addMicrotone(_C_A->mt);
    ma.addMicrotone(_C_B->mt);
    ma.addMicrotone(_C_D->mt);
    ma.addMicrotone(_D_A->mt);
    ma.addMicrotone(_D_B->mt);
    ma.addMicrotone(_D_C->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()

    // SUBSETS

    if(getShouldComputeSubsets() == true) {
        if(_getDidAllocateSubsets() == false) {
            _allocateSubsets();
        }

        _harmonic_subset_0->setABCD(_one->mt, _B_A->mt, _C_A->mt, _D_A->mt);
        _subharmonic_subset_0->setABCD(_one->mt, _A_B->mt, _A_C->mt, _A_D->mt);

        _harmonic_subset_1->setABCD(_one->mt, _C_B->mt, _D_B->mt, _A_B->mt);
        _subharmonic_subset_1->setABCD(_one->mt, _B_C->mt, _B_D->mt, _B_A->mt);

        _harmonic_subset_2->setABCD(_one->mt, _D_C->mt, _A_C->mt, _B_C->mt);
        _subharmonic_subset_2->setABCD(_one->mt, _C_D->mt, _C_A->mt, _C_B->mt);

        _harmonic_subset_3->setABCD(_one->mt, _A_D->mt, _B_D->mt, _C_D->mt);
        _subharmonic_subset_3->setABCD(_one->mt, _D_A->mt, _D_B->mt, _D_C->mt);
    }
}

#pragma mark - subsets

void TetradicDiamond::_allocateSubsets() {
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    // will clobber these in update
    _harmonic_subset_0 = make_shared<Tetrad> (_A, _B, _C, _D, true);
    _harmonic_subset_1 = make_shared<Tetrad> (_A, _B, _C, _D, true);
    _harmonic_subset_2 = make_shared<Tetrad> (_A, _B, _C, _D, true);
    _harmonic_subset_3 = make_shared<Tetrad> (_A, _B, _C, _D, true);

    _subharmonic_subset_0 = make_shared<Tetrad> (_A, _B, _C, _D, false);
    _subharmonic_subset_1 = make_shared<Tetrad> (_A, _B, _C, _D, false);
    _subharmonic_subset_2 = make_shared<Tetrad> (_A, _B, _C, _D, false);
    _subharmonic_subset_3 = make_shared<Tetrad> (_A, _B, _C, _D, false);
    // subsets 0
    _subsets0.push_back(_harmonic_subset_0);
    _subsets0.push_back(_harmonic_subset_1);
    _subsets0.push_back(_harmonic_subset_2);
    _subsets0.push_back(_harmonic_subset_3);

    // subsets 1
    _subsets1.push_back(_subharmonic_subset_0);
    _subsets1.push_back(_subharmonic_subset_1);
    _subsets1.push_back(_subharmonic_subset_2);
    _subsets1.push_back(_subharmonic_subset_3);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void TetradicDiamond::selectS0_0() {
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void TetradicDiamond::selectS0_1() {
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
    ;
}

void TetradicDiamond::selectS0_2() {
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void TetradicDiamond::selectS0_3() {
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void TetradicDiamond::selectS0_4() {
    jassertfalse;
}

void TetradicDiamond::selectS0_5() {
    jassertfalse;
}

void TetradicDiamond::selectS0_6() {
    jassertfalse;
}

void TetradicDiamond::selectS0_7() {
    jassertfalse;
}

void TetradicDiamond::selectS1_0() {
    _clearSelection();
    _subsets1[0]->setIsSelected(true);
}

void TetradicDiamond::selectS1_1() {
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void TetradicDiamond::selectS1_2() {
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void TetradicDiamond::selectS1_3() {
    _clearSelection();
    _subsets1[3]->setIsSelected(true);
}

void TetradicDiamond::selectS1_4() {
    jassertfalse;
}

void TetradicDiamond::selectS1_5() {
    jassertfalse;
}

void TetradicDiamond::selectS1_6() {
    jassertfalse;
}

void TetradicDiamond::selectS1_7() {
    jassertfalse;
}

bool TetradicDiamond::isEulerGenusTuningType() {
    return false;
}

#pragma mark - description

const string TetradicDiamond::getShortDescriptionText() {
    string retVal = "Tetradic Diamond:(";
    retVal += getA()->getShortDescriptionText();
    retVal += ",";
    retVal += getB()->getShortDescriptionText();
    retVal += ",";
    retVal += getC()->getShortDescriptionText();
    retVal += ",";
    retVal += getD()->getShortDescriptionText();
    retVal += ")";

    return retVal;
}
