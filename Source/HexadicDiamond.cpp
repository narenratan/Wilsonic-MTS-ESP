/*
 ==============================================================================

 HexadicDiamond.cpp
 Created: 6 Jun 2023 4:32:54pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "HexadicDiamond.h"
#include "CPS.h"

#pragma mark - lifecycle

HexadicDiamond::HexadicDiamond(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F)
: Seed6(A, B, C, D, E, F) // Replaced Seed5 with Seed6
{
    setCanNPOOverride(true); // redundant, for clarity
    
    // basename
    _tuningType = CPS_Class::HexadicDiamond;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

HexadicDiamond::HexadicDiamond(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed6(master_set, common_tones) // Replaced Seed5 with Seed6
{
    // no common tones for HexadicDiamond
    jassertfalse;

    // basename
    _tuningType = CPS_Class::HexadicDiamond;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

HexadicDiamond::~HexadicDiamond()
{

}

bool HexadicDiamond::canPaintTuning()
{
    return true;
}

void HexadicDiamond::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    // custom geometry on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [](auto x, auto y)
    {
        auto xx = 0.5f - x;
        xx *= -1.f;
        auto yy = 0.5f - y;
        yy *= -1.f;
        auto const s = 0.95f;
        xx *= s;
        yy *= s;
        return Point<float>(xx, yy);
    };

    // xfm
    auto const x0 = 0.10f;
    auto const x1 = 0.17f;
    auto const x2 = 0.25f;
    auto const x3 = 0.30f;
    auto const x4 = 0.37f;
    auto const x5 = 0.42f;
    auto const x6 = 0.50f;
    auto const x7 = 1.0f - x5;
    auto const x8 = 1.0f - x4;
    auto const x9 = 1.0f - x3;
    auto const x10 = 1.0f - x2;
    auto const x11 = 1.0f - x1;
    auto const x12 = 1.0f - x0;
    auto const y0 = 0.12f;
    auto const y1 = 0.27f;
    auto const y2 = 0.29f;
    auto const y3 = 0.33f;
    auto const y4 = 0.36f;
    auto const y5 = 0.44f;
    auto const y6 = 0.50f;
    auto const y7 = 1.0f - y5;
    auto const y8 = 1.0f - y4;
    auto const y9 = 1.0f - y3;
    auto const y10 = 1.0f - y2;
    auto const y11 = 1.0f - y1;
    auto const y12 = 1.0f - y0;

    // tones, lines, points
    // A1 B3 C5 D7 E9 F11
    CPSMicrotone& _1_3 = _A_B;
    CPSMicrotone& _1_5 = _A_C;
    CPSMicrotone& _1_7 = _A_D;
    CPSMicrotone& _1_9 = _A_E;
    CPSMicrotone& _1_11 = _A_F;
    CPSMicrotone& _3_1 = _B_A;
    CPSMicrotone& _3_5 = _B_C;
    CPSMicrotone& _3_7 = _B_D;
    CPSMicrotone& _3_9 = _B_E;
    CPSMicrotone& _3_11 = _B_F;
    CPSMicrotone& _5_1 = _C_A;
    CPSMicrotone& _5_3 = _C_B;
    CPSMicrotone& _5_7 = _C_D;
    CPSMicrotone& _5_9 = _C_E;
    CPSMicrotone& _5_11 = _C_F;
    CPSMicrotone& _7_1 = _D_A;
    CPSMicrotone& _7_3 = _D_B;
    CPSMicrotone& _7_5 = _D_C;
    CPSMicrotone& _7_9 = _D_E;
    CPSMicrotone& _7_11 = _D_F;
    CPSMicrotone& _9_1 = _E_A;
    CPSMicrotone& _9_3 = _E_B;
    CPSMicrotone& _9_5 = _E_C;
    CPSMicrotone& _9_7 = _E_D;
    CPSMicrotone& _9_11 = _E_F;
    CPSMicrotone& _11_1 = _F_A;
    CPSMicrotone& _11_3 = _F_B;
    CPSMicrotone& _11_5 = _F_C;
    CPSMicrotone& _11_7 = _F_D;
    CPSMicrotone& _11_9 = _F_E;
    auto const Af = _A->getFrequencyValue();
    auto const Bf = _B->getFrequencyValue();
    auto const Cf = _C->getFrequencyValue();
    auto const Df = _D->getFrequencyValue();
    auto const Ef = _E->getFrequencyValue();
    auto const Ff = _F->getFrequencyValue();
    _1_3 = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::B(Bf)), hpc(x6, y10));
    _1_5 = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::C(Cf)), hpc(x3, y7));
    _1_7 = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::D(Df)), hpc(x4, y3));
    _1_9 = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::E(Ef)), hpc(x8, y3));
    _1_11 = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::F(Ff)), hpc(x9, y7));
    _3_1 = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::A(Af)), hpc(x6, y2));
    _3_5 = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::C(Cf)), hpc(x3, y4));
    _3_7 = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::D(Df)), hpc(x4, y0));
    _3_9 = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::E(Ef)), hpc(x8, y0));
    _3_11 = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::F(Ff)), hpc(x9, y4));
    _5_1 = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::A(Af)), hpc(x9, y5));
    _5_3 = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::B(Bf)), hpc(x9, y8));
    _5_7 = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::D(Df)), hpc(x7, y1));
    _5_9 = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::E(Ef)), hpc(x11, y1));
    _5_11 = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::F(Ff)), hpc(x12, y6));
    _7_1 = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::A(Af)), hpc(x8, y9));
    _7_3 = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::B(Bf)), hpc(x8, y12));
    _7_5 = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::C(Cf)), hpc(x5, y11));
    _7_9 = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::E(Ef)), hpc(x10, y6));
    _7_11 = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::F(Ff)), hpc(x11, y11));
    _9_1 = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::A(Af)), hpc(x4, y9));
    _9_3 = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::B(Bf)), hpc(x4, y12));
    _9_5 = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::C(Cf)), hpc(x1, y11));
    _9_7 = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::D(Df)), hpc(x2, y6));
    _9_11 = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::F(Ff)), hpc(x7, y11));
    _11_1 = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::A(Af)), hpc(x3, y5));
    _11_3 = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::B(Bf)), hpc(x3, y8));
    _11_5 = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::C(Cf)), hpc(x0, y6));
    _11_7 = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::D(Df)), hpc(x1, y1));
    _11_9 = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::E(Ef)), hpc(x5, y1));
    _one = CPSMicrotone_t::create(CPS::one(), hpc(x6, y6));

    // trick to get last interleaf line segment to overlap
    // _1_3 _1_11
    auto tmpPt_1_3 = hpc(x6, y10);
    auto tmpPt_1_11 = hpc(x9, y7);
    auto tmpPt = tmpPt_1_3 + 0.5f * (tmpPt_1_11 - tmpPt_1_3);
    _half_1_3__1_11 = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Ff), CPS::B(Af)), tmpPt);

    // lines, order is important
    // back
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_7, _3_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_5, _11_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_5, _11_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_3, _9_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_3, _9_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_11, _7_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_11, _7_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_9, _5_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_9, _5_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_7, _3_7));
    // root radial
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _3_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _11_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _9_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _7_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _5_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _5_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _3_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _11_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _9_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _7_5));
    // perimeter
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_7, _11_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_7, _11_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_5, _9_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_5, _9_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_3, _7_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_3, _7_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_11, _5_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_11, _5_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_9, _3_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_9, _3_7));
    // interleaf
    _lineArray.push_back(CPSMicrotone_t::create_line(_1_3, _1_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_1, _5_1));
    _lineArray.push_back(CPSMicrotone_t::create_line(_1_11, _1_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_1, _3_1));
    _lineArray.push_back(CPSMicrotone_t::create_line(_1_9, _1_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_1, _11_1));
    _lineArray.push_back(CPSMicrotone_t::create_line(_1_7, _1_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_1, _9_1));
    _lineArray.push_back(CPSMicrotone_t::create_line(_1_5, _1_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_1, _7_1));
    _lineArray.push_back(CPSMicrotone_t::create_line(_1_3, _half_1_3__1_11));
    // front radial
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_9, _11_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_9, _11_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_7, _9_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_7, _9_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_5, _7_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_5, _7_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_3, _5_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_3, _5_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_11, _3_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_11, _3_9));

    // labels
    _labelArray.push_back(_1_3);
    _labelArray.push_back(_1_5);
    _labelArray.push_back(_1_7);
    _labelArray.push_back(_1_9);
    _labelArray.push_back(_1_11);
    _labelArray.push_back(_3_1);
    _labelArray.push_back(_3_5);
    _labelArray.push_back(_3_7);
    _labelArray.push_back(_3_9);
    _labelArray.push_back(_3_11);
    _labelArray.push_back(_5_1);
    _labelArray.push_back(_5_3);
    _labelArray.push_back(_5_7);
    _labelArray.push_back(_5_9);
    _labelArray.push_back(_5_11);
    _labelArray.push_back(_7_1);
    _labelArray.push_back(_7_3);
    _labelArray.push_back(_7_5);
    _labelArray.push_back(_7_9);
    _labelArray.push_back(_7_11);
    _labelArray.push_back(_9_1);
    _labelArray.push_back(_9_3);
    _labelArray.push_back(_9_5);
    _labelArray.push_back(_9_7);
    _labelArray.push_back(_9_11);
    _labelArray.push_back(_11_1);
    _labelArray.push_back(_11_3);
    _labelArray.push_back(_11_5);
    _labelArray.push_back(_11_7);
    _labelArray.push_back(_11_9);
    _labelArray.push_back(_one);

    // all points for drawing
    _masterPtArray.push_back(_1_3);
    _masterPtArray.push_back(_1_5);
    _masterPtArray.push_back(_1_7);
    _masterPtArray.push_back(_1_9);
    _masterPtArray.push_back(_1_11);
    _masterPtArray.push_back(_3_1);
    _masterPtArray.push_back(_3_5);
    _masterPtArray.push_back(_3_7);
    _masterPtArray.push_back(_3_9);
    _masterPtArray.push_back(_3_11);
    _masterPtArray.push_back(_5_1);
    _masterPtArray.push_back(_5_3);
    _masterPtArray.push_back(_5_7);
    _masterPtArray.push_back(_5_9);
    _masterPtArray.push_back(_5_11);
    _masterPtArray.push_back(_7_1);
    _masterPtArray.push_back(_7_3);
    _masterPtArray.push_back(_7_5);
    _masterPtArray.push_back(_7_9);
    _masterPtArray.push_back(_7_11);
    _masterPtArray.push_back(_9_1);
    _masterPtArray.push_back(_9_3);
    _masterPtArray.push_back(_9_5);
    _masterPtArray.push_back(_9_7);
    _masterPtArray.push_back(_9_11);
    _masterPtArray.push_back(_11_1);
    _masterPtArray.push_back(_11_3);
    _masterPtArray.push_back(_11_5);
    _masterPtArray.push_back(_11_7);
    _masterPtArray.push_back(_11_9);
    _masterPtArray.push_back(_one);
}

#pragma mark - update

void HexadicDiamond::update()
{
    auto const A_Freq = _A->getFrequencyValue();
    auto const B_Freq = _B->getFrequencyValue();
    auto const C_Freq = _C->getFrequencyValue();
    auto const D_Freq = _D->getFrequencyValue();
    auto const E_Freq = _E->getFrequencyValue();
    auto const F_Freq = _F->getFrequencyValue();
    _A_B->mt  = CPS::A_div_B(CPS::A(A_Freq), CPS::B(B_Freq));
    _A_C->mt  = CPS::A_div_B(CPS::A(A_Freq), CPS::C(C_Freq));
    _A_D->mt  = CPS::A_div_B(CPS::A(A_Freq), CPS::D(D_Freq));
    _A_E->mt  = CPS::A_div_B(CPS::A(A_Freq), CPS::E(E_Freq));
    _A_F->mt  = CPS::A_div_B(CPS::A(A_Freq), CPS::F(F_Freq));
    _B_A->mt  = CPS::A_div_B(CPS::B(B_Freq), CPS::A(A_Freq));
    _B_C->mt  = CPS::A_div_B(CPS::B(B_Freq), CPS::C(C_Freq));
    _B_D->mt  = CPS::A_div_B(CPS::B(B_Freq), CPS::D(D_Freq));
    _B_E->mt  = CPS::A_div_B(CPS::B(B_Freq), CPS::E(E_Freq));
    _B_F->mt  = CPS::A_div_B(CPS::B(B_Freq), CPS::F(F_Freq));
    _C_A->mt  = CPS::A_div_B(CPS::C(C_Freq), CPS::A(A_Freq));
    _C_B->mt  = CPS::A_div_B(CPS::C(C_Freq), CPS::B(B_Freq));
    _C_D->mt  = CPS::A_div_B(CPS::C(C_Freq), CPS::D(D_Freq));
    _C_E->mt  = CPS::A_div_B(CPS::C(C_Freq), CPS::E(E_Freq));
    _C_F->mt  = CPS::A_div_B(CPS::C(C_Freq), CPS::F(F_Freq));
    _D_A->mt  = CPS::A_div_B(CPS::D(D_Freq), CPS::A(A_Freq));
    _D_B->mt  = CPS::A_div_B(CPS::D(D_Freq), CPS::B(B_Freq));
    _D_C->mt  = CPS::A_div_B(CPS::D(D_Freq), CPS::C(C_Freq));
    _D_E->mt  = CPS::A_div_B(CPS::D(D_Freq), CPS::E(E_Freq));
    _D_F->mt  = CPS::A_div_B(CPS::D(D_Freq), CPS::F(F_Freq));
    _E_A->mt  = CPS::A_div_B(CPS::E(E_Freq), CPS::A(A_Freq));
    _E_B->mt  = CPS::A_div_B(CPS::E(E_Freq), CPS::B(B_Freq));
    _E_C->mt  = CPS::A_div_B(CPS::E(E_Freq), CPS::C(C_Freq));
    _E_D->mt  = CPS::A_div_B(CPS::E(E_Freq), CPS::D(D_Freq));
    _E_F->mt  = CPS::A_div_B(CPS::E(E_Freq), CPS::F(F_Freq));
    _F_A->mt  = CPS::A_div_B(CPS::F(F_Freq), CPS::A(A_Freq));
    _F_B->mt  = CPS::A_div_B(CPS::F(F_Freq), CPS::B(B_Freq));
    _F_C->mt  = CPS::A_div_B(CPS::F(F_Freq), CPS::C(C_Freq));
    _F_D->mt  = CPS::A_div_B(CPS::F(F_Freq), CPS::D(D_Freq));
    _F_E->mt  = CPS::A_div_B(CPS::F(F_Freq), CPS::E(E_Freq));
    //_one->mt  = CPS::A_div_B(CPS::A(1),                       CPS::A(1));

    auto ma = MicrotoneArray();
    ma.addMicrotone(_one->mt);
    ma.addMicrotone(_A_B->mt);
    ma.addMicrotone(_A_C->mt);
    ma.addMicrotone(_A_D->mt);
    ma.addMicrotone(_A_E->mt);
    ma.addMicrotone(_A_F->mt);
    ma.addMicrotone(_B_A->mt);
    ma.addMicrotone(_B_C->mt);
    ma.addMicrotone(_B_D->mt);
    ma.addMicrotone(_B_E->mt);
    ma.addMicrotone(_B_F->mt);
    ma.addMicrotone(_C_A->mt);
    ma.addMicrotone(_C_B->mt);
    ma.addMicrotone(_C_D->mt);
    ma.addMicrotone(_C_E->mt);
    ma.addMicrotone(_C_F->mt);
    ma.addMicrotone(_D_A->mt);
    ma.addMicrotone(_D_B->mt);
    ma.addMicrotone(_D_C->mt);
    ma.addMicrotone(_D_E->mt);
    ma.addMicrotone(_D_F->mt);
    ma.addMicrotone(_E_A->mt);
    ma.addMicrotone(_E_B->mt);
    ma.addMicrotone(_E_C->mt);
    ma.addMicrotone(_E_D->mt);
    ma.addMicrotone(_E_F->mt);
    ma.addMicrotone(_F_A->mt);
    ma.addMicrotone(_F_B->mt);
    ma.addMicrotone(_F_C->mt);
    ma.addMicrotone(_F_D->mt);
    ma.addMicrotone(_F_E->mt);
    
    setMicrotoneArray(ma); // calls update

    // SUBSETS

    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        _harmonic_subset_0->setABCDEF(_one->mt, _B_A->mt, _C_A->mt, _D_A->mt, _E_A->mt, _F_A->mt);
        _subharmonic_subset_0->setABCDEF(_one->mt, _A_B->mt, _A_C->mt, _A_D->mt, _A_E->mt, _A_F->mt);

        _harmonic_subset_1->setABCDEF(_one->mt, _C_B->mt, _D_B->mt, _E_B->mt, _F_B->mt, _A_B->mt);
        _subharmonic_subset_1->setABCDEF(_one->mt, _B_C->mt, _B_D->mt, _B_E->mt, _B_F->mt, _B_A->mt);

        _harmonic_subset_2->setABCDEF(_one->mt, _D_C->mt, _E_C->mt, _F_C->mt, _A_C->mt, _B_C->mt);
        _subharmonic_subset_2->setABCDEF(_one->mt, _C_D->mt, _C_E->mt, _C_F->mt, _C_A->mt, _C_B->mt);

        _harmonic_subset_3->setABCDEF(_one->mt, _E_D->mt, _F_D->mt, _A_D->mt, _B_D->mt, _C_D->mt);
        _subharmonic_subset_3->setABCDEF(_one->mt, _D_E->mt, _D_F->mt, _D_A->mt, _D_B->mt, _D_C->mt);

        _harmonic_subset_4->setABCDEF(_one->mt, _F_E->mt, _A_E->mt, _B_E->mt, _C_E->mt, _D_E->mt);
        _subharmonic_subset_4->setABCDEF(_one->mt, _E_F->mt, _E_A->mt, _E_B->mt, _E_C->mt, _E_D->mt);

        _harmonic_subset_5->setABCDEF(_one->mt, _A_F->mt, _B_F->mt, _C_F->mt, _D_F->mt, _E_F->mt);
        _subharmonic_subset_5->setABCDEF(_one->mt, _F_A->mt, _F_B->mt, _F_C->mt, _F_D->mt, _F_E->mt);
    }
}

#pragma mark - subsets

void HexadicDiamond::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false);

    // will clobber these in update
    _harmonic_subset_0 = make_shared<Hexad> (_A, _B, _C, _D, _E, _F, true);
    _harmonic_subset_1 = make_shared<Hexad> (_A, _B, _C, _D, _E, _F, true);
    _harmonic_subset_2 = make_shared<Hexad> (_A, _B, _C, _D, _E, _F, true);
    _harmonic_subset_3 = make_shared<Hexad> (_A, _B, _C, _D, _E, _F, true);
    _harmonic_subset_4 = make_shared<Hexad> (_A, _B, _C, _D, _E, _F, true);
    _harmonic_subset_5 = make_shared<Hexad> (_A, _B, _C, _D, _E, _F, true);

    _subharmonic_subset_0 = make_shared<Hexad> (_A, _B, _C, _D, _E, _F, false);
    _subharmonic_subset_1 = make_shared<Hexad> (_A, _B, _C, _D, _E, _F, false);
    _subharmonic_subset_2 = make_shared<Hexad> (_A, _B, _C, _D, _E, _F, false);
    _subharmonic_subset_3 = make_shared<Hexad> (_A, _B, _C, _D, _E, _F, false);
    _subharmonic_subset_4 = make_shared<Hexad> (_A, _B, _C, _D, _E, _F, false);
    _subharmonic_subset_5 = make_shared<Hexad> (_A, _B, _C, _D, _E, _F, false);

    // subsets 0
    _subsets0.push_back(_harmonic_subset_0);
    _subsets0.push_back(_harmonic_subset_1);
    _subsets0.push_back(_harmonic_subset_2);
    _subsets0.push_back(_harmonic_subset_3);
    _subsets0.push_back(_harmonic_subset_4);
    _subsets0.push_back(_harmonic_subset_5);

    // subsets 1
    _subsets1.push_back(_subharmonic_subset_0);
    _subsets1.push_back(_subharmonic_subset_1);
    _subsets1.push_back(_subharmonic_subset_2);
    _subsets1.push_back(_subharmonic_subset_3);
    _subsets1.push_back(_subharmonic_subset_4);
    _subsets1.push_back(_subharmonic_subset_5);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void HexadicDiamond::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void HexadicDiamond::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void HexadicDiamond::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void HexadicDiamond::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void HexadicDiamond::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void HexadicDiamond::selectS0_5()
{
    _clearSelection();
    _subsets0[5]->setIsSelected(true);
}

void HexadicDiamond::selectS0_6()
{
    jassertfalse;
}

void HexadicDiamond::selectS0_7()
{
    jassertfalse;
}

void HexadicDiamond::selectS1_0()
{
    _clearSelection();
    _subsets1[0]->setIsSelected(true);}

void HexadicDiamond::selectS1_1()
{
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void HexadicDiamond::selectS1_2()
{
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void HexadicDiamond::selectS1_3()
{
    _clearSelection();
    _subsets1[3]->setIsSelected(true);
}

void HexadicDiamond::selectS1_4()
{
    _clearSelection();
    _subsets1[4]->setIsSelected(true);
}

void HexadicDiamond::selectS1_5()
{
    _clearSelection();
    _subsets1[5]->setIsSelected(true);
}

void HexadicDiamond::selectS1_6()
{
    jassertfalse;
}

void HexadicDiamond::selectS1_7()
{
    jassertfalse;
}

bool HexadicDiamond::isEulerGenusTuningType()
{
    return false;
}

#pragma mark - description

const string HexadicDiamond::getShortDescriptionText()
{
    string retVal = "Pentadic Diamond:(";
    retVal += getA()->getShortDescriptionText();
    retVal += ",";
    retVal += getB()->getShortDescriptionText();
    retVal += ",";
    retVal += getC()->getShortDescriptionText();
    retVal += ",";
    retVal += getD()->getShortDescriptionText();
    retVal += ",";
    retVal += getE()->getShortDescriptionText();
    retVal += ",";
    retVal += getF()->getShortDescriptionText();
    retVal += ")";

    return retVal;
}
