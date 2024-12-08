/*
 ==============================================================================

 CPS_6_4.cpp
 Created: 13 Aug 2021 9:05:38pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "CPS_6_4.h"
#include "CPS.h"
#include "EulerGenusModel.h"

#pragma mark - lifecycle

CPS_6_4::CPS_6_4(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F)
: Seed6(A, B, C, D, E, F)
{
    // basename
    _tuningType = CPS_Class::CPS_6_4;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_6_4::CPS_6_4(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed6(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_6_4;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_6_4::canPaintTuning()
{
    return true;
}

void CPS_6_4::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    // same as(6,2)
    auto const x00 = 0.08f;
    auto const x01 = 0.24f;
    auto const x02 = 0.34f;
    auto const x03 = 0.41f;
    auto const x04 = 0.50f;
    auto const x05 = 1 - x03;
    auto const x06 = 1 - x02;
    auto const x07 = 1 - x01;
    auto const x08 = 1 - x00;

    // inverse of(6,2)
    auto const y08 = 1 - 0.16f;
    auto const y07 = 1 - 0.24f;
    auto const y06 = 1 - 0.34f;
    auto const y05 = 1 - 0.42f;
    auto const y04 = 1 - 0.45f;
    auto const y03 = 1 - 0.64f;
    auto const y02 = 1 - 0.65f;
    auto const y01 = 1 - 0.73f;
    auto const y00 = 1 - 0.93f;

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

    _mCDEF = CPSMicrotone_t::create(CPS::ABCD(_C, _D, _E, _F), hpc(x08, y02));
    _mBDEF = CPSMicrotone_t::create(CPS::ABCD(_B, _D, _E, _F), hpc(x06, y04));
    _mBCEF = CPSMicrotone_t::create(CPS::ABCD(_B, _C, _E, _F), hpc(x03, y03));
    _mBCDF = CPSMicrotone_t::create(CPS::ABCD(_B, _C, _D, _F), hpc(x04, y00));
    _mBCDE = CPSMicrotone_t::create(CPS::ABCD(_B, _C, _D, _E), hpc(x06, y01));
    _mADEF = CPSMicrotone_t::create(CPS::ABCD(_A, _D, _E, _F), hpc(x07, y08));
    _mACEF = CPSMicrotone_t::create(CPS::ABCD(_A, _C, _E, _F), hpc(x04, y06));
    _mACDF = CPSMicrotone_t::create(CPS::ABCD(_A, _C, _D, _F), hpc(x05, y03));
    _mACDE = CPSMicrotone_t::create(CPS::ABCD(_A, _C, _D, _E), hpc(x07, y05));
    _mABEF = CPSMicrotone_t::create(CPS::ABCD(_A, _B, _E, _F), hpc(x01, y08));
    _mABDF = CPSMicrotone_t::create(CPS::ABCD(_A, _B, _D, _F), hpc(x02, y04));
    _mABDE = CPSMicrotone_t::create(CPS::ABCD(_A, _B, _D, _E), hpc(x04, y07));
    _mABCF = CPSMicrotone_t::create(CPS::ABCD(_A, _B, _C, _F), hpc (  x00, y02));
    _mABCE = CPSMicrotone_t::create(CPS::ABCD(_A, _B, _C, _E), hpc(x01, y05));
    _mABCD = CPSMicrotone_t::create(CPS::ABCD(_A, _B, _C, _D), hpc(x02, y01));
    _p0  = CPSMicrotone_t::create_center(hpc(0.5f, 0.5f));

    // outline
    _lineArray.push_back(CPSMicrotone_t::create_line(_mCDEF, _mACDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mACDE, _mADEF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mADEF, _mABDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABDE, _mABEF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABEF, _mABCE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABCE, _mABCF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABCF, _mABCD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABCD, _mBCDF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBCDF, _mBCDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBCDE, _mCDEF));
    // interior
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBCDE, _mBDEF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABDE, _mABDF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABCD, _mACDF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mACDE, _mACEF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABCE, _mBCEF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBDEF, _mABDE));//
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABDF, _mABCD));//
    _lineArray.push_back(CPSMicrotone_t::create_line(_mACDF, _mACDE));//
    _lineArray.push_back(CPSMicrotone_t::create_line(_mACEF, _mABCE));//
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBCEF, _mBCDE));//

    _labelArray.push_back(_mCDEF);
    _labelArray.push_back(_mBDEF);
    _labelArray.push_back(_mBCEF);
    _labelArray.push_back(_mBCDF);
    _labelArray.push_back(_mBCDE);
    _labelArray.push_back(_mADEF);
    _labelArray.push_back(_mACEF);
    _labelArray.push_back(_mACDF);
    _labelArray.push_back(_mACDE);
    _labelArray.push_back(_mABEF);
    _labelArray.push_back(_mABDF);
    _labelArray.push_back(_mABDE);
    _labelArray.push_back(_mABCF);
    _labelArray.push_back(_mABCE);
    _labelArray.push_back(_mABCD);

    _masterPtArray.push_back(_mCDEF);
    _masterPtArray.push_back(_mBDEF);
    _masterPtArray.push_back(_mBCEF);
    _masterPtArray.push_back(_mBCDF);
    _masterPtArray.push_back(_mBCDE);
    _masterPtArray.push_back(_mADEF);
    _masterPtArray.push_back(_mACEF);
    _masterPtArray.push_back(_mACDF);
    _masterPtArray.push_back(_mACDE);
    _masterPtArray.push_back(_mABEF);
    _masterPtArray.push_back(_mABDF);
    _masterPtArray.push_back(_mABDE);
    _masterPtArray.push_back(_mABCF);
    _masterPtArray.push_back(_mABCE);
    _masterPtArray.push_back(_mABCD);
    _masterPtArray.push_back(_p0);
}

CPS_6_4::~CPS_6_4()
{

}

#pragma mark - update

void CPS_6_4::update()
{
    /*
     ------------------------------------------------------
     CPS AT PASCALS TRIANGLE AT ROW: 6
     ------------------------------------------------------
     Master Set: ['A', 'B', 'C', 'D', 'E', 'F']
     (n,k):( 6 , 4 )
     [('A', 'B', 'C', 'D'), ('A', 'B', 'C', 'E'), ('A', 'B', 'C', 'F'), ('A', 'B', 'D', 'E'), ('A', 'B', 'D', 'F'), ('A', 'B', 'E', 'F'), ('A', 'C', 'D', 'E'), ('A', 'C', 'D', 'F'), ('A', 'C', 'E', 'F'), ('A', 'D', 'E', 'F'), ('B', 'C', 'D', 'E'), ('B', 'C', 'D', 'F'), ('B', 'C', 'E', 'F'), ('B', 'D', 'E', 'F'), ('C', 'D', 'E', 'F')]
     count: 15
     ------------------------------------------------------
     */

    _mABCD->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _C, _D} );
    _mABCE->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _C, _E} );
    _mABCF->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _C, _F} );
    _mABDE->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _D, _E} );
    _mABDF->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _D, _F} );
    _mABEF->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _E, _F} );
    _mACDE->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _C, _D, _E} );
    _mACDF->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _C, _D, _F} );
    _mACEF->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _C, _E, _F} );
    _mADEF->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _D, _E, _F} );
    _mBCDE->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _C, _D, _E} );
    _mBCDF->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _C, _D, _F} );
    _mBCEF->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _C, _E, _F} );
    _mBDEF->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _D, _E, _F} );
    _mCDEF->mt = multiplyByCommonTones(vector<Microtone_p> {_C, _D, _E, _F} );

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mABCD->mt);
    ma.addMicrotone(_mABCE->mt);
    ma.addMicrotone(_mABCF->mt);
    ma.addMicrotone(_mABDE->mt);
    ma.addMicrotone(_mABDF->mt);
    ma.addMicrotone(_mABEF->mt);
    ma.addMicrotone(_mACDE->mt);
    ma.addMicrotone(_mACDF->mt);
    ma.addMicrotone(_mACEF->mt);
    ma.addMicrotone(_mADEF->mt);
    ma.addMicrotone(_mBCDE->mt);
    ma.addMicrotone(_mBCDF->mt);
    ma.addMicrotone(_mBCEF->mt);
    ma.addMicrotone(_mBDEF->mt);
    ma.addMicrotone(_mCDEF->mt);
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
        //    (n,k):( 6 , 4 )
        //    (m,j):( 5 , 3 )
        //    count: 6
        //    [[[{'D', 'B', 'C', 'F'}, {'D', 'B', 'F', 'A'}, {'D', 'B', 'F', 'E'}, {'D', 'C', 'A', 'F'}, {'D', 'C', 'F', 'E'}, {'D', 'F', 'A', 'E'}, {'F', 'B', 'C', 'A'}, {'B', 'C', 'F', 'E'}, {'B', 'F', 'A', 'E'}, {'F', 'C', 'A', 'E'}]],
        //     [[{'D', 'B', 'C', 'E'}, {'D', 'B', 'A', 'E'}, {'D', 'B', 'F', 'E'}, {'D', 'C', 'A', 'E'}, {'D', 'C', 'F', 'E'}, {'D', 'F', 'A', 'E'}, {'B', 'C', 'A', 'E'}, {'B', 'C', 'F', 'E'}, {'B', 'F', 'A', 'E'}, {'F', 'C', 'A', 'E'}]],
        //     [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'C', 'F'}, {'D', 'B', 'C', 'E'}, {'D', 'B', 'F', 'A'}, {'D', 'B', 'A', 'E'}, {'D', 'B', 'F', 'E'}, {'F', 'C', 'A', 'D'}, {'D', 'C', 'A', 'E'}, {'D', 'C', 'F', 'E'}, {'D', 'F', 'A', 'E'}]],
        //     [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'C', 'F'}, {'D', 'B', 'C', 'E'}, {'D', 'C', 'F', 'A'}, {'D', 'C', 'A', 'E'}, {'D', 'C', 'F', 'E'}, {'B', 'F', 'C', 'A'}, {'B', 'C', 'A', 'E'}, {'B', 'C', 'F', 'E'}, {'C', 'F', 'A', 'E'}]],
        //     [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'C', 'F'}, {'D', 'B', 'C', 'E'}, {'D', 'B', 'F', 'A'}, {'D', 'B', 'A', 'E'}, {'D', 'B', 'F', 'E'}, {'F', 'B', 'C', 'A'}, {'B', 'C', 'A', 'E'}, {'B', 'C', 'F', 'E'}, {'B', 'F', 'A', 'E'}]],
        //     [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'F', 'A'}, {'D', 'B', 'A', 'E'}, {'D', 'C', 'F', 'A'}, {'D', 'C', 'A', 'E'}, {'D', 'F', 'E', 'A'}, {'B', 'C', 'F', 'A'}, {'B', 'C', 'A', 'E'}, {'B', 'F', 'E', 'A'}, {'C', 'F', 'E', 'A'}]]]
        //    ------------------------------------------------------
        _cps_5_3_0->setCommonTones(_F, getCommonTones());
        _cps_5_3_0->setABCDE(_A, _B, _C, _D, _E); //F

        _cps_5_3_1->setCommonTones(_E, getCommonTones());
        _cps_5_3_1->setABCDE(_A, _B, _C, _D, _F); //E

        _cps_5_3_2->setCommonTones(_D, getCommonTones());
        _cps_5_3_2->setABCDE(_A, _B, _C, _E, _F); //D

        _cps_5_3_3->setCommonTones(_C, getCommonTones());
        _cps_5_3_3->setABCDE(_A, _B, _D, _E, _F); //C

        _cps_5_3_4->setCommonTones(_B, getCommonTones());
        _cps_5_3_4->setABCDE(_A, _C, _D, _E, _F); //B

        _cps_5_3_5->setCommonTones(_A, getCommonTones());
        _cps_5_3_5->setABCDE(_B, _C, _D, _E, _F); //A

        //    ------------------------------------------------------
        //    CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
        //    (n,k):( 6 , 4 )
        //    (m,j):( 5 , 4 )
        //    count: 6
        //    [[[{'D', 'B', 'C', 'A'}, {'D', 'B', 'C', 'E'}, {'D', 'B', 'A', 'E'}, {'D', 'C', 'A', 'E'}, {'B', 'C', 'A', 'E'}]],
        //     [[{'D', 'B', 'C', 'A'}, {'D', 'B', 'C', 'F'}, {'D', 'B', 'F', 'A'}, {'D', 'C', 'A', 'F'}, {'F', 'B', 'C', 'A'}]],
        //     [[{'F', 'B', 'C', 'A'}, {'B', 'C', 'A', 'E'}, {'B', 'C', 'F', 'E'}, {'B', 'F', 'A', 'E'}, {'F', 'C', 'A', 'E'}]],
        //     [[{'D', 'B', 'F', 'A'}, {'D', 'B', 'A', 'E'}, {'D', 'B', 'F', 'E'}, {'D', 'F', 'A', 'E'}, {'B', 'F', 'A', 'E'}]],
        //     [[{'D', 'C', 'A', 'F'}, {'D', 'C', 'A', 'E'}, {'D', 'C', 'F', 'E'}, {'D', 'F', 'A', 'E'}, {'F', 'C', 'A', 'E'}]],
        //     [[{'D', 'B', 'C', 'F'}, {'D', 'B', 'C', 'E'}, {'D', 'B', 'F', 'E'}, {'D', 'C', 'F', 'E'}, {'B', 'C', 'F', 'E'}]]]
        //    ------------------------------------------------------
        _cps_5_4_0->setCommonTones(nullptr, getCommonTones());
        _cps_5_4_0->setABCDE(_A, _B, _C, _D, _E); // F

        _cps_5_4_1->setCommonTones(nullptr, getCommonTones());
        _cps_5_4_1->setABCDE(_A, _B, _C, _D, _F); // E

        _cps_5_4_2->setCommonTones(nullptr, getCommonTones());
        _cps_5_4_2->setABCDE(_A, _B, _C, _E, _F); // D

        _cps_5_4_3->setCommonTones(nullptr, getCommonTones());
        _cps_5_4_3->setABCDE(_A, _B, _D, _E, _F); // C

        _cps_5_4_4->setCommonTones(nullptr, getCommonTones());
        _cps_5_4_4->setABCDE(_A, _C, _D, _E, _F); // B

        _cps_5_4_5->setCommonTones(nullptr, getCommonTones());
        _cps_5_4_5->setABCDE(_B, _C, _D, _E, _F); // A
    }
}

