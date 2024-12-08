/*
 ==============================================================================

 HeptadicDiamond.cpp
 Created: 6 Jun 2023 4:33:24pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "HeptadicDiamond.h"

HeptadicDiamond::HeptadicDiamond(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F, Microtone_p G)
: Seed7(A, B, C, D, E, F, G)
{
    setCanNPOOverride(true); // redundant, for clarity
    
    // basename
    _tuningType = CPS_Class::HeptadicDiamond;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

HeptadicDiamond::HeptadicDiamond(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed7(master_set, common_tones)
{
    // no common tones for HexadicDiamond
    jassertfalse;

    // basename
    _tuningType = CPS_Class::HeptadicDiamond;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

HeptadicDiamond::~HeptadicDiamond()
{

}

bool HeptadicDiamond::canPaintTuning()
{
    return true;
}

// TODO: Fix Diamond Drawing Code
void HeptadicDiamond::_commonConstructorHelper()
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
    auto const x1 = 0.14f;
    auto const x2 = 0.18f;
    auto const x3 = 0.21f;
    auto const x4 = 0.25f;
    auto const x5 = 0.30f;
    auto const x6 = 0.32f;
    auto const x7 = 0.33f;
    auto const x8 = 0.39f;
    auto const x9 = 0.40f;
    auto const x10 = 0.43f;
    auto const x11 = 0.46f;
    auto const x12 = 0.5f;
    auto const x13 = 1.0f - x11;
    auto const x14 = 1.0f - x10;
    auto const x15 = 1.0f - x9;
    auto const x16 = 1.0f - x8;
    auto const x17 = 1.0f - x7;
    auto const x18 = 1.0f - x6;
    auto const x19 = 1.0f - x5;
    auto const x20 = 1.0f - x4;
    auto const x21 = 1.0f - x3;
    auto const x22 = 1.0f - x2;
    auto const x23 = 1.0f - x1;
    auto const x24 = 1.0f - x0;
    auto const y0 = 0.11f;
    auto const y1 = 0.19f;
    auto const y2 = 0.25f;
    auto const y3 = 0.33f;
    auto const y4 = 0.36f;
    auto const y5 = 0.43f;
    auto const y6 = 0.5f;
    auto const y7 = 1.0f - y5;
    auto const y8 = 1.0f - y4;
    auto const y9 = 1.0f - y3;
    auto const y10 = 1.0f - y2;
    auto const y11 = 1.0f - y1;
    auto const y12 = 1.0f - y0;

    // tones, lines, points
    auto const Af = _A->getFrequencyValue();
    auto const Bf = _B->getFrequencyValue();
    auto const Cf = _C->getFrequencyValue();
    auto const Df = _D->getFrequencyValue();
    auto const Ef = _E->getFrequencyValue();
    auto const Ff = _F->getFrequencyValue();
    auto const Gf = _G->getFrequencyValue();
    _A_B = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::B(Bf)), hpc(x7, y5));
    _A_C = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::C(Cf)), hpc(x5, y2));
    _A_D = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::D(Df)), hpc(x9, y0));
    _A_E = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::E(Ef)), hpc(x15, y0));
    _A_F = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::F(Ff)), hpc(x19, y2));
    _A_G = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::G(Gf)), hpc(x17, y5));
    _B_A = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::A(Af)), hpc(x17, y7));
    _B_C = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::C(Cf)), hpc(x11, y3));
    _B_D = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::D(Df)), hpc(x14, y1));
    _B_E = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::E(Ef)), hpc(x20, y1));
    _B_F = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::F(Ff)), hpc(x23, y3));
    _B_G = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::G(Gf)), hpc(x22, y6));
    _C_A = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::A(Af)), hpc(x19, y10));
    _C_B = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::B(Bf)), hpc(x13, y9));
    _C_D = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::D(Df)), hpc(x16, y4));
    _C_E = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::E(Ef)), hpc(x21, y4));
    _C_F = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::F(Ff)), hpc(x24, y6));
    _C_G = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::G(Gf)), hpc(x23, y9));
    _D_A = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::A(Af)), hpc(x15, y12));
    _D_B = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::B(Bf)), hpc(x10, y11));
    _D_C = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::C(Cf)), hpc(x8, y8));
    _D_E = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::E(Ef)), hpc(x18, y6));
    _D_F = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::F(Ff)), hpc(x21, y8));
    _D_G = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::G(Gf)), hpc(x20, y11));
    _E_A = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::A(Af)), hpc(x9, y12));
    _E_B = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::B(Bf)), hpc(x4, y11));
    _E_C = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::C(Cf)), hpc(x3, y8));
    _E_D = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::D(Df)), hpc(x5, y6));
    _E_F = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::F(Ff)), hpc(x16, y8));
    _E_G = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::G(Gf)), hpc(x14, y11));
    _F_A = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::A(Af)), hpc(x5, y10));
    _F_B = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::B(Bf)), hpc(x1, y9));
    _F_C = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::C(Cf)), hpc(x0, y6));
    _F_D = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::D(Df)), hpc(x3, y4));
    _F_E = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::E(Ef)), hpc(x8, y4));
    _F_G = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::G(Gf)), hpc(x11, y9));
    _G_A = CPSMicrotone_t::create(CPS::A_div_B(CPS::G(Gf), CPS::A(Af)), hpc(x7, y7));
    _G_B = CPSMicrotone_t::create(CPS::A_div_B(CPS::G(Gf), CPS::B(Bf)), hpc(x2, y6));
    _G_C = CPSMicrotone_t::create(CPS::A_div_B(CPS::G(Gf), CPS::C(Cf)), hpc(x1, y3));
    _G_D = CPSMicrotone_t::create(CPS::A_div_B(CPS::G(Gf), CPS::D(Df)), hpc(x4, y1));
    _G_E = CPSMicrotone_t::create(CPS::A_div_B(CPS::G(Gf), CPS::E(Ef)), hpc(x10, y1));
    _G_F = CPSMicrotone_t::create(CPS::A_div_B(CPS::G(Gf), CPS::F(Ff)), hpc(x13, y3));
    _one = CPSMicrotone_t::create(CPS::one(), hpc(x12, y6));

    // lines, in order of appearance
    // rear necklace, groups of 4 lines
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_E, _A_F));//0
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_F, _G_F));
    _lineArray.push_back(CPSMicrotone_t::create_line(_G_F, _G_E));
    _lineArray.push_back(CPSMicrotone_t::create_line(_G_E, _A_E));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_F, _B_G));//1
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_G, _A_G));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_G, _A_F));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_F, _B_F));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_G, _C_A));//2
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_A, _B_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_A, _B_G));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_G, _C_G));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_A, _D_B));//3
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_B, _C_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_B, _C_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_A, _D_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_B, _E_C));//4
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_C, _D_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_C, _D_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_B, _E_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_F_C, _F_D));//5
    _lineArray.push_back(CPSMicrotone_t::create_line(_F_D, _E_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_D, _E_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_C, _F_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_G_D, _G_E));//6
    _lineArray.push_back(CPSMicrotone_t::create_line(_G_E, _F_E));
    _lineArray.push_back(CPSMicrotone_t::create_line(_F_E, _F_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_F_D, _G_D));
    // rear necklace to 1/1
    _lineArray.push_back(CPSMicrotone_t::create_line(_G_F, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_G, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_A, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_B, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_C, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_D, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_F_E, _one));
    //front necklace, groups of 4 lines
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_E, _C_E));//0
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_E, _C_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_D, _B_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_D, _B_E));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_F, _D_F));//1
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_F, _D_E));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_E, _C_E));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_E, _C_F));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_G, _E_G));//2
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_G, _E_F));
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_F, _D_F));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_F, _D_G));
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_A, _F_A));//3
    _lineArray.push_back(CPSMicrotone_t::create_line(_F_A, _F_G));
    _lineArray.push_back(CPSMicrotone_t::create_line(_F_G, _E_G));
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_G, _E_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_F_B, _G_B));//4
    _lineArray.push_back(CPSMicrotone_t::create_line(_G_B, _G_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_G_A, _F_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_F_A, _F_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_G_C, _A_C));//5
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_C, _A_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_B, _G_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_G_B, _G_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_D, _B_D));//6
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_D, _B_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_C, _A_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_C, _A_D));
    // front necklace to 1/1
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_D, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_E, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_F, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_F_G, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_G_A, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_B, _one));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_C, _one));
    // perimeter
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_E, _B_E));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_E, _B_F));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_F, _C_F));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_F, _C_G));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_G, _D_G));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_G, _D_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_A, _E_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_A, _E_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_B, _F_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_F_B, _F_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_F_C, _G_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_G_C, _G_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_G_D, _A_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_D, _A_E));

    // labels
    _labelArray.push_back(_A_B);
    _labelArray.push_back(_A_C);
    _labelArray.push_back(_A_D);
    _labelArray.push_back(_A_E);
    _labelArray.push_back(_A_F);
    _labelArray.push_back(_A_G);
    _labelArray.push_back(_B_A);
    _labelArray.push_back(_B_C);
    _labelArray.push_back(_B_D);
    _labelArray.push_back(_B_E);
    _labelArray.push_back(_B_F);
    _labelArray.push_back(_B_G);
    _labelArray.push_back(_C_A);
    _labelArray.push_back(_C_B);
    _labelArray.push_back(_C_D);
    _labelArray.push_back(_C_E);
    _labelArray.push_back(_C_F);
    _labelArray.push_back(_C_G);
    _labelArray.push_back(_D_A);
    _labelArray.push_back(_D_B);
    _labelArray.push_back(_D_C);
    _labelArray.push_back(_D_E);
    _labelArray.push_back(_D_F);
    _labelArray.push_back(_D_G);
    _labelArray.push_back(_E_A);
    _labelArray.push_back(_E_B);
    _labelArray.push_back(_E_C);
    _labelArray.push_back(_E_D);
    _labelArray.push_back(_E_F);
    _labelArray.push_back(_E_G);
    _labelArray.push_back(_F_A);
    _labelArray.push_back(_F_B);
    _labelArray.push_back(_F_C);
    _labelArray.push_back(_F_D);
    _labelArray.push_back(_F_E);
    _labelArray.push_back(_F_G);
    _labelArray.push_back(_G_A);
    _labelArray.push_back(_G_B);
    _labelArray.push_back(_G_C);
    _labelArray.push_back(_G_D);
    _labelArray.push_back(_G_E);
    _labelArray.push_back(_G_F);
    _labelArray.push_back(_one);

    // all points for drawing
    _masterPtArray.push_back(_A_B);
    _masterPtArray.push_back(_A_C);
    _masterPtArray.push_back(_A_D);
    _masterPtArray.push_back(_A_E);
    _masterPtArray.push_back(_A_F);
    _masterPtArray.push_back(_A_G);
    _masterPtArray.push_back(_B_A);
    _masterPtArray.push_back(_B_C);
    _masterPtArray.push_back(_B_D);
    _masterPtArray.push_back(_B_E);
    _masterPtArray.push_back(_B_F);
    _masterPtArray.push_back(_B_G);
    _masterPtArray.push_back(_C_A);
    _masterPtArray.push_back(_C_B);
    _masterPtArray.push_back(_C_D);
    _masterPtArray.push_back(_C_E);
    _masterPtArray.push_back(_C_F);
    _masterPtArray.push_back(_C_G);
    _masterPtArray.push_back(_D_A);
    _masterPtArray.push_back(_D_B);
    _masterPtArray.push_back(_D_C);
    _masterPtArray.push_back(_D_E);
    _masterPtArray.push_back(_D_F);
    _masterPtArray.push_back(_D_G);
    _masterPtArray.push_back(_E_A);
    _masterPtArray.push_back(_E_B);
    _masterPtArray.push_back(_E_C);
    _masterPtArray.push_back(_E_D);
    _masterPtArray.push_back(_E_F);
    _masterPtArray.push_back(_E_G);
    _masterPtArray.push_back(_F_A);
    _masterPtArray.push_back(_F_B);
    _masterPtArray.push_back(_F_C);
    _masterPtArray.push_back(_F_D);
    _masterPtArray.push_back(_F_E);
    _masterPtArray.push_back(_F_G);
    _masterPtArray.push_back(_G_A);
    _masterPtArray.push_back(_G_B);
    _masterPtArray.push_back(_G_C);
    _masterPtArray.push_back(_G_D);
    _masterPtArray.push_back(_G_E);
    _masterPtArray.push_back(_G_F);
    _masterPtArray.push_back(_one);
}

#pragma mark - update

void HeptadicDiamond::update()
{
    auto const A_Freq = _A->getFrequencyValue();
    auto const B_Freq = _B->getFrequencyValue();
    auto const C_Freq = _C->getFrequencyValue();
    auto const D_Freq = _D->getFrequencyValue();
    auto const E_Freq = _E->getFrequencyValue();
    auto const F_Freq = _F->getFrequencyValue();
    auto const G_Freq = _G->getFrequencyValue();
    _A_B->mt  = CPS::A_div_B(CPS::A(A_Freq), CPS::B(B_Freq));
    _A_C->mt  = CPS::A_div_B(CPS::A(A_Freq), CPS::C(C_Freq));
    _A_D->mt  = CPS::A_div_B(CPS::A(A_Freq), CPS::D(D_Freq));
    _A_E->mt  = CPS::A_div_B(CPS::A(A_Freq), CPS::E(E_Freq));
    _A_F->mt  = CPS::A_div_B(CPS::A(A_Freq), CPS::F(F_Freq));
    _A_G->mt  = CPS::A_div_B(CPS::A(A_Freq), CPS::G(G_Freq));
    _B_A->mt  = CPS::A_div_B(CPS::B(B_Freq), CPS::A(A_Freq));
    _B_C->mt  = CPS::A_div_B(CPS::B(B_Freq), CPS::C(C_Freq));
    _B_D->mt  = CPS::A_div_B(CPS::B(B_Freq), CPS::D(D_Freq));
    _B_E->mt  = CPS::A_div_B(CPS::B(B_Freq), CPS::E(E_Freq));
    _B_F->mt  = CPS::A_div_B(CPS::B(B_Freq), CPS::F(F_Freq));
    _B_G->mt  = CPS::A_div_B(CPS::B(B_Freq), CPS::G(G_Freq));
    _C_A->mt  = CPS::A_div_B(CPS::C(C_Freq), CPS::A(A_Freq));
    _C_B->mt  = CPS::A_div_B(CPS::C(C_Freq), CPS::B(B_Freq));
    _C_D->mt  = CPS::A_div_B(CPS::C(C_Freq), CPS::D(D_Freq));
    _C_E->mt  = CPS::A_div_B(CPS::C(C_Freq), CPS::E(E_Freq));
    _C_F->mt  = CPS::A_div_B(CPS::C(C_Freq), CPS::F(F_Freq));
    _C_G->mt  = CPS::A_div_B(CPS::C(C_Freq), CPS::G(G_Freq));
    _D_A->mt  = CPS::A_div_B(CPS::D(D_Freq), CPS::A(A_Freq));
    _D_B->mt  = CPS::A_div_B(CPS::D(D_Freq), CPS::B(B_Freq));
    _D_C->mt  = CPS::A_div_B(CPS::D(D_Freq), CPS::C(C_Freq));
    _D_E->mt  = CPS::A_div_B(CPS::D(D_Freq), CPS::E(E_Freq));
    _D_F->mt  = CPS::A_div_B(CPS::D(D_Freq), CPS::F(F_Freq));
    _D_G->mt  = CPS::A_div_B(CPS::D(D_Freq), CPS::G(G_Freq));
    _E_A->mt  = CPS::A_div_B(CPS::E(E_Freq), CPS::A(A_Freq));
    _E_B->mt  = CPS::A_div_B(CPS::E(E_Freq), CPS::B(B_Freq));
    _E_C->mt  = CPS::A_div_B(CPS::E(E_Freq), CPS::C(C_Freq));
    _E_D->mt  = CPS::A_div_B(CPS::E(E_Freq), CPS::D(D_Freq));
    _E_F->mt  = CPS::A_div_B(CPS::E(E_Freq), CPS::F(F_Freq));
    _E_G->mt  = CPS::A_div_B(CPS::E(E_Freq), CPS::G(G_Freq));
    _F_A->mt  = CPS::A_div_B(CPS::F(F_Freq), CPS::A(A_Freq));
    _F_B->mt  = CPS::A_div_B(CPS::F(F_Freq), CPS::B(B_Freq));
    _F_C->mt  = CPS::A_div_B(CPS::F(F_Freq), CPS::C(C_Freq));
    _F_D->mt  = CPS::A_div_B(CPS::F(F_Freq), CPS::D(D_Freq));
    _F_E->mt  = CPS::A_div_B(CPS::F(F_Freq), CPS::E(E_Freq));
    _F_G->mt  = CPS::A_div_B(CPS::F(F_Freq), CPS::G(G_Freq));
    _G_A->mt  = CPS::A_div_B(CPS::G(G_Freq), CPS::A(A_Freq));
    _G_B->mt  = CPS::A_div_B(CPS::G(G_Freq), CPS::B(B_Freq));
    _G_C->mt  = CPS::A_div_B(CPS::G(G_Freq), CPS::C(C_Freq));
    _G_D->mt  = CPS::A_div_B(CPS::G(G_Freq), CPS::D(D_Freq));
    _G_E->mt  = CPS::A_div_B(CPS::G(G_Freq), CPS::E(E_Freq));
    _G_F->mt  = CPS::A_div_B(CPS::G(G_Freq), CPS::F(F_Freq));
    // _one->mt = CPS::A_div_B(CPS::A(1), CPS::A(1));

    auto ma = MicrotoneArray();
    ma.addMicrotone(_one->mt);
    ma.addMicrotone(_A_B->mt);
    ma.addMicrotone(_A_C->mt);
    ma.addMicrotone(_A_D->mt);
    ma.addMicrotone(_A_E->mt);
    ma.addMicrotone(_A_F->mt);
    ma.addMicrotone(_A_G->mt);
    ma.addMicrotone(_B_A->mt);
    ma.addMicrotone(_B_C->mt);
    ma.addMicrotone(_B_D->mt);
    ma.addMicrotone(_B_E->mt);
    ma.addMicrotone(_B_F->mt);
    ma.addMicrotone(_B_G->mt);
    ma.addMicrotone(_C_A->mt);
    ma.addMicrotone(_C_B->mt);
    ma.addMicrotone(_C_D->mt);
    ma.addMicrotone(_C_E->mt);
    ma.addMicrotone(_C_F->mt);
    ma.addMicrotone(_C_G->mt);
    ma.addMicrotone(_D_A->mt);
    ma.addMicrotone(_D_B->mt);
    ma.addMicrotone(_D_C->mt);
    ma.addMicrotone(_D_E->mt);
    ma.addMicrotone(_D_F->mt);
    ma.addMicrotone(_D_G->mt);
    ma.addMicrotone(_E_A->mt);
    ma.addMicrotone(_E_B->mt);
    ma.addMicrotone(_E_C->mt);
    ma.addMicrotone(_E_D->mt);
    ma.addMicrotone(_E_F->mt);
    ma.addMicrotone(_E_G->mt);
    ma.addMicrotone(_F_A->mt);
    ma.addMicrotone(_F_B->mt);
    ma.addMicrotone(_F_C->mt);
    ma.addMicrotone(_F_D->mt);
    ma.addMicrotone(_F_E->mt);
    ma.addMicrotone(_F_G->mt);
    ma.addMicrotone(_G_A->mt);
    ma.addMicrotone(_G_B->mt);
    ma.addMicrotone(_G_C->mt);
    ma.addMicrotone(_G_D->mt);
    ma.addMicrotone(_G_E->mt);
    ma.addMicrotone(_G_F->mt);
    setMicrotoneArray(ma); // calls _update()

    // SUBSETS

    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        _harmonic_subset_0->setABCDEFG(_one->mt, _B_A->mt, _C_A->mt, _D_A->mt, _E_A->mt, _F_A->mt, _G_A->mt);
        _subharmonic_subset_0->setABCDEFG(_one->mt, _A_B->mt, _A_C->mt, _A_D->mt, _A_E->mt, _A_F->mt, _A_G->mt);

        _harmonic_subset_1->setABCDEFG(_one->mt, _C_B->mt, _D_B->mt, _E_B->mt, _F_B->mt, _G_B->mt, _A_B->mt);
        _subharmonic_subset_1->setABCDEFG(_one->mt, _B_C->mt, _B_D->mt, _B_E->mt, _B_F->mt, _B_G->mt, _B_A->mt);

        _harmonic_subset_2->setABCDEFG(_one->mt, _D_C->mt, _E_C->mt, _F_C->mt, _G_C->mt, _A_C->mt, _B_C->mt);
        _subharmonic_subset_2->setABCDEFG(_one->mt, _C_D->mt, _C_E->mt, _C_F->mt, _C_G->mt, _C_A->mt, _C_B->mt);

        _harmonic_subset_3->setABCDEFG(_one->mt, _E_D->mt, _F_D->mt, _G_D->mt, _A_D->mt, _B_D->mt, _C_D->mt);
        _subharmonic_subset_3->setABCDEFG(_one->mt, _D_E->mt, _D_F->mt, _D_G->mt, _D_A->mt, _D_B->mt, _D_C->mt);

        _harmonic_subset_4->setABCDEFG(_one->mt, _F_E->mt, _G_E->mt, _A_E->mt, _B_E->mt, _C_E->mt, _D_E->mt);
        _subharmonic_subset_4->setABCDEFG(_one->mt, _E_F->mt, _E_G->mt, _E_A->mt, _E_B->mt, _E_C->mt, _E_D->mt);

        _harmonic_subset_5->setABCDEFG(_one->mt, _G_F->mt, _A_F->mt, _B_F->mt, _C_F->mt, _D_F->mt, _E_F->mt);
        _subharmonic_subset_5->setABCDEFG(_one->mt, _F_G->mt, _F_A->mt, _F_B->mt, _F_C->mt, _F_D->mt, _F_E->mt);

        _harmonic_subset_6->setABCDEFG(_one->mt, _A_G->mt, _B_G->mt, _C_G->mt, _D_G->mt, _E_G->mt, _F_G->mt);
        _subharmonic_subset_6->setABCDEFG(_one->mt, _G_A->mt, _G_B->mt, _G_C->mt, _G_D->mt, _G_E->mt, _G_F->mt);
    }
}


#pragma mark - subsets

void HeptadicDiamond::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _harmonic_subset_0 = make_shared<Heptad> (_A, _B, _C, _D, _E, _F, _G, true);
    _harmonic_subset_1 = make_shared<Heptad> (_A, _B, _C, _D, _E, _F, _G, true);
    _harmonic_subset_2 = make_shared<Heptad> (_A, _B, _C, _D, _E, _F, _G, true);
    _harmonic_subset_3 = make_shared<Heptad> (_A, _B, _C, _D, _E, _F, _G, true);
    _harmonic_subset_4 = make_shared<Heptad> (_A, _B, _C, _D, _E, _F, _G, true);
    _harmonic_subset_5 = make_shared<Heptad> (_A, _B, _C, _D, _E, _F, _G, true);
    _harmonic_subset_6 = make_shared<Heptad> (_A, _B, _C, _D, _E, _F, _G, true);

    _subharmonic_subset_0 = make_shared<Heptad> (_A, _B, _C, _D, _E, _F, _G, false);
    _subharmonic_subset_1 = make_shared<Heptad> (_A, _B, _C, _D, _E, _F, _G, false);
    _subharmonic_subset_2 = make_shared<Heptad> (_A, _B, _C, _D, _E, _F, _G, false);
    _subharmonic_subset_3 = make_shared<Heptad> (_A, _B, _C, _D, _E, _F, _G, false);
    _subharmonic_subset_4 = make_shared<Heptad> (_A, _B, _C, _D, _E, _F, _G, false);
    _subharmonic_subset_5 = make_shared<Heptad> (_A, _B, _C, _D, _E, _F, _G, false);
    _subharmonic_subset_6 = make_shared<Heptad> (_A, _B, _C, _D, _E, _F, _G, false);

    // subsets 0
    _subsets0.push_back(_harmonic_subset_0);
    _subsets0.push_back(_harmonic_subset_1);
    _subsets0.push_back(_harmonic_subset_2);
    _subsets0.push_back(_harmonic_subset_3);
    _subsets0.push_back(_harmonic_subset_4);
    _subsets0.push_back(_harmonic_subset_5);
    _subsets0.push_back(_harmonic_subset_6);

    // subsets 1
    _subsets1.push_back(_subharmonic_subset_0);
    _subsets1.push_back(_subharmonic_subset_1);
    _subsets1.push_back(_subharmonic_subset_2);
    _subsets1.push_back(_subharmonic_subset_3);
    _subsets1.push_back(_subharmonic_subset_4);
    _subsets1.push_back(_subharmonic_subset_5);
    _subsets1.push_back(_subharmonic_subset_6);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void HeptadicDiamond::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void HeptadicDiamond::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void HeptadicDiamond::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void HeptadicDiamond::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void HeptadicDiamond::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void HeptadicDiamond::selectS0_5()
{
    _clearSelection();
    _subsets0[5]->setIsSelected(true);
}

void HeptadicDiamond::selectS0_6()
{
    _clearSelection();
    _subsets0[6]->setIsSelected(true);
}

void HeptadicDiamond::selectS0_7()
{
    jassertfalse;
}

void HeptadicDiamond::selectS1_0()
{
    _clearSelection();
    _subsets1[0]->setIsSelected(true);
}

void HeptadicDiamond::selectS1_1()
{
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void HeptadicDiamond::selectS1_2()
{
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void HeptadicDiamond::selectS1_3()
{
    _clearSelection();
    _subsets1[3]->setIsSelected(true);
}

void HeptadicDiamond::selectS1_4()
{
    _clearSelection();
    _subsets1[4]->setIsSelected(true);
}

void HeptadicDiamond::selectS1_5()
{
    _clearSelection();
    _subsets1[5]->setIsSelected(true);
}

void HeptadicDiamond::selectS1_6()
{
    _clearSelection();
    _subsets1[6]->setIsSelected(true);
}

void HeptadicDiamond::selectS1_7()
{
    jassertfalse;
}

bool HeptadicDiamond::isEulerGenusTuningType()
{
    return false;
}

#pragma mark - description

const string HeptadicDiamond::getShortDescriptionText()
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
    retVal += ",";
    retVal += getG()->getShortDescriptionText();
    retVal += ")";

    return retVal;
}
