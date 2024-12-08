/*
 ==============================================================================

 CPS_5_2.cpp
 Created: 13 Aug 2021 8:33:14pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "CPS_5_2.h"
#include "EulerGenusModel.h"
#include "WilsonicProcessor.h"
#include "CPS.h"

#pragma mark - lifecycle

CPS_5_2::CPS_5_2(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E)
: Seed5(A, B, C, D, E)
{
    // basename
    _tuningType = CPS_Class::CPS_5_2;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_5_2::CPS_5_2(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed5(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_5_2;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_5_2::canPaintTuning()
{
    return true;
}

void CPS_5_2::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    auto const x00 = 0.f;
    auto const x01 = 0.185f;
    auto const x02 = 0.300f;
    auto const x03 = 0.375f;
    auto const x04 = 0.5f;
    auto const x05 = 1 - x03;
    auto const x06 = 1 - x02;
    auto const x07 = 1 - x01;
    auto const x08 = 1 - x00;

    auto const y00 = 0.f;
    auto const y01 = 0.055f;
    auto const y04 = 0.270f;
    auto const y05 = 0.365f;
    auto const y06 = 0.415f;
    auto const y08 = 1 - y05;
    auto const y13 = 1 - y00;

    // scaling func for coords...on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [] (float x, float y)
    {
        auto xx = -(0.5f - x);
        auto yy = -(0.5f - y);
        auto s = 0.55708f; // magic
        xx *= s;
        yy *= s;
        return Point<float> (xx, yy);
    };
    
    _mAC = CPSMicrotone_t::create(CPS::AB(_A, _C), hpc(x02, y06));
    _mAB = CPSMicrotone_t::create(CPS::AB(_A, _B), hpc(x00, y08));
    _mBE = CPSMicrotone_t::create(CPS::AB(_B, _E), hpc(x03, y08));
    _mAE = CPSMicrotone_t::create(CPS::AB(_A, _E), hpc(x04, y13));
    _mAD = CPSMicrotone_t::create(CPS::AB(_A, _D), hpc(x05, y08));
    _mDE = CPSMicrotone_t::create(CPS::AB(_D, _E), hpc(x08, y08));
    _mCE = CPSMicrotone_t::create(CPS::AB(_C, _E), hpc(x06, y06));
    _mCD = CPSMicrotone_t::create(CPS::AB(_C, _D), hpc(x07, y01));
    _mBD = CPSMicrotone_t::create(CPS::AB(_B, _D), hpc(x04, y04));
    _mBC = CPSMicrotone_t::create(CPS::AB(_B, _C), hpc(x01, y01));
    _p0  = CPSMicrotone_t::create_center(hpc(0.5f, 0.5f));

    // trick to get star line segment overlapping
    // CE AC
    auto tmpPtCE = hpc(x06, y06);
    auto tmpPtAC = hpc(x02, y06);
    auto tmpPt = tmpPtCE + 0.5f * (tmpPtAC - tmpPtCE);
    _half_CE_AC = CPSMicrotone_t::create(CPS::AB(_C, _E), tmpPt);

    // Outline
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAB, _mBE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBE, _mAE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAE, _mAD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAD, _mDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mDE, _mCE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mCE, _mCD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mCD, _mBD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBD, _mBC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBC, _mAC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAC, _mAB));
    // interior star
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAC, _mCE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBD, _mAD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mCE, _mBE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAD, _mAC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBE, _mBD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAC, _half_CE_AC));

    _labelArray.push_back(_mAC);
    _labelArray.push_back(_mAB);
    _labelArray.push_back(_mBE);
    _labelArray.push_back(_mAE);
    _labelArray.push_back(_mAD);
    _labelArray.push_back(_mDE);
    _labelArray.push_back(_mCE);
    _labelArray.push_back(_mCD);
    _labelArray.push_back(_mBD);
    _labelArray.push_back(_mBC);

    _masterPtArray.push_back(_mAC);
    _masterPtArray.push_back(_mAB);
    _masterPtArray.push_back(_mBE);
    _masterPtArray.push_back(_mAE);
    _masterPtArray.push_back(_mAD);
    _masterPtArray.push_back(_mDE);
    _masterPtArray.push_back(_mCE);
    _masterPtArray.push_back(_mCD);
    _masterPtArray.push_back(_mBD);
    _masterPtArray.push_back(_mBC);
    _masterPtArray.push_back(_p0);
}

CPS_5_2::~CPS_5_2()
{

}

#pragma mark - update

void CPS_5_2::update()
{
    /*
     ------------------------------------------------------
     CPS AT PASCALS TRIANGLE AT ROW: 5
     ------------------------------------------------------
     Master Set: ['A', 'B', 'C', 'D', 'E']
     (n,k):( 5 , 2 )
     [('A', 'B'), ('A', 'C'), ('A', 'D'), ('A', 'E'), ('B', 'C'), ('B', 'D'), ('B', 'E'), ('C', 'D'), ('C', 'E'), ('D', 'E')]
     count: 10
     ------------------------------------------------------
     */
    _mAB->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B} );
    _mAC->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _C} );
    _mAD->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _D} );
    _mAE->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _E} );
    _mBC->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _C} );
    _mBD->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _D} );
    _mBE->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _E} );
    _mCD->mt = multiplyByCommonTones(vector<Microtone_p> {_C, _D} );
    _mCE->mt = multiplyByCommonTones(vector<Microtone_p> {_C, _E} );
    _mDE->mt = multiplyByCommonTones(vector<Microtone_p> {_D, _E} );
    _half_CE_AC->mt = multiplyByCommonTones(vector<Microtone_p> {_C, _E} ); // for drawing only

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mAB->mt);
    ma.addMicrotone(_mAC->mt);
    ma.addMicrotone(_mAD->mt);
    ma.addMicrotone(_mAE->mt);
    ma.addMicrotone(_mBC->mt);
    ma.addMicrotone(_mBD->mt);
    ma.addMicrotone(_mBE->mt);
    ma.addMicrotone(_mCD->mt);
    ma.addMicrotone(_mCE->mt);
    ma.addMicrotone(_mDE->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()

    // SUBSETS
    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        /*
         ------------------------------------------------------
         CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 5
         (n,k):( 5 , 2 )
         (m,j):( 4 , 1 )
         count: 5
         [[{'D', 'E'}, {'B', 'E'}, {'C', 'E'}, {'A', 'E'}]] //E
         [[{'D', 'B'}, {'D', 'C'}, {'D', 'A'}, {'D', 'E'}]] //D
         [[{'D', 'C'}, {'B', 'C'}, {'C', 'A'}, {'C', 'E'}]] //C
         [[{'D', 'B'}, {'B', 'C'}, {'B', 'A'}, {'B', 'E'}]] //B
         [[{'D', 'A'}, {'B', 'A'}, {'C', 'A'}, {'A', 'E'}]] //A
         ------------------------------------------------------
         */
        _cps_4_1_0->setCommonTones(_E, getCommonTones());
        _cps_4_1_0->setABCD(_A, _B, _C, _D); //E

        _cps_4_1_1->setCommonTones(_D, getCommonTones());
        _cps_4_1_1->setABCD(_A, _B, _C, _E); //D

        _cps_4_1_2->setCommonTones(_C, getCommonTones());
        _cps_4_1_2->setABCD(_A, _B, _D, _E); //C

        _cps_4_1_3->setCommonTones(_B, getCommonTones());
        _cps_4_1_3->setABCD(_A, _C, _D, _E); //B

        _cps_4_1_4->setCommonTones(_A, getCommonTones());
        _cps_4_1_4->setABCD(_B, _C, _D, _E); //A

        /*
         ------------------------------------------------------
         CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 5
         (n,k):( 5 , 2 )
         (m,j):( 4 , 2 )
         count: 5
         [[{'D', 'B'}, {'D', 'C'}, {'D', 'A'}, {'B', 'C'}, {'B', 'A'}, {'C', 'A'}]] //E
         [[{'B', 'C'}, {'B', 'A'}, {'B', 'E'}, {'C', 'A'}, {'C', 'E'}, {'A', 'E'}]] //D
         [[{'D', 'B'}, {'D', 'A'}, {'D', 'E'}, {'B', 'A'}, {'B', 'E'}, {'A', 'E'}]] //C
         [[{'D', 'C'}, {'D', 'A'}, {'D', 'E'}, {'C', 'A'}, {'C', 'E'}, {'A', 'E'}]] //B
         [[{'D', 'B'}, {'D', 'C'}, {'D', 'E'}, {'B', 'C'}, {'B', 'E'}, {'C', 'E'}]] //A
         ------------------------------------------------------
         */
        _cps_4_2_0->setCommonTones(nullptr, getCommonTones());
        _cps_4_2_0->setABCD(_A, _B, _C, _D);

        _cps_4_2_1->setCommonTones(nullptr, getCommonTones());
        _cps_4_2_1->setABCD(_A, _B, _C, _E);

        _cps_4_2_2->setCommonTones(nullptr, getCommonTones());
        _cps_4_2_2->setABCD(_A, _B, _D, _E);

        _cps_4_2_3->setCommonTones(nullptr, getCommonTones());
        _cps_4_2_3->setABCD(_A, _C, _D, _E);

        _cps_4_2_4->setCommonTones(nullptr, getCommonTones());
        _cps_4_2_4->setABCD(_B, _C, _D, _E);
    }
}


