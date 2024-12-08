/*
  ==============================================================================

    EulerGenus_4.h
    Created: 10 Aug 2021 10:35:26pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPS_4_1.h"
#include "CPS_4_2.h"
#include "CPS_4_3.h"
#include "CPS_4_4.h"
#include "Seed4.h"
#include "Microtone.h"

// Row 5 of Figure 19 "A Pascal Triangle of Combination Set Lattices"
// D'Alessandro, Like A Hurricane, Erv Wilson, (c) 1989

class EulerGenus_4 : public Seed4
{
public:
    // lifecycle
    EulerGenus_4(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D);
    EulerGenus_4(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~EulerGenus_4() override;

    // every cps of row 5 resulting from the master set
    const shared_ptr<CPS_4_1> getCps_4_1();
    const shared_ptr<CPS_4_2> getCps_4_2();
    const shared_ptr<CPS_4_3> getCps_4_3();
    const shared_ptr<CPS_4_4> getCps_4_4();

    //
    const string getShortDescriptionText();

    // select subsets
    void selectS0_0() override;
    void selectS0_1() override;
    void selectS0_2() override;
    void selectS0_3() override;
    void selectS0_4() override;
    void selectS0_5() override;
    void selectS0_6() override;
    void selectS0_7() override;
    void selectS1_0() override;
    void selectS1_1() override;
    void selectS1_2() override;
    void selectS1_3() override;
    void selectS1_4() override;
    void selectS1_5() override;
    void selectS1_6() override;
    void selectS1_7() override;
    bool isEulerGenusTuningType() override;

private:
    // update
    void update() override;
    void _allocateSubsets() override; // unused in EulerGenus

    // every cps of row 2 resulting from the master set
    shared_ptr<CPS_4_1> _cps_4_1;
    shared_ptr<CPS_4_2> _cps_4_2;
    shared_ptr<CPS_4_3> _cps_4_3;
    shared_ptr<CPS_4_4> _cps_4_4;
};
