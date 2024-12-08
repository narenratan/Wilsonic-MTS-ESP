/*
 ==============================================================================

 CPS_6_3.cpp
 Created: 13 Aug 2021 9:05:09pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "CPS_6_3.h"
#include "EulerGenusModel.h"
#include "WilsonicProcessor.h"
#include "CPS.h"

#pragma mark - lifecycle

CPS_6_3::CPS_6_3(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F)
: Seed6(A, B, C, D, E, F)
{
    // basename
    _tuningType = CPS_Class::CPS_6_3;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

CPS_6_3::CPS_6_3(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed6(master_set, common_tones)
{
    // basename
    _tuningType = CPS_Class::CPS_6_3;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    _commonConstructorHelper();

    // update
    update();
}

bool CPS_6_3::canPaintTuning()
{
    return true;
}

void CPS_6_3::_commonConstructorHelper()
{
    // called at construction only, will be updated in update

    auto const xfudge  = 0.01197916f;
    auto const x0      = 0.51197916f - xfudge;
    auto const x1      = 0.62656248f - xfudge;
    auto const x2      = 0.69687498f - xfudge;
    auto const x3      = 0.39895833f - xfudge;
    auto const x4      = 0.32499999f - xfudge;
    auto const yAdjust = 0.05f;
    auto const yfudge  = 0.023404925f - yAdjust;
    auto const y0      = 0.83248699f - yfudge;
    auto const y1      = 0.76357424f - yfudge;
    auto const y2      = 0.57949221f - yfudge;
    auto const y3      = 0.37369794f - yfudge;
    auto const y4      = 0.17545575f - yfudge;
    auto const y5      = 0.11220706f - yfudge;
    auto const x5      = 0.60833335f - xfudge;
    auto const x6      = 0.45156249f - xfudge;
    auto const x7      = 0.41666666f - xfudge;
    auto const x8      = 0.56822914f - xfudge;
    auto const y6      = 0.65218103f - yfudge;
    auto const y7      = 0.41334635f - yfudge;
    auto const y8      = 0.33404946f - yfudge;
    auto const y9      = 0.62291670f - yfudge;
    auto const y10     = 0.53323567f - yfudge;
    auto const y11     = 0.29156899f - yfudge;

    // scaling func for coords...on [(-0.5,-0.5)x(0.5,0.5)]
    auto hpc = [] (auto x, auto y)
    {
        auto xx = 0.5f - x;
        xx *= 960.f / 530;
        auto yy = 0.5f - y;
        auto const s = 1.f;
        xx *= s;
        yy *= s;
        return Point<float> (xx, yy);
    };

    _mABC = CPSMicrotone_t::create(CPS::ABC(_A, _B, _C), hpc(x1, y1) );
    _mABD = CPSMicrotone_t::create(CPS::ABC(_A, _B, _D), hpc(x5, y10));
    _mABE = CPSMicrotone_t::create(CPS::ABC(_A, _B, _E), hpc(x7, y10));
    _mABF = CPSMicrotone_t::create(CPS::ABC(_A, _B, _F), hpc(x3, y1) );
    _mACD = CPSMicrotone_t::create(CPS::ABC(_A, _C, _D), hpc(x2, y3) );
    _mACE = CPSMicrotone_t::create(CPS::ABC(_A, _C, _E), hpc(x8, y8) );
    _mACF = CPSMicrotone_t::create(CPS::ABC(_A, _C, _F), hpc(x0, y6) );
    _mADE = CPSMicrotone_t::create(CPS::ABC(_A, _D, _E), hpc(x0, y5) );
    _mADF = CPSMicrotone_t::create(CPS::ABC(_A, _D, _F), hpc(x6, y8) );
    _mAEF = CPSMicrotone_t::create(CPS::ABC(_A, _E, _F), hpc(x4, y3) );
    _mBCD = CPSMicrotone_t::create(CPS::ABC(_B, _C, _D), hpc(x2, y2) );
    _mBCE = CPSMicrotone_t::create(CPS::ABC(_B, _C, _E), hpc(x8, y9) );
    _mBCF = CPSMicrotone_t::create(CPS::ABC(_B, _C, _F), hpc(x0, y0) );
    _mBDE = CPSMicrotone_t::create(CPS::ABC(_B, _D, _E), hpc(x0, y11));
    _mBDF = CPSMicrotone_t::create(CPS::ABC(_B, _D, _F), hpc(x6, y9) );
    _mBEF = CPSMicrotone_t::create(CPS::ABC(_B, _E, _F), hpc(x4, y2) );
    _mCDE = CPSMicrotone_t::create(CPS::ABC(_C, _D, _E), hpc(x1, y4) );
    _mCDF = CPSMicrotone_t::create(CPS::ABC(_C, _D, _F), hpc(x5, y7) );
    _mCEF = CPSMicrotone_t::create(CPS::ABC(_C, _E, _F), hpc(x7, y7) );
    _mDEF = CPSMicrotone_t::create(CPS::ABC(_D, _E, _F), hpc(x3, y4) );
    _p0 = CPSMicrotone_t::create_center(Point<float> (0.5, 0.5));

    // Trick to get overlap in inner ring
    auto tmpPtACF = hpc(x0, y6);
    auto tmpPtCEF = hpc(x7, y7);
    auto tmpPt = tmpPtACF + 0.5f * (tmpPtCEF - tmpPtACF);
    _half_ACF_CEF = CPSMicrotone_t::create(CPS::ABC(_C, _E, _F), tmpPt);

    // line segment array
    // path of inner ring
    _lineArray.push_back(CPSMicrotone_t::create_line(_mACF, _mCEF));// half-covered by _half below
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBDF, _mADF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABE, _mBDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mCEF, _mACE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mADF, _mCDF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBDE, _mABD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mACE, _mBCE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mCDF, _mACF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABD, _mBDF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBCE, _mABE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mACF, _half_ACF_CEF));
    // clockwise outer ring
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBCF, _mABC));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABC, _mBCD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBCD, _mACD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mACD, _mCDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mCDE, _mADE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mADE, _mDEF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mDEF, _mAEF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mAEF, _mBEF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBEF, _mABF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABF, _mBCF));
    // radial lines
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBCF, _mACF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABC, _mBCE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABD, _mBCD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mCDF, _mACD));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mACE, _mCDE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBDE, _mADE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mADF, _mDEF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mCEF, _mAEF));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mBEF, _mABE));
    _lineArray.push_back(CPSMicrotone_t::create_line(_mABF, _mBDF));

    _labelArray.push_back(_mABC);
    _labelArray.push_back(_mABD);
    _labelArray.push_back(_mABE);
    _labelArray.push_back(_mABF);
    _labelArray.push_back(_mACD);
    _labelArray.push_back(_mACE);
    _labelArray.push_back(_mACF);
    _labelArray.push_back(_mADE);
    _labelArray.push_back(_mADF);
    _labelArray.push_back(_mAEF);
    _labelArray.push_back(_mBCD);
    _labelArray.push_back(_mBCE);
    _labelArray.push_back(_mBCF);
    _labelArray.push_back(_mBDE);
    _labelArray.push_back(_mBDF);
    _labelArray.push_back(_mBEF);
    _labelArray.push_back(_mCDE);
    _labelArray.push_back(_mCDF);
    _labelArray.push_back(_mCEF);
    _labelArray.push_back(_mDEF);

    _masterPtArray.push_back(_mABC);
    _masterPtArray.push_back(_mABD);
    _masterPtArray.push_back(_mABE);
    _masterPtArray.push_back(_mABF);
    _masterPtArray.push_back(_mACD);
    _masterPtArray.push_back(_mACE);
    _masterPtArray.push_back(_mACF);
    _masterPtArray.push_back(_mADE);
    _masterPtArray.push_back(_mADF);
    _masterPtArray.push_back(_mAEF);
    _masterPtArray.push_back(_mBCD);
    _masterPtArray.push_back(_mBCE);
    _masterPtArray.push_back(_mBCF);
    _masterPtArray.push_back(_mBDE);
    _masterPtArray.push_back(_mBDF);
    _masterPtArray.push_back(_mBEF);
    _masterPtArray.push_back(_mCDE);
    _masterPtArray.push_back(_mCDF);
    _masterPtArray.push_back(_mCEF);
    _masterPtArray.push_back(_p0  );
}

CPS_6_3::~CPS_6_3()
{

}

#pragma mark - update

void CPS_6_3::update()
{
    /*
     ------------------------------------------------------
     CPS AT PASCALS TRIANGLE AT ROW: 6
     ------------------------------------------------------
     Master Set: ['A', 'B', 'C', 'D', 'E', 'F']
     (n,k):( 6 , 3 )
     [('A', 'B', 'C'), ('A', 'B', 'D'), ('A', 'B', 'E'), ('A', 'B', 'F'), ('A', 'C', 'D'), ('A', 'C', 'E'), ('A', 'C', 'F'), ('A', 'D', 'E'), ('A', 'D', 'F'), ('A', 'E', 'F'), ('B', 'C', 'D'), ('B', 'C', 'E'), ('B', 'C', 'F'), ('B', 'D', 'E'), ('B', 'D', 'F'), ('B', 'E', 'F'), ('C', 'D', 'E'), ('C', 'D', 'F'), ('C', 'E', 'F'), ('D', 'E', 'F')]
     count: 20
     ------------------------------------------------------
     */
    _mABC->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _C} );
    _mABD->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _D} );
    _mABE->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _E} );
    _mABF->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _B, _F} );
    _mACD->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _C, _D} );
    _mACE->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _C, _E} );
    _mACF->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _C, _F} );
    _mADE->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _D, _E} );
    _mADF->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _D, _F} );
    _mAEF->mt = multiplyByCommonTones(vector<Microtone_p> {_A, _E, _F} );
    _mBCD->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _C, _D} );
    _mBCE->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _C, _E} );
    _mBCF->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _C, _F} );
    _mBDE->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _D, _E} );
    _mBDF->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _D, _F} );
    _mBEF->mt = multiplyByCommonTones(vector<Microtone_p> {_B, _E, _F} );
    _mCDE->mt = multiplyByCommonTones(vector<Microtone_p> {_C, _D, _E} );
    _mCDF->mt = multiplyByCommonTones(vector<Microtone_p> {_C, _D, _F} );
    _mCEF->mt = multiplyByCommonTones(vector<Microtone_p> {_C, _E, _F} );
    _mDEF->mt = multiplyByCommonTones(vector<Microtone_p> {_D, _E, _F} );

    auto ma = MicrotoneArray();
    ma.addMicrotone(_mABC->mt);
    ma.addMicrotone(_mABD->mt);
    ma.addMicrotone(_mABE->mt);
    ma.addMicrotone(_mABF->mt);
    ma.addMicrotone(_mACD->mt);
    ma.addMicrotone(_mACE->mt);
    ma.addMicrotone(_mACF->mt);
    ma.addMicrotone(_mADE->mt);
    ma.addMicrotone(_mADF->mt);
    ma.addMicrotone(_mAEF->mt);
    ma.addMicrotone(_mBCD->mt);
    ma.addMicrotone(_mBCE->mt);
    ma.addMicrotone(_mBCF->mt);
    ma.addMicrotone(_mBDE->mt);
    ma.addMicrotone(_mBDF->mt);
    ma.addMicrotone(_mBEF->mt);
    ma.addMicrotone(_mCDE->mt);
    ma.addMicrotone(_mCDF->mt);
    ma.addMicrotone(_mCEF->mt);
    ma.addMicrotone(_mDEF->mt);
    setMicrotoneArray(ma);  // calls TuningImp::_update()

    // SUBSETS

    if(getShouldComputeSubsets() == true) // lazy
    {
        if(_getDidAllocateSubsets() == false) // lazy
        {
            _allocateSubsets();
        }


        //    ------------------------ ------------------------------
        //    CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
        //    (n,k):( 6 , 3 )
        //    (m,j):( 5 , 2 )
        //    count: 6
        //    ------------------------------------------------------
        //    [[[{'D', 'B', 'F'}, {'D', 'C', 'F'}, {'D', 'F', 'A'}, {'D', 'F', 'E'}, {'B', 'C', 'F'}, {'B', 'F', 'A'}, {'B', 'F', 'E'}, {'F', 'C', 'A'}, {'C', 'F', 'E'}, {'F', 'A', 'E'}]], //F
        _cps_5_2_0->setCommonTones(_F, getCommonTones());
        _cps_5_2_0->setABCDE(_A, _B, _C, _D, _E); // F

        //     [[{'D', 'B', 'E'}, {'D', 'C', 'E'}, {'D', 'A', 'E'}, {'D', 'F', 'E'}, {'B', 'C', 'E'}, {'B', 'A', 'E'}, {'B', 'F', 'E'}, {'C', 'A', 'E'}, {'C', 'F', 'E'}, {'F', 'A', 'E'}]], //E
        _cps_5_2_1->setCommonTones(_E, getCommonTones());
        _cps_5_2_1->setABCDE(_A, _B, _C, _D, _F); // E

        //     [[{'D', 'B', 'C'}, {'D', 'B', 'A'}, {'D', 'B', 'F'}, {'D', 'B', 'E'}, {'D', 'C', 'A'}, {'D', 'C', 'F'}, {'D', 'C', 'E'}, {'D', 'F', 'A'}, {'D', 'A', 'E'}, {'D', 'F', 'E'}]], //D
        _cps_5_2_2->setCommonTones(_D, getCommonTones());
        _cps_5_2_2->setABCDE(_A, _B, _C, _E, _F); // D

        //     [[{'D', 'B', 'C'}, {'D', 'C', 'A'}, {'D', 'C', 'F'}, {'D', 'C', 'E'}, {'B', 'C', 'A'}, {'B', 'C', 'F'}, {'B', 'C', 'E'}, {'C', 'F', 'A'}, {'C', 'A', 'E'}, {'C', 'F', 'E'}]], //C
        _cps_5_2_3->setCommonTones(_C, getCommonTones());
        _cps_5_2_3->setABCDE(_A, _B, _D, _E, _F); // C

        //     [[{'D', 'B', 'C'}, {'D', 'B', 'A'}, {'D', 'B', 'F'}, {'D', 'B', 'E'}, {'B', 'C', 'A'}, {'B', 'C', 'F'}, {'B', 'C', 'E'}, {'B', 'F', 'A'}, {'B', 'A', 'E'}, {'B', 'F', 'E'}]], //B
        _cps_5_2_4->setCommonTones(_B, getCommonTones());
        _cps_5_2_4->setABCDE(_A, _C, _D, _E, _F); // B

        //     [[{'D', 'B', 'A'}, {'D', 'C', 'A'}, {'D', 'F', 'A'}, {'D', 'A', 'E'}, {'B', 'C', 'A'}, {'B', 'F', 'A'}, {'B', 'A', 'E'}, {'C', 'F', 'A'}, {'C', 'A', 'E'}, {'F', 'E', 'A'}]]] //A
        _cps_5_2_5->setCommonTones(_A, getCommonTones());
        _cps_5_2_5->setABCDE(_B, _C, _D, _E, _F); // A

        //    ------------------------------------------------------
        //    CPS SUBSETS OF CPS AT PASCALS TRIANGLE AT ROW: 6
        //    (n,k):( 6 , 3 )
        //    (m,j):( 5 , 3 )
        //    count: 6
        //    [[[{'D', 'B', 'C'}, {'D', 'B', 'A'}, {'D', 'B', 'E'}, {'D', 'C', 'A'}, {'D', 'C', 'E'}, {'D', 'A', 'E'}, {'B', 'C', 'A'}, {'B', 'C', 'E'}, {'B', 'A', 'E'}, {'C', 'A', 'E'}]], //F
        _cps_5_3_0->setCommonTones(nullptr, getCommonTones());
        _cps_5_3_0->setABCDE(_A, _B, _C, _D, _E); // F

        //     [[{'D', 'B', 'C'}, {'D', 'B', 'A'}, {'D', 'B', 'F'}, {'D', 'C', 'A'}, {'D', 'C', 'F'}, {'D', 'F', 'A'}, {'B', 'C', 'A'}, {'B', 'C', 'F'}, {'B', 'F', 'A'}, {'F', 'C', 'A'}]], //E
        _cps_5_3_1->setCommonTones(nullptr, getCommonTones());
        _cps_5_3_1->setABCDE(_A, _B, _C, _D, _F); // E

        //     [[{'B', 'C', 'A'}, {'B', 'C', 'F'}, {'B', 'C', 'E'}, {'B', 'F', 'A'}, {'B', 'A', 'E'}, {'B', 'F', 'E'}, {'F', 'C', 'A'}, {'C', 'A', 'E'}, {'C', 'F', 'E'}, {'F', 'A', 'E'}]], //D
        _cps_5_3_2->setCommonTones(nullptr, getCommonTones());
        _cps_5_3_2->setABCDE(_A, _B, _C, _E, _F); // D

        //     [[{'D', 'B', 'A'}, {'D', 'B', 'F'}, {'D', 'B', 'E'}, {'D', 'F', 'A'}, {'D', 'A', 'E'}, {'D', 'F', 'E'}, {'B', 'F', 'A'}, {'B', 'A', 'E'}, {'B', 'F', 'E'}, {'F', 'A', 'E'}]], //C
        _cps_5_3_3->setCommonTones(nullptr, getCommonTones());
        _cps_5_3_3->setABCDE(_A, _B, _D, _E, _F); // C

        //     [[{'D', 'C', 'A'}, {'D', 'C', 'F'}, {'D', 'C', 'E'}, {'D', 'F', 'A'}, {'D', 'A', 'E'}, {'D', 'F', 'E'}, {'F', 'C', 'A'}, {'C', 'A', 'E'}, {'C', 'F', 'E'}, {'F', 'A', 'E'}]], //B
        _cps_5_3_4->setCommonTones(nullptr, getCommonTones());
        _cps_5_3_4->setABCDE(_A, _C, _D, _E, _F); // B

        //     [[{'D', 'B', 'C'}, {'D', 'B', 'F'}, {'D', 'B', 'E'}, {'D', 'C', 'F'}, {'D', 'C', 'E'}, {'D', 'F', 'E'}, {'B', 'C', 'F'}, {'B', 'C', 'E'}, {'B', 'F', 'E'}, {'C', 'F', 'E'}]]] //A
        _cps_5_3_5->setCommonTones(nullptr, getCommonTones());
        _cps_5_3_5->setABCDE(_B, _C, _D, _E, _F); // A
    }
}

