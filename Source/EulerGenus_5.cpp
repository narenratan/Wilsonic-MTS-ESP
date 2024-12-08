/*
  ==============================================================================

    EulerGenus_5.cpp
    Created: 10 Aug 2021 10:35:40pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "EulerGenus_5.h"

#pragma mark - lifecycle

EulerGenus_5::EulerGenus_5(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E)
: Seed5(A, B, C, D, E)
, _cps_5_1(make_shared<CPS_5_1>(_A, _B, _C, _D, _E))
, _cps_5_2(make_shared<CPS_5_2>(_A, _B, _C, _D, _E))
, _cps_5_3(make_shared<CPS_5_3>(_A, _B, _C, _D, _E))
, _cps_5_4(make_shared<CPS_5_4>(_A, _B, _C, _D, _E))
, _cps_5_5(make_shared<CPS_5_5>(_A, _B, _C, _D, _E))
{
    // properties
    setCanNPOOverride(true); // redundant, for clarity
    setCanUniquify(false);
    setCanSort(true);
    setSort(true);
    _tuningType = CPS_Class::EulerGenus_5;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);

    // subsets
    _subsets0.push_back(_cps_5_1);
    _subsets0.push_back(_cps_5_2);
    _subsets0.push_back(_cps_5_3);
    _subsets0.push_back(_cps_5_4);
    _subsets0.push_back(_cps_5_5);

    // update
    update();

    // select
    selectS0_3();
}

EulerGenus_5::EulerGenus_5(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed5(master_set, common_tones)
, _cps_5_1(make_shared<CPS_5_1>(_A, _B, _C, _D, _E))
, _cps_5_2(make_shared<CPS_5_2>(_A, _B, _C, _D, _E))
, _cps_5_3(make_shared<CPS_5_3>(_A, _B, _C, _D, _E))
, _cps_5_4(make_shared<CPS_5_4>(_A, _B, _C, _D, _E))
, _cps_5_5(make_shared<CPS_5_5>(_A, _B, _C, _D, _E))
{
    // properties
    setCanNPOOverride(true); // redundant, for clarity
    setCanUniquify(false);
    setCanSort(true);
    setSort(true);
    _tuningType = CPS_Class::EulerGenus_5;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);

    // subsets
    _subsets0.push_back(_cps_5_1);
    _subsets0.push_back(_cps_5_2);
    _subsets0.push_back(_cps_5_3);
    _subsets0.push_back(_cps_5_4);
    _subsets0.push_back(_cps_5_5);

    // update
    update();

    // select
    selectS0_3();
}

EulerGenus_5::~EulerGenus_5()
{

}

#pragma mark - update row

void EulerGenus_5::update()
{
    _cps_5_1->setABCDE(_A, _B, _C, _D, _E);
    _cps_5_2->setABCDE(_A, _B, _C, _D, _E);
    _cps_5_3->setABCDE(_A, _B, _C, _D, _E);
    _cps_5_4->setABCDE(_A, _B, _C, _D, _E);
    _cps_5_5->setABCDE(_A, _B, _C, _D, _E);
}

void EulerGenus_5::_allocateSubsets()
{
    // NOP for EulerGenus
}


#pragma mark - description

const string EulerGenus_5::getShortDescriptionText()
{
    string retVal = "EulerGenus_5:(";
    retVal += getA()->getShortDescriptionText();
    retVal += ",";
    retVal += getB()->getShortDescriptionText();
    retVal += ",";
    retVal += getC()->getShortDescriptionText();
    retVal += ",";
    retVal += getD()->getShortDescriptionText();
    retVal += ",";
    retVal += getE()->getShortDescriptionText();
    retVal += ")";

    return retVal;
}

#pragma mark - subset selection

void EulerGenus_5::selectS0_0()
{
    _clearSelection();
    _subsets0[0]->setIsSelected (true);
}

void EulerGenus_5::selectS0_1()
{
    _clearSelection();
    _subsets0[1]->setIsSelected (true);
}

void EulerGenus_5::selectS0_2()
{
    _clearSelection();
    _subsets0[2]->setIsSelected (true);
}

void EulerGenus_5::selectS0_3()
{
    _clearSelection();
    _subsets0[3]->setIsSelected (true);
}

void EulerGenus_5::selectS0_4()
{
    _clearSelection();
    _subsets0[4]->setIsSelected (true);
}

void EulerGenus_5::selectS0_5()
{
    jassertfalse;
}

void EulerGenus_5::selectS0_6()
{
    jassertfalse;
}

void EulerGenus_5::selectS0_7()
{
    jassertfalse;
}

void EulerGenus_5::selectS1_0()
{
    jassertfalse;
}

void EulerGenus_5::selectS1_1()
{
    jassertfalse;
}

void EulerGenus_5::selectS1_2()
{
    jassertfalse;
}

void EulerGenus_5::selectS1_3()
{
    jassertfalse;
}

void EulerGenus_5::selectS1_4()
{
    jassertfalse;
}

void EulerGenus_5::selectS1_5()
{
    jassertfalse;
}

void EulerGenus_5::selectS1_6()
{
    jassertfalse;
}

void EulerGenus_5::selectS1_7()
{
    jassertfalse;
}

bool EulerGenus_5::isEulerGenusTuningType()
{
    return true;
}
