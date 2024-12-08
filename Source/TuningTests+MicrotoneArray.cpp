/*
 ==============================================================================

 TuningTests+MicrotoneArray.cpp
 Created: 24 Feb 2021 6:20:52pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "TuningTests.h"
#include "MicrotoneArray.h"
#include "CPS.h"

void TuningTests::testMicrotoneArray()
{
    cout << "--------------------------------------------------\n\n";

    // Test MicrotoneArray
    cout << "BEGIN TEST: MicrotoneArray() ---------------------\n";
    cout << endl;

    //
    cout << "--------------------------------------------------\n\n";

    // rationals
    auto mt_v_mt_rationals = MicrotoneArray();
    mt_v_mt_rationals.addMicrotone (make_shared<Microtone>(1,1));
    mt_v_mt_rationals.addMicrotone (make_shared<Microtone>(5,4));
    mt_v_mt_rationals.addMicrotone (make_shared<Microtone>(3,2));
    mt_v_mt_rationals.addMicrotone (make_shared<Microtone>(7,4));
    cout << "MicrotoneArray( rationals )            : " << mt_v_mt_rationals << endl;

    // copy
    auto mt_v_mt_rationals_copy = MicrotoneArray (mt_v_mt_rationals);
    cout << "MicrotoneArray( rationals ): copy of ^^: " << mt_v_mt_rationals_copy << endl;
    cout << endl;

    cout << "--------------------------------------------------\n\n";

    // numbers
    {
        {
            // numbers
            auto mt_v_mt_numbers = MicrotoneArray();
            mt_v_mt_numbers.addMicrotone (make_shared<Microtone>(1.f));
            mt_v_mt_numbers.addMicrotone (make_shared<Microtone>(1.25f));
            mt_v_mt_numbers.addMicrotone (make_shared<Microtone>(1.5f));
            mt_v_mt_numbers.addMicrotone (make_shared<Microtone>(1.75f));
            cout << "MicrotoneArray( numbers ):           : " << mt_v_mt_numbers << endl;

            // copy
            auto mt_v_mt_numbers_copy = MicrotoneArray(mt_v_mt_numbers);
            cout << "MicrotoneArray( numbers ): copy of ^^: " << mt_v_mt_numbers_copy << endl;
            cout << endl;

            cout << "--------------------------------------------------\n\n";
        }

        cout << "--------------------------------------------------\n\n";

        {
            // numbers
            auto mt_v_mt_numbers = MicrotoneArray();
            mt_v_mt_numbers.addMicrotone(CPS::A (3));
            mt_v_mt_numbers.addMicrotone(CPS::B (5));
            mt_v_mt_numbers.addMicrotone(CPS::C (7));
            mt_v_mt_numbers.addMicrotone(CPS::D (13));
            cout << "MicrotoneArray( numbers ):                         : " << mt_v_mt_numbers << endl;
            cout << mt_v_mt_numbers.getDebugDescription() << endl;

            cout << "--------------------------------------------------\n\n";

            // test deep copy
            auto mt_v_mt_numbers_copy = MicrotoneArray (mt_v_mt_numbers);
            cout << "MicrotoneArray( numbers ): copy of ^^              : " << mt_v_mt_numbers_copy << endl;
            cout << mt_v_mt_numbers_copy.getDebugDescription() << endl;

            cout << "--------------------------------------------------\n\n";
            // octave reduce by 2
            mt_v_mt_numbers_copy = mt_v_mt_numbers_copy.octaveReduce (2.f);
            cout << "MicrotoneArray( numbers ): copy of ^^ octave reduce by 2.f: " << mt_v_mt_numbers_copy << endl;
            cout << mt_v_mt_numbers_copy.getDebugDescription() << endl;
            cout << endl;

            cout << "--------------------------------------------------\n\n";
            // octave reduce by 3
            auto mt_v_mt_numbers_copy3 = MicrotoneArray (mt_v_mt_numbers);
            mt_v_mt_numbers_copy3 = mt_v_mt_numbers_copy3.octaveReduce (3.f);
            cout << "MicrotoneArray( numbers ): copy of ^^ octave reduce by 3.f: " << mt_v_mt_numbers_copy3 << endl;
            cout << mt_v_mt_numbers_copy3.getDebugDescription() << endl;
            cout << endl;

            cout << "--------------------------------------------------\n\n";
            // octave reduce by 1.618
            auto mt_v_mt_numbers_copy4 = MicrotoneArray (mt_v_mt_numbers);
            mt_v_mt_numbers_copy4 = mt_v_mt_numbers_copy4.octaveReduce (1.618f);
            cout << "MicrotoneArray( numbers ): copy of ^^ octave reduce by 1.618: " << mt_v_mt_numbers_copy4 << endl;
            cout << mt_v_mt_numbers_copy4.getDebugDescription() << endl;
            cout << endl;

            cout << "--------------------------------------------------\n\n";
        }

        cout << "--------------------------------------------------\n\n";

    }

    // vector<float>
    cout << endl;
    cout << endl;
    auto mt_v_floats = MicrotoneArray( vector<float>{1, 3, 5, 7} );
    cout << "MicrotoneArray( vector<Microtone> floats ): " << mt_v_floats << endl;
    cout << endl;
    cout << "--------------------------------------------------\n\n";

    // microtoneArrayHarmonicLimit
    cout << endl;
    cout << endl;
    auto mt_a_hl = MicrotoneArray::microtoneArrayHarmonicLimit (13, 2);
    cout << "MicrotoneArray::microtoneArrayHarmonicLimit(): " << mt_a_hl << endl;
    cout << endl;
    cout << "--------------------------------------------------\n\n";

    // octave reduce, sort, uniquify
    cout << endl;
    cout << endl;
    auto mt_or = MicrotoneArray();
    constexpr int limit = 8;
    for (auto i = 1; i < limit; i++)
    {
        for (auto j = 1; j < limit; j++)
        {
            mt_or.addMicrotone(make_shared<Microtone>(i,j));
        }
    }
    cout << "MicrotoneArray():              " << mt_or << endl;
    mt_or = mt_or.sort();
    cout << "MicrotoneArray().sort():       " << mt_or << endl;
    mt_or = mt_or.octaveReduce (2.f);
    cout << "MicrotoneArray.octaveReduce (2.f): " << mt_or << endl;
    mt_or = mt_or.uniquify();
    cout << "MicrotoneArray.uniquify():     " << mt_or << endl;
    mt_or = mt_or.sort();
    cout << "MicrotoneArray().sort():       " << mt_or << endl;
    cout << endl;
    cout << "--------------------------------------------------\n\n";


    // numeratorDenominatorPairs
    cout << "MicrotoneArray::MicrotoneArray (vector<unsigned long> numeratorDenominatorPairs)" << endl;
    auto mt_ndp_00 = MicrotoneArray(vector<unsigned long> {135,128, 32,27, 16,15, 9,8, 135,128, 32,27, 16,15} );
    cout << "delta input: " << mt_ndp_00 << endl;

    cout << "--------------------------------------------------\n\n";

    
    // Test MicrotoneArray
    cout << endl;
    cout << endl;
    cout << "END TEST: MicrotoneArray() ---------------------\n\n";

    //
    cout << "--------------------------------------------------\n\n";
}
