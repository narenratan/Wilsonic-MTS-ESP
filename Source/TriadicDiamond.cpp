/*
 ==============================================================================

 TriadicDiamond.cpp
 Created: 6 Jun 2023 4:31:06pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "TriadicDiamond.h"
#include "CPS.h"

#pragma mark - lifecycle

TriadicDiamond::TriadicDiamond(Microtone_p A, Microtone_p B, Microtone_p C)
: Seed3(A, B, C)
{
    setCanNPOOverride(true); // redundant, for clarity

    // basename
    _tuningType = CPS_Class::TriadicDiamond;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

TriadicDiamond::TriadicDiamond(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed3(master_set, common_tones)
{
    // no common tones for TriadicDiamond
    jassertfalse;

    // basename
    _tuningType = CPS_Class::TriadicDiamond;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

TriadicDiamond::~TriadicDiamond()
{

}

bool TriadicDiamond::canPaintTuning()
{
    return true;
}

// TODO: Fix Diamond Drawing Code
void TriadicDiamond::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    // custom geometry on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [](auto x, auto y)
    {
        auto xx = 0.5f - x;
        xx *= -1.f;
        auto yy = 0.5f - y;
        yy *= -1.f;
        auto const s = 0.743f+0.04f;
        xx *= s;
        yy *= s;
        return Point<float>(xx, yy);
    };

    // xfm
    auto const x0 = 0.10f;
    auto const x1 = 0.30f;
    auto const x2 = 0.5f;
    auto const x3 = 1.0f - x1;
    auto const x4 = 1.0f - x0;
    auto const y0 = 0.15f;
    auto const y1 = 0.5f;
    auto const y2 = 1.0f - y0;

    // tones and points
    auto const Af = _A->getFrequencyValue();
    auto const Bf = _B->getFrequencyValue();
    auto const Cf = _C->getFrequencyValue();
    _A_B = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::B(Bf)), hpc(x1, y2));
    _A_C = CPSMicrotone_t::create(CPS::A_div_B(CPS::A(Af), CPS::C(Cf)), hpc(x0, y1));
    _B_A = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::A(Af)), hpc(x3, y0));
    _B_C = CPSMicrotone_t::create(CPS::A_div_B(CPS::B(Bf), CPS::C(Cf)), hpc(x1, y0));
    _C_A = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::A(Af)), hpc(x4, y1));
    _C_B = CPSMicrotone_t::create(CPS::A_div_B(CPS::C(Cf), CPS::B(Bf)), hpc(x3, y2));
    _one = CPSMicrotone_t::create(CPS::one(), hpc(x2, y1));

    // lines, order is important
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _A_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _A_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _B_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _B_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _C_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_one, _C_B));

    _lineArray.push_back(CPSMicrotone_t::create_line(_A_B, _A_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A_C, _B_C));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_C, _B_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B_A, _C_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_A, _C_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_B, _A_B));

    // labels
    _labelArray.push_back(_A_B);
    _labelArray.push_back(_A_C);
    _labelArray.push_back(_B_A);
    _labelArray.push_back(_B_C);
    _labelArray.push_back(_C_A);
    _labelArray.push_back(_C_B);
    _labelArray.push_back(_one);

    // all points for drawing
    _masterPtArray.push_back(_A_B);
    _masterPtArray.push_back(_A_C);
    _masterPtArray.push_back(_B_A);
    _masterPtArray.push_back(_B_C);
    _masterPtArray.push_back(_C_A);
    _masterPtArray.push_back(_C_B);
    _masterPtArray.push_back(_one);
}

#pragma mark - update

void TriadicDiamond::update()
{
    auto const a_freq = _A->getFrequencyValue();
    auto const b_freq = _B->getFrequencyValue();
    auto const c_freq = _C->getFrequencyValue();
    _A_B->mt  = CPS::A_div_B(CPS::A(a_freq), CPS::B(b_freq));
    _A_C->mt  = CPS::A_div_B(CPS::A(a_freq), CPS::C(c_freq));
    _B_A->mt  = CPS::A_div_B(CPS::B(b_freq), CPS::A(a_freq));
    _B_C->mt  = CPS::A_div_B(CPS::B(b_freq), CPS::C(c_freq));
    _C_A->mt  = CPS::A_div_B(CPS::C(c_freq), CPS::A(a_freq));
    _C_B->mt  = CPS::A_div_B(CPS::C(c_freq), CPS::B(b_freq));
    //_one->mt  = CPS::A_div_B(CPS::A(1), CPS::A(1));


    auto ma = MicrotoneArray();
    ma.addMicrotone(_one->mt);
    ma.addMicrotone(_A_B->mt);
    ma.addMicrotone(_A_C->mt);
    ma.addMicrotone(_B_A->mt);
    ma.addMicrotone(_B_C->mt);
    ma.addMicrotone(_C_A->mt);
    ma.addMicrotone(_C_B->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()

    // SUBSETS

    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        _harmonic_subset_0->setABC(_one->mt, _B_A->mt, _C_A->mt);
        _subharmonic_subset_0->setABC(_one->mt, _A_B->mt, _A_C->mt);

        _harmonic_subset_1->setABC(_one->mt, _C_B->mt, _A_B->mt);
        _subharmonic_subset_1->setABC(_one->mt, _B_C->mt, _B_A->mt);

        _harmonic_subset_2->setABC(_one->mt, _A_C->mt, _B_C->mt);
        _subharmonic_subset_2->setABC(_one->mt, _C_A->mt, _C_B->mt);
    }
}

#pragma mark - subsets

void TriadicDiamond::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    // will clobber these in update
    _harmonic_subset_0 = make_shared<Triad>(_A, _B, _C, true);
    _harmonic_subset_1 = make_shared<Triad>(_A, _B, _C, true);
    _harmonic_subset_2 = make_shared<Triad>(_A, _B, _C, true);

    _subharmonic_subset_0 = make_shared<Triad>(_A, _B, _C, false);
    _subharmonic_subset_1 = make_shared<Triad>(_A, _B, _C, false);
    _subharmonic_subset_2 = make_shared<Triad>(_A, _B, _C, false);

    // subsets 0
    _subsets0.push_back(_harmonic_subset_0);
    _subsets0.push_back(_harmonic_subset_1);
    _subsets0.push_back(_harmonic_subset_2);

    // subsets 1
    _subsets1.push_back(_subharmonic_subset_0);
    _subsets1.push_back(_subharmonic_subset_1);
    _subsets1.push_back(_subharmonic_subset_2);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void TriadicDiamond::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void TriadicDiamond::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void TriadicDiamond::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void TriadicDiamond::selectS0_3()
{
    jassertfalse;
}

void TriadicDiamond::selectS0_4()
{
    jassertfalse;
}

void TriadicDiamond::selectS0_5()
{
    jassertfalse;
}

void TriadicDiamond::selectS0_6()
{
    jassertfalse;
}

void TriadicDiamond::selectS0_7()
{
    jassertfalse;
}

void TriadicDiamond::selectS1_0()
{
    _clearSelection();
    _subsets1[0]->setIsSelected(true);
}

void TriadicDiamond::selectS1_1()
{
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void TriadicDiamond::selectS1_2()
{
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void TriadicDiamond::selectS1_3()
{
    jassertfalse;
}

void TriadicDiamond::selectS1_4()
{
    jassertfalse;
}

void TriadicDiamond::selectS1_5()
{
    jassertfalse;
}

void TriadicDiamond::selectS1_6()
{
    jassertfalse;
}

void TriadicDiamond::selectS1_7()
{
    jassertfalse;
}

bool TriadicDiamond::isEulerGenusTuningType()
{
    return false;
}

#pragma mark - description

const string TriadicDiamond::getShortDescriptionText()
{
    string retVal = "Triadic Diamond:(";
    retVal += getA()->getShortDescriptionText();
    retVal += ",";
    retVal += getB()->getShortDescriptionText();
    retVal += ",";
    retVal += getC()->getShortDescriptionText();
    retVal += ")";

    return retVal;
}
