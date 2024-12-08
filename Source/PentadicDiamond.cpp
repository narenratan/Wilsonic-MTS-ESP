/*
 ==============================================================================

 PentadicDiamond.cpp
 Created: 6 Jun 2023 4:32:22pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "PentadicDiamond.h"
#include "CPS.h"

#pragma mark - lifecycle

PentadicDiamond::PentadicDiamond(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E)
: Seed5(A, B, C, D, E)
{
    setCanNPOOverride(true); // redundant, for clarity
    
    // basename
    _tuningType = CPS_Class::PentadicDiamond;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

PentadicDiamond::PentadicDiamond(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed5(master_set, common_tones)
{
    // no common tones for PentadicDiamond
    jassertfalse;

    // basename
    _tuningType = CPS_Class::PentadicDiamond;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

PentadicDiamond::~PentadicDiamond()
{

}

bool PentadicDiamond::canPaintTuning()
{
    return true;
}

void PentadicDiamond::_commonConstructorHelper()
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
        return Point<float> (xx, yy);
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
    auto const y0 = 0.11f;
    auto const y1 = 0.26f;
    auto const y2 = 0.35f;
    auto const y3 = 0.5f;
    auto const y4 = 1.0f - y2;
    auto const y5 = 1.0f - y1;
    auto const y6 = 1.0f - y0;

    // auto const x_ = 0.f;
    // auto const y_ = 0.f;

    // tones and points
    auto const Af = _A->getFrequencyValue();
    auto const Bf = _B->getFrequencyValue();
    auto const Cf = _C->getFrequencyValue();
    auto const Df = _D->getFrequencyValue();
    auto const Ef = _E->getFrequencyValue();
    _A_B = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::B(Bf)), hpc(x7, y5));
    _A_C = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::C(Cf)), hpc(x4, y6));
    _A_D = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::D(Df)), hpc(x1, y5));
    _A_E = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::E(Ef)), hpc(x2, y3));
    _B_A = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::A(Af)), hpc(x5, y1));
    _B_C = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::C(Cf)), hpc(x3, y4));
    _B_D = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::D(Df)), hpc(x0, y3));
    _B_E = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::E(Ef)), hpc(x1, y1));
    _C_A = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::A(Af)), hpc(x8, y0));
    _C_B = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::B(Bf)), hpc(x9, y2));
    _C_D = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::D(Df)), hpc(x3, y2));
    _C_E = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::E(Ef)), hpc(x4, y0));
    _D_A = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::A(Af)), hpc(x11, y1));
    _D_B = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::B(Bf)), hpc(x12, y3));
    _D_C = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::C(Cf)), hpc(x9, y4));
    _D_E = CPSMicrotone_t::create(CPS::A_div_B(CPS::D(Df), CPS::E(Ef)), hpc(x7, y1));
    _E_A = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::A(Af)), hpc(x10, y3));
    _E_B = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::B(Bf)), hpc(x11, y5));
    _E_C = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::C(Cf)), hpc(x8, y6));
    _E_D = CPSMicrotone_t::create(CPS::A_div_B(CPS::E(Ef), CPS::D(Df)), hpc(x5, y5));
    _one = CPSMicrotone_t::create(CPS::one(), hpc(x6, y3));

    // lines, order is important
    // behind
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_E, _C_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_D, _B_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_D, _B_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_C, _A_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_C, _A_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_B, _E_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_B, _E_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_A, _D_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_A, _D_E));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_E, _C_E));
    // behind
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_A, _B_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_A, _B_E));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_E, _A_E));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_E, _A_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_D, _E_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_D, _E_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_C, _D_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_C, _D_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_B, _C_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_B, _C_A));
    // perimeter
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_E, _B_E));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_E, _B_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_D, _A_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_D, _A_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_C, _E_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_C, _E_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_E_B, _D_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_B, _D_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D_A, _C_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_A, _C_E));
    // radial
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _B_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _C_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _A_E));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _B_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _E_D));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _A_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _D_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _E_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _C_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _D_E));
    
    // labels
    _labelArray.push_back(_A_B);
    _labelArray.push_back(_A_C);
    _labelArray.push_back(_A_D);
    _labelArray.push_back(_A_E);
    _labelArray.push_back(_B_A);
    _labelArray.push_back(_B_C);
    _labelArray.push_back(_B_D);
    _labelArray.push_back(_B_E);
    _labelArray.push_back(_C_A);
    _labelArray.push_back(_C_B);
    _labelArray.push_back(_C_D);
    _labelArray.push_back(_C_E);
    _labelArray.push_back(_D_A);
    _labelArray.push_back(_D_B);
    _labelArray.push_back(_D_C);
    _labelArray.push_back(_D_E);
    _labelArray.push_back(_E_A);
    _labelArray.push_back(_E_B);
    _labelArray.push_back(_E_C);
    _labelArray.push_back(_E_D);
    _labelArray.push_back(_one);

    // all points for drawing
    _masterPtArray.push_back(_A_B);
    _masterPtArray.push_back(_A_C);
    _masterPtArray.push_back(_A_D);
    _masterPtArray.push_back(_A_E);
    _masterPtArray.push_back(_B_A);
    _masterPtArray.push_back(_B_C);
    _masterPtArray.push_back(_B_D);
    _masterPtArray.push_back(_B_E);
    _masterPtArray.push_back(_C_A);
    _masterPtArray.push_back(_C_B);
    _masterPtArray.push_back(_C_D);
    _masterPtArray.push_back(_C_E);
    _masterPtArray.push_back(_D_A);
    _masterPtArray.push_back(_D_B);
    _masterPtArray.push_back(_D_C);
    _masterPtArray.push_back(_D_E);
    _masterPtArray.push_back(_E_A);
    _masterPtArray.push_back(_E_B);
    _masterPtArray.push_back(_E_C);
    _masterPtArray.push_back(_E_D);
    _masterPtArray.push_back(_one);
}

#pragma mark - update

void PentadicDiamond::update()
{
    auto const freqA = _A->getFrequencyValue();
    auto const freqB = _B->getFrequencyValue();
    auto const freqC = _C->getFrequencyValue();
    auto const freqD = _D->getFrequencyValue();
    auto const freqE = _E->getFrequencyValue();
    _A_B->mt  = CPS::A_div_B(CPS::A(freqA), CPS::B(freqB));
    _A_C->mt  = CPS::A_div_B(CPS::A(freqA), CPS::C(freqC));
    _A_D->mt  = CPS::A_div_B(CPS::A(freqA), CPS::D(freqD));
    _A_E->mt  = CPS::A_div_B(CPS::A(freqA), CPS::E(freqE));
    _B_A->mt  = CPS::A_div_B(CPS::B(freqB), CPS::A(freqA));
    _B_C->mt  = CPS::A_div_B(CPS::B(freqB), CPS::C(freqC));
    _B_D->mt  = CPS::A_div_B(CPS::B(freqB), CPS::D(freqD));
    _B_E->mt  = CPS::A_div_B(CPS::B(freqB), CPS::E(freqE));
    _C_A->mt  = CPS::A_div_B(CPS::C(freqC), CPS::A(freqA));
    _C_B->mt  = CPS::A_div_B(CPS::C(freqC), CPS::B(freqB));
    _C_D->mt  = CPS::A_div_B(CPS::C(freqC), CPS::D(freqD));
    _C_E->mt  = CPS::A_div_B(CPS::C(freqC), CPS::E(freqE));
    _D_A->mt  = CPS::A_div_B(CPS::D(freqD), CPS::A(freqA));
    _D_B->mt  = CPS::A_div_B(CPS::D(freqD), CPS::B(freqB));
    _D_C->mt  = CPS::A_div_B(CPS::D(freqD), CPS::C(freqC));
    _D_E->mt  = CPS::A_div_B(CPS::D(freqD), CPS::E(freqE));
    _E_A->mt  = CPS::A_div_B(CPS::E(freqE), CPS::A(freqA));
    _E_B->mt  = CPS::A_div_B(CPS::E(freqE), CPS::B(freqB));
    _E_C->mt  = CPS::A_div_B(CPS::E(freqE), CPS::C(freqC));
    _E_D->mt  = CPS::A_div_B(CPS::E(freqE), CPS::D(freqD));
    //_one->mt  = CPS::A_div_B(CPS::A(1),                       CPS::A(1));

    auto ma = MicrotoneArray();
    ma.addMicrotone(_one->mt);
    ma.addMicrotone(_A_B->mt);
    ma.addMicrotone(_A_C->mt);
    ma.addMicrotone(_A_D->mt);
    ma.addMicrotone(_A_E->mt);
    ma.addMicrotone(_B_A->mt);
    ma.addMicrotone(_B_C->mt);
    ma.addMicrotone(_B_D->mt);
    ma.addMicrotone(_B_E->mt);
    ma.addMicrotone(_C_A->mt);
    ma.addMicrotone(_C_B->mt);
    ma.addMicrotone(_C_D->mt);
    ma.addMicrotone(_C_E->mt);
    ma.addMicrotone(_D_A->mt);
    ma.addMicrotone(_D_B->mt);
    ma.addMicrotone(_D_C->mt);
    ma.addMicrotone(_D_E->mt);
    ma.addMicrotone(_E_A->mt);
    ma.addMicrotone(_E_B->mt);
    ma.addMicrotone(_E_C->mt);
    ma.addMicrotone(_E_D->mt);

    setMicrotoneArray(ma);

    // SUBSETS

    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        _harmonic_subset_0->setABCDE(_one->mt, _B_A->mt, _C_A->mt, _D_A->mt, _E_A->mt);
        _subharmonic_subset_0->setABCDE(_one->mt, _A_B->mt, _A_C->mt, _A_D->mt, _A_E->mt);

        _harmonic_subset_1->setABCDE(_one->mt, _C_B->mt, _D_B->mt, _E_B->mt, _A_B->mt);
        _subharmonic_subset_1->setABCDE(_one->mt, _B_C->mt, _B_D->mt, _B_E->mt, _B_A->mt);

        _harmonic_subset_2->setABCDE(_one->mt, _D_C->mt, _E_C->mt, _A_C->mt, _B_C->mt);
        _subharmonic_subset_2->setABCDE(_one->mt, _C_D->mt, _C_E->mt, _C_A->mt, _C_B->mt);

        _harmonic_subset_3->setABCDE(_one->mt, _E_D->mt, _A_D->mt, _B_D->mt, _C_D->mt);
        _subharmonic_subset_3->setABCDE(_one->mt, _D_E->mt, _D_A->mt, _D_B->mt, _D_C->mt);

        _harmonic_subset_4->setABCDE(_one->mt, _A_E->mt, _B_E->mt, _C_E->mt, _D_E->mt);
        _subharmonic_subset_4->setABCDE(_one->mt, _E_A->mt, _E_B->mt, _E_C->mt, _E_D->mt);
    }
}

#pragma mark - subsets

void PentadicDiamond::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false);

    // will clobber these in update
    _harmonic_subset_0 = make_shared<Pentad> (_A, _B, _C, _D, _E, true);
    _harmonic_subset_1 = make_shared<Pentad> (_A, _B, _C, _D, _E, true);
    _harmonic_subset_2 = make_shared<Pentad> (_A, _B, _C, _D, _E, true);
    _harmonic_subset_3 = make_shared<Pentad> (_A, _B, _C, _D, _E, true);
    _harmonic_subset_4 = make_shared<Pentad> (_A, _B, _C, _D, _E, true);

    _subharmonic_subset_0 = make_shared<Pentad> (_A, _B, _C, _D, _E, false);
    _subharmonic_subset_1 = make_shared<Pentad> (_A, _B, _C, _D, _E, false);
    _subharmonic_subset_2 = make_shared<Pentad> (_A, _B, _C, _D, _E, false);
    _subharmonic_subset_3 = make_shared<Pentad> (_A, _B, _C, _D, _E, false);
    _subharmonic_subset_4 = make_shared<Pentad> (_A, _B, _C, _D, _E, false);

    // subsets 0
    _subsets0.push_back(_harmonic_subset_0);
    _subsets0.push_back(_harmonic_subset_1);
    _subsets0.push_back(_harmonic_subset_2);
    _subsets0.push_back(_harmonic_subset_3);
    _subsets0.push_back(_harmonic_subset_4);

    // subsets 1
    _subsets1.push_back(_subharmonic_subset_0);
    _subsets1.push_back(_subharmonic_subset_1);
    _subsets1.push_back(_subharmonic_subset_2);
    _subsets1.push_back(_subharmonic_subset_3);
    _subsets1.push_back(_subharmonic_subset_4);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void PentadicDiamond::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void PentadicDiamond::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void PentadicDiamond::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void PentadicDiamond::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void PentadicDiamond::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void PentadicDiamond::selectS0_5()
{
    jassertfalse;
}

void PentadicDiamond::selectS0_6()
{
    jassertfalse;
}

void PentadicDiamond::selectS0_7()
{
    jassertfalse;
}

void PentadicDiamond::selectS1_0()
{
    _clearSelection();
    _subsets1[0]->setIsSelected(true);
}

void PentadicDiamond::selectS1_1()
{
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void PentadicDiamond::selectS1_2()
{
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void PentadicDiamond::selectS1_3()
{
    _clearSelection();
    _subsets1[3]->setIsSelected(true);
}

void PentadicDiamond::selectS1_4()
{
    _clearSelection();
    _subsets1[4]->setIsSelected(true);
}

void PentadicDiamond::selectS1_5()
{
    jassertfalse;
}

void PentadicDiamond::selectS1_6()
{
    jassertfalse;
}

void PentadicDiamond::selectS1_7()
{
    jassertfalse;
}

bool PentadicDiamond::isEulerGenusTuningType()
{
    return false;
}

#pragma mark - description

const string PentadicDiamond::getShortDescriptionText()
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
    retVal += ")";

    return retVal;
}
