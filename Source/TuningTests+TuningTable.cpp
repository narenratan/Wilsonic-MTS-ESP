/*
  ==============================================================================

    TuningTests+TuningTable.cpp
    Created: 24 Feb 2021 6:22:16pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "TuningTests.h"
#include "TuningTableImp.h"

void TuningTests::testTuningTableImp()
{
    // Test TuningTableImp
    cout << "BEGIN TEST: TuningTableImp() ---------------------\n";

    // print the default (12 ET)
    TuningTableImp tt;
    cout << "TuningTableImp: \n" << tt << "\n";

    //
    cout << "END TEST: TuningTableImp() ---------------------\n\n";
}
