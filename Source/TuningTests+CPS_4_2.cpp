/*
 ==============================================================================

 TuningTests+CPS_4_2.cpp
 Created: 22 Aug 2021 3:22:07pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "TuningTests.h"
#include "CPS_4_2.h"

void TuningTests::testCPS_4_2()
{
    // Test EulerGenus_1
    cout << "BEGIN TEST: CPS_4_2() ---------------------" << endl;
    auto time = logRelativeTime ("start", nullptr);

    // construct
    auto mtA = CPS::A (3);
    auto mtB = CPS::B (5);
    auto mtC = CPS::C (7);
    auto mtD = CPS::D (11);
    cout << "Microtone: " << mtA->getDebugDescription() << endl;
    cout << "Microtone: " << mtB->getDebugDescription() << endl;
    cout << "Microtone: " << mtC->getDebugDescription() << endl;
    cout << "Microtone: " << mtD->getDebugDescription() << endl;
    auto cps_4_2_A_B_C_D = CPS_4_2 (mtA, mtB, mtC, mtD);
    cout << "CPS_4_2 constructor with Microtone:" << endl;
    cout << "CPS_4_2 getDebugDescription: " << cps_4_2_A_B_C_D.getDebugDescription() << endl;

    //
    time = logRelativeTime ("constructor complete", time);
    cout << "END TEST: CPS_4_2() ---------------------\n\n";
}
