/*
 ==============================================================================

 CPS_4_3.cpp
 Created: 13 Aug 2021 8:10:57pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "CPS_4_3.h"
#include "EulerGenusModel.h"
#include "WilsonicProcessor.h"
#include "CPS.h"


#pragma mark - lifecycle

CPS_4_3::CPS_4_3(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D)
: Seed4(A, B, C, D)
{
    // basename
    _tuningType = CPS_Class::CPS_4_3;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update

    update();
}

CPS_4_3::CPS_4_3(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed4(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_4_3;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_4_3::canPaintTuning()
{
    return true;
}

void CPS_4_3::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    // scaling func for hex coords...on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [](auto x, auto y)
    {
        auto const sr3 = 1.f / (sqrtf(3) / 2.f);
        auto xx = 0.5f - x;
        xx *= sr3;
        auto yy = -(0.5f - y);
        auto const s = 0.4f;
        xx *= s;
        yy *= s;
        return Point<float> (xx, yy);
    };

    auto const ysr3 = 1 - (1 / sqrtf(3));
    _mABC = CPSMicrotone_t::create(CPS::ABC(_A, _B, _C), hpc(0.5f, ysr3));
    _mABD = CPSMicrotone_t::create(CPS::ABC(_A, _B, _D), hpc(0.5f, 1   ));
    _mACD = CPSMicrotone_t::create(CPS::ABC(_A, _C, _D), hpc(1  , 0   ));
    _mBCD = CPSMicrotone_t::create(CPS::ABC(_B, _C, _D), hpc(0  , 0   ));
    _p0 = CPSMicrotone_t::create_center(hpc(0.5f, 0.5f));

    _lineArray.push_back(CPSMicrotone_t::create_line(_mBCD, _mABC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBCD, _mABD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBCD, _mACD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABD, _mABC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mACD, _mABD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABC, _mACD));

    _labelArray.push_back(_mABC);
    _labelArray.push_back(_mABD);
    _labelArray.push_back(_mACD);
    _labelArray.push_back(_mBCD);

    _masterPtArray.push_back(_mABC);
    _masterPtArray.push_back(_mABD);
    _masterPtArray.push_back(_mACD);
    _masterPtArray.push_back(_mBCD);
    _masterPtArray.push_back(_p0);
}

CPS_4_3::~CPS_4_3()
{

}

#pragma mark - update

void CPS_4_3::update()
{
    /*
     ------------------------------------------------------
     CPS AT PASCALS TRIANGLE AT ROW: 4
     ------------------------------------------------------
     Master Set: ['A', 'B', 'C', 'D']
     (n,k):( 4 , 3 )
     [('A', 'B', 'C'), ('A', 'B', 'D'), ('A', 'C', 'D'), ('B', 'C', 'D')]
     count: 4
     ------------------------------------------------------
     */

    _mABC->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _C} );
    _mABD->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _D} );
    _mACD->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _C, _D} );
    _mBCD->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _C, _D} );

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mABC->mt);
    ma.addMicrotone(_mABD->mt);
    ma.addMicrotone(_mACD->mt);
    ma.addMicrotone(_mBCD->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()

    // SUBSETS

    // ------------------------------------------------------
    // CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 4
    // (n,k):( 4 , 3 )
    // (m,j):( 3 , 2 )
    // count: 4
    // ------------------------------------------------------
    if(getShouldComputeSubsets() == true)
    {
        if(_getDidAllocateSubsets() == false)
        {
            _allocateSubsets();
        }

        //     [[[{'D', 'B', 'C'}, {'D', 'B', 'A'}, {'D', 'C', 'A'}]],  D
        _cps_3_2_0->setCommonTones(_D, getCommonTones());
        _cps_3_2_0->setABC(_A, _B, _C);

        //     [[{'D', 'B', 'C'}, {'D', 'C', 'A'}, {'B', 'C', 'A'}]],  C
        _cps_3_2_1->setCommonTones(_C, getCommonTones());
        _cps_3_2_1->setABC(_A, _B, _D);

        //     [[{'D', 'B', 'C'}, {'D', 'B', 'A'}, {'B', 'C', 'A'}]],  B
        _cps_3_2_2->setCommonTones(_B, getCommonTones());
        _cps_3_2_2->setABC(_A, _C, _D);

        //     [[{'D', 'B', 'A'}, {'D', 'C', 'A'}, {'B', 'C', 'A'}]]]  A
        _cps_3_2_3->setCommonTones(_A, getCommonTones());
        _cps_3_2_3->setABC(_B, _C, _D);

        /*
         ------------------------------------------------------
         CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 4
         (n,k):( 4 , 3 )
         (m,j):( 3 , 3 )
         count: 4
         [[[{'B', 'C', 'A'}]],
         [[{'D', 'B', 'A'}]],
         [[{'D', 'C', 'A'}]],
         [[{'D', 'B', 'C'}]]]
         ------------------------------------------------------
         */
        _cps_3_3_0->setCommonTones(nullptr, getCommonTones());
        _cps_3_3_0->setABC(_A, _B, _C);

        _cps_3_3_1->setCommonTones(nullptr, getCommonTones());
        _cps_3_3_1->setABC(_A, _B, _D);

        _cps_3_3_2->setCommonTones(nullptr, getCommonTones());
        _cps_3_3_2->setABC(_A, _C, _D);

        _cps_3_3_3->setCommonTones(nullptr, getCommonTones());
        _cps_3_3_3->setABC(_B, _C, _D);
    }
}

