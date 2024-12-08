/*
  ==============================================================================

    EulerGenus_6.cpp
    Created: 10 Aug 2021 10:35:56pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "EulerGenus_6.h"

#pragma mark - lifecycle

EulerGenus_6::EulerGenus_6(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F)
: Seed6(A, B, C, D, E, F)
, _cps_6_1(make_shared<CPS_6_1>(_A, _B, _C, _D, _E, _F))
, _cps_6_2(make_shared<CPS_6_2>(_A, _B, _C, _D, _E, _F))
, _cps_6_3(make_shared<CPS_6_3>(_A, _B, _C, _D, _E, _F))
, _cps_6_4(make_shared<CPS_6_4>(_A, _B, _C, _D, _E, _F))
, _cps_6_5(make_shared<CPS_6_5>(_A, _B, _C, _D, _E, _F))
, _cps_6_6(make_shared<CPS_6_6>(_A, _B, _C, _D, _E, _F))
{
    // properties
    setCanNPOOverride(true); // redundant, for clarity
    setCanUniquify(false);
    setCanSort(true);
    setSort(true);
    _tuningType = CPS_Class::EulerGenus_6;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);

    // subsets
    _subsets0.push_back(_cps_6_1);
    _subsets0.push_back(_cps_6_2);
    _subsets0.push_back(_cps_6_3);
    _subsets0.push_back(_cps_6_4);
    _subsets0.push_back(_cps_6_5);
    _subsets0.push_back(_cps_6_6);

    // update
    update();

    // select
    selectS0_3();
}

EulerGenus_6::EulerGenus_6(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed6(master_set, common_tones)
, _cps_6_1(make_shared<CPS_6_1>(_A, _B, _C, _D, _E, _F))
, _cps_6_2(make_shared<CPS_6_2>(_A, _B, _C, _D, _E, _F))
, _cps_6_3(make_shared<CPS_6_3>(_A, _B, _C, _D, _E, _F))
, _cps_6_4(make_shared<CPS_6_4>(_A, _B, _C, _D, _E, _F))
, _cps_6_5(make_shared<CPS_6_5>(_A, _B, _C, _D, _E, _F))
, _cps_6_6(make_shared<CPS_6_6>(_A, _B, _C, _D, _E, _F))
{
    // properties
    setCanNPOOverride(true); // redundant, for clarity
    setCanUniquify(false);
    setCanSort(true);
    setSort(true);
    _tuningType = CPS_Class::EulerGenus_6;
    auto basename = CPS::__cpsTuningClassMap[_tuningType];
    setTuningName(basename);

    // subsets
    _subsets0.push_back(_cps_6_1);
    _subsets0.push_back(_cps_6_2);
    _subsets0.push_back(_cps_6_3);
    _subsets0.push_back(_cps_6_4);
    _subsets0.push_back(_cps_6_5);
    _subsets0.push_back(_cps_6_6);

    // update
    update();

    // select
    selectS0_3();
}

EulerGenus_6::~EulerGenus_6() {

}

#pragma mark - properties

const shared_ptr<CPS_6_1> EulerGenus_6::getCps_6_1() {
    return _cps_6_1;
}

const shared_ptr<CPS_6_2> EulerGenus_6::getCps_6_2() {
    return _cps_6_2;
}

const shared_ptr<CPS_6_3> EulerGenus_6::getCps_6_3() {
    return _cps_6_3;
}

const shared_ptr<CPS_6_4> EulerGenus_6::getCps_6_4() {
    return _cps_6_4;
}

const shared_ptr<CPS_6_5> EulerGenus_6::getCps_6_5() {
    return _cps_6_5;
}

const shared_ptr<CPS_6_6> EulerGenus_6::getCps_6_6() {
    return _cps_6_6;
}

#pragma mark - update row

void EulerGenus_6::update() {
    _cps_6_1->setABCDEF(_A, _B, _C, _D, _E, _F);
    _cps_6_2->setABCDEF(_A, _B, _C, _D, _E, _F);
    _cps_6_3->setABCDEF(_A, _B, _C, _D, _E, _F);
    _cps_6_4->setABCDEF(_A, _B, _C, _D, _E, _F);
    _cps_6_5->setABCDEF(_A, _B, _C, _D, _E, _F);
    _cps_6_6->setABCDEF(_A, _B, _C, _D, _E, _F);
}

void EulerGenus_6::_allocateSubsets() {
    // NOP for EulerGenus
}

#pragma mark - description

const string EulerGenus_6::getShortDescriptionText() {
    string retVal = "EulerGenus_6:(";
    retVal += getA()->getShortDescriptionText();
    retVal += ",";
    retVal += getB()->getShortDescriptionText();
    retVal += ",";
    retVal += getC()->getShortDescriptionText();
    retVal += ",";
    retVal += getD()->getShortDescriptionText();
    retVal += ",";
    retVal += getE()->getShortDescriptionText();
    retVal += ",";
    retVal += getF()->getShortDescriptionText();
    retVal += ")";

    return retVal;
}

#pragma mark - subset selection

void EulerGenus_6::selectS0_0() {
    _clearSelection();
    _subsets0[0]->setIsSelected(true);
}

void EulerGenus_6::selectS0_1() {
    _clearSelection();
    _subsets0[1]->setIsSelected(true);
}

void EulerGenus_6::selectS0_2() {
    _clearSelection();
    _subsets0[2]->setIsSelected(true);
}

void EulerGenus_6::selectS0_3() {
    _clearSelection();
    _subsets0[3]->setIsSelected(true);
}

void EulerGenus_6::selectS0_4() {
    _clearSelection();
    _subsets0[4]->setIsSelected(true);
}

void EulerGenus_6::selectS0_5() {
    _clearSelection();
    _subsets0[5]->setIsSelected(true);
}

void EulerGenus_6::selectS0_6() {
    jassertfalse;
}

void EulerGenus_6::selectS0_7() {
    jassertfalse;
}

void EulerGenus_6::selectS1_0() {
    jassertfalse;
}

void EulerGenus_6::selectS1_1() {
    jassertfalse;
}

void EulerGenus_6::selectS1_2() {
    jassertfalse;
}

void EulerGenus_6::selectS1_3() {
    jassertfalse;
}

void EulerGenus_6::selectS1_4() {
    jassertfalse;
}

void EulerGenus_6::selectS1_5() {
    jassertfalse;
}

void EulerGenus_6::selectS1_6() {
    jassertfalse;
}

void EulerGenus_6::selectS1_7() {
    jassertfalse;
}

bool EulerGenus_6::isEulerGenusTuningType() {
    return true;
}
