/*
 ==============================================================================

 CPS_4_2.cpp
 Created: 13 Aug 2021 8:10:44pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "CPS_4_2.h"
#include "WilsonicProcessor.h"
#include "EulerGenusModel.h"
#include "CPS.h"

#pragma mark - lifecycle

CPS_4_2::CPS_4_2(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D)
: Seed4(A, B, C, D)
{
    // basename
    _tuningType = CPS_Class::CPS_4_2;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_4_2::CPS_4_2(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed4(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_4_2;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_4_2::canPaintTuning()
{
    return true;
}

void CPS_4_2::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    // scaling func for hex coords...on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [](auto x, auto y)
    {
        auto xx = 0.5f - x;
        xx *= (1.f / 1.136f);
        auto yy = 0.5f - y;
        auto const s = 0.4f;
        xx *= s;
        yy *= s;
        return Point<float> (xx, yy);
    };

    // 6 hexany degrees in percentage coordinates
    _mAB = CPSMicrotone_t::create(CPS::AB(_A, _B), hpc(1.0f, 0.75f) );
    _mAC = CPSMicrotone_t::create(CPS::AB(_A, _C), hpc(0.5f, 0.00f) );
    _mAD = CPSMicrotone_t::create(CPS::AB(_A, _D), hpc(1.0f, 0.25f) );
    _mBC = CPSMicrotone_t::create(CPS::AB(_B, _C), hpc(0.0f, 0.75f) );
    _mBD = CPSMicrotone_t::create(CPS::AB(_B, _D), hpc(0.5f, 1.00f) );
    _mCD = CPSMicrotone_t::create(CPS::AB(_C, _D), hpc(0.0f, 0.25f) );
    _p0  = CPSMicrotone_t::create_center(hpc(0.50f, 0.50f));

    _lineArray.push_back(CPSMicrotone_t::create_line(_mAB, _mAC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAC, _mAD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAD, _mAB));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBD, _mBC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBC, _mCD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAB, _mBC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBC, _mAC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAC, _mCD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mCD, _mAD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAD, _mBD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mCD, _mBD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBD, _mAB));

    _labelArray.push_back(_mAB);
    _labelArray.push_back(_mAC);
    _labelArray.push_back(_mAD);
    _labelArray.push_back(_mBC);
    _labelArray.push_back(_mBD);
    _labelArray.push_back(_mCD);

    _masterPtArray.push_back(_mAB);
    _masterPtArray.push_back(_mAC);
    _masterPtArray.push_back(_mAD);
    _masterPtArray.push_back(_mBC);
    _masterPtArray.push_back(_mBD);
    _masterPtArray.push_back(_mCD);
    _masterPtArray.push_back(_p0);
}

CPS_4_2::~CPS_4_2()
{

}

#pragma mark - update

void CPS_4_2::update()
{
    /*
     ------------------------------------------------------
     CPS AT PASCALS TRIANGLE AT ROW: 4
     ------------------------------------------------------
     Master Set: ['A', 'B', 'C', 'D']
     (n,k):( 4 , 2 )
     [('A', 'B'), ('A', 'C'), ('A', 'D'), ('B', 'C'), ('B', 'D'), ('C', 'D')]
     count: 6
     ------------------------------------------------------
     */

    _mAB->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B} );
    _mAC->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _C} );
    _mAD->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _D} );
    _mBC->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _C} );
    _mBD->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _D} );
    _mCD->mt = multiplyByCommonTones(vector<Microtone_p> {_C, _D} );

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mAB->mt);
    ma.addMicrotone(_mAC->mt);
    ma.addMicrotone(_mAD->mt);
    ma.addMicrotone(_mBC->mt);
    ma.addMicrotone(_mBD->mt);
    ma.addMicrotone(_mCD->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()

    // SUBSETS

    /*
     ------------------------------------------------------
     CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 4
     (n,k):( 4 , 2 )
     (m,j):( 3 , 1 )
     count: 4
     [[[{'D', 'B'}, {'D', 'C'}, {'D', 'A'}]],
     [[{'D', 'C'}, {'B', 'C'}, {'C', 'A'}]],
     [[{'D', 'B'}, {'B', 'C'}, {'B', 'A'}]],
     [[{'D', 'A'}, {'B', 'A'}, {'C', 'A'}]]]
     ------------------------------------------------------
     */
    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        _cps_3_1_0->setCommonTones(_D, getCommonTones());
        _cps_3_1_0->setABC(_A, _B, _C);

        _cps_3_1_1->setCommonTones(_C, getCommonTones());
        _cps_3_1_1->setABC(_A, _B, _D);

        _cps_3_1_2->setCommonTones(_B, getCommonTones());
        _cps_3_1_2->setABC(_A, _C, _D);

        _cps_3_1_3->setCommonTones(_A, getCommonTones());
        _cps_3_1_3->setABC(_B, _C, _D);

        /*
         ------------------------------------------------------
         CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 4
         (n,k):( 4 , 2 )
         (m,j):( 3 , 2 )
         count: 4
         [[[{'B', 'C'}, {'B', 'A'}, {'C', 'A'}]],// D
         [[{'D', 'B'}, {'D', 'A'}, {'B', 'A'}]], // C
         [[{'D', 'C'}, {'D', 'A'}, {'C', 'A'}]], // B
         [[{'D', 'B'}, {'D', 'C'}, {'B', 'C'}]]] // A
         ------------------------------------------------------
         */
        _cps_3_2_0->setCommonTones(nullptr, getCommonTones());
        _cps_3_2_0->setABC(_A, _B, _C);

        _cps_3_2_1->setCommonTones(nullptr, getCommonTones());
        _cps_3_2_1->setABC(_A, _B, _D);

        _cps_3_2_2->setCommonTones(nullptr, getCommonTones());
        _cps_3_2_2->setABC(_A, _C, _D);

        _cps_3_2_3->setCommonTones(nullptr, getCommonTones());
        _cps_3_2_3->setABC(_B, _C, _D);
    }
}

