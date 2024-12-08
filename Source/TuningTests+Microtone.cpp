/*
  ==============================================================================

    TuningTests+Microtone.cpp
    Created: 24 Feb 2021 6:19:39pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "TuningTests.h"
#include "Microtone.h"

void TuningTests::testMicrotone()
{
    // test microtones
    cout << "BEGIN TEST: Microtone() ---------------------\n";

    Microtone_p a = make_shared<Microtone>( 7, 12 );
    cout << a << "\n";

    Microtone_p b = make_shared<Microtone>( 5, 12 );
    cout << b << "\n";

    Microtone_p sum = a->add (b);
    cout << "sum: " << sum << "\n";

    Microtone_p difference = a->subtract (b);
    cout << "difference: " << difference << "\n";

    Microtone_p freshman = Microtone::freshmanSum (a, b);
    cout << "freshman: " << freshman << "\n";

    Microtone_p product = a->multiply (b);
    cout << "product: " << product << "\n";

    Microtone_p divide = a->divide(b);
    cout << "divide: " << divide << "\n";

    //
    cout << "END TEST: Microtone() ---------------------\n\n";
}
