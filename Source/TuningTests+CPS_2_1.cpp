/*
 ==============================================================================

 TuningTests+CPS_2_1.cpp
 Created: 16 Aug 2021 9:45:41pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "TuningTests.h"
#include "CPS_2_1.h"

void TuningTests::testCPS_2_1()
{
    // Test EulerGenus_1
    cout << "BEGIN TEST: CPS_2_1() ---------------------" << endl;

    // construct
    auto time = logRelativeTime ("start", nullptr);
    auto mtA = CPS::A (3);
    auto mtB = CPS::B (5);
    cout << "Microtone: " << mtA->getDebugDescription() << endl;
    cout << "Microtone: " << mtB->getDebugDescription() << endl;
    auto cps_2_1_A_B = CPS_2_1 (mtA, mtB);
    cout << "CPS_2_1 constructor with Microtone:" << endl;
    cout << "CPS_2_1 getDebugDescription:\n" << cps_2_1_A_B.getDebugDescription() << endl;

    //
    time = logRelativeTime ("constructor complete", time);
    cout << "END TEST: CPS_2_1() ---------------------\n\n";
}