#pragma mark - subsets

void CPS_6_3::_allocateSubsets()
{
    jassert(_getDidAllocateSubsets() == false); // lazy

    _cps_5_2_0 = make_shared<CPS_5_2> (_A, _B, _C, _D, _E);
    _cps_5_2_1 = make_shared<CPS_5_2> (_A, _B, _C, _D, _E);
    _cps_5_2_2 = make_shared<CPS_5_2> (_A, _B, _C, _D, _E);
    _cps_5_2_3 = make_shared<CPS_5_2> (_A, _B, _C, _D, _E);
    _cps_5_2_4 = make_shared<CPS_5_2> (_A, _B, _C, _D, _E);
    _cps_5_2_5 = make_shared<CPS_5_2> (_A, _B, _C, _D, _E);

    _cps_5_3_0 = make_shared<CPS_5_3> (_A, _B, _C, _D, _E);
    _cps_5_3_1 = make_shared<CPS_5_3> (_A, _B, _C, _D, _E);
    _cps_5_3_2 = make_shared<CPS_5_3> (_A, _B, _C, _D, _E);
    _cps_5_3_3 = make_shared<CPS_5_3> (_A, _B, _C, _D, _E);
    _cps_5_3_4 = make_shared<CPS_5_3> (_A, _B, _C, _D, _E);
    _cps_5_3_5 = make_shared<CPS_5_3> (_A, _B, _C, _D, _E);

    // subsets 0
    _subsets0.push_back(_cps_5_2_0);
    _subsets0.push_back(_cps_5_2_1);
    _subsets0.push_back(_cps_5_2_2);
    _subsets0.push_back(_cps_5_2_3);
    _subsets0.push_back(_cps_5_2_4);
    _subsets0.push_back(_cps_5_2_5);

    // subsets 1
    _subsets1.push_back(_cps_5_3_0);
    _subsets1.push_back(_cps_5_3_1);
    _subsets1.push_back(_cps_5_3_2);
    _subsets1.push_back(_cps_5_3_3);
    _subsets1.push_back(_cps_5_3_4);
    _subsets1.push_back(_cps_5_3_5);

    _setDidAllocateSubsets(true);
}

