/*
 ==============================================================================

 CPS_6_2.cpp
 Created: 13 Aug 2021 8:37:35pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "CPS_6_2.h"
#include "CPS.h"
#include "EulerGenusModel.h"

#pragma mark - lifecycle

CPS_6_2::CPS_6_2(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F)
: Seed6(A, B, C, D, E, F)
{
    // basename
    _tuningType = CPS_Class::CPS_6_2;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_6_2::CPS_6_2(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed6(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_6_2;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_6_2::canPaintTuning()
{
    return true;
}

void CPS_6_2::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    auto const x00 = 0.08f;
    auto const x01 = 0.24f;
    auto const x02 = 0.34f;
    auto const x03 = 0.41f;
    auto const x04 = 0.50f;
    auto const x05 = 1 - x03;
    auto const x06 = 1 - x02;
    auto const x07 = 1 - x01;
    auto const x08 = 1 - x00;

    auto const y00 = 0.16f;
    auto const y01 = 0.24f;
    auto const y02 = 0.34f;
    auto const y03 = 0.42f;
    auto const y04 = 0.45f;
    auto const y05 = 0.64f;
    auto const y06 = 0.65f;
    auto const y07 = 0.73f;
    auto const y08 = 0.93f;

    // scaling func for coords...on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [] (float x, float y)
    {
        auto xx = -(0.5f - x);
        auto yy = -(0.5f - y);
        auto s = 0.733f;
        s *= 0.95f;
        xx *= s;
        yy *= s;
        return Point<float> (xx, yy);
    };

    _mAB = CPSMicrotone_t::create(CPS::AB(_A, _B), hpc(x00, y06));
    _mAC = CPSMicrotone_t::create(CPS::AB(_A, _C), hpc(x02, y04));
    _mAD = CPSMicrotone_t::create(CPS::AB(_A, _D), hpc(x05, y05));
    _mAE = CPSMicrotone_t::create(CPS::AB(_A, _E), hpc(x04, y08));
    _mAF = CPSMicrotone_t::create(CPS::AB(_A, _F), hpc(x02, y07));
    _mBC = CPSMicrotone_t::create(CPS::AB(_B, _C), hpc(x01, y00));
    _mBD = CPSMicrotone_t::create(CPS::AB(_B, _D), hpc(x04, y02));
    _mBE = CPSMicrotone_t::create(CPS::AB(_B, _E), hpc(x03, y05));
    _mBF = CPSMicrotone_t::create(CPS::AB(_B, _F), hpc(x01, y03));
    _mCD = CPSMicrotone_t::create(CPS::AB(_C, _D), hpc(x07, y00));
    _mCE = CPSMicrotone_t::create(CPS::AB(_C, _E), hpc(x06, y04));
    _mCF = CPSMicrotone_t::create(CPS::AB(_C, _F), hpc(x04, y01));
    _mDE = CPSMicrotone_t::create(CPS::AB(_D, _E), hpc(x08, y06));
    _mDF = CPSMicrotone_t::create(CPS::AB(_D, _F), hpc(x07, y03));
    _mEF = CPSMicrotone_t::create(CPS::AB(_E, _F), hpc(x06, y07));
    _p0  = CPSMicrotone_t::create_center(hpc(0.5f, 0.5f));

    // outline
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAB, _mBF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBF, _mBC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBC, _mCF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mCF, _mCD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mCD, _mDF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mDF, _mDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mDE, _mEF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mEF, _mAE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAE, _mAF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAF, _mAB));
    // interior
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAF, _mAC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mCF, _mCE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mEF, _mBE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBF, _mBD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mDF, _mAD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAD, _mAF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAC, _mCF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mCE, _mEF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBE, _mBF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBD, _mDF));

    _labelArray.push_back(_mAB);
    _labelArray.push_back(_mAC);
    _labelArray.push_back(_mAD);
    _labelArray.push_back(_mAE);
    _labelArray.push_back(_mAF);
    _labelArray.push_back(_mBC);
    _labelArray.push_back(_mBD);
    _labelArray.push_back(_mBE);
    _labelArray.push_back(_mBF);
    _labelArray.push_back(_mCD);
    _labelArray.push_back(_mCE);
    _labelArray.push_back(_mCF);
    _labelArray.push_back(_mDE);
    _labelArray.push_back(_mDF);
    _labelArray.push_back(_mEF);

    _masterPtArray.push_back(_mAB);
    _masterPtArray.push_back(_mAC);
    _masterPtArray.push_back(_mAD);
    _masterPtArray.push_back(_mAE);
    _masterPtArray.push_back(_mAF);
    _masterPtArray.push_back(_mBC);
    _masterPtArray.push_back(_mBD);
    _masterPtArray.push_back(_mBE);
    _masterPtArray.push_back(_mBF);
    _masterPtArray.push_back(_mCD);
    _masterPtArray.push_back(_mCE);
    _masterPtArray.push_back(_mCF);
    _masterPtArray.push_back(_mDE);
    _masterPtArray.push_back(_mDF);
    _masterPtArray.push_back(_mEF);
    _masterPtArray.push_back(_p0);
}

CPS_6_2::~CPS_6_2()
{

}

#pragma mark - update

void CPS_6_2::update()
{
    // no common tone logic because there is no level 7 to set one

    // PENTADEKANY(6, 2) = 15 npo

    /*
     ------------------------------------------------------
     CPS AT PASCALS TRIANGLE AT ROW: 6
     ------------------------------------------------------
     Master Set: ['A', 'B', 'C', 'D', 'E', 'F']
     (n,k):( 6 , 2 )
     [('A', 'B'), ('A', 'C'), ('A', 'D'), ('A', 'E'), ('A', 'F'), ('B', 'C'), ('B', 'D'), ('B', 'E'), ('B', 'F'), ('C', 'D'), ('C', 'E'), ('C', 'F'), ('D', 'E'), ('D', 'F'), ('E', 'F')]
     count: 15
     ------------------------------------------------------
     */

    _mAB->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B} );
    _mAC->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _C} );
    _mAD->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _D} );
    _mAE->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _E} );
    _mAF->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _F} );
    _mBC->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _C} );
    _mBD->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _D} );
    _mBE->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _E} );
    _mBF->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _F} );
    _mCD->mt = multiplyByCommonTones(vector<Microtone_p> {_C, _D} );
    _mCE->mt = multiplyByCommonTones(vector<Microtone_p> {_C, _E} );
    _mCF->mt = multiplyByCommonTones(vector<Microtone_p> {_C, _F} );
    _mDE->mt = multiplyByCommonTones(vector<Microtone_p> {_D, _E} );
    _mDF->mt = multiplyByCommonTones(vector<Microtone_p> {_D, _F} );
    _mEF->mt = multiplyByCommonTones(vector<Microtone_p> {_E, _F} );

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mAB->mt);
    ma.addMicrotone(_mAC->mt);
    ma.addMicrotone(_mAD->mt);
    ma.addMicrotone(_mAE->mt);
    ma.addMicrotone(_mAF->mt);
    ma.addMicrotone(_mBC->mt);
    ma.addMicrotone(_mBD->mt);
    ma.addMicrotone(_mBE->mt);
    ma.addMicrotone(_mBF->mt);
    ma.addMicrotone(_mCD->mt);
    ma.addMicrotone(_mCE->mt);
    ma.addMicrotone(_mCF->mt);
    ma.addMicrotone(_mDE->mt);
    ma.addMicrotone(_mDF->mt);
    ma.addMicrotone(_mEF->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()

    // SUBSETS

    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }


        //    ------------------------------------------------------
        //    CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
        //    (n,k):( 6 , 2 )
        //    (m,j):( 5 , 1 )
        //     count: 6

        // [[[{'D', 'F'}, {'B', 'F'}, {'C', 'F'}, {'F', 'A'}, {'F', 'E'}]],
        _cps_5_1_0->setCommonTones(_F, getCommonTones());
        _cps_5_1_0->setABCDE(_A, _B, _C, _D, _E); //F

        // [[{'D', 'E'}, {'B', 'E'}, {'C', 'E'}, {'A', 'E'}, {'F', 'E'}]],
        _cps_5_1_1->setCommonTones(_E, getCommonTones());
        _cps_5_1_1->setABCDE(_A, _B, _C, _D, _F); //E

        // [[{'D', 'B'}, {'D', 'C'}, {'D', 'A'}, {'D', 'F'}, {'D', 'E'}]],
        _cps_5_1_2->setCommonTones(_D, getCommonTones());
        _cps_5_1_2->setABCDE(_A, _B, _C, _E, _F); //D

        // [[{'D', 'C'}, {'B', 'C'}, {'C', 'A'}, {'C', 'F'}, {'C', 'E'}]],
        _cps_5_1_3->setCommonTones(_C, getCommonTones());
        _cps_5_1_3->setABCDE(_A, _B, _D, _E, _F); //C

        // [[{'D', 'B'}, {'B', 'C'}, {'B', 'A'}, {'B', 'F'}, {'B', 'E'}]],
        _cps_5_1_4->setCommonTones(_B, getCommonTones());
        _cps_5_1_4->setABCDE(_A, _C, _D, _E, _F); //B

        // [[{'D', 'A'}, {'B', 'A'}, {'C', 'A'}, {'F', 'A'}, {'A', 'E'}]]]
        _cps_5_1_5->setCommonTones(_A, getCommonTones());
        _cps_5_1_5->setABCDE(_B, _C, _D, _E, _F); //A

        //    ------------------------------------------------------
        //    CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
        //    (n,k):( 6 , 2 )
        //    (m,j):( 5 , 2 )
        //    count: 6
        //    [[[{'D', 'B'}, {'D', 'C'}, {'D', 'A'}, {'D', 'E'}, {'B', 'C'}, {'B', 'A'}, {'B', 'E'}, {'C', 'A'}, {'C', 'E'}, {'A', 'E'}]],
        _cps_5_2_0->setCommonTones(nullptr, getCommonTones());
        _cps_5_2_0->setABCDE(_A, _B, _C, _D, _E); // F

        //    [[{'D', 'B'}, {'D', 'C'}, {'D', 'A'}, {'D', 'F'}, {'B', 'C'}, {'B', 'A'}, {'B', 'F'}, {'C', 'A'}, {'C', 'F'}, {'F', 'A'}]],
        _cps_5_2_1->setCommonTones(nullptr, getCommonTones());
        _cps_5_2_1->setABCDE(_A, _B, _C, _D, _F); // E

        //    [[{'B', 'C'}, {'B', 'A'}, {'B', 'F'}, {'B', 'E'}, {'C', 'A'}, {'C', 'F'}, {'C', 'E'}, {'F', 'A'}, {'A', 'E'}, {'F', 'E'}]],
        _cps_5_2_2->setCommonTones(nullptr, getCommonTones());
        _cps_5_2_2->setABCDE(_A, _B, _C, _E, _F); // D

        //    [[{'D', 'B'}, {'D', 'A'}, {'D', 'F'}, {'D', 'E'}, {'B', 'A'}, {'B', 'F'}, {'B', 'E'}, {'F', 'A'}, {'A', 'E'}, {'F', 'E'}]],
        _cps_5_2_3->setCommonTones(nullptr, getCommonTones());
        _cps_5_2_3->setABCDE(_A, _B, _D, _E, _F); // C

        //  [[{'D', 'C'}, {'D', 'A'}, {'D', 'F'}, {'D', 'E'}, {'C', 'A'}, {'C', 'F'}, {'C', 'E'}, {'F', 'A'}, {'A', 'E'}, {'F', 'E'}]],
        _cps_5_2_4->setCommonTones(nullptr, getCommonTones());
        _cps_5_2_4->setABCDE(_A, _C, _D, _E, _F); // B

        //    [[{'D', 'B'}, {'D', 'C'}, {'D', 'F'}, {'D', 'E'}, {'B', 'C'}, {'B', 'F'}, {'B', 'E'}, {'C', 'F'}, {'C', 'E'}, {'F', 'E'}]]]
        _cps_5_2_5->setCommonTones(nullptr, getCommonTones());
        _cps_5_2_5->setABCDE(_B, _C, _D, _E, _F); // A
    }
}

