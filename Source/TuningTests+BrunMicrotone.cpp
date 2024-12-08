/*
  ==============================================================================

    TuningTests+BrunMicrotone.cpp
    Created: 27 Feb 2021 9:08:01pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "TuningTests.h"
#include "BrunMicrotone.h"
#include "Tuning.h"
#include "Brun.h"


void TuningTests::testBrunMicrotone()
{
    cout << "BEGIN TEST: testBrunMicrotone() ---------------------\n";
    cout << endl;

    Microtone_p mm = make_shared<Microtone>(0.415f, "", Microtone::Space::LogPeriod, TuningConstants::defaultPeriod);
    cout << mm << endl;
    auto bm = make_shared<BrunMicrotone> (0.415f, 1, 6);
    cout << bm << endl;

    cout << "END TEST: testBrunMicrotone() ---------------------\n\n";
}

void TuningTests::testBrunMicrotoneCollection()
{
    cout << "BEGIN TEST: testBrunMicrotoneCollection() ---------------------\n";
    cout << endl;

    // array of pointers
    auto mtnr = make_shared<Microtone> (3, 2, "", Microtone::Space::LogPeriod, TuningConstants::defaultPeriod);
    auto mtn = make_shared<Microtone> (0.415f, "", Microtone::Space::LogPeriod, TuningConstants::defaultPeriod);
    auto bmtn = make_shared<BrunMicrotone> (0.583333f, 3, 5);
    auto ma = MicrotoneArray();
    ma.addMicrotone (mtnr);
    ma.addMicrotone (mtn);
    ma.addMicrotone (bmtn);
    
    cout << ma << endl;
    cout << "END TEST: testBrunMicrotoneCollection() ---------------------\n\n";
}