#pragma mark - subset selection

void CPS_6_3::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void CPS_6_3::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void CPS_6_3::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void CPS_6_3::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void CPS_6_3::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void CPS_6_3::selectS0_5()
{
    _clearSelection();
    _subsets0[5]->setIsSelected(true);
}

void CPS_6_3::selectS0_6()
{
    jassertfalse;
}

void CPS_6_3::selectS0_7()
{
    jassertfalse;
}

void CPS_6_3::selectS1_0()
{
    _clearSelection();
    _subsets1[0]->setIsSelected(true);
}

void CPS_6_3::selectS1_1()
{
    _clearSelection();
    _subsets1[1]->setIsSelected(true);
}

void CPS_6_3::selectS1_2()
{
    _clearSelection();
    _subsets1[2]->setIsSelected(true);
}

void CPS_6_3::selectS1_3()
{
    _clearSelection();
    _subsets1[3]->setIsSelected(true);
}

void CPS_6_3::selectS1_4()
{
    _clearSelection();
    _subsets1[4]->setIsSelected(true);
}

void CPS_6_3::selectS1_5()
{
    _clearSelection();
    _subsets1[5]->setIsSelected(true);
}

void CPS_6_3::selectS1_6()
{
    jassertfalse;
}

void CPS_6_3::selectS1_7()
{
    jassertfalse;
}

bool CPS_6_3::isEulerGenusTuningType()
{
    return false;
}

