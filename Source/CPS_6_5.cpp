/*
 ==============================================================================

 CPS_6_5.cpp
 Created: 13 Aug 2021 9:06:00pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "CPS_6_5.h"
#include "CPS.h"
#include "EulerGenusModel.h"

// HEXANY(6, 5) = 6 npo

#pragma mark - lifecycle

CPS_6_5::CPS_6_5(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F)
: Seed6(A, B, C, D, E, F)
{
    // basename
    _tuningType = CPS_Class::CPS_6_5;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_6_5::CPS_6_5(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed6(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_6_5;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_6_5::canPaintTuning()
{
    return true;
}

void CPS_6_5::_commonConstructorHelper()
{
    auto const x00 = 0.110f;
    auto const x01 = 0.260f;
    auto const x02 = 0.500f;
    auto const x03 = 1 - x01;
    auto const x04 = 1 - x00;

    auto const y00 = 0.170f;
    auto const y01 = 0.500f;
    auto const y02 = 0.630f;
    auto const y03 = 0.920f;

    auto hpc = [] (auto x, auto y)
    {
        auto xx = -(0.5f - x);
        auto yy = -(0.5f - y);
        auto s = 0.733f;
        s *= 0.95f;
        xx *= s;
        yy *= s;
        return Point<float> (xx, yy);
    };

    _mABCDE = CPSMicrotone_t::create(CPS::ABCDE(_A, _B, _C, _D, _E), hpc(x02, y01)); // ABCDE is the center
    _mABCDF = CPSMicrotone_t::create(CPS::ABCDE(_A, _B, _C, _D, _F), hpc(x01, y00));
    _mABCEF = CPSMicrotone_t::create(CPS::ABCDE(_A, _B, _C, _E, _F), hpc(x00, y02));
    _mABDEF = CPSMicrotone_t::create(CPS::ABCDE(_A, _B, _D, _E, _F), hpc(x02, y03));
    _mACDEF = CPSMicrotone_t::create(CPS::ABCDE(_A, _C, _D, _E, _F), hpc(x04, y02));
    _mBCDEF = CPSMicrotone_t::create(CPS::ABCDE(_B, _C, _D, _E, _F), hpc(x03, y00));
    _p0     = CPSMicrotone_t::create_center(hpc(x02, y02));

    // ABCDE [inverse of F] is the center, so always make it the last point
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABCDF, _mABCDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABCEF, _mABCDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABDEF, _mABCDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mACDEF, _mABCDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBCDEF, _mABCDE));

    _labelArray.push_back(_mBCDEF);
    _labelArray.push_back(_mACDEF);
    _labelArray.push_back(_mABDEF);
    _labelArray.push_back(_mABCEF);
    _labelArray.push_back(_mABCDF);
    _labelArray.push_back(_mABCDE); // draw ABCDE last

    _masterPtArray.push_back(_mBCDEF);
    _masterPtArray.push_back(_mACDEF);
    _masterPtArray.push_back(_mABDEF);
    _masterPtArray.push_back(_mABCEF);
    _masterPtArray.push_back(_mABCDF);
    _masterPtArray.push_back(_mABCDE);
    _masterPtArray.push_back(_p0);
}


CPS_6_5::~CPS_6_5()
{

}

#pragma mark - update

void CPS_6_5::update()
{
    /*
     ------------------------------------------------------
     CPS AT PASCALS TRIANGLE AT ROW: 6
     ------------------------------------------------------
     Master Set: ['A', 'B', 'C', 'D', 'E', 'F']
     (n,k):( 6 , 5 )
     [('A', 'B', 'C', 'D', 'E'), ('A', 'B', 'C', 'D', 'F'), ('A', 'B', 'C', 'E', 'F'), ('A', 'B', 'D', 'E', 'F'), ('A', 'C', 'D', 'E', 'F'), ('B', 'C', 'D', 'E', 'F')]
     count: 6
     ------------------------------------------------------
     */

    _mABCDE->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _C, _D, _E} );
    _mABCDF->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _C, _D, _F} );
    _mABCEF->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _C, _E, _F} );
    _mABDEF->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _D, _E, _F} );
    _mACDEF->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _C, _D, _E, _F} );
    _mBCDEF->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _C, _D, _E, _F} );

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mABCDE->mt);
    ma.addMicrotone(_mABCDF->mt);
    ma.addMicrotone(_mABCEF->mt);
    ma.addMicrotone(_mABDEF->mt);
    ma.addMicrotone(_mACDEF->mt);
    ma.addMicrotone(_mBCDEF->mt);
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
        //    (n,k):( 6 , 5 )
        //    (m,j):( 5 , 4 )
        //    count: 6
        //    [[[{'D', 'B', 'C', 'A', 'F'}, {'D', 'B', 'C', 'F', 'E'}, {'D', 'B', 'A', 'F', 'E'}, {'D', 'C', 'A', 'F', 'E'}, {'B', 'C', 'A', 'F', 'E'}]], //F
        //     [[{'D', 'B', 'C', 'A', 'E'}, {'D', 'B', 'C', 'F', 'E'}, {'D', 'B', 'A', 'F', 'E'}, {'D', 'C', 'A', 'F', 'E'}, {'B', 'C', 'A', 'F', 'E'}]], //E
        //     [[{'D', 'B', 'C', 'A', 'F'}, {'D', 'B', 'C', 'A', 'E'}, {'D', 'B', 'C', 'F', 'E'}, {'D', 'B', 'A', 'F', 'E'}, {'D', 'C', 'A', 'F', 'E'}]], //D
        //     [[{'D', 'B', 'C', 'A', 'F'}, {'D', 'B', 'C', 'A', 'E'}, {'D', 'B', 'C', 'F', 'E'}, {'D', 'C', 'A', 'F', 'E'}, {'B', 'C', 'A', 'F', 'E'}]], //C
        //     [[{'D', 'B', 'C', 'A', 'F'}, {'D', 'B', 'C', 'A', 'E'}, {'D', 'B', 'C', 'F', 'E'}, {'D', 'B', 'A', 'F', 'E'}, {'B', 'C', 'A', 'F', 'E'}]], //B
        //     [[{'D', 'B', 'C', 'A', 'F'}, {'D', 'B', 'C', 'A', 'E'}, {'D', 'B', 'A', 'F', 'E'}, {'D', 'C', 'A', 'F', 'E'}, {'B', 'C', 'A', 'F', 'E'}]]] //A
        //    ------------------------------------------------------
        _cps_5_4_0->setCommonTones(_F, getCommonTones());
        _cps_5_4_0->setABCDE(_A, _B, _C, _D, _E); //F

        _cps_5_4_1->setCommonTones(_E, getCommonTones());
        _cps_5_4_1->setABCDE(_A, _B, _C, _D, _F); //E

        _cps_5_4_2->setCommonTones(_D, getCommonTones());
        _cps_5_4_2->setABCDE(_A, _B, _C, _E, _F); //D

        _cps_5_4_3->setCommonTones(_C, getCommonTones());
        _cps_5_4_3->setABCDE(_A, _B, _D, _E, _F); //C

        _cps_5_4_4->setCommonTones(_B, getCommonTones());
        _cps_5_4_4->setABCDE(_A, _C, _D, _E, _F); //B

        _cps_5_4_5->setCommonTones(_A, getCommonTones());
        _cps_5_4_5->setABCDE(_B, _C, _D, _E, _F); //A

        //    ------------------------------------------------------
        //    CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
        //    (n,k):( 6 , 5 )
        //    (m,j):( 5 , 5 )
        //    count: 6
        //    [[[{'D', 'B', 'C', 'A', 'E'}]], [[{'D', 'B', 'C', 'F', 'A'}]], [[{'B', 'C', 'F', 'A', 'E'}]], [[{'D', 'B', 'F', 'A', 'E'}]], [[{'D', 'C', 'F', 'A', 'E'}]], [[{'D', 'B', 'C', 'F', 'E'}]]]
        //    ------------------------------------------------------
        _cps_5_5_0->setCommonTones(nullptr, getCommonTones());
        _cps_5_5_0->setABCDE(_A, _B, _C, _D, _E); // F

        _cps_5_5_1->setCommonTones(nullptr, getCommonTones());
        _cps_5_5_1->setABCDE(_A, _B, _C, _D, _F); // E

        _cps_5_5_2->setCommonTones(nullptr, getCommonTones());
        _cps_5_5_2->setABCDE(_A, _B, _C, _E, _F); // D

        _cps_5_5_3->setCommonTones(nullptr, getCommonTones());
        _cps_5_5_3->setABCDE(_A, _B, _D, _E, _F); // C

        _cps_5_5_4->setCommonTones(nullptr, getCommonTones());
        _cps_5_5_4->setABCDE(_A, _C, _D, _E, _F); // B

        _cps_5_5_5->setCommonTones(nullptr, getCommonTones());
        _cps_5_5_5->setABCDE(_B, _C, _D, _E, _F); // A
    }
}

