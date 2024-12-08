/*
 ==============================================================================

 CPS_5_3.cpp
 Created: 13 Aug 2021 8:36:29pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "CPS_5_3.h"
#include "EulerGenusModel.h"
#include "WilsonicProcessor.h"
#include "CPS.h"

#pragma mark - lifecycle

CPS_5_3::CPS_5_3(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E)
: Seed5(A, B, C, D, E)
{
    // basename
    _tuningType = CPS_Class::CPS_5_3;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_5_3::CPS_5_3(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed5(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_5_3;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_5_3::canPaintTuning()
{
    return true;
}

void CPS_5_3::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    auto const x00 = 0.f;
    auto const x01 = 0.185f;
    auto const x02 = 0.3f;
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
    auto const y07 = 1 - y06;
    auto const y09 = 1 - y04;
    auto const y12 = 1 - y01;

    // scaling func for hex coords...on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [] (float x, float y)
    {
        auto xx = -(0.5f - x);
        auto yy = -(0.5f - y);
        auto s = 0.55708f; // magic
        xx *= s;
        yy *= s;
        return Point<float> (xx, yy);
    };

    _mABC = CPSMicrotone_t::create(CPS::ABC(_A, _B, _C), hpc(x00, y05));
    _mABD = CPSMicrotone_t::create(CPS::ABC(_A, _B, _D), hpc(x02, y07));
    _mABE = CPSMicrotone_t::create(CPS::ABC(_A, _B, _E), hpc(x01, y12));
    _mACE = CPSMicrotone_t::create(CPS::ABC(_A, _C, _E), hpc(x04, y09));
    _mADE = CPSMicrotone_t::create(CPS::ABC(_A, _D, _E), hpc(x07, y12));
    _mBDE = CPSMicrotone_t::create(CPS::ABC(_B, _D, _E), hpc(x06, y07));
    _mCDE = CPSMicrotone_t::create(CPS::ABC(_C, _D, _E), hpc(x08, y05));
    _mACD = CPSMicrotone_t::create(CPS::ABC(_A, _C, _D), hpc(x05, y05));
    _mBCD = CPSMicrotone_t::create(CPS::ABC(_B, _C, _D), hpc(x04, y00));
    _mBCE = CPSMicrotone_t::create(CPS::ABC(_B, _C, _E), hpc(x03, y05));

    // trick to get star line segment overlapping
    auto tmpPtABD = hpc(x02, y07);
    auto tmpPtACD = hpc(x05, y05);
    auto tmpPt = tmpPtABD + 0.5f * (tmpPtACD - tmpPtABD);
    _halfACD = CPSMicrotone_t::create(CPS::ABC(_A, _C, _D), tmpPt);
    _p0 = CPSMicrotone_t::create_center(hpc(0.5f, 0.5f));

    // Outline
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABD, _mABE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABE, _mACE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mACE, _mADE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mADE, _mBDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBDE, _mCDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mCDE, _mACD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mACD, _mBCD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBCD, _mBCE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBCE, _mABC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABC, _mABD));
    // interior star
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABD, _mACD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBCE, _mBDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mACD, _mACE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBDE, _mABD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mACE, _mBCE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABD, _halfACD));

    _labelArray.push_back(_mABC);
    _labelArray.push_back(_mABD);
    _labelArray.push_back(_mABE);
    _labelArray.push_back(_mACE);
    _labelArray.push_back(_mADE);
    _labelArray.push_back(_mBDE);
    _labelArray.push_back(_mCDE);
    _labelArray.push_back(_mACD);
    _labelArray.push_back(_mBCD);
    _labelArray.push_back(_mBCE);

    _masterPtArray.push_back(_mABC);
    _masterPtArray.push_back(_mABD);
    _masterPtArray.push_back(_mABE);
    _masterPtArray.push_back(_mACE);
    _masterPtArray.push_back(_mADE);
    _masterPtArray.push_back(_mBDE);
    _masterPtArray.push_back(_mCDE);
    _masterPtArray.push_back(_mACD);
    _masterPtArray.push_back(_mBCD);
    _masterPtArray.push_back(_mBCE);
    _masterPtArray.push_back(_p0);
}

CPS_5_3::~CPS_5_3()
{

}

#pragma mark - update

void CPS_5_3::update()
{
    /*
     ------------------------------------------------------
     CPS AT PASCALS TRIANGLE AT ROW: 5
     ------------------------------------------------------
     Master Set: ['A', 'B', 'C', 'D', 'E']
     (n,k):( 5 , 3 )
     [('A', 'B', 'C'), ('A', 'B', 'D'), ('A', 'B', 'E'), ('A', 'C', 'D'), ('A', 'C', 'E'), ('A', 'D', 'E'), ('B', 'C', 'D'), ('B', 'C', 'E'), ('B', 'D', 'E'), ('C', 'D', 'E')]
     count: 10
     ------------------------------------------------------
     */
    _mABC->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _C} );
    _mABD->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _D} );
    _mABE->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _E} );
    _mACD->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _C, _D} );
    _mACE->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _C, _E} );
    _mADE->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _D, _E} );
    _mBCD->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _C, _D} );
    _mBCE->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _C, _E} );
    _mBDE->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _D, _E} );
    _mCDE->mt = multiplyByCommonTones(vector<Microtone_p> {_C, _D, _E} );
    _halfACD->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _C, _D} ); // for drawing only

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mABC->mt);
    ma.addMicrotone(_mABD->mt);
    ma.addMicrotone(_mABE->mt);
    ma.addMicrotone(_mACD->mt);
    ma.addMicrotone(_mACE->mt);
    ma.addMicrotone(_mADE->mt);
    ma.addMicrotone(_mBCD->mt);
    ma.addMicrotone(_mBCE->mt);
    ma.addMicrotone(_mBDE->mt);
    ma.addMicrotone(_mCDE->mt);
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
         (n,k):( 5 , 3 )
         (m,j):( 4 , 2 )
         count: 5
         [[{'D', 'B', 'E'}, {'D', 'C', 'E'}, {'D', 'A', 'E'}, {'B', 'C', 'E'}, {'B', 'A', 'E'}, {'C', 'A', 'E'}]], //E
         [[{'D', 'B', 'C'}, {'D', 'B', 'A'}, {'D', 'B', 'E'}, {'D', 'C', 'A'}, {'D', 'C', 'E'}, {'D', 'A', 'E'}]], //D
         [[{'D', 'B', 'C'}, {'D', 'C', 'A'}, {'D', 'C', 'E'}, {'B', 'C', 'A'}, {'B', 'C', 'E'}, {'C', 'A', 'E'}]], //C
         [[{'D', 'B', 'C'}, {'D', 'B', 'A'}, {'D', 'B', 'E'}, {'B', 'C', 'A'}, {'B', 'C', 'E'}, {'B', 'A', 'E'}]], //B
         [[{'D', 'B', 'A'}, {'D', 'C', 'A'}, {'D', 'A', 'E'}, {'B', 'C', 'A'}, {'B', 'A', 'E'}, {'C', 'A', 'E'}]] //A
         ------------------------------------------------------
         */
        _cps_4_2_0->setCommonTones(_E, getCommonTones());
        _cps_4_2_0->setABCD(_A, _B, _C, _D); //E

        _cps_4_2_1->setCommonTones(_D, getCommonTones());
        _cps_4_2_1->setABCD(_A, _B, _C, _E); //D

        _cps_4_2_2->setCommonTones(_C, getCommonTones());
        _cps_4_2_2->setABCD(_A, _B, _D, _E); //C

        _cps_4_2_3->setCommonTones(_B, getCommonTones());
        _cps_4_2_3->setABCD(_A, _C, _D, _E); //B

        _cps_4_2_4->setCommonTones(_A, getCommonTones());
        _cps_4_2_4->setABCD(_B, _C, _D, _E); //A

        /*
         ------------------------------------------------------
         CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 5
         (n,k):( 5 , 3 )
         (m,j):( 4 , 3 )
         count: 5
         [[{'D', 'B', 'C'}, {'D', 'B', 'A'}, {'D', 'C', 'A'}, {'B', 'C', 'A'}]] //E
         [[{'B', 'C', 'A'}, {'B', 'C', 'E'}, {'B', 'A', 'E'}, {'C', 'A', 'E'}]] //D
         [[{'D', 'B', 'A'}, {'D', 'B', 'E'}, {'D', 'A', 'E'}, {'B', 'A', 'E'}]] //C
         [[{'D', 'C', 'A'}, {'D', 'C', 'E'}, {'D', 'A', 'E'}, {'C', 'A', 'E'}]] //B
         [[{'D', 'B', 'C'}, {'D', 'B', 'E'}, {'D', 'C', 'E'}, {'B', 'C', 'E'}]] //A
         ------------------------------------------------------
         */
        _cps_4_3_0->setCommonTones(nullptr, getCommonTones());
        _cps_4_3_0->setABCD(_A, _B, _C, _D);

        _cps_4_3_1->setCommonTones(nullptr, getCommonTones());
        _cps_4_3_1->setABCD(_A, _B, _C, _E);

        _cps_4_3_2->setCommonTones(nullptr, getCommonTones());
        _cps_4_3_2->setABCD(_A, _B, _D, _E);

        _cps_4_3_3->setCommonTones(nullptr, getCommonTones());
        _cps_4_3_3->setABCD(_A, _C, _D, _E);

        _cps_4_3_4->setCommonTones(nullptr, getCommonTones());
        _cps_4_3_4->setABCD(_B, _C, _D, _E);
    }
}