#pragma mark - subsets

void CPS_6_2::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _cps_5_1_0 = make_shared<CPS_5_1> (_A, _B, _C, _D, _E);
    _cps_5_1_1 = make_shared<CPS_5_1> (_A, _B, _C, _D, _E);
    _cps_5_1_2 = make_shared<CPS_5_1> (_A, _B, _C, _D, _E);
    _cps_5_1_3 = make_shared<CPS_5_1> (_A, _B, _C, _D, _E);
    _cps_5_1_4 = make_shared<CPS_5_1> (_A, _B, _C, _D, _E);
    _cps_5_1_5 = make_shared<CPS_5_1> (_A, _B, _C, _D, _E);

    _cps_5_2_0 = make_shared<CPS_5_2> (_A, _B, _C, _D, _E);
    _cps_5_2_1 = make_shared<CPS_5_2> (_A, _B, _C, _D, _E);
    _cps_5_2_2 = make_shared<CPS_5_2> (_A, _B, _C, _D, _E);
    _cps_5_2_3 = make_shared<CPS_5_2> (_A, _B, _C, _D, _E);
    _cps_5_2_4 = make_shared<CPS_5_2> (_A, _B, _C, _D, _E);
    _cps_5_2_5 = make_shared<CPS_5_2> (_A, _B, _C, _D, _E);

    // subsets 0
    _subsets0.push_back(_cps_5_1_0);
    _subsets0.push_back(_cps_5_1_1);
    _subsets0.push_back(_cps_5_1_2);
    _subsets0.push_back(_cps_5_1_3);
    _subsets0.push_back(_cps_5_1_4);
    _subsets0.push_back(_cps_5_1_5);

    // subsets 1
    _subsets1.push_back(_cps_5_2_0);
    _subsets1.push_back(_cps_5_2_1);
    _subsets1.push_back(_cps_5_2_2);
    _subsets1.push_back(_cps_5_2_3);
    _subsets1.push_back(_cps_5_2_4);
    _subsets1.push_back(_cps_5_2_5);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_6_2::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void CPS_6_2::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void CPS_6_2::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void CPS_6_2::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void CPS_6_2::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void CPS_6_2::selectS0_5()
{
    _clearSelection();
    _subsets0[5]->setIsSelected(true);
}

void CPS_6_2::selectS0_6()
{
    jassertfalse;
}

void CPS_6_2::selectS0_7()
{
    jassertfalse;
}

void CPS_6_2::selectS1_0()
{
    _clearSelection();
    _subsets1[0]->setIsSelected(true);
}

void CPS_6_2::selectS1_1()
{
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void CPS_6_2::selectS1_2()
{
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void CPS_6_2::selectS1_3()
{
    _clearSelection();
    _subsets1[3]->setIsSelected(true);
}

void CPS_6_2::selectS1_4()
{
    _clearSelection();
    _subsets1[4]->setIsSelected(true);
}

void CPS_6_2::selectS1_5()
{
    _clearSelection();
    _subsets1[5]->setIsSelected(true);
}

void CPS_6_2::selectS1_6()
{
    jassertfalse;
}

void CPS_6_2::selectS1_7()
{
    jassertfalse;
}

bool CPS_6_2::isEulerGenusTuningType()
{
    return false;
}

