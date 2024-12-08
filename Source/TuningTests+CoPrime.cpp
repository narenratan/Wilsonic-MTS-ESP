/*
  ==============================================================================

    TuningTests+CoPrime.cpp
    Created: 23 Apr 2023 9:07:20pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "TuningTests.h"
#include "CoPrime.h"
#include "CoPrimeMicrotone.h"

void TuningTests::testCoPrime()
{
    // Test CoPrime
    cout << "BEGIN TEST: CoPrime() ---------------------" << endl;

    CoPrime scale;
    auto ma = scale.getProcessedArray();
    auto const num = ma.count();
    for (unsigned long i = 0; i < num; i++)
    {
        auto mt = ma.microtoneAtIndex (i);
        cout << i << ": " << mt->getShortDescriptionText() << endl;
    }

    cout << endl << "Testing GCD:" << endl;
    for (auto i = 1UL; i < 10; i++)
    {
        for (auto j = 1UL; j < 10; j++)
        {
            auto const result = CoPrime::GCD (i, j);
            cout << "i:" << i << ", j:" << j << ", result: " << result << endl;
        }
    }
    //
    cout << "END TEST: CoPrime() ---------------------" << endl;
}
