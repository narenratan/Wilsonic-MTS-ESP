/*
 ==============================================================================

 TuningTests+CPS_2_2.cpp
 Created: 16 Aug 2021 9:46:11pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "TuningTests.h"
#include "CPS_2_2.h"

void TuningTests::testCPS_2_2()
{
    // Test CPS_2_2
    cout << "BEGIN TEST: CPS_2_2() ---------------------" << endl;

    // construct 
    auto time = logRelativeTime ("start", nullptr);
    auto mtA = CPS::A (3);
    auto mtB = CPS::B (5);
    cout << "Microtone: " << mtA->getDebugDescription() << endl;
    cout << "Microtone: " << mtB->getDebugDescription() << endl;
    auto cps_2_2_A_B = CPS_2_2 (mtA, mtB);
    cout << "CPS_2_2 constructor with Microtone:" << endl;
    cout << "CPS_2_2 getTuningDescription: " << cps_2_2_A_B.getTuningDescription() << endl;
    cout << "CPS_2_2 getDebugDescription: " << cps_2_2_A_B.getDebugDescription() << endl;

    //
    time = logRelativeTime ("constructor complete", time);
    cout << "END TEST: CPS_2_2() ---------------------\n\n";
}
