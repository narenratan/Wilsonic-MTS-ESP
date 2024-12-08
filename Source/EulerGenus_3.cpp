/*
  ==============================================================================

    EulerGenus_3.cpp
    Created: 10 Aug 2021 10:33:53pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "EulerGenus_3.h"

#pragma mark - lifecycle

EulerGenus_3::EulerGenus_3(Microtone_p A, Microtone_p B, Microtone_p C)
: Seed3(A, B, C)
, _cps_3_1(make_shared<CPS_3_1>(_A, _B, _C))
, _cps_3_2(make_shared<CPS_3_2>(_A, _B, _C))
, _cps_3_3(make_shared<CPS_3_3>(_A, _B, _C))
{
    // properties
    setCanNPOOverride(true); // redundant, for clarity
    setCanUniquify(false);
    setCanSort(true);
    setSort(true);
    _tuningType = CPS_Class::EulerGenus_3;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);

    // subsets
    _subsets0.push_back(_cps_3_1);
    _subsets0.push_back(_cps_3_2);
    _subsets0.push_back(_cps_3_3);

    // update
    update();

    // select
    selectS0_1();
}

EulerGenus_3::EulerGenus_3(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed3 (master_set, common_tones)
, _cps_3_1(make_shared<CPS_3_1>(_A, _B, _C))
, _cps_3_2(make_shared<CPS_3_2>(_A, _B, _C))
, _cps_3_3(make_shared<CPS_3_3>(_A, _B, _C))
{
    // properties
    setCanNPOOverride(true); // redundant, for clarity
    setCanUniquify(false);
    setCanSort(true);
    setSort(true);
    _tuningType = CPS_Class::EulerGenus_3;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);

    // subsets
    _subsets0.push_back (_cps_3_1);
    _subsets0.push_back (_cps_3_2);
    _subsets0.push_back (_cps_3_3);

    // update
    update();

    // select
    selectS0_1();
}

EulerGenus_3::~EulerGenus_3()
{

}

//

const shared_ptr<CPS_3_1> EulerGenus_3::getCps_3_1()
{
    return _cps_3_1;
}

const shared_ptr<CPS_3_2> EulerGenus_3::getCps_3_2()
{
    return _cps_3_2;
}

const shared_ptr<CPS_3_3> EulerGenus_3::getCps_3_3()
{
    return _cps_3_3;
}

#pragma mark - update row

void EulerGenus_3::update()
{
    _cps_3_1->setABC (_A, _B, _C);
    _cps_3_2->setABC (_A, _B, _C);
    _cps_3_3->setABC (_A, _B, _C);
}

void EulerGenus_3::_allocateSubsets()
{
    // NOP for EulerGenus
}

#pragma mark - description

const string EulerGenus_3::getShortDescriptionText()
{
    string retVal = "EulerGenus_3:(";
    retVal += getA()->getShortDescriptionText();
    retVal += ",";
    retVal += getB()->getShortDescriptionText();
    retVal += ",";
    retVal += getC()->getShortDescriptionText();
    retVal += ")";

    return retVal;
}

#pragma mark - subset selection

void EulerGenus_3::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected (true);
}

void EulerGenus_3::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected (true);
}

void EulerGenus_3::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected (true);
;
}

void EulerGenus_3::selectS0_3()
{
    jassertfalse;
}

void EulerGenus_3::selectS0_4()
{
    jassertfalse;
}

void EulerGenus_3::selectS0_5()
{
    jassertfalse;
}

void EulerGenus_3::selectS0_6()
{
    jassertfalse;
}

void EulerGenus_3::selectS0_7()
{
    jassertfalse;
}

void EulerGenus_3::selectS1_0()
{
    jassertfalse;
}

void EulerGenus_3::selectS1_1()
{
    jassertfalse;
}

void EulerGenus_3::selectS1_2()
{
    jassertfalse;
}

void EulerGenus_3::selectS1_3()
{
    jassertfalse;
}

void EulerGenus_3::selectS1_4()
{
    jassertfalse;
}

void EulerGenus_3::selectS1_5()
{
    jassertfalse;
}

void EulerGenus_3::selectS1_6()
{
    jassertfalse;
}

void EulerGenus_3::selectS1_7()
{
    jassertfalse;
}

bool EulerGenus_3::isEulerGenusTuningType()
{
    return true;
}
