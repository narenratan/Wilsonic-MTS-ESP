/*
  ==============================================================================

    Mandala.cpp
    Created: 23 May 2022 1:05:34pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "Mandala.h"
#include "CPS.h"

#pragma mark - lifecycle

Mandala::Mandala(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D)
: Seed4(A, B, C, D)
{
    _commonConstructorHelper();

    // update
    update();
}

Mandala::Mandala(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed4(master_set, common_tones)
{
    // no common tones for Mandala
    jassertfalse;

    _commonConstructorHelper();

    // update
    update();
}

void Mandala::_commonConstructorHelper()
{
    // called at construction only, will be updated in update
    // basename
    _tuningType = CPS_Class::Mandala;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);

    // custom geometry on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [](float x, float y)
    {
        auto xx = 0.5f - x;
        xx *= -1.f;
        auto yy = 0.5f - y;
        yy *= -1.f;
        auto const s = 0.743f;
        xx *= s;
        yy *= s;
        return Point<float> (xx, yy);
    };

    // degrees in percentage coordinates
    auto const x0 = 0.066666f;
    auto const x1 = 0.28f;
    auto const x2 = 0.5f;
    auto const x3 = 1.0f - x1;
    auto const x4 = 1.0f - x0;
    auto const y0 = 0.0f;
    auto const y1 = 0.25f;
    auto const y2 = 0.375f;
    auto const y3 = 0.45f;      //0.5;//0.47f-0.07f+0.03f; // D^2
    auto const y4 = 1.0f - y3; // ABC/D
    auto const y5 = 1.0f - y2;
    auto const y6 = 1.0f - y1;
    auto const y7 = 1.0f - y0;

    auto mt_B2    = CPS::AB(_B, _B);
    auto mt_ABD_C = CPS::A_div_B(CPS::ABC(_A, _B, _D), _C);
    auto mt_BD    = CPS::AB(_B, _D);
    auto mt_BCD_A = CPS::A_div_B(CPS::ABC(_B, _C, _D), _A);
    auto mt_AB    = CPS::AB(_A, _B);
    auto mt_BC    = CPS::AB(_B, _C);
    auto mt_D2    = CPS::AB(_D, _D);
    auto mt_ABC_D = CPS::A_div_B(CPS::ABC(_A, _B, _C), _D);
    auto mt_AD    = CPS::AB(_A, _D);
    auto mt_CD    = CPS::AB(_C, _D);
    auto mt_A2    = CPS::AB(_A, _A);
    auto mt_AC    = CPS::AB(_A, _C);
    auto mt_C_squared    = CPS::AB(_C, _C);
    auto mt_ACD_B = CPS::A_div_B(CPS::ABC(_A, _C, _D), _B);

    _B2    = CPSMicrotone_t::create(mt_B2   , hpc(x2, y0));
    _ABD_C = CPSMicrotone_t::create(mt_ABD_C, hpc(x0, y1));
    _BD    = CPSMicrotone_t::create(mt_BD   , hpc(x2, y1));
    _BCD_A = CPSMicrotone_t::create(mt_BCD_A, hpc(x4, y1));
    _AB    = CPSMicrotone_t::create(mt_AB   , hpc(x1, y2));
    _BC    = CPSMicrotone_t::create(mt_BC   , hpc(x3, y2));
    _D2    = CPSMicrotone_t::create(mt_D2   , hpc(x2, y3));
    _ABC_D = CPSMicrotone_t::create(mt_ABC_D, hpc(x2, y4));
    _AD    = CPSMicrotone_t::create(mt_AD   , hpc(x1, y5));
    _CD    = CPSMicrotone_t::create(mt_CD   , hpc(x3, y5));
    _A2    = CPSMicrotone_t::create(mt_A2   , hpc(x0, y6));
    _AC    = CPSMicrotone_t::create(mt_AC   , hpc(x2, y6));
    _C_squared    = CPSMicrotone_t::create(mt_C_squared   , hpc(x4, y6));
    _ACD_B = CPSMicrotone_t::create(mt_ACD_B, hpc(x2, y7));
    _ptCenter = CPSMicrotone_t::create(CPS::A(1), hpc(x2, 0.5f * (y3 + y4)));

    _lineArray.push_back(CPSMicrotone_t::create_line(_ABC_D, _BC   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_ABC_D, _AB   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_ABC_D, _AC   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_AB   , _AC   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_AC   , _AD   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_AD   , _AB   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_BD   , _BC   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_BC   , _CD   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_AB   , _BC   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_BC   , _AC   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_AC   , _CD   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_CD   , _AD   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_AD   , _BD   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_CD   , _BD   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_BD   , _AB   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_ABD_C, _BD   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_BD   , _BCD_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_ABD_C, _AD   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_AD   , _ACD_B));
    _lineArray.push_back(CPSMicrotone_t::create_line(_ACD_B, _CD   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_CD   , _BCD_A));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B2   , _BD   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A2   , _AD   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_squared   , _CD   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_BCD_A, _BC   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_ABD_C, _AB   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_ACD_B, _AC   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B2   , _AB   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_B2   , _BC   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A2   , _AB   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_A2   , _AC   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_squared   , _AC   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_C_squared   , _BC   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D2   , _AD   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D2   , _BD   ));
    _lineArray.push_back(CPSMicrotone_t::create_line(_D2   , _CD   ));

    // labels
    _labelArray.push_back(_B2);
    _labelArray.push_back(_ABD_C);
    _labelArray.push_back(_BD);
    _labelArray.push_back(_BCD_A);
    _labelArray.push_back(_AB);
    _labelArray.push_back(_BC);
    _labelArray.push_back(_D2);
    _labelArray.push_back(_ABC_D);
    _labelArray.push_back(_AD);
    _labelArray.push_back(_CD);
    _labelArray.push_back(_A2);
    _labelArray.push_back(_AC);
    _labelArray.push_back(_C_squared);
    _labelArray.push_back(_ACD_B);

    // all points for drawing
    _masterPtArray.push_back(_B2);
    _masterPtArray.push_back(_ABD_C);
    _masterPtArray.push_back(_BD);
    _masterPtArray.push_back(_BCD_A);
    _masterPtArray.push_back(_AB);
    _masterPtArray.push_back(_BC);
    _masterPtArray.push_back(_D2);
    _masterPtArray.push_back(_ABC_D);
    _masterPtArray.push_back(_AD);
    _masterPtArray.push_back(_CD);
    _masterPtArray.push_back(_A2);
    _masterPtArray.push_back(_AC);
    _masterPtArray.push_back(_C_squared);
    _masterPtArray.push_back(_ACD_B);
    _masterPtArray.push_back(_ptCenter);
}

#pragma mark - update

bool Mandala::canPaintTuning()
{
    return true;
}


void Mandala::update()
{
    auto mt_B2    = CPS::AB(_B, _B);
    auto mt_ABD_C = CPS::A_div_B(CPS::ABC(_A, _B, _D), _C);
    auto mt_BD    = CPS::AB(_B, _D);
    auto mt_BCD_A = CPS::A_div_B(CPS::ABC(_B, _C, _D), _A);
    auto mt_AB    = CPS::AB(_A, _B);
    auto mt_BC    = CPS::AB(_B, _C);
    auto mt_D2    = CPS::AB(_D, _D);
    auto mt_ABC_D = CPS::A_div_B(CPS::ABC(_A, _B, _C), _D);
    auto mt_AD    = CPS::AB(_A, _D);
    auto mt_CD    = CPS::AB(_C, _D);
    auto mt_A2    = CPS::AB(_A, _A);
    auto mt_AC    = CPS::AB(_A, _C);
    auto mt_C_squared    = CPS::AB(_C, _C);
    auto mt_ACD_B = CPS::A_div_B(CPS::ABC(_A, _C, _D), _B);

    _B2->mt    = multiplyByCommonTones(vector<Microtone_p> {mt_B2} );
    _ABD_C->mt = multiplyByCommonTones(vector<Microtone_p> {mt_ABD_C} );
    _BD->mt    = multiplyByCommonTones(vector<Microtone_p> {mt_BD} );
    _BCD_A->mt = multiplyByCommonTones(vector<Microtone_p> {mt_BCD_A} );
    _AB->mt    = multiplyByCommonTones(vector<Microtone_p> {mt_AB} );
    _BC->mt    = multiplyByCommonTones(vector<Microtone_p> {mt_BC} );
    _D2->mt    = multiplyByCommonTones(vector<Microtone_p> {mt_D2} );
    _ABC_D->mt = multiplyByCommonTones(vector<Microtone_p> {mt_ABC_D} );
    _AD->mt    = multiplyByCommonTones(vector<Microtone_p> {mt_AD} );
    _CD->mt    = multiplyByCommonTones(vector<Microtone_p> {mt_CD} );
    _A2->mt    = multiplyByCommonTones(vector<Microtone_p> {mt_A2} );
    _AC->mt    = multiplyByCommonTones(vector<Microtone_p> {mt_AC} );
    _C_squared->mt    = multiplyByCommonTones(vector<Microtone_p> {mt_C_squared} );
    _ACD_B->mt = multiplyByCommonTones(vector<Microtone_p> {mt_ACD_B} );

    auto ma = MicrotoneArray();
    ma.addMicrotone(_B2->mt   );
    ma.addMicrotone(_ABD_C->mt);
    ma.addMicrotone(_BD->mt   );
    ma.addMicrotone(_BCD_A->mt);
    ma.addMicrotone(_AB->mt   );
    ma.addMicrotone(_BC->mt   );
    ma.addMicrotone(_D2->mt   );
    ma.addMicrotone(_ABC_D->mt);
    ma.addMicrotone(_AD->mt   );
    ma.addMicrotone(_CD->mt   );
    ma.addMicrotone(_A2->mt   );
    ma.addMicrotone(_AC->mt   );
    ma.addMicrotone(_C_squared->mt   );
    ma.addMicrotone(_ACD_B->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()

    // SUBSETS

    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        _harmonic_subset_0->setABCD    (_A2->mt   , _AB->mt, _AC->mt, _AD->mt);
        _subharmonic_subset_0->setABCD(_BCD_A->mt, _BC->mt, _BD->mt, _CD->mt);

        _harmonic_subset_1->setABCD    (_B2->mt   , _AB->mt, _BD->mt, _BC->mt);
        _subharmonic_subset_1->setABCD(_ACD_B->mt, _AC->mt, _AD->mt, _CD->mt);

        _harmonic_subset_2->setABCD    (_C_squared->mt   , _AC->mt, _BC->mt, _CD->mt);
        _subharmonic_subset_2->setABCD(_ABD_C->mt, _AB->mt, _AD->mt, _BD->mt);

        _harmonic_subset_3->setABCD    (_D2->mt   , _AD->mt, _BD->mt, _CD->mt);
        _subharmonic_subset_3->setABCD(_ABC_D->mt, _AB->mt, _BC->mt, _AC->mt);
    }
}

#pragma mark - subsets

void Mandala::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    // will clobber these in update
    _harmonic_subset_0 = make_shared<CPS_4_1> (_A, _B, _C, _D);
    _harmonic_subset_1 = make_shared<CPS_4_1> (_A, _B, _C, _D);
    _harmonic_subset_2 = make_shared<CPS_4_1> (_A, _B, _C, _D);
    _harmonic_subset_3 = make_shared<CPS_4_1> (_A, _B, _C, _D);

    _subharmonic_subset_0 = make_shared<CPS_4_1> (_A, _B, _C, _D);
    _subharmonic_subset_1 = make_shared<CPS_4_1> (_A, _B, _C, _D);
    _subharmonic_subset_2 = make_shared<CPS_4_1> (_A, _B, _C, _D);
    _subharmonic_subset_3 = make_shared<CPS_4_1> (_A, _B, _C, _D);

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

void Mandala::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void Mandala::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
    ;
}

void Mandala::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void Mandala::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void Mandala::selectS0_4()
{
    jassertfalse;
}

void Mandala::selectS0_5()
{
    jassertfalse;
}

void Mandala::selectS0_6()
{
    jassertfalse;
}

void Mandala::selectS0_7()
{
    jassertfalse;
}

void Mandala::selectS1_0()
{
    _clearSelection();
    _subsets1[0]->setIsSelected(true);
}

void Mandala::selectS1_1()
{
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void Mandala::selectS1_2()
{
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void Mandala::selectS1_3()
{
    _clearSelection();
    _subsets1[3]->setIsSelected(true);
}

void Mandala::selectS1_4()
{
    jassertfalse;
}

void Mandala::selectS1_5()
{
    jassertfalse;
}

void Mandala::selectS1_6()
{
    jassertfalse;
}

void Mandala::selectS1_7()
{
    jassertfalse;
}

bool Mandala::isEulerGenusTuningType()
{
    return false;
}

#pragma mark - description

const string Mandala::getShortDescriptionText()
{
    string retVal = "Mandala:(";
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