#pragma mark - subsets

void CPS_6_5::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _cps_5_4_0 = make_shared<CPS_5_4> (_A, _B, _C, _D, _E);
    _cps_5_4_1 = make_shared<CPS_5_4> (_A, _B, _C, _D, _E);
    _cps_5_4_2 = make_shared<CPS_5_4> (_A, _B, _C, _D, _E);
    _cps_5_4_3 = make_shared<CPS_5_4> (_A, _B, _C, _D, _E);
    _cps_5_4_4 = make_shared<CPS_5_4> (_A, _B, _C, _D, _E);
    _cps_5_4_5 = make_shared<CPS_5_4> (_A, _B, _C, _D, _E);

    _cps_5_5_0 = make_shared<CPS_5_5> (_A, _B, _C, _D, _E);
    _cps_5_5_1 = make_shared<CPS_5_5> (_A, _B, _C, _D, _E);
    _cps_5_5_2 = make_shared<CPS_5_5> (_A, _B, _C, _D, _E);
    _cps_5_5_3 = make_shared<CPS_5_5> (_A, _B, _C, _D, _E);
    _cps_5_5_4 = make_shared<CPS_5_5> (_A, _B, _C, _D, _E);
    _cps_5_5_5 = make_shared<CPS_5_5> (_A, _B, _C, _D, _E);

    // subsets0
    _subsets0.push_back(_cps_5_4_0);
    _subsets0.push_back(_cps_5_4_1);
    _subsets0.push_back(_cps_5_4_2);
    _subsets0.push_back(_cps_5_4_3);
    _subsets0.push_back(_cps_5_4_4);
    _subsets0.push_back(_cps_5_4_5);

    // subsets1
    _subsets1.push_back(_cps_5_5_0);
    _subsets1.push_back(_cps_5_5_1);
    _subsets1.push_back(_cps_5_5_2);
    _subsets1.push_back(_cps_5_5_3);
    _subsets1.push_back(_cps_5_5_4);
    _subsets1.push_back(_cps_5_5_5);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_6_5::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void CPS_6_5::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void CPS_6_5::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void CPS_6_5::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void CPS_6_5::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void CPS_6_5::selectS0_5()
{
    _clearSelection();
    _subsets0[5]->setIsSelected(true);
}

void CPS_6_5::selectS0_6()
{
    jassertfalse;
}

void CPS_6_5::selectS0_7()
{
    jassertfalse;
}

void CPS_6_5::selectS1_0()
{
    _clearSelection();
    _subsets1[0]->setIsSelected(true);
}

void CPS_6_5::selectS1_1()
{
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void CPS_6_5::selectS1_2()
{
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void CPS_6_5::selectS1_3()
{
    _clearSelection();
    _subsets1[3]->setIsSelected(true);
}

void CPS_6_5::selectS1_4()
{
    _clearSelection();
    _subsets1[4]->setIsSelected(true);
}

void CPS_6_5::selectS1_5()
{
    _clearSelection();
    _subsets1[5]->setIsSelected(true);
}

void CPS_6_5::selectS1_6()
{
    jassertfalse;
}

void CPS_6_5::selectS1_7()
{
    jassertfalse;
}

bool CPS_6_5::isEulerGenusTuningType()
{
    return false;
}

