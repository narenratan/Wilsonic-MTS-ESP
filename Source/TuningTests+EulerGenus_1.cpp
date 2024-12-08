/*
  ==============================================================================

    TuningTests+Monad.cpp
    Created: 29 Jul 2021 7:39:29pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "TuningTests.h"
#include "EulerGenus_1.h"

void TuningTests::testEulerGenus_1()
{
    // Test EulerGenus_1
    cout << "BEGIN TEST: EulerGenus_1() ---------------------" << endl;

    //
    auto mtA = CPS::A(3);
    auto eg1_1 = EulerGenus_1 (mtA);
    cout << "EulerGenus_1 constructor with Microtone" << endl;
    cout << "Microtone: " << mtA->getDebugDescription() << endl;
    cout << "EulerGenus_1 shortDescriptionText: " << eg1_1.getDebugDescription() << endl;
    cout << "EulerGenus_1 _cps_1_1: " << eg1_1.getCps_1_1()->getDebugDescription() << endl;

    //
    cout << "END TEST: EulerGenus_1() ---------------------\n\n";
}
