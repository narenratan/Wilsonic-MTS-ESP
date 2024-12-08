/*
 ==============================================================================

 OgdoadicDiamond.cpp
 Created: 6 Jun 2023 4:34:00pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "OgdoadicDiamond.h"

OgdoadicDiamond::OgdoadicDiamond(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F, Microtone_p G, Microtone_p H)
: Seed8(A, B, C, D, E, F, G, H)
{
    setCanNPOOverride(true); // redundant, for clarity
    
    // basename
    _tuningType = CPS_Class::OgdoadicDiamond;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

OgdoadicDiamond::OgdoadicDiamond(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed8(master_set, common_tones)
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

OgdoadicDiamond::~OgdoadicDiamond()
{

}

bool OgdoadicDiamond::canPaintTuning()
{
    return true;
}

void OgdoadicDiamond::_commonConstructorHelper()
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
    auto const x7 = 0.34f;
    auto const x8 = 0.39f;
    auto const x9 = 0.40f;
    auto const x10 = 0.42f;
    auto const x11 = 0.45f;
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
    auto const y3 = 0.29f;
    auto const y4 = 0.315f;
    auto const y5 = 0.325f;
    auto const y6 = 0.361f;
    auto const y7 = 0.371f;
    auto const y8 = 0.42f;
    auto const y9 = 0.456f;
    auto const y10 = 0.5f;
    auto const y11 = 1.0f - y9;
    auto const y12 = 1.0f - y8;
    auto const y13 = 1.0f - y7;
    auto const y14 = 1.0f - y6;
    auto const y15 = 1.0f - y5;
    auto const y16 = 1.0f - y4;
    auto const y17 = 1.0f - y3;
    auto const y18 = 1.0f - y2;
    auto const y19 = 1.0f - y1;
    auto const y20 = 1.0f - y0;

    // tones, lines, points
    // A1,B3,C5,D7,E9,F11,G13,H15
    CPSMicrotone& _1_3=_A_B;
    CPSMicrotone& _1_5=_A_C;
    CPSMicrotone& _1_7=_A_D;
    CPSMicrotone& _1_9=_A_E;
    CPSMicrotone& _1_11=_A_F;
    CPSMicrotone& _1_13=_A_G;
    CPSMicrotone& _1_15=_A_H;
    CPSMicrotone& _3_1=_B_A;
    CPSMicrotone& _3_5=_B_C;
    CPSMicrotone& _3_7=_B_D;
    CPSMicrotone& _3_9=_B_E;
    CPSMicrotone& _3_11=_B_F;
    CPSMicrotone& _3_13=_B_G;
    CPSMicrotone& _3_15=_B_H;
    CPSMicrotone& _5_1=_C_A;
    CPSMicrotone& _5_3=_C_B;
    CPSMicrotone& _5_7=_C_D;
    CPSMicrotone& _5_9=_C_E;
    CPSMicrotone& _5_11=_C_F;
    CPSMicrotone& _5_13=_C_G;
    CPSMicrotone& _5_15=_C_H;
    CPSMicrotone& _7_1=_D_A;
    CPSMicrotone& _7_3=_D_B;
    CPSMicrotone& _7_5=_D_C;
    CPSMicrotone& _7_9=_D_E;
    CPSMicrotone& _7_11=_D_F;
    CPSMicrotone& _7_13=_D_G;
    CPSMicrotone& _7_15=_D_H;
    CPSMicrotone& _9_1=_E_A;
    CPSMicrotone& _9_3=_E_B;
    CPSMicrotone& _9_5=_E_C;
    CPSMicrotone& _9_7=_E_D;
    CPSMicrotone& _9_11=_E_F;
    CPSMicrotone& _9_13=_E_G;
    CPSMicrotone& _9_15=_E_H;
    CPSMicrotone& _11_1=_F_A;
    CPSMicrotone& _11_3=_F_B;
    CPSMicrotone& _11_5=_F_C;
    CPSMicrotone& _11_7=_F_D;
    CPSMicrotone& _11_9=_F_E;
    CPSMicrotone& _11_13=_F_G;
    CPSMicrotone& _11_15=_F_H;
    CPSMicrotone& _13_1=_G_A;
    CPSMicrotone& _13_3=_G_B;
    CPSMicrotone& _13_5=_G_C;
    CPSMicrotone& _13_7=_G_D;
    CPSMicrotone& _13_9=_G_E;
    CPSMicrotone& _13_11=_G_F;
    CPSMicrotone& _13_15=_G_H;
    CPSMicrotone& _15_1=_H_A;
    CPSMicrotone& _15_3=_H_B;
    CPSMicrotone& _15_5=_H_C;
    CPSMicrotone& _15_7=_H_D;
    CPSMicrotone& _15_9=_H_E;
    CPSMicrotone& _15_11=_H_F;
    CPSMicrotone& _15_13=_H_G;
    auto const Af = _A->getFrequencyValue();
    auto const Bf = _B->getFrequencyValue();
    auto const Cf = _C->getFrequencyValue();
    auto const Df = _D->getFrequencyValue();
    auto const Ef = _E->getFrequencyValue();
    auto const Ff = _F->getFrequencyValue();
    auto const Gf = _G->getFrequencyValue();
    auto const Hf = _H->getFrequencyValue();

    _1_3 = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::B(Bf)), hpc(x12, y17));
    _1_5 = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::C(Cf)), hpc(x7, y13));
    _1_7 = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::D(Df)), hpc(x5, y9));
    _1_9 = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::E(Ef)), hpc(x9, y4));
    _1_11 = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::F(Ff)), hpc(x15, y4));
    _1_13 = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::G(Gf)), hpc(x19, y9));
    _1_15 = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::H(Hf)), hpc(x17, y13));
    _3_1 = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::A(Af)), hpc(x12, y3));
    _3_5 = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::C(Cf)), hpc(x7, y8));
    _3_7 = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::D(Df)), hpc(x5, y2));
    _3_9 = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::E(Ef)), hpc(x9, y0));
    _3_11 = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::F(Ff)), hpc(x15, y0));
    _3_13 = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::G(Gf)), hpc(x19, y2));
    _3_15 = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::H(Hf)), hpc(x17, y8));
    _5_1 = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::A(Af)), hpc(x17, y7));
    _5_3 = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::B(Bf)), hpc(x17, y12));
    _5_7 = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::D(Df)), hpc(x11, y5));
    _5_9 = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::E(Ef)), hpc(x14, y1));
    _5_11 = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::F(Ff)), hpc(x20, y1));
    _5_13 = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::G(Gf)), hpc(x23, y5));
    _5_15 = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::H(Hf)), hpc(x22, y10));
    _7_1 = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::A(Af)), hpc(x19, y11));
    _7_3 = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::B(Bf)), hpc(x19, y18));
    _7_5 = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::C(Cf)), hpc(x13, y15));
    _7_9 = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::E(Ef)), hpc(x16, y6));
    _7_11 = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::F(Ff)), hpc(x21, y6));
    _7_13 = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::G(Gf)), hpc(x24, y10));
    _7_15 = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::H(Hf)), hpc(x23, y16));
    _9_1 = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::A(Af)), hpc(x15, y16));
    _9_3 = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::B(Bf)), hpc(x15, y20));
    _9_5 = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::C(Cf)), hpc(x10, y19));
    _9_7 = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::D(Df)), hpc(x8, y14));
    _9_11 = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::F(Ff)), hpc(x18, y10));
    _9_13 = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::G(Gf)), hpc(x21, y14));
    _9_15 = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::H(Hf)), hpc(x20, y19));
    _11_1 = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::A(Af)), hpc(x9, y16));
    _11_3 = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::B(Bf)), hpc(x9, y20));
    _11_5 = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::C(Cf)), hpc(x4, y19));
    _11_7 = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::D(Df)), hpc(x3, y14));
    _11_9 = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::E(Ef)), hpc(x6, y10));
    _11_13 = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::G(Gf)), hpc(x16, y14));
    _11_15 = CPSMicrotone_t::create(CPS::A_div_B(CPS::F(Ff), CPS::H(Hf)), hpc(x14, y19));
    _13_1 = CPSMicrotone_t::create(CPS::A_div_B(CPS::G(Gf), CPS::A(Af)), hpc(x5, y11));
    _13_3 = CPSMicrotone_t::create(CPS::A_div_B(CPS::G(Gf), CPS::B(Bf)), hpc(x5, y18));
    _13_5 = CPSMicrotone_t::create(CPS::A_div_B(CPS::G(Gf), CPS::C(Cf)), hpc(x1, y16));
    _13_7 = CPSMicrotone_t::create(CPS::A_div_B(CPS::G(Gf), CPS::D(Df)), hpc(x0, y10));
    _13_9 = CPSMicrotone_t::create(CPS::A_div_B(CPS::G(Gf), CPS::E(Ef)), hpc(x3, y6));
    _13_11 = CPSMicrotone_t::create(CPS::A_div_B(CPS::G(Gf), CPS::F(Ff)), hpc(x8, y6));
    _13_15 = CPSMicrotone_t::create(CPS::A_div_B(CPS::G(Gf), CPS::H(Hf)), hpc(x11, y15));
    _15_1 = CPSMicrotone_t::create(CPS::A_div_B(CPS::H(Hf), CPS::A(Af)), hpc(x7, y7));
    _15_3 = CPSMicrotone_t::create(CPS::A_div_B(CPS::H(Hf), CPS::B(Bf)), hpc(x7, y12));
    _15_5 = CPSMicrotone_t::create(CPS::A_div_B(CPS::H(Hf), CPS::C(Cf)), hpc(x2, y10));
    _15_7 = CPSMicrotone_t::create(CPS::A_div_B(CPS::H(Hf), CPS::D(Df)), hpc(x1, y5));
    _15_9 = CPSMicrotone_t::create(CPS::A_div_B(CPS::H(Hf), CPS::E(Ef)), hpc(x4, y1));
    _15_11 = CPSMicrotone_t::create(CPS::A_div_B(CPS::H(Hf), CPS::F(Ff)), hpc(x10, y1));
    _15_13 = CPSMicrotone_t::create(CPS::A_div_B(CPS::H(Hf), CPS::G(Gf)), hpc(x13, y5));
    _one = CPSMicrotone_t::create(CPS::one(), hpc(x12, y10));

    // lines, in order of appearance
    // rear necklace
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_11, _3_13)); // 0
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_13, _15_13));
    _lineArray.push_back(CPSMicrotone_t::create_line(_15_13, _15_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_15_11, _3_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_13, _5_15)); // 1
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_15, _3_15));
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_15, _3_13));
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_13, _5_13));
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_15, _7_3)); // 2
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_3, _5_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_3, _5_15));
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_15, _7_15));
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_3, _9_5)); // 3
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_5, _7_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_5, _7_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_3, _9_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_5, _11_7)); // 4
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_7, _9_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_7, _9_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_5, _11_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_13_7, _13_9)); // 5
    _lineArray.push_back(CPSMicrotone_t::create_line(_13_9, _11_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_9, _11_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_7, _13_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_15_9, _15_11)); // 6
    _lineArray.push_back(CPSMicrotone_t::create_line(_15_11, _13_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_13_11, _13_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_13_9, _15_9));
    // interior braid
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_1, _5_1));
    _lineArray.push_back(CPSMicrotone_t::create_line(_1_11, _1_13));
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_1, _7_1));
    _lineArray.push_back(CPSMicrotone_t::create_line(_1_13, _1_15));
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_1, _9_1));
    _lineArray.push_back(CPSMicrotone_t::create_line(_1_15, _1_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_1, _11_1));
    _lineArray.push_back(CPSMicrotone_t::create_line(_1_3, _1_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_1, _13_1));
    _lineArray.push_back(CPSMicrotone_t::create_line(_1_5, _1_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_13_1, _15_1));
    _lineArray.push_back(CPSMicrotone_t::create_line(_1_7, _1_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_15_1, _3_1));
    _lineArray.push_back(CPSMicrotone_t::create_line(_1_9, _1_11));
    // front necklace
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_11, _7_11)); // 0
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_11, _7_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_9, _5_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_9, _5_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_13, _9_13)); // 1
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_13, _9_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_11, _7_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_11, _7_13));
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_15, _11_15)); // 2
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_15, _11_13));
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_13, _9_13));
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_13, _9_15));
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_3, _13_3)); // 3
    _lineArray.push_back(CPSMicrotone_t::create_line(_13_3, _13_15));
    _lineArray.push_back(CPSMicrotone_t::create_line(_13_15, _11_15));
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_15, _11_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_13_5, _15_5)); // 4
    _lineArray.push_back(CPSMicrotone_t::create_line(_15_5, _15_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_15_3, _13_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_13_3, _13_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_15_7, _3_7)); // 5
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_7, _3_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_5, _15_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_15_5, _15_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_9, _5_9)); // 6
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_9, _5_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_7, _3_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_7, _3_9));
    // perimeter
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_11, _5_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_11, _5_13));
    _lineArray.push_back(CPSMicrotone_t::create_line(_5_13, _7_13));
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_13, _7_15));
    _lineArray.push_back(CPSMicrotone_t::create_line(_7_15, _9_15));
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_15, _9_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_9_3, _11_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_3, _11_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_11_5, _13_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_13_5, _13_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_13_7, _15_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_15_7, _15_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_15_9, _3_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_3_9, _3_11));
    // origin
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _15_13));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _7_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _3_15));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _9_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _5_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _11_13));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _7_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _13_15));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _9_7));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _15_3));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _11_9));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _3_5));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _13_11));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _5_7));
    
    // labels
    _labelArray.push_back(_A_B);
    _labelArray.push_back(_A_C);
    _labelArray.push_back(_A_D);
    _labelArray.push_back(_A_E);
    _labelArray.push_back(_A_F);
    _labelArray.push_back(_A_G);
    _labelArray.push_back(_A_H);
    _labelArray.push_back(_B_A);
    _labelArray.push_back(_B_C);
    _labelArray.push_back(_B_D);
    _labelArray.push_back(_B_E);
    _labelArray.push_back(_B_F);
    _labelArray.push_back(_B_G);
    _labelArray.push_back(_B_H);
    _labelArray.push_back(_C_A);
    _labelArray.push_back(_C_B);
    _labelArray.push_back(_C_D);
    _labelArray.push_back(_C_E);
    _labelArray.push_back(_C_F);
    _labelArray.push_back(_C_G);
    _labelArray.push_back(_C_H);
    _labelArray.push_back(_D_A);
    _labelArray.push_back(_D_B);
    _labelArray.push_back(_D_C);
    _labelArray.push_back(_D_E);
    _labelArray.push_back(_D_F);
    _labelArray.push_back(_D_G);
    _labelArray.push_back(_D_H);
    _labelArray.push_back(_E_A);
    _labelArray.push_back(_E_B);
    _labelArray.push_back(_E_C);
    _labelArray.push_back(_E_D);
    _labelArray.push_back(_E_F);
    _labelArray.push_back(_E_G);
    _labelArray.push_back(_E_H);
    _labelArray.push_back(_F_A);
    _labelArray.push_back(_F_B);
    _labelArray.push_back(_F_C);
    _labelArray.push_back(_F_D);
    _labelArray.push_back(_F_E);
    _labelArray.push_back(_F_G);
    _labelArray.push_back(_F_H);
    _labelArray.push_back(_G_A);
    _labelArray.push_back(_G_B);
    _labelArray.push_back(_G_C);
    _labelArray.push_back(_G_D);
    _labelArray.push_back(_G_E);
    _labelArray.push_back(_G_F);
    _labelArray.push_back(_G_H);
    _labelArray.push_back(_H_A);
    _labelArray.push_back(_H_B);
    _labelArray.push_back(_H_C);
    _labelArray.push_back(_H_D);
    _labelArray.push_back(_H_E);
    _labelArray.push_back(_H_F);
    _labelArray.push_back(_H_G);
    _labelArray.push_back(_one);

    // all points for drawing
    _masterPtArray.push_back(_A_B);
    _masterPtArray.push_back(_A_C);
    _masterPtArray.push_back(_A_D);
    _masterPtArray.push_back(_A_E);
    _masterPtArray.push_back(_A_F);
    _masterPtArray.push_back(_A_G);
    _masterPtArray.push_back(_A_H);
    _masterPtArray.push_back(_B_A);
    _masterPtArray.push_back(_B_C);
    _masterPtArray.push_back(_B_D);
    _masterPtArray.push_back(_B_E);
    _masterPtArray.push_back(_B_F);
    _masterPtArray.push_back(_B_G);
    _masterPtArray.push_back(_B_H);
    _masterPtArray.push_back(_C_A);
    _masterPtArray.push_back(_C_B);
    _masterPtArray.push_back(_C_D);
    _masterPtArray.push_back(_C_E);
    _masterPtArray.push_back(_C_F);
    _masterPtArray.push_back(_C_G);
    _masterPtArray.push_back(_C_H);
    _masterPtArray.push_back(_D_A);
    _masterPtArray.push_back(_D_B);
    _masterPtArray.push_back(_D_C);
    _masterPtArray.push_back(_D_E);
    _masterPtArray.push_back(_D_F);
    _masterPtArray.push_back(_D_G);
    _masterPtArray.push_back(_D_H);
    _masterPtArray.push_back(_E_A);
    _masterPtArray.push_back(_E_B);
    _masterPtArray.push_back(_E_C);
    _masterPtArray.push_back(_E_D);
    _masterPtArray.push_back(_E_F);
    _masterPtArray.push_back(_E_G);
    _masterPtArray.push_back(_E_H);
    _masterPtArray.push_back(_F_A);
    _masterPtArray.push_back(_F_B);
    _masterPtArray.push_back(_F_C);
    _masterPtArray.push_back(_F_D);
    _masterPtArray.push_back(_F_E);
    _masterPtArray.push_back(_F_G);
    _masterPtArray.push_back(_F_H);
    _masterPtArray.push_back(_G_A);
    _masterPtArray.push_back(_G_B);
    _masterPtArray.push_back(_G_C);
    _masterPtArray.push_back(_G_D);
    _masterPtArray.push_back(_G_E);
    _masterPtArray.push_back(_G_F);
    _masterPtArray.push_back(_G_H);
    _masterPtArray.push_back(_H_A);
    _masterPtArray.push_back(_H_B);
    _masterPtArray.push_back(_H_C);
    _masterPtArray.push_back(_H_D);
    _masterPtArray.push_back(_H_E);
    _masterPtArray.push_back(_H_F);
    _masterPtArray.push_back(_H_G);
    _masterPtArray.push_back(_one);
}

#pragma mark - update

void OgdoadicDiamond::update()
{
    auto const Af = _A->getFrequencyValue();
    auto const Bf = _B->getFrequencyValue();
    auto const Cf = _C->getFrequencyValue();
    auto const Df = _D->getFrequencyValue();
    auto const Ef = _E->getFrequencyValue();
    auto const Ff = _F->getFrequencyValue();
    auto const Gf = _G->getFrequencyValue();
    auto const Hf = _H->getFrequencyValue();

    _A_B->mt = CPS::A_div_B(CPS::A(Af), CPS::B(Bf));
    _A_C->mt = CPS::A_div_B(CPS::A(Af), CPS::C(Cf));
    _A_D->mt = CPS::A_div_B(CPS::A(Af), CPS::D(Df));
    _A_E->mt = CPS::A_div_B(CPS::A(Af), CPS::E(Ef));
    _A_F->mt = CPS::A_div_B(CPS::A(Af), CPS::F(Ff));
    _A_G->mt = CPS::A_div_B(CPS::A(Af), CPS::G(Gf));
    _A_H->mt = CPS::A_div_B(CPS::A(Af), CPS::H(Hf));
    _B_A->mt = CPS::A_div_B(CPS::B(Bf), CPS::A(Af));
    _B_C->mt = CPS::A_div_B(CPS::B(Bf), CPS::C(Cf));
    _B_D->mt = CPS::A_div_B(CPS::B(Bf), CPS::D(Df));
    _B_E->mt = CPS::A_div_B(CPS::B(Bf), CPS::E(Ef));
    _B_F->mt = CPS::A_div_B(CPS::B(Bf), CPS::F(Ff));
    _B_G->mt = CPS::A_div_B(CPS::B(Bf), CPS::G(Gf));
    _B_H->mt = CPS::A_div_B(CPS::B(Bf), CPS::H(Hf));
    _C_A->mt = CPS::A_div_B(CPS::C(Cf), CPS::A(Af));
    _C_B->mt = CPS::A_div_B(CPS::C(Cf), CPS::B(Bf));
    _C_D->mt = CPS::A_div_B(CPS::C(Cf), CPS::D(Df));
    _C_E->mt = CPS::A_div_B(CPS::C(Cf), CPS::E(Ef));
    _C_F->mt = CPS::A_div_B(CPS::C(Cf), CPS::F(Ff));
    _C_G->mt = CPS::A_div_B(CPS::C(Cf), CPS::G(Gf));
    _C_H->mt = CPS::A_div_B(CPS::C(Cf), CPS::H(Hf));
    _D_A->mt = CPS::A_div_B(CPS::D(Df), CPS::A(Af));
    _D_B->mt = CPS::A_div_B(CPS::D(Df), CPS::B(Bf));
    _D_C->mt = CPS::A_div_B(CPS::D(Df), CPS::C(Cf));
    _D_E->mt = CPS::A_div_B(CPS::D(Df), CPS::E(Ef));
    _D_F->mt = CPS::A_div_B(CPS::D(Df), CPS::F(Ff));
    _D_G->mt = CPS::A_div_B(CPS::D(Df), CPS::G(Gf));
    _D_H->mt = CPS::A_div_B(CPS::D(Df), CPS::H(Hf));
    _E_A->mt = CPS::A_div_B(CPS::E(Ef), CPS::A(Af));
    _E_B->mt = CPS::A_div_B(CPS::E(Ef), CPS::B(Bf));
    _E_C->mt = CPS::A_div_B(CPS::E(Ef), CPS::C(Cf));
    _E_D->mt = CPS::A_div_B(CPS::E(Ef), CPS::D(Df));
    _E_F->mt = CPS::A_div_B(CPS::E(Ef), CPS::F(Ff));
    _E_G->mt = CPS::A_div_B(CPS::E(Ef), CPS::G(Gf));
    _E_H->mt = CPS::A_div_B(CPS::E(Ef), CPS::H(Hf));
    _F_A->mt = CPS::A_div_B(CPS::F(Ff), CPS::A(Af));
    _F_B->mt = CPS::A_div_B(CPS::F(Ff), CPS::B(Bf));
    _F_C->mt = CPS::A_div_B(CPS::F(Ff), CPS::C(Cf));
    _F_D->mt = CPS::A_div_B(CPS::F(Ff), CPS::D(Df));
    _F_E->mt = CPS::A_div_B(CPS::F(Ff), CPS::E(Ef));
    _F_G->mt = CPS::A_div_B(CPS::F(Ff), CPS::G(Gf));
    _F_H->mt = CPS::A_div_B(CPS::F(Ff), CPS::H(Hf));
    _G_A->mt = CPS::A_div_B(CPS::G(Gf), CPS::A(Af));
    _G_B->mt = CPS::A_div_B(CPS::G(Gf), CPS::B(Bf));
    _G_C->mt = CPS::A_div_B(CPS::G(Gf), CPS::C(Cf));
    _G_D->mt = CPS::A_div_B(CPS::G(Gf), CPS::D(Df));
    _G_E->mt = CPS::A_div_B(CPS::G(Gf), CPS::E(Ef));
    _G_F->mt = CPS::A_div_B(CPS::G(Gf), CPS::F(Ff));
    _G_H->mt = CPS::A_div_B(CPS::G(Gf), CPS::H(Hf));
    _H_A->mt = CPS::A_div_B(CPS::H(Hf), CPS::A(Af));
    _H_B->mt = CPS::A_div_B(CPS::H(Hf), CPS::B(Bf));
    _H_C->mt = CPS::A_div_B(CPS::H(Hf), CPS::C(Cf));
    _H_D->mt = CPS::A_div_B(CPS::H(Hf), CPS::D(Df));
    _H_E->mt = CPS::A_div_B(CPS::H(Hf), CPS::E(Ef));
    _H_F->mt = CPS::A_div_B(CPS::H(Hf), CPS::F(Ff));
    _H_G->mt = CPS::A_div_B(CPS::H(Hf), CPS::G(Gf));
    //_one->mt  = CPS::A_div_B(CPS::A(1),                       CPS::A(1));

    auto ma = MicrotoneArray();
    ma.addMicrotone(_one->mt);
    ma.addMicrotone(_A_B->mt);
    ma.addMicrotone(_A_C->mt);
    ma.addMicrotone(_A_D->mt);
    ma.addMicrotone(_A_E->mt);
    ma.addMicrotone(_A_F->mt);
    ma.addMicrotone(_A_G->mt);
    ma.addMicrotone(_A_H->mt);
    ma.addMicrotone(_B_A->mt);
    ma.addMicrotone(_B_C->mt);
    ma.addMicrotone(_B_D->mt);
    ma.addMicrotone(_B_E->mt);
    ma.addMicrotone(_B_F->mt);
    ma.addMicrotone(_B_G->mt);
    ma.addMicrotone(_B_H->mt);
    ma.addMicrotone(_C_A->mt);
    ma.addMicrotone(_C_B->mt);
    ma.addMicrotone(_C_D->mt);
    ma.addMicrotone(_C_E->mt);
    ma.addMicrotone(_C_F->mt);
    ma.addMicrotone(_C_G->mt);
    ma.addMicrotone(_C_H->mt);
    ma.addMicrotone(_D_A->mt);
    ma.addMicrotone(_D_B->mt);
    ma.addMicrotone(_D_C->mt);
    ma.addMicrotone(_D_E->mt);
    ma.addMicrotone(_D_F->mt);
    ma.addMicrotone(_D_G->mt);
    ma.addMicrotone(_D_H->mt);
    ma.addMicrotone(_E_A->mt);
    ma.addMicrotone(_E_B->mt);
    ma.addMicrotone(_E_C->mt);
    ma.addMicrotone(_E_D->mt);
    ma.addMicrotone(_E_F->mt);
    ma.addMicrotone(_E_G->mt);
    ma.addMicrotone(_E_H->mt);
    ma.addMicrotone(_F_A->mt);
    ma.addMicrotone(_F_B->mt);
    ma.addMicrotone(_F_C->mt);
    ma.addMicrotone(_F_D->mt);
    ma.addMicrotone(_F_E->mt);
    ma.addMicrotone(_F_G->mt);
    ma.addMicrotone(_F_H->mt);
    ma.addMicrotone(_G_A->mt);
    ma.addMicrotone(_G_B->mt);
    ma.addMicrotone(_G_C->mt);
    ma.addMicrotone(_G_D->mt);
    ma.addMicrotone(_G_E->mt);
    ma.addMicrotone(_G_F->mt);
    ma.addMicrotone(_G_H->mt);
    ma.addMicrotone(_H_A->mt);
    ma.addMicrotone(_H_B->mt);
    ma.addMicrotone(_H_C->mt);
    ma.addMicrotone(_H_D->mt);
    ma.addMicrotone(_H_E->mt);
    ma.addMicrotone(_H_F->mt);
    ma.addMicrotone(_H_G->mt);

    setMicrotoneArray(ma);

    // SUBSETS

    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        _harmonic_subset_0->setABCDEFGH(_one->mt, _B_A->mt, _C_A->mt, _D_A->mt, _E_A->mt, _F_A->mt, _G_A->mt, _H_A->mt);
        _subharmonic_subset_0->setABCDEFGH(_one->mt, _A_B->mt, _A_C->mt, _A_D->mt, _A_E->mt, _A_F->mt, _A_G->mt, _A_H->mt);

        _harmonic_subset_1->setABCDEFGH(_one->mt, _C_B->mt, _D_B->mt, _E_B->mt, _F_B->mt, _G_B->mt, _H_B->mt, _A_B->mt);
        _subharmonic_subset_1->setABCDEFGH(_one->mt, _B_C->mt, _B_D->mt, _B_E->mt, _B_F->mt, _B_G->mt, _B_H->mt, _B_A->mt);

        _harmonic_subset_2->setABCDEFGH(_one->mt, _D_C->mt, _E_C->mt, _F_C->mt, _G_C->mt, _H_C->mt, _A_C->mt, _B_C->mt);
        _subharmonic_subset_2->setABCDEFGH(_one->mt, _C_D->mt, _C_E->mt, _C_F->mt, _C_G->mt, _C_H->mt, _C_A->mt, _C_B->mt);

        _harmonic_subset_3->setABCDEFGH(_one->mt, _E_D->mt, _F_D->mt, _G_D->mt, _H_D->mt, _A_D->mt, _B_D->mt, _C_D->mt);
        _subharmonic_subset_3->setABCDEFGH(_one->mt, _D_E->mt, _D_F->mt, _D_G->mt, _D_H->mt, _D_A->mt, _D_B->mt, _D_C->mt);

        _harmonic_subset_4->setABCDEFGH(_one->mt, _F_E->mt, _G_E->mt, _H_E->mt, _A_E->mt, _B_E->mt, _C_E->mt, _D_E->mt);
        _subharmonic_subset_4->setABCDEFGH(_one->mt, _E_F->mt, _E_G->mt, _E_H->mt, _E_A->mt, _E_B->mt, _E_C->mt, _E_D->mt);

        _harmonic_subset_5->setABCDEFGH(_one->mt, _G_F->mt, _H_F->mt, _A_F->mt, _B_F->mt, _C_F->mt, _D_F->mt, _E_F->mt);
        _subharmonic_subset_5->setABCDEFGH(_one->mt, _F_G->mt, _F_H->mt, _F_A->mt, _F_B->mt, _F_C->mt, _F_D->mt, _F_E->mt);

        _harmonic_subset_6->setABCDEFGH(_one->mt, _H_G->mt, _A_G->mt, _B_G->mt, _C_G->mt, _D_G->mt, _E_G->mt, _F_G->mt);
        _subharmonic_subset_6->setABCDEFGH(_one->mt, _G_H->mt, _G_A->mt, _G_B->mt, _G_C->mt, _G_D->mt, _G_E->mt, _G_F->mt);

        _harmonic_subset_7->setABCDEFGH(_one->mt, _A_H->mt, _B_H->mt, _C_H->mt, _D_H->mt, _E_H->mt, _F_H->mt, _G_H->mt);
        _subharmonic_subset_7->setABCDEFGH(_one->mt, _H_A->mt, _H_B->mt, _H_C->mt, _H_D->mt, _H_E->mt, _H_F->mt, _H_G->mt);
    }
}


#pragma mark - subsets

void OgdoadicDiamond::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _harmonic_subset_0 = make_shared<Ogdoad> (_A, _B, _C, _D, _E, _F, _G, _H, true);
    _harmonic_subset_1 = make_shared<Ogdoad> (_A, _B, _C, _D, _E, _F, _G, _H, true);
    _harmonic_subset_2 = make_shared<Ogdoad> (_A, _B, _C, _D, _E, _F, _G, _H, true);
    _harmonic_subset_3 = make_shared<Ogdoad> (_A, _B, _C, _D, _E, _F, _G, _H, true);
    _harmonic_subset_4 = make_shared<Ogdoad> (_A, _B, _C, _D, _E, _F, _G, _H, true);
    _harmonic_subset_5 = make_shared<Ogdoad> (_A, _B, _C, _D, _E, _F, _G, _H, true);
    _harmonic_subset_6 = make_shared<Ogdoad> (_A, _B, _C, _D, _E, _F, _G, _H, true);
    _harmonic_subset_7 = make_shared<Ogdoad> (_A, _B, _C, _D, _E, _F, _G, _H, true);

    _subharmonic_subset_0 = make_shared<Ogdoad> (_A, _B, _C, _D, _E, _F, _G, _H, false);
    _subharmonic_subset_1 = make_shared<Ogdoad> (_A, _B, _C, _D, _E, _F, _G, _H, false);
    _subharmonic_subset_2 = make_shared<Ogdoad> (_A, _B, _C, _D, _E, _F, _G, _H, false);
    _subharmonic_subset_3 = make_shared<Ogdoad> (_A, _B, _C, _D, _E, _F, _G, _H, false);
    _subharmonic_subset_4 = make_shared<Ogdoad> (_A, _B, _C, _D, _E, _F, _G, _H, false);
    _subharmonic_subset_5 = make_shared<Ogdoad> (_A, _B, _C, _D, _E, _F, _G, _H, false);
    _subharmonic_subset_6 = make_shared<Ogdoad> (_A, _B, _C, _D, _E, _F, _G, _H, false);
    _subharmonic_subset_7 = make_shared<Ogdoad> (_A, _B, _C, _D, _E, _F, _G, _H, false);

    // subsets 0
    _subsets0.push_back(_harmonic_subset_0);
    _subsets0.push_back(_harmonic_subset_1);
    _subsets0.push_back(_harmonic_subset_2);
    _subsets0.push_back(_harmonic_subset_3);
    _subsets0.push_back(_harmonic_subset_4);
    _subsets0.push_back(_harmonic_subset_5);
    _subsets0.push_back(_harmonic_subset_6);
    _subsets0.push_back(_harmonic_subset_7);

    // subsets 1
    _subsets1.push_back(_subharmonic_subset_0);
    _subsets1.push_back(_subharmonic_subset_1);
    _subsets1.push_back(_subharmonic_subset_2);
    _subsets1.push_back(_subharmonic_subset_3);
    _subsets1.push_back(_subharmonic_subset_4);
    _subsets1.push_back(_subharmonic_subset_5);
    _subsets1.push_back(_subharmonic_subset_6);
    _subsets1.push_back(_subharmonic_subset_7);
    
    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void OgdoadicDiamond::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void OgdoadicDiamond::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void OgdoadicDiamond::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void OgdoadicDiamond::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void OgdoadicDiamond::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void OgdoadicDiamond::selectS0_5()
{
    _clearSelection();
    _subsets0[5]->setIsSelected(true);
}

void OgdoadicDiamond::selectS0_6()
{
    _clearSelection();
    _subsets0[6]->setIsSelected(true);
}

void OgdoadicDiamond::selectS0_7()
{
    _clearSelection();
    _subsets0[7]->setIsSelected(true);
}

void OgdoadicDiamond::selectS1_0()
{
    _clearSelection();
    _subsets1[0]->setIsSelected(true);
}

void OgdoadicDiamond::selectS1_1()
{
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void OgdoadicDiamond::selectS1_2()
{
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void OgdoadicDiamond::selectS1_3()
{
    _clearSelection();
    _subsets1[3]->setIsSelected(true);
}

void OgdoadicDiamond::selectS1_4()
{
    _clearSelection();
    _subsets1[4]->setIsSelected(true);
}

void OgdoadicDiamond::selectS1_5()
{
    _clearSelection();
    _subsets1[5]->setIsSelected(true);
}

void OgdoadicDiamond::selectS1_6()
{
    _clearSelection();
    _subsets1[6]->setIsSelected(true);
}

void OgdoadicDiamond::selectS1_7()
{
    _clearSelection();
    _subsets1[7]->setIsSelected(true);
}

bool OgdoadicDiamond::isEulerGenusTuningType()
{
    return false;
}

#pragma mark - description

const string OgdoadicDiamond::getShortDescriptionText()
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
    retVal += ",";
    retVal += getH()->getShortDescriptionText();
    retVal += ")";

    return retVal;
}
