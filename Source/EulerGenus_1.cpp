/*
  ==============================================================================

    EulerGenus_1.cpp
    Created: 25 Jul 2021 5:23:19pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "EulerGenus_1.h"

#pragma mark - lifecycle

EulerGenus_1::EulerGenus_1(Microtone_p A)
: Seed1(A)
, _cps_1_1(make_shared<CPS_1_1> (_A))
{
    // properties
    setCanNPOOverride(true); // redundant, for clarity
    setCanUniquify(false);
    setCanSort(true);
    setSort(true);
    _tuningType = CPS_Class::EulerGenus_1;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);
    
    // subsets
    _subsets0.push_back(_cps_1_1);

    // update
    update();

    // select
    selectS0_0();
}

EulerGenus_1::EulerGenus_1 (vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed1 (master_set, common_tones)
, _cps_1_1 (make_shared<CPS_1_1> (_A))
{
    // properties
    setCanUniquify (false);
    setCanSort (true);
    setSort (true);
    _tuningType = CPS_Class::EulerGenus_1;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName (basename);

    // subsets
    _subsets0.push_back (_cps_1_1);

    // update
    update();

    // select
    selectS0_0();
}

EulerGenus_1::~EulerGenus_1()
{

}

#pragma mark - update

void EulerGenus_1::update()
{
    // update all the cps in this row
    _cps_1_1->setA (_A);
}

void EulerGenus_1::_allocateSubsets()
{
    // NOP for EulerGenus
}

#pragma mark - subsets

const shared_ptr<CPS_1_1> EulerGenus_1::getCps_1_1()
{
    return _cps_1_1;
}

#pragma mark - description

const string EulerGenus_1::getShortDescriptionText()
{
    auto mt = _A;
    string retVal = "EulerGenus_1:(";
    retVal += mt->getShortDescriptionText();
    retVal += ")";

    return retVal;
}

#pragma mark - subset selection

void EulerGenus_1::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected (true);
}

void EulerGenus_1::selectS0_1()
{
    jassertfalse;
}

void EulerGenus_1::selectS0_2()
{
    jassertfalse;
}

void EulerGenus_1::selectS0_3()
{
    jassertfalse;
}

void EulerGenus_1::selectS0_4()
{
    jassertfalse;
}

void EulerGenus_1::selectS0_5()
{
    jassertfalse;
}

void EulerGenus_1::selectS0_6()
{
    jassertfalse;
}

void EulerGenus_1::selectS0_7()
{
    jassertfalse;
}

void EulerGenus_1::selectS1_0()
{
    jassertfalse;
}

void EulerGenus_1::selectS1_1()
{
    jassertfalse;
}

void EulerGenus_1::selectS1_2()
{
    jassertfalse;
}

void EulerGenus_1::selectS1_3()
{
    jassertfalse;
}

void EulerGenus_1::selectS1_4()
{
    jassertfalse;
}

void EulerGenus_1::selectS1_5()
{
    jassertfalse;
}

void EulerGenus_1::selectS1_6()
{
    jassertfalse;
}

void EulerGenus_1::selectS1_7()
{
    jassertfalse;
}

bool EulerGenus_1::isEulerGenusTuningType()
{
    return true;
}