#pragma mark - subsets

void CPS_4_2::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _cps_3_1_0 = make_shared<CPS_3_1> (_A, _B, _C);
    _cps_3_1_1 = make_shared<CPS_3_1> (_A, _B, _C);
    _cps_3_1_2 = make_shared<CPS_3_1> (_A, _B, _C);
    _cps_3_1_3 = make_shared<CPS_3_1> (_A, _B, _C);

    _cps_3_2_0 = make_shared<CPS_3_2> (_A, _B, _C);
    _cps_3_2_1 = make_shared<CPS_3_2> (_A, _B, _C);
    _cps_3_2_2 = make_shared<CPS_3_2> (_A, _B, _C);
    _cps_3_2_3 = make_shared<CPS_3_2> (_A, _B, _C);

    // subsets 0
    _subsets0.push_back(_cps_3_1_0);
    _subsets0.push_back(_cps_3_1_1);
    _subsets0.push_back(_cps_3_1_2);
    _subsets0.push_back(_cps_3_1_3);

    // subsets 1
    _subsets1.push_back(_cps_3_2_0);
    _subsets1.push_back(_cps_3_2_1);
    _subsets1.push_back(_cps_3_2_2);
    _subsets1.push_back(_cps_3_2_3);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_4_2::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void CPS_4_2::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
;
}

void CPS_4_2::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void CPS_4_2::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void CPS_4_2::selectS0_4()
{
    jassertfalse;
}

void CPS_4_2::selectS0_5()
{
    jassertfalse;
}

void CPS_4_2::selectS0_6()
{
    jassertfalse;
}

void CPS_4_2::selectS0_7()
{
    jassertfalse;
}

void CPS_4_2::selectS1_0()
{
    _clearSelection();
    _subsets1[0]->setIsSelected(true);
}

void CPS_4_2::selectS1_1()
{
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void CPS_4_2::selectS1_2()
{
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void CPS_4_2::selectS1_3()
{
    _clearSelection();
    _subsets1[3]->setIsSelected(true);
}

void CPS_4_2::selectS1_4()
{
    jassertfalse;
}

void CPS_4_2::selectS1_5()
{
    jassertfalse;
}

void CPS_4_2::selectS1_6()
{
    jassertfalse;
}

void CPS_4_2::selectS1_7()
{
    jassertfalse;
}

bool CPS_4_2::isEulerGenusTuningType()
{
    return false;
}

