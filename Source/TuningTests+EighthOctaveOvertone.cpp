/*
  ==============================================================================

    TuningTests+EighthOctaveOvertone.cpp
    Created: 21 Oct 2021 7:36:46pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "TuningTests.h"
#include "TuningImp.h"

//    BEGIN TEST: testEighthOctaveOvertone() ---------------------
//    start: 0 ms
//    CORRECTION: VV this is octaves 1-8.  It just so happened that they octave reduce to 128 tones.
//    Eighth Octave Overtone:
//    1, 129, 65, 131, 33, 133, 67, 135, 17, 137, 69, 139, 35, 141, 71, 143, 9, 145, 73, 147, 37, 149, 75, 151, 19, 153, 77, 155, 39, 157, 79, 159, 5, 161, 81, 163, 41, 165, 83, 167, 21, 169, 85, 171, 43, 173, 87, 175, 11, 177, 89, 179, 45, 181, 91, 183, 23, 185, 93, 187, 47, 189, 95, 191, 3, 193, 97, 195, 49, 197, 99, 199, 25, 201, 101, 203, 51, 205, 103, 207, 13, 209, 105, 211, 53, 213, 107, 215, 27, 217, 109, 219, 55, 221, 111, 223, 7, 225, 113, 227, 57, 229, 115, 231, 29, 233, 117, 235, 59, 237, 119, 239, 15, 241, 121, 243, 61, 245, 123, 247, 31, 249, 125, 251, 63, 253, 127, 255
//    scale creation complete: 0 ms
//    END TEST: testEighthOctaveOvertone() ---------------------

void TuningTests::testEighthOctaveOvertone()
{
    // Test EulerGenus_1
    cout << "BEGIN TEST: testEighthOctaveOvertone() ---------------------" << endl;

    // construct 
    auto time = logRelativeTime ("start", nullptr);

    // TODO: After 2021-10-23 discussion w Johnny Reinhard: this should be 128-256, i.e., the 8th octave only
    // ^^ i "got lucky" because previous 7 octaves were reduced and captured in the 8th octave
    //
    auto ma = MicrotoneArray();
    for (auto i = 1; i < 256; i += 2) // odd numbers (1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, ...)
    {
        auto mt = make_shared<Microtone> (i, 1, to_string(i), Microtone::Space::Linear);
        ma.addMicrotone (mt);
    }
    ma = ma.octaveReduce (2.f);
    ma = ma.sort();
    ma = ma.uniquify();

    cout << "Eighth Octave Overtone NPO: " << ma.count() << endl;
    cout << "Eighth Octave Overtone:\n" << ma << endl;

    //
    time = logRelativeTime ("scale creation complete", time);
    cout << "END TEST: testEighthOctaveOvertone() ---------------------\n\n";
}


// using this test to create a subset of presets
void TuningTests::testOctaveOvertone()
{
    // Test EulerGenus_1
    cout << "BEGIN TEST: testOctaveOvertone() ---------------------" << endl;

    // log start time
    auto time = logRelativeTime ("start", nullptr);

    // explore octaves of the harmonic series
    for (auto octave = 1; octave < 9; octave++)
    {
        auto ma = MicrotoneArray();
        auto harmonic0 = exp2 (octave - 1);
        auto harmonic1 = exp2 (octave - 0);
        for (auto harmonic = harmonic0; harmonic < harmonic1; harmonic++)
        {
            auto mt = make_shared<Microtone> (harmonic, 1, to_string(harmonic), Microtone::Space::Linear);
            ma.addMicrotone (mt);
        }
        ma = ma.octaveReduce (2.);
        ma = ma.uniquify();
        ma = ma.sort();

        // log each octave
        cout << "Octave Overtone: " << octave << endl;
        cout << "Octave Overtone NPO: " << ma.count() << endl;
        cout << "Octave Overtone:\n" << ma << endl;
        auto t = TuningImp();
        t.setMicrotoneArray (ma);
        cout << endl << endl;
    }


    // log end time
    time = logRelativeTime ("scale creation complete", time);
    cout << "END TEST: testOctaveOvertone() ---------------------\n\n";
}

// using this test to create a subset of presets
void TuningTests::testOctaveUndertone()
{
    // Test EulerGenus_1
    cout << "BEGIN TEST: testOctaveUndertone() ---------------------" << endl;

    // log start time
    auto time = logRelativeTime ("start", nullptr);

    // explore octaves of the harmonic series
    for (auto octave = 1; octave < 9; octave++)
    {
        auto ma = MicrotoneArray();
        auto subharmonic0 = exp2 (octave - 1);
        auto subharmonic1 = exp2 (octave - 0);
        for (auto subharmonic = subharmonic0; subharmonic < subharmonic1; subharmonic++)
        {
//            auto mt = make_shared<Microtone> (subharmonic0, subharmonic, "/" + to_string(subharmonic), Microtone::Space::Linear);
            auto mt = make_shared<Microtone> (subharmonic0, subharmonic);
            ma.addMicrotone (mt);
        }
        ma = ma.octaveReduce (2.f);
        ma = ma.uniquify();
        ma = ma.sort();

        // log each octave
        cout << "Octave Undertone: " << octave << endl;
        cout << "Octave Undertone NPO: " << ma.count() << endl;
        cout << "Octave Undertone:\n" << ma << endl;
        auto t = TuningImp();
        t.setMicrotoneArray (ma);
        cout << endl << endl;
    }


    // log end time
    time = logRelativeTime ("scale creation complete", time);
    cout << "END TEST: testOctaveOvertone() ---------------------\n\n";
}