#pragma mark - subsets

void CPS_5_2::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _cps_4_1_0 = make_shared<CPS_4_1> (_A, _B, _C, _D);
    _cps_4_1_1 = make_shared<CPS_4_1> (_A, _B, _C, _D);
    _cps_4_1_2 = make_shared<CPS_4_1> (_A, _B, _C, _D);
    _cps_4_1_3 = make_shared<CPS_4_1> (_A, _B, _C, _D);
    _cps_4_1_4 = make_shared<CPS_4_1> (_A, _B, _C, _D);

    _cps_4_2_0 = make_shared<CPS_4_2> (_A, _B, _C, _D);
    _cps_4_2_1 = make_shared<CPS_4_2> (_A, _B, _C, _D);
    _cps_4_2_2 = make_shared<CPS_4_2> (_A, _B, _C, _D);
    _cps_4_2_3 = make_shared<CPS_4_2> (_A, _B, _C, _D);
    _cps_4_2_4 = make_shared<CPS_4_2> (_A, _B, _C, _D);

    // subsets 0
    _subsets0.push_back(_cps_4_1_0);
    _subsets0.push_back(_cps_4_1_1);
    _subsets0.push_back(_cps_4_1_2);
    _subsets0.push_back(_cps_4_1_3);
    _subsets0.push_back(_cps_4_1_4);

    // subsets 1
    _subsets1.push_back(_cps_4_2_0);
    _subsets1.push_back(_cps_4_2_1);
    _subsets1.push_back(_cps_4_2_2);
    _subsets1.push_back(_cps_4_2_3);
    _subsets1.push_back(_cps_4_2_4);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_5_2::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void CPS_5_2::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void CPS_5_2::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void CPS_5_2::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void CPS_5_2::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void CPS_5_2::selectS0_5()
{
    jassertfalse;
}

void CPS_5_2::selectS0_6()
{
    jassertfalse;
}

void CPS_5_2::selectS0_7()
{
    jassertfalse;
}

void CPS_5_2::selectS1_0()
{
    _clearSelection();
    _subsets1[0]->setIsSelected(true);
}

void CPS_5_2::selectS1_1()
{
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void CPS_5_2::selectS1_2()
{
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void CPS_5_2::selectS1_3()
{
    _clearSelection();
    _subsets1[3]->setIsSelected(true);
}

void CPS_5_2::selectS1_4()
{
    _clearSelection();
    _subsets1[4]->setIsSelected(true);
}

void CPS_5_2::selectS1_5()
{
    jassertfalse;
}

void CPS_5_2::selectS1_6()
{
    jassertfalse;
}

void CPS_5_2::selectS1_7()
{
    jassertfalse;
}

bool CPS_5_2::isEulerGenusTuningType()
{
    return false;
}

