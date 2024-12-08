/*
  ==============================================================================

    EulerGenus_4.cpp
    Created: 10 Aug 2021 10:35:26pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "EulerGenus_4.h"

#pragma mark - lifecycle

EulerGenus_4::EulerGenus_4(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D)
: Seed4(A, B, C, D)
, _cps_4_1(make_shared<CPS_4_1>(_A, _B, _C, _D))
, _cps_4_2(make_shared<CPS_4_2>(_A, _B, _C, _D))
, _cps_4_3(make_shared<CPS_4_3>(_A, _B, _C, _D))
, _cps_4_4(make_shared<CPS_4_4>(_A, _B, _C, _D))
{
    // properties
    setCanNPOOverride(true); // redundant, for clarity
    setCanUniquify(false);
    setCanSort(true);
    setSort(true);
    _tuningType = CPS_Class::EulerGenus_4;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);

    // subsets
    _subsets0.push_back(_cps_4_1);
    _subsets0.push_back(_cps_4_2);
    _subsets0.push_back(_cps_4_3);
    _subsets0.push_back(_cps_4_4);

    // update
    update();

    // select
    selectS0_2();
}

EulerGenus_4::EulerGenus_4(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed4(master_set, common_tones)
, _cps_4_1(make_shared<CPS_4_1>(_A, _B, _C, _D))
, _cps_4_2(make_shared<CPS_4_2>(_A, _B, _C, _D))
, _cps_4_3(make_shared<CPS_4_3>(_A, _B, _C, _D))
, _cps_4_4(make_shared<CPS_4_4>(_A, _B, _C, _D))
{
    // properties
    setCanNPOOverride(true); // redundant, for clarity
    setCanUniquify(false);
    setCanSort(true);
    setSort(true);
    _tuningType = CPS_Class::EulerGenus_4;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);

    // subsets
    _subsets0.push_back(_cps_4_1);
    _subsets0.push_back(_cps_4_2);
    _subsets0.push_back(_cps_4_3);
    _subsets0.push_back(_cps_4_4);

    // update
    update();

    // select
    selectS0_2();
}

EulerGenus_4::~EulerGenus_4()
{

}

//

const shared_ptr<CPS_4_1> EulerGenus_4::getCps_4_1()
{
    return _cps_4_1;
}

const shared_ptr<CPS_4_2> EulerGenus_4::getCps_4_2()
{
    return _cps_4_2;
}

const shared_ptr<CPS_4_3> EulerGenus_4::getCps_4_3()
{
    return _cps_4_3;
}

const shared_ptr<CPS_4_4> EulerGenus_4::getCps_4_4()
{
    return _cps_4_4;
}

#pragma mark - update row

void EulerGenus_4::update()
{
    _cps_4_1->setABCD(_A, _B, _C, _D);
    _cps_4_2->setABCD(_A, _B, _C, _D);
    _cps_4_3->setABCD(_A, _B, _C, _D);
    _cps_4_4->setABCD(_A, _B, _C, _D);
}

void EulerGenus_4::_allocateSubsets()
{
    // NOP for EulerGenus
}

#pragma mark - description

const string EulerGenus_4::getShortDescriptionText()
{
    string retVal = "EulerGenus_4:(";
    retVal += getA()->getShortDescriptionText();
    retVal += ",";
    retVal += getB()->getShortDescriptionText();
    retVal += ",";
    retVal += getC()->getShortDescriptionText();
    retVal += ",";
    retVal += getD()->getShortDescriptionText();
    retVal += ")";
    // TODO: print cps

    return retVal;
}

#pragma mark - subset selection

void EulerGenus_4::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected (true);
}

void EulerGenus_4::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected (true);
}

void EulerGenus_4::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected (true);
}

void EulerGenus_4::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected (true);
}

void EulerGenus_4::selectS0_4()
{
    jassertfalse;
}

void EulerGenus_4::selectS0_5()
{
    jassertfalse;
}

void EulerGenus_4::selectS0_6()
{
    jassertfalse;
}

void EulerGenus_4::selectS0_7()
{
    jassertfalse;
}

void EulerGenus_4::selectS1_0()
{
    jassertfalse;
}

void EulerGenus_4::selectS1_1()
{
    jassertfalse;
}

void EulerGenus_4::selectS1_2()
{
    jassertfalse;
}

void EulerGenus_4::selectS1_3()
{
    jassertfalse;
}

void EulerGenus_4::selectS1_4()
{
    jassertfalse;
}

void EulerGenus_4::selectS1_5()
{
    jassertfalse;
}

void EulerGenus_4::selectS1_6()
{
    jassertfalse;
}

void EulerGenus_4::selectS1_7()
{
    jassertfalse;
}

bool EulerGenus_4::isEulerGenusTuningType()
{
    return true;
}
