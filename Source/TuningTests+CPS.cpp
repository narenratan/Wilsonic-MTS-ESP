/*
  ==============================================================================

    TuningTests+CPS.cpp
    Created: 8 Aug 2021 10:18:04am
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "TuningTests.h"
#include "CPS.h"

void TuningTests::testCPS()
{
    // Test EulerGenus_1
    cout << "BEGIN TEST: CPS() ---------------------" << endl;

    auto printMicrotone =  [&](auto& mt)
    {
        cout <<
        mt->getFrequencyValue() << ":" <<
        mt->getShortDescriptionText() << ":" <<
        mt->getShortDescriptionText2() << ":" <<
        mt->getShortDescriptionText3() << endl;
    };

    auto mtA = CPS::A (3);
    printMicrotone (mtA);

    auto mtB = CPS::B (5);
    printMicrotone (mtB);

    auto mtC = CPS::C (7);
    printMicrotone (mtC);

    auto mtD = CPS::D (11);
    printMicrotone (mtD);

    auto mtE = CPS::E (13);
    printMicrotone (mtE);

    auto mtF = CPS::F (17);
    printMicrotone (mtF);

    auto mtAB = CPS::AB (mtA, mtB);
    printMicrotone (mtAB);

    auto mtEF = CPS::AB (mtE, mtF);
    printMicrotone (mtEF);

    auto mtBCD = CPS::ABC (mtB, mtC, mtD);
    printMicrotone (mtBCD);

    auto mtBCDE = CPS::ABCD (mtB, mtC, mtD, mtE);
    printMicrotone (mtBCDE);

    auto mtBCDEF = CPS::ABCDE (mtB, mtC, mtD, mtE, mtF);
    printMicrotone (mtBCDEF);

    auto mtABCDEF = CPS::ABCDEF (mtA, mtB, mtC, mtD, mtE, mtF);
    printMicrotone (mtABCDEF);

#if 0
    // proves that iterating with CPS::AB is collapsing the frequency description.
    auto mta = vector<Microtone_p> {mtB, mtC, mtD, mtE, mtF};
    auto retVal = mtA;
    for (auto mtt : mta)
    {
        retVal = CPS::AB (retVal, mtt);
    }
    printMicrotone (retVal);
#endif
    
    //
    cout << "END TEST: CPS() ---------------------\n\n";
}