#pragma mark - subsets

void CPS_6_4::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // playing it safe

    _cps_5_3_0 = make_shared<CPS_5_3> (_A, _B, _C, _D, _E);
    _cps_5_3_1 = make_shared<CPS_5_3> (_A, _B, _C, _D, _E);
    _cps_5_3_2 = make_shared<CPS_5_3> (_A, _B, _C, _D, _E);
    _cps_5_3_3 = make_shared<CPS_5_3> (_A, _B, _C, _D, _E);
    _cps_5_3_4 = make_shared<CPS_5_3> (_A, _B, _C, _D, _E);
    _cps_5_3_5 = make_shared<CPS_5_3> (_A, _B, _C, _D, _E);

    _cps_5_4_0 = make_shared<CPS_5_4> (_A, _B, _C, _D, _E);
    _cps_5_4_1 = make_shared<CPS_5_4> (_A, _B, _C, _D, _E);
    _cps_5_4_2 = make_shared<CPS_5_4> (_A, _B, _C, _D, _E);
    _cps_5_4_3 = make_shared<CPS_5_4> (_A, _B, _C, _D, _E);
    _cps_5_4_4 = make_shared<CPS_5_4> (_A, _B, _C, _D, _E);
    _cps_5_4_5 = make_shared<CPS_5_4> (_A, _B, _C, _D, _E);

    // subsets 0
    _subsets0.push_back(_cps_5_3_0);
    _subsets0.push_back(_cps_5_3_1);
    _subsets0.push_back(_cps_5_3_2);
    _subsets0.push_back(_cps_5_3_3);
    _subsets0.push_back(_cps_5_3_4);
    _subsets0.push_back(_cps_5_3_5);

    // subsets 1
    _subsets1.push_back(_cps_5_4_0);
    _subsets1.push_back(_cps_5_4_1);
    _subsets1.push_back(_cps_5_4_2);
    _subsets1.push_back(_cps_5_4_3);
    _subsets1.push_back(_cps_5_4_4);
    _subsets1.push_back(_cps_5_4_5);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_6_4::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void CPS_6_4::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void CPS_6_4::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void CPS_6_4::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void CPS_6_4::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void CPS_6_4::selectS0_5()
{
    _clearSelection();
    _subsets0[5]->setIsSelected(true);
}

void CPS_6_4::selectS0_6()
{
    jassertfalse;
}

void CPS_6_4::selectS0_7()
{
    jassertfalse;
}

void CPS_6_4::selectS1_0()
{
    _clearSelection();
    _subsets1[0]->setIsSelected(true);
}

void CPS_6_4::selectS1_1()
{
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void CPS_6_4::selectS1_2()
{
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void CPS_6_4::selectS1_3()
{
    _clearSelection();
    _subsets1[3]->setIsSelected(true);
}

void CPS_6_4::selectS1_4()
{
    _clearSelection();
    _subsets1[4]->setIsSelected(true);
}

void CPS_6_4::selectS1_5()
{
    _clearSelection();
    _subsets1[5]->setIsSelected(true);
}

void CPS_6_4::selectS1_6()
{
    jassertfalse;
}

void CPS_6_4::selectS1_7()
{
    jassertfalse;
}

bool CPS_6_4::isEulerGenusTuningType()
{
    return false;
}

