/*
 ==============================================================================

 CPS_5_4.cpp
 Created: 13 Aug 2021 8:35:04pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "CPS_5_4.h"
#include "CPS.h"
#include "EulerGenusModel.h"

#pragma mark - lifecycle

CPS_5_4::CPS_5_4(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E)
: Seed5(A, B, C, D, E)
{
    // basename
    _tuningType = CPS_Class::CPS_5_4;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_5_4::CPS_5_4(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed5(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_5_4;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_5_4::canPaintTuning()
{
    return true;
}

void CPS_5_4::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    auto const x01 = 0.185f;
    auto const x02 = 0.300f;
    auto const x04 = 0.5f;
    auto const x06 = 1.f - x02;
    auto const x07 = 1.f - x01;
    auto const y02 = 0.185f;
    auto const y03 = 0.235f;
    auto const y06 = 0.415f;
    auto const y10 = 1.f - y03;

    // scaling func for coords...on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [] (float x, float y)
    {
        auto const sr3 = 1.f;
        auto xx = -(0.5f - x);
        xx *= sr3;
        auto yy = (0.5f - y);
        auto s = 0.55708f; // magic
        xx *= s;
        yy *= s;
        return Point<float> (xx, yy);
    };

    _mABCD = CPSMicrotone_t::create(CPS::ABCD(_A, _B, _C, _D), hpc(x02, y10) );
    _mABCE = CPSMicrotone_t::create(CPS::ABCD(_A, _B, _C, _E), hpc(x01, y06) );
    _mABDE = CPSMicrotone_t::create(CPS::ABCD(_A, _B, _D, _E), hpc(x04, y02) );
    _mACDE = CPSMicrotone_t::create(CPS::ABCD(_A, _C, _D, _E), hpc(x07, y06) );
    _mBCDE = CPSMicrotone_t::create(CPS::ABCD(_B, _C, _D, _E), hpc(x06, y10) );
    _p0 = CPSMicrotone_t::create_center(hpc(0.5f, 0.5f));

    _lineArray.push_back(CPSMicrotone_t::create_line(_mABCE, _mABCD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABCD, _mBCDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBCDE, _mACDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mACDE, _mABDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABDE, _mABCE));

    _labelArray.push_back(_mABCE);
    _labelArray.push_back(_mABCD);
    _labelArray.push_back(_mBCDE);
    _labelArray.push_back(_mACDE);
    _labelArray.push_back(_mABDE);

    _masterPtArray.push_back(_mABCD);
    _masterPtArray.push_back(_mABCE);
    _masterPtArray.push_back(_mABDE);
    _masterPtArray.push_back(_mACDE);
    _masterPtArray.push_back(_mBCDE);
    _masterPtArray.push_back(_p0);
}


CPS_5_4::~CPS_5_4()
{

}

#pragma mark - update

void CPS_5_4::update()
{
    /*
     ------------------------------------------------------
     CPS AT PASCALS TRIANGLE AT ROW: 5
     ------------------------------------------------------
     Master Set: ['A', 'B', 'C', 'D', 'E']
     (n,k):( 5 , 4 )
     [('A', 'B', 'C', 'D'), ('A', 'B', 'C', 'E'), ('A', 'B', 'D', 'E'), ('A', 'C', 'D', 'E'), ('B', 'C', 'D', 'E')]
     count: 5
     ------------------------------------------------------
     */
    _mABCD->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _C, _D} );
    _mABCE->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _C, _E} );
    _mABDE->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _D, _E} );
    _mACDE->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _C, _D, _E} );
    _mBCDE->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _C, _D, _E} );


    auto ma = MicrotoneArray();
    ma.addMicrotone(_mABCD->mt);
    ma.addMicrotone(_mABCE->mt);
    ma.addMicrotone(_mABDE->mt);
    ma.addMicrotone(_mACDE->mt);
    ma.addMicrotone(_mBCDE->mt);
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
         (n,k):( 5 , 4 )
         (m,j):( 4 , 3 )
         count: 5
         [[{'D', 'B', 'C', 'E'}, {'D', 'B', 'A', 'E'}, {'D', 'C', 'A', 'E'}, {'B', 'C', 'A', 'E'}]],//E
         [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'C', 'E'}, {'D', 'B', 'A', 'E'}, {'D', 'C', 'A', 'E'}]],//D
         [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'C', 'E'}, {'D', 'C', 'A', 'E'}, {'B', 'C', 'A', 'E'}]],//C
         [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'C', 'E'}, {'D', 'B', 'A', 'E'}, {'B', 'C', 'A', 'E'}]],//B
         [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'A', 'E'}, {'D', 'C', 'A', 'E'}, {'B', 'C', 'A', 'E'}]]]//A
         ------------------------------------------------------
         */
        _cps_4_3_0->setCommonTones(_E, getCommonTones());
        _cps_4_3_0->setABCD(_A, _B, _C, _D); //E

        _cps_4_3_1->setCommonTones(_D, getCommonTones());
        _cps_4_3_1->setABCD(_A, _B, _C, _E); //D

        _cps_4_3_2->setCommonTones(_C, getCommonTones());
        _cps_4_3_2->setABCD(_A, _B, _D, _E); //C

        _cps_4_3_3->setCommonTones(_B, getCommonTones());
        _cps_4_3_3->setABCD(_A, _C, _D, _E); //B

        _cps_4_3_4->setCommonTones(_A, getCommonTones());
        _cps_4_3_4->setABCD(_B, _C, _D, _E); //A

        /*
         ------------------------------------------------------
         CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 5
         (n,k):( 5 , 4 )
         (m,j):( 4 , 4 )
         count: 5
         [[{'D', 'B', 'C', 'A'}]],
         [[{'B', 'C', 'A', 'E'}]],
         [[{'D', 'B', 'A', 'E'}]],
         [[{'D', 'C', 'A', 'E'}]],
         [[{'D', 'B', 'C', 'E'}]]
         ------------------------------------------------------
         */
        _cps_4_4_0->setCommonTones(nullptr, getCommonTones());
        _cps_4_4_0->setABCD(_A, _B, _C, _D);

        _cps_4_4_1->setCommonTones(nullptr, getCommonTones());
        _cps_4_4_1->setABCD(_A, _B, _C, _E);

        _cps_4_4_2->setCommonTones(nullptr, getCommonTones());
        _cps_4_4_2->setABCD(_A, _B, _D, _E);

        _cps_4_4_3->setCommonTones(nullptr, getCommonTones());
        _cps_4_4_3->setABCD(_A, _C, _D, _E);

        _cps_4_4_4->setCommonTones(nullptr, getCommonTones());
        _cps_4_4_4->setABCD(_B, _C, _D, _E);
    }
}

