/*
 ==============================================================================

 TuningTests+Brun.cpp
 Created: 24 Feb 2021 6:23:02pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "TuningTests.h"
#include "Microtone.h"
#include "Brun.h"
#include "BrunMicrotone.h"

void TuningTests::testBrun()
{
    cout << "BEGIN TEST: testBrun() ---------------------\n";
    cout << endl;

    //TuningTests::test_brun_level_array();
    //TuningTests::test_brun_level_array01();
    //TuningTests::test_brun_array_infinity();
    //TuningTests::test_brun_generator_setters_getters();
    //TuningTests::test_brun_g_l_m();
    //TuningTests::test_brun_terumi_gral_disjunction();
    //TuningTests::test_brun_gral_mapping();

    cout << "END TEST: testBrun() ---------------------\n\n";
}

void TuningTests::test_brun_level_array()
{
    // proves 0/1 x 1/0 works
    cout << "test_brun_level_array: TESTING (0,1)x(1,1):";
    Microtone_p zero = make_shared<Microtone>(0, 1, "", Microtone::Space::Linear, TuningConstants::defaultPeriod);
    Microtone_p one = make_shared<Microtone>( 1, 1, "", Microtone::Space::Linear, TuningConstants::defaultPeriod);
    auto ba = Brun::brunArray (Brun::absoluteMinLevel, Brun::absoluteMaxLevel, zero, one);
    for (auto baa : ba)
    {
        for (auto mt : baa)
        {
            cout << mt << ", ";
        }
        cout << endl;
        cout << endl;
    }
}

void TuningTests::test_brun_level_array01()
{
    // proves 0/1 x 1/0 works
    cout << "test_brun_level_array01: TESTING (1,1)x(2,1):";
    Microtone_p zero = make_shared<Microtone>(1, 1, "", Microtone::Space::Linear, TuningConstants::defaultPeriod);
    Microtone_p one = make_shared<Microtone>(2, 1, "", Microtone::Space::Linear, TuningConstants::defaultPeriod);
    auto ba = Brun::brunArray (Brun::absoluteMinLevel, Brun::absoluteMaxLevel, zero, one);
    for (auto baa : ba)
    {
        for (auto mt : baa)
        {
            cout << mt << ", ";
        }
        cout << endl;
        cout << endl;
    }
}

void TuningTests::test_brun_array_infinity()
{
    cout << "test_brun_array_infinity: testing Brun::getLevelArray()\n";
    cout << endl;
    auto ba08 = Brun::getLevelArray();
    for (auto baa : ba08)
    {
        unsigned long max_denom = 1;

        for (auto mt : baa)
        {
            cout << mt << ", ";
            max_denom = mt->getDenominator() > max_denom ? mt->getDenominator() : max_denom;
        }
        cout << endl;
        cout << "test_brun_array_infinity: max denominator = " << max_denom << endl;
        cout << endl;
    }
    cout << endl;
}

void TuningTests::test_brun_generator_setters_getters()
{
    Brun b{};
    b.setGenerator(0.415226f);
    b.setLevel(4);

    cout << "test_brun_generator_setters_getters: processed array: ";
    auto ma = b.getProcessedArray();
    cout << ma << endl;

    cout << "test_brun_generator_setters_getters: Brun: " << endl << b << endl;
}

void TuningTests::test_brun_g_l_m()
{
    Brun b{};
    b.setLevel(5);
    b.setMurchana(0);

    {
        cout << "test_brun_g_l_m: Test 9 linear generators" << endl;
        auto const num_terms = 9;
        for ( auto i = 0; i < num_terms; i++ )
        {
            auto const g = float(i)/float(num_terms);
            b.setGenerator(g);
            cout << "test_brun_g_l_m: g:" << to_string(g) << " ";
            auto pa = b.getProcessedArray();
            cout << "test_brun_g_l_m: f: " << pa << endl;
        }
    }

    {
        cout << "test_brun_g_l_m: Test 3 proportional triad generators, with update after generator setter" << endl;
        vector<float> generators{0.238186f,0.415226f,0.583333f};
        for ( auto g : generators )
        {
            b.setGenerator(g);
            cout << "test_brun_g_l_m: g:" << to_string(g) << " ";
            auto pa = b.getProcessedArray();
            cout << "test_brun_g_l_m: f: " << pa << endl;
        }
    }

    // test update gets processedArray after setting generator
    {
        cout << "test_brun_g_l_m: Test 3 proportional triad generators, WITHOUT EXPLICIT update after generator setter" << endl;
        vector<float> generators{0.238186f,0.415226f,0.583333f};
        for ( auto g : generators )
        {
            b.setGenerator(g);
            cout << "test_brun_g_l_m: g:" << to_string(g) << " ";
            auto pa = b.getProcessedArray();
            cout << "test_brun_g_l_m: f: " << pa << endl;
        }
    }
}

void TuningTests::test_brun_terumi_gral_disjunction()
{
    cout << endl << "test_brun_terumi_gral_disjunction" << endl;

    auto b = Brun();
    auto const g = fmodf(log2f(3.f), 1.f);
    auto const level = 5;
    b.setGenerator(g);
    b.setLevel(level);
    b.setMurchana(0);
    auto const npo = static_cast<int>(b.getNotesPerOctave());
    jassert(npo == 12);
    int const npo_2 = npo / 2;

    cout << endl << "generator: " << to_string(g) << ", level:" << to_string(level) << ", npo:" << to_string(npo) << ", npo_2:" << to_string(npo_2) << endl << endl;
#if 0
    for (unsigned long murchana = 0; murchana < npo; murchana++)
    {
        b.setMurchana(murchana);
        cout << endl << endl << "test_brun_terumi_gral_disjunction: murchana:" << to_string(murchana) << endl << endl;

        auto pmta = b.getProcessedArray();
        unsigned long pmtai = 0;
        for (unsigned long nnRoot = 0 + nnMiddleC; nnRoot < npo + nnMiddleC; nnRoot++)
        {
            auto mt = pmta.microtoneAtIndex(pmtai);
            BrunMicrotone* bmt = dynamic_cast<BrunMicrotone*>(mt.get());
            auto bsd = bmt->getScaleDegree();
            auto const fRoot = b.getTuningTableFrequency(nnRoot);
            auto const nnFifth = nnRoot + 7;
            auto const fFifth = b.getTuningTableFrequency(nnFifth);
            auto const fifthIntervalSize = fFifth/fRoot;
            cout << "test_brun_terumi_gral_disjunction: degree: " << to_string(bsd) << ", nn:" << to_string(nnRoot) << ", f: " << to_string(fifthIntervalSize) << endl;
            pmtai++;
        }
    }
#endif
    // Murchana 5 is equivalent to offsetting the chain by -5
    // Places the disjunct 5th at F#/Db
//test_brun_terumi_gral_disjunction: murchana:5
//
//test_brun_terumi_gral_disjunction: nn:60, f: 1.500000
//test_brun_terumi_gral_disjunction: nn:61, f: 1.500000
//test_brun_terumi_gral_disjunction: nn:62, f: 1.500000
//test_brun_terumi_gral_disjunction: nn:63, f: 1.500000
//test_brun_terumi_gral_disjunction: nn:64, f: 1.500000
//test_brun_terumi_gral_disjunction: nn:65, f: 1.500000
//test_brun_terumi_gral_disjunction: nn:66, f: 1.479811
//test_brun_terumi_gral_disjunction: nn:67, f: 1.500000
//test_brun_terumi_gral_disjunction: nn:68, f: 1.500000
//test_brun_terumi_gral_disjunction: nn:69, f: 1.500000
//test_brun_terumi_gral_disjunction: nn:70, f: 1.500000
//test_brun_terumi_gral_disjunction: nn:71, f: 1.500000

    auto brunArray = Brun::brunArray(level, g);
    cout << "Brun Array:" << endl << brunArray << endl;
//    Brun Array:
//    1, 1/2, 2/3, 3/5, 4/7, 7/12

    auto pointMod = [](Point<float> inPoint, Point<float> octavePoint)
    {
        // x + y = column of the generator
        auto x = inPoint.getX();
        auto y = inPoint.getY();
        // ox + oy = column of the octave
        auto ox = octavePoint.getX();
        auto oy = octavePoint.getY();
        jassert(!isinf(x) && !isinf(y) && !isinf(ox) && !isinf(oy));
        jassert(!isnan(x) && !isnan(y) && !isnan(ox) && !isnan(oy));
        auto retVal = inPoint;
        if ((x + y) > (ox + oy))
        {
            retVal = inPoint - octavePoint;
        }
        else if ((x + y) < 0) // 0 is column of the origin
        {
            retVal = inPoint + octavePoint;
        }

        return retVal;
    };

    auto const vectorIndex = 0;
    auto generator_vectors = vector<Point<float>>{{4,3}, {1,3}, {1,2}, {1,1}, {0,1}, {0,1}};
    auto generator_vector = generator_vectors[vectorIndex];
    cout << "generator vector: " << generator_vector.toString() << endl;
    cout << "generator column: " << to_string(generator_vector.getX()+generator_vector.getY()) << endl;
    auto octave_vectors =    vector<Point<float>>{{7,5}, {2,5}, {2,3}, {2,1}, {1,1}, {1,0}};
    auto octave_vector = octave_vectors[vectorIndex];
    cout << "octave vector: " << octave_vector.toString() << endl;
    cout << "octave column: " << to_string(octave_vector.getX()+octave_vector.getY()) << endl;
    auto labels = vector<string> {"C","G","D","A","E","B","F#","Db","Ab","Eb","Bb","F"};
    auto labelIndex = 0;
    auto note_point = Point<float>(0,0);
    bool degreeFlippedToNegative = false;
    for (auto i = 0; i < npo; i++)
    {
        auto j = i;
        if (i <= npo_2) // positive degrees
        {
            if (i == 0)
            {
                // 0 degree = origin = (0,0)
                // NOP
            }
            else
            {
                note_point += generator_vector;
            }
            labelIndex = i;
        }
        else // negative degrees
        {
            if (!degreeFlippedToNegative)
            {
                degreeFlippedToNegative = true;
                note_point = octave_vector;
                labelIndex = npo - 1;
            }
            j = npo_2 - i;
            note_point -= generator_vector;
        }
        auto q = pointMod(note_point, octave_vector);
        cout << "label: " << labels[static_cast<unsigned long>(labelIndex)] << ", degree: " << to_string(j) << ", (" << note_point.toString() << ") ==> (" << q.toString() << ")" << endl;
        note_point = q;
        labelIndex--;
    }
}

void TuningTests::test_brun_gral_mapping()
{
    cout << endl << "test_brun_gral_mapping" << endl;

    auto b = Brun();
    auto const g = fmodf(log2f(3.f), 1.f);
    //auto const g = 1.f - fmodf(log2f(3.f), 1.f);
    //auto const g = 1.f - 0.238186f;
    auto const level = 5;
    b.setGenerator(g);
    b.setLevel(level);
    b.setMurchana(0);
    auto const npo = static_cast<int>(b.getNotesPerOctave());
    int const npo_2 = npo / 2;

    cout << endl << "generator: " << to_string(g) << ", level:" << to_string(level) << ", npo:" << to_string(npo) << ", npo_2:" << to_string(npo_2) << endl << endl;

    //    Brun Array:
    //    i.e., 1, 1/2, 2/3, 3/5, 4/7, 7/12
    auto brunArray = Brun::brunArray(level, g);
    cout << "Brun Array:" << endl << brunArray << endl;
    auto which_keyboard = 0UL;
    auto bac = brunArray.count() - which_keyboard; // i.e., the last term in the array, or next to last, ...
    jassert(bac >= 3);
    auto mt_0 = brunArray.microtoneAtIndex(bac - 1);
    auto mt_1 = brunArray.microtoneAtIndex(bac - 2);
    // freshman difference lol
    auto mt_2num = static_cast<unsigned long>(abs(static_cast<int>(mt_0->getNumerator()) - static_cast<int>(mt_1->getNumerator())));
    auto mt_2den = static_cast<unsigned long>(abs(static_cast<int>(mt_0->getDenominator()) - static_cast<int>(mt_1->getDenominator())));
    auto mt_2 = make_shared<Microtone>(mt_2num, mt_2den);
    cout << "mt_0: " << mt_0 << ", mt_1: " << mt_1 << ", mt_2: " << mt_2 << endl;
    auto keyboard_pt = Point<float>(static_cast<int>(mt_0->getNumerator()), static_cast<int>(mt_0->getDenominator()));
    // account for scale tree zig zag pattern
    Point<float> generator_vector, octave_vector;
    if (mt_2->getFrequencyValue() < mt_1->getFrequencyValue())
    {
        octave_vector = Point<float>(static_cast<int>(mt_2->getDenominator()), static_cast<int>(mt_1->getDenominator()));
        generator_vector = Point<float>(static_cast<int>(mt_2->getNumerator()), static_cast<int>(mt_1->getNumerator()));
    }
    else
    {
        octave_vector = Point<float>(static_cast<int>(mt_1->getDenominator()), static_cast<int>(mt_2->getDenominator()));
        generator_vector = Point<float>(static_cast<float>(mt_1->getNumerator()), static_cast<float>(mt_2->getNumerator()));
    }
    cout << "keyboard: " << keyboard_pt.toString() << endl;
    cout << "generator vector: " << generator_vector.toString() << endl;
    cout << "generator column: " << to_string(generator_vector.getX()+generator_vector.getY()) << endl;
    cout << "octave vector: " << octave_vector.toString() << endl;
    cout << "octave column: " << to_string(octave_vector.getX()+octave_vector.getY()) << endl;


    auto pointMod = [](Point<float> inPoint, Point<float> octavePoint)
    {
        // x + y = column of the generator
        auto x = inPoint.getX();
        auto y = inPoint.getY();
        // ox + oy = column of the octave
        auto ox = octavePoint.getX();
        auto oy = octavePoint.getY();
        jassert(!isinf(x) && !isinf(y) && !isinf(ox) && !isinf(oy));
        jassert(!isnan(x) && !isnan(y) && !isnan(ox) && !isnan(oy));
        auto retVal = inPoint;
        if ((x + y) > (ox + oy))
        {
            retVal = inPoint - octavePoint;
        }
        else if ((x + y) < 0) // 0 is column of the origin
        {
            retVal = inPoint + octavePoint;
        }

        return retVal;
    };

    // transform gral vector to hexagonal "odd-q vertical layout"
    auto xfmGral2Hex = [](Point<float> gralPoint)
    {
        return Point<float>(gralPoint.getX() + gralPoint.getY(), truncf(0.5f * gralPoint.getX() - 0.5f * gralPoint.getY()));
    };

    auto note_point = Point<float>(0, 0);
    bool degreeFlippedToNegative = false;
    for (auto i = 0; i < npo; i++)
    {
        auto j = i;
        if (i <= npo_2) // positive degrees
        {
            if (i == 0)
            {
                // 0 degree = origin = (0,0)
                // NOP
            }
            else
            {
                note_point += generator_vector;
            }
        }
        else // negative degrees
        {
            if (!degreeFlippedToNegative)
            {
                degreeFlippedToNegative = true;
                note_point = octave_vector;
            }
            j = npo_2 - i;
            note_point -= generator_vector;
        }
        auto q = pointMod(note_point, octave_vector);
        auto hex_point = xfmGral2Hex(q);
        cout << "degree: " << to_string(j) << ", (" << note_point.toString() << ") ==> (" << q.toString() << "), hex_point: (" << hex_point.toString() << ")" << endl;
        note_point = q;
    }
}
