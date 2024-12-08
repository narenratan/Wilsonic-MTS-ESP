/*
 ==============================================================================

 TuningTests+CPS_6_3.h
 Created: 16 Aug 2021 10:56:02pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "TuningTests.h"
#include "CPS_6_3.h"

void TuningTests::testCPS_6_3()
{
    // Test EulerGenus_1
    cout << "BEGIN TEST: CPS_6_3() ---------------------\n\n";

    // construct 
    cout << "CPS_6_3 constructor:-----------------\n";
    auto time = logRelativeTime ("start", nullptr);
    auto cps_6_3 = CPS_6_3 (CPS::A (3), CPS::B (5), CPS::C (7), CPS::D (11), CPS::E (13), CPS::F (17));
    time  = logRelativeTime ("constructor complete", time);

    // description (takes time)
    cout << "CPS_6_3 description:-----------------\n";
    cout << "CPS_6_3 getTuningDescription: " << cps_6_3.getTuningDescription() << endl;
    cout << "CPS_6_3 getDebugDescription: " << cps_6_3.getDebugDescription() << endl;
    time  = logRelativeTime ("description complete", time);

    // modify seeds
    cout << "CPS_6_3 setABCEDF:-----------------\n";
    cps_6_3.setABCDEF(CPS::A (19), CPS::B (23), CPS::C (29), CPS::D (31), CPS::E (37), CPS::F (41));
    time  = logRelativeTime ("modify seeds complete", time);

    // description (takes time)
    cout << "CPS_6_3 description:-----------------\n";
    cout << "CPS_6_3 getTuningDescription: " << cps_6_3.getTuningDescription() << endl;
    cout << "CPS_6_3 getDebugDescription: " << cps_6_3.getDebugDescription() << endl;
    time  = logRelativeTime ("description complete", time);

    //
    cout << "END TEST: CPS_6_3() ---------------------\n\n";
}