void CPS_5_4::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _cps_4_3_0 = make_shared<CPS_4_3> (_A, _B, _C, _D);
    _cps_4_3_1 = make_shared<CPS_4_3> (_A, _B, _C, _D);
    _cps_4_3_2 = make_shared<CPS_4_3> (_A, _B, _C, _D);
    _cps_4_3_3 = make_shared<CPS_4_3> (_A, _B, _C, _D);
    _cps_4_3_4 = make_shared<CPS_4_3> (_A, _B, _C, _D);

    _cps_4_4_0 = make_shared<CPS_4_4> (_A, _B, _C, _D);
    _cps_4_4_1 = make_shared<CPS_4_4> (_A, _B, _C, _D);
    _cps_4_4_2 = make_shared<CPS_4_4> (_A, _B, _C, _D);
    _cps_4_4_3 = make_shared<CPS_4_4> (_A, _B, _C, _D);
    _cps_4_4_4 = make_shared<CPS_4_4> (_A, _B, _C, _D);

    // subsets0
    _subsets0.push_back(_cps_4_3_0);
    _subsets0.push_back(_cps_4_3_1);
    _subsets0.push_back(_cps_4_3_2);
    _subsets0.push_back(_cps_4_3_3);
    _subsets0.push_back(_cps_4_3_4);

    // subsets1
    _subsets1.push_back(_cps_4_4_0);
    _subsets1.push_back(_cps_4_4_1);
    _subsets1.push_back(_cps_4_4_2);
    _subsets1.push_back(_cps_4_4_3);
    _subsets1.push_back(_cps_4_4_4);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_5_4::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void CPS_5_4::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void CPS_5_4::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void CPS_5_4::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void CPS_5_4::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void CPS_5_4::selectS0_5()
{
    jassertfalse;
}

void CPS_5_4::selectS0_6()
{
    jassertfalse;
}

void CPS_5_4::selectS0_7()
{
    jassertfalse;
}

void CPS_5_4::selectS1_0()
{
    _clearSelection();
    _subsets1[0]->setIsSelected(true);
}

void CPS_5_4::selectS1_1()
{
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void CPS_5_4::selectS1_2()
{
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void CPS_5_4::selectS1_3()
{
    _clearSelection();
    _subsets1[3]->setIsSelected(true);
}

void CPS_5_4::selectS1_4()
{
    _clearSelection();
    _subsets1[4]->setIsSelected(true);
}

void CPS_5_4::selectS1_5()
{
    jassertfalse;
}

void CPS_5_4::selectS1_6()
{
    jassertfalse;
}

void CPS_5_4::selectS1_7()
{
    jassertfalse;
}

bool CPS_5_4::isEulerGenusTuningType()
{
    return false;
}

