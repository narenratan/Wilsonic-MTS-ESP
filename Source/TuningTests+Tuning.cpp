/*
  ==============================================================================

    TuningTests+Tuning.cpp
    Created: 24 Feb 2021 6:22:30pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "TuningTests.h"
#include "TuningImp.h"

void TuningTests::testTuningImp()
{
    // Test Tuning
    cout << "BEGIN TEST: TuningImp() ---------------------\n";

    cout << "--------------------------------------------------\n\n";

    TuningImp t;
    t.setTuningName ("tuning name");
    t.setTuningDescription ("tuning description");
    t.setUserDescription ("tuning user comments");
    MicrotoneArray ma;
    ma.addMicrotone (make_shared<Microtone>(1.f));
    ma.addMicrotone (make_shared<Microtone>(3.f));
    ma.addMicrotone (make_shared<Microtone>(5.f));
    ma.addMicrotone (make_shared<Microtone>(7.f));
    t.setMicrotoneArray (ma);
    cout << "TuningImp: \n" << t.getDebugDescription() << "\n";

    cout << "--------------------------------------------------\n\n";

    //
    cout << "END TEST: TuningImp() ---------------------\n\n";
}

