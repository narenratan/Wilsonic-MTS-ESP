/*
  ==============================================================================

    EulerGenus_2.cpp
    Created: 31 Jul 2021 12:59:50pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "EulerGenus_2.h"

#pragma mark - lifecycle

EulerGenus_2::EulerGenus_2(Microtone_p A, Microtone_p B)
: Seed2 (A, B)
, _cps_2_1 (make_shared<CPS_2_1>(_A, _B))
, _cps_2_2 (make_shared<CPS_2_2>(_A, _B))
{
    // properties
    setCanNPOOverride(true); // redundant, for clarity
    setCanUniquify(false);
    setCanSort(true);
    setSort(true);
    _tuningType = CPS_Class::EulerGenus_2;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);

    // subsets
    _subsets0.push_back(_cps_2_1);
    _subsets0.push_back(_cps_2_2);

    // update
    update();

    // select
    selectS0_1();
}

EulerGenus_2::EulerGenus_2 (vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed2(master_set, common_tones)
, _cps_2_1(make_shared<CPS_2_1>(_A, _B))
, _cps_2_2(make_shared<CPS_2_2>(_A, _B))
{
    // properties
    setCanNPOOverride(true); // redundant, for clarity
    setCanUniquify(false);
    setCanSort(true);
    setSort(true);
    _tuningType = CPS_Class::EulerGenus_2;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);

    // subsets
    _subsets0.push_back(_cps_2_1);
    _subsets0.push_back(_cps_2_2);

    // update
    update();

    // select
    selectS0_1();
}

EulerGenus_2::~EulerGenus_2()
{

}

#pragma mark - subsets

const shared_ptr<CPS_2_1> EulerGenus_2::getCps_2_1()
{
    return _cps_2_1;
}

const shared_ptr<CPS_2_2> EulerGenus_2::getCps_2_2()
{
    return _cps_2_2;
}

#pragma mark - update

void EulerGenus_2::update()
{
    _cps_2_1->setAB (_A, _B);
    _cps_2_2->setAB (_A, _B);    
}

void EulerGenus_2::_allocateSubsets()
{
    // NOP for EulerGenus
}

#pragma mark - description

const string EulerGenus_2::getShortDescriptionText()
{
    string retVal = "EulerGenus_2:(";
    retVal += getA()->getShortDescriptionText();
    retVal += ",";
    retVal += getB()->getShortDescriptionText();
    retVal += ")";

    // TODO: print cps

    return retVal;
}

#pragma mark - subset selection

void EulerGenus_2::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected (true);
}

void EulerGenus_2::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected (true);
}

void EulerGenus_2::selectS0_2()
{
    jassertfalse;
}

void EulerGenus_2::selectS0_3()
{
    jassertfalse;
}

void EulerGenus_2::selectS0_4()
{
    jassertfalse;
}

void EulerGenus_2::selectS0_5()
{
    jassertfalse;
}

void EulerGenus_2::selectS0_6()
{
    jassertfalse;
}

void EulerGenus_2::selectS0_7()
{
    jassertfalse;
}

void EulerGenus_2::selectS1_0()
{
    jassertfalse;
}

void EulerGenus_2::selectS1_1()
{
    jassertfalse;
}

void EulerGenus_2::selectS1_2()
{
    jassertfalse;
}

void EulerGenus_2::selectS1_3()
{
    jassertfalse;
}

void EulerGenus_2::selectS1_4()
{
    jassertfalse;
}

void EulerGenus_2::selectS1_5()
{
    jassertfalse;
}

void EulerGenus_2::selectS1_6()
{
    jassertfalse;
}

void EulerGenus_2::selectS1_7()
{
    jassertfalse;
}

bool EulerGenus_2::isEulerGenusTuningType()
{
    return true;
}