void CPS_5_3::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _cps_4_2_0 = make_shared<CPS_4_2> (_A, _B, _C, _D);
    _cps_4_2_1 = make_shared<CPS_4_2> (_A, _B, _C, _D);
    _cps_4_2_2 = make_shared<CPS_4_2> (_A, _B, _C, _D);
    _cps_4_2_3 = make_shared<CPS_4_2> (_A, _B, _C, _D);
    _cps_4_2_4 = make_shared<CPS_4_2> (_A, _B, _C, _D);

    _cps_4_3_0 = make_shared<CPS_4_3> (_A, _B, _C, _D);
    _cps_4_3_1 = make_shared<CPS_4_3> (_A, _B, _C, _D);
    _cps_4_3_2 = make_shared<CPS_4_3> (_A, _B, _C, _D);
    _cps_4_3_3 = make_shared<CPS_4_3> (_A, _B, _C, _D);
    _cps_4_3_4 = make_shared<CPS_4_3> (_A, _B, _C, _D);

    // subsets0
    _subsets0.push_back(_cps_4_2_0);
    _subsets0.push_back(_cps_4_2_1);
    _subsets0.push_back(_cps_4_2_2);
    _subsets0.push_back(_cps_4_2_3);
    _subsets0.push_back(_cps_4_2_4);

    // subsets1
    _subsets1.push_back(_cps_4_3_0);
    _subsets1.push_back(_cps_4_3_1);
    _subsets1.push_back(_cps_4_3_2);
    _subsets1.push_back(_cps_4_3_3);
    _subsets1.push_back(_cps_4_3_4);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_5_3::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void CPS_5_3::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void CPS_5_3::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void CPS_5_3::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void CPS_5_3::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void CPS_5_3::selectS0_5()
{
    jassertfalse;
}

void CPS_5_3::selectS0_6()
{
    jassertfalse;
}

void CPS_5_3::selectS0_7()
{
    jassertfalse;
}

void CPS_5_3::selectS1_0()
{
    _clearSelection();
    _subsets1[0]->setIsSelected(true);
}

void CPS_5_3::selectS1_1()
{
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void CPS_5_3::selectS1_2()
{
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void CPS_5_3::selectS1_3()
{
    _clearSelection();
    _subsets1[3]->setIsSelected(true);
}

void CPS_5_3::selectS1_4()
{
    _clearSelection();
    _subsets1[4]->setIsSelected(true);
}

void CPS_5_3::selectS1_5()
{
    jassertfalse;
}

void CPS_5_3::selectS1_6()
{
    jassertfalse;
}

void CPS_5_3::selectS1_7()
{
    jassertfalse;
}

bool CPS_5_3::isEulerGenusTuningType()
{
    return false;
}

