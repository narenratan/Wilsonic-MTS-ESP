/*
 ==============================================================================

 TuningTests+CPS_1_1.cpp
 Created: 16 Aug 2021 8:35:14pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "TuningTests.h"
#include "CPS_1_1.h"

void TuningTests::testCPS_1_1()
{
    // Test EulerGenus_1
    cout << "BEGIN TEST: CPS_1_1() ---------------------" << endl;

    // construct 
    auto time = logRelativeTime ("start", nullptr);
    auto mtA = CPS::A(3);
    cout << "Microtone: (before CPS_1_1 creation): " << mtA->getDebugDescription() << endl;
    cout << "CPS_1_1 constructor with Microtone:" << endl;
    auto cps_1_1_3 = CPS_1_1(mtA);
    cout << "CPS_1_1 getDebugDescription: " << cps_1_1_3.getDebugDescription() << endl;

    //
    time = logRelativeTime ("constructor complete", time);
    cout << "END TEST: CPS_1_1() ---------------------\n\n";
}