#pragma mark - subsets

void CPS_4_3::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _cps_3_2_0 = make_shared<CPS_3_2> (_A, _B, _C);
    _cps_3_2_1 = make_shared<CPS_3_2> (_A, _B, _C);
    _cps_3_2_2 = make_shared<CPS_3_2> (_A, _B, _C);
    _cps_3_2_3 = make_shared<CPS_3_2> (_A, _B, _C);
    
    _cps_3_3_0 = make_shared<CPS_3_3> (_A, _B, _C);
    _cps_3_3_1 = make_shared<CPS_3_3> (_A, _B, _C);
    _cps_3_3_2 = make_shared<CPS_3_3> (_A, _B, _C);
    _cps_3_3_3 = make_shared<CPS_3_3> (_A, _B, _C);

    // subsets0
    _subsets0.push_back(_cps_3_2_0);
    _subsets0.push_back(_cps_3_2_1);
    _subsets0.push_back(_cps_3_2_2);
    _subsets0.push_back(_cps_3_2_3);

    //subsets1
    _subsets1.push_back(_cps_3_3_0);
    _subsets1.push_back(_cps_3_3_1);
    _subsets1.push_back(_cps_3_3_2);
    _subsets1.push_back(_cps_3_3_3);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_4_3::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void CPS_4_3::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
    ;
}

void CPS_4_3::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void CPS_4_3::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void CPS_4_3::selectS0_4()
{
    jassertfalse;
}

void CPS_4_3::selectS0_5()
{
    jassertfalse;
}

void CPS_4_3::selectS0_6()
{
    jassertfalse;
}

void CPS_4_3::selectS0_7()
{
    jassertfalse;
}

void CPS_4_3::selectS1_0()
{
    _clearSelection();
    _subsets1[0]->setIsSelected(true);
}

void CPS_4_3::selectS1_1()
{
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void CPS_4_3::selectS1_2()
{
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void CPS_4_3::selectS1_3()
{
    _clearSelection();
    _subsets1[3]->setIsSelected(true);
}

void CPS_4_3::selectS1_4()
{
    jassertfalse;
}

void CPS_4_3::selectS1_5()
{
    jassertfalse;
}

void CPS_4_3::selectS1_6()
{
    jassertfalse;
}

void CPS_4_3::selectS1_7()
{
    jassertfalse;
}

bool CPS_4_3::isEulerGenusTuningType()
{
    return false;
}

