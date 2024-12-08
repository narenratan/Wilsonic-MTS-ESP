/*
  ==============================================================================

    TuningTests+CPS_DAW_Automation.cpp
    Created: 25 Nov 2021 4:39:51pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "TuningTests.h"
#include "EulerGenus_6.h"
#include "CPS_4_1.h"
#include "CPS_4_2.h"
#include "CPS_4_3.h"
#include "CPS_4_4.h"
#include "CPS_6_1.h"
#include "CPS_6_2.h"
#include "CPS_6_3.h"
#include "CPS_6_4.h"
#include "CPS_6_5.h"
#include "CPS_6_6.h"

#pragma mark - Euler Genus 4

void TuningTests::testCPS_4_1_DAW_Automation()
{
    // Test EulerGenus_4
    cout << "BEGIN TEST: testCPS_4_1_DAW_Automation() ---------------------\n\n";

    // construct
    //cout << "CPS_4_1 constructor:-----------------\n";
    //auto time = logRelativeTime ("start", nullptr);

    // root
    auto cps_4_1 = make_shared<CPS_4_1> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126));
    cps_4_1->setShouldComputeSubsets (true);
    cps_4_1->update();
    //time  = logRelativeTime ("constructor complete", time);

    // recursively walk this cps
    //walkCPSTuningBase (cps_4_1);
    //walkCPSTuningBase2 (cps_4_1);
    //walkCPSTuningBase3 (cps_4_1, "");
    //walkCPSTuningBase4 (cps_4_1, "EulerGenus6");
    //walkCPSTuningBase5 (cps_4_1, "EulerGenus4");
    //walkCPSTuningBase6 (cps_4_1, "EulerGenus4");
    walkCPSTuningBase7 (cps_4_1, "EulerGenus4");

    //
    cout << "END TEST: testCPS_4_1_DAW_Automation() ---------------------\n\n";
}

void TuningTests::testCPS_4_2_DAW_Automation()
{
    // Test EulerGenus_4
    cout << "BEGIN TEST: testCPS_4_2_DAW_Automation() ---------------------\n\n";

    // construct
    //cout << "CPS_4_2 constructor:-----------------\n";
    //auto time = logRelativeTime ("start", nullptr);

    // root
    auto cps_4_2 = make_shared<CPS_4_2> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126));
    cps_4_2->setShouldComputeSubsets (true);
    cps_4_2->update();
    //time  = logRelativeTime ("constructor complete", time);

    // recursively walk this cps
    //walkCPSTuningBase (cps_4_2);
    //walkCPSTuningBase2 (cps_4_2);
    //walkCPSTuningBase3 (cps_4_2, "");
    //walkCPSTuningBase4 (cps_4_2, "EulerGenus6");
    //walkCPSTuningBase5 (cps_4_2, "EulerGenus4");
    //walkCPSTuningBase6 (cps_4_2, "EulerGenus4");
    walkCPSTuningBase7 (cps_4_2, "EulerGenus4");

    //
    cout << "END TEST: testCPS_4_2_DAW_Automation() ---------------------\n\n";
}

void TuningTests::testCPS_4_3_DAW_Automation()
{
    // Test EulerGenus_4
    cout << "BEGIN TEST: testCPS_4_3_DAW_Automation() ---------------------\n\n";

    // construct
    //cout << "CPS_4_3 constructor:-----------------\n";
    //auto time = logRelativeTime ("start", nullptr);

    // root
    auto cps_4_3 = make_shared<CPS_4_3> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126));
    cps_4_3->setShouldComputeSubsets (true);
    cps_4_3->update();
    //time  = logRelativeTime ("constructor complete", time);

    // recursively walk this cps
    //walkCPSTuningBase (cps_4_3);
    //walkCPSTuningBase2 (cps_4_3);
    //walkCPSTuningBase3 (cps_4_3, "");
    //walkCPSTuningBase4 (cps_4_3, "EulerGenus6");
    //walkCPSTuningBase5 (cps_4_3, "EulerGenus4");
    //walkCPSTuningBase6 (cps_4_3, "EulerGenus4");
    walkCPSTuningBase7 (cps_4_3, "EulerGenus4");

    //
    cout << "END TEST: testCPS_4_3_DAW_Automation() ---------------------\n\n";
}

void TuningTests::testCPS_4_4_DAW_Automation()
{
    // Test EulerGenus_4
    cout << "BEGIN TEST: testCPS_4_4_DAW_Automation() ---------------------\n\n";

    // construct
    //cout << "CPS_4_4 constructor:-----------------\n";
    //auto time = logRelativeTime ("start", nullptr);

    // root
    auto cps_4_4 = make_shared<CPS_4_4> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126));
    cps_4_4->setShouldComputeSubsets (true);
    cps_4_4->update();
    //time  = logRelativeTime ("constructor complete", time);

    // recursively walk this cps
    //walkCPSTuningBase (cps_4_4);
    //walkCPSTuningBase2 (cps_4_4);
    //walkCPSTuningBase3 (cps_4_4, "");
    //walkCPSTuningBase4 (cps_4_4, "EulerGenus6");
    //walkCPSTuningBase5 (cps_4_4, "EulerGenus4");
    //walkCPSTuningBase6 (cps_4_4, "EulerGenus4");
    walkCPSTuningBase7 (cps_4_4, "EulerGenus4");

    //
    cout << "END TEST: testCPS_4_4_DAW_Automation() ---------------------\n\n";
}

#pragma mark - Euler Genus 6

void TuningTests::testEulerGenus6_DAW_Automation()
{
    // Test EulerGenus_1
    cout << "BEGIN TEST: testEulerGenus6_DAW_Automation() ---------------------\n\n";

    auto euler_genus_6 = make_shared<EulerGenus_6> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126), CPS::E (127), CPS::F (128));

    euler_genus_6->setShouldComputeSubsets (true);
    //euler_genus_6->CPSTuningBase::update();
//    walkCPSTuningBase5 (euler_genus_6, "EulerGenus6");
//    walkCPSTuningBase6 (euler_genus_6, "");
    walkCPSTuningBase7 (euler_genus_6, "");

    //
//    testCPS_6_1_DAW_Automation();
//    testCPS_6_2_DAW_Automation();
//    testCPS_6_3_DAW_Automation();
//    testCPS_6_4_DAW_Automation();
//    testCPS_6_5_DAW_Automation();
//    testCPS_6_6_DAW_Automation();

    //
    cout << "END TEST: testEulerGenus6_DAW_Automation() ---------------------\n\n";
}

#pragma mark - CPS_6_k

void TuningTests::testCPS_6_1_DAW_Automation()
{
    // Test EulerGenus_1
    cout << "BEGIN TEST: testCPS_6_1_DAW_Automation() ---------------------\n\n";

    // construct
    //cout << "CPS_6_1 constructor:-----------------\n";
    //auto time = logRelativeTime ("start", nullptr);

    // root
    auto cps_6_1 = make_shared<CPS_6_1> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126), CPS::E (127), CPS::F (128));
    cps_6_1->setShouldComputeSubsets (true);
    cps_6_1->update();
    //time  = logRelativeTime ("constructor complete", time);

    // recursively walk this cps
    //walkCPSTuningBase (cps_6_1);
    //walkCPSTuningBase2 (cps_6_1);
    //walkCPSTuningBase3 (cps_6_1, "");
    //walkCPSTuningBase4 (cps_6_1, "EulerGenus6");
    //walkCPSTuningBase5 (cps_6_1, "EulerGenus6");
    //walkCPSTuningBase6 (cps_6_1, "EulerGenus6");
    walkCPSTuningBase7 (cps_6_1, "EulerGenus6");

    //
    cout << "END TEST: testCPS_6_1_DAW_Automation() ---------------------\n\n";
}

void TuningTests::testCPS_6_2_DAW_Automation()
{
    // Test EulerGenus_1
    cout << "BEGIN TEST: testCPS_6_2_DAW_Automation() ---------------------\n\n";

    // construct
    //cout << "CPS_6_2 constructor:-----------------\n";
    //auto time = logRelativeTime ("start", nullptr);

    // root
    auto cps_6_2 = make_shared<CPS_6_2> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126), CPS::E (127), CPS::F (128));
    cps_6_2->setShouldComputeSubsets (true);
    cps_6_2->update();
    //time  = logRelativeTime ("constructor complete", time);

    // recursively walk this cps
    //walkCPSTuningBase (cps_6_2);
    //walkCPSTuningBase2 (cps_6_2);
    //walkCPSTuningBase3 (cps_6_2, "");
    //walkCPSTuningBase4 (cps_6_2, "EulerGenus6");
    //walkCPSTuningBase5 (cps_6_2, "EulerGenus6");
    //walkCPSTuningBase6 (cps_6_2, "EulerGenus6");
    walkCPSTuningBase7 (cps_6_2, "EulerGenus6");

    //
    cout << "END TEST: testCPS_6_2_DAW_Automation() ---------------------\n\n";
}

void TuningTests::testCPS_6_3_DAW_Automation()
{
    // Test EulerGenus_1
    cout << "BEGIN TEST: testCPS_6_3_DAW_Automation() ---------------------\n\n";

    // construct
    //cout << "CPS_6_3 constructor:-----------------\n";
    //auto time = logRelativeTime ("start", nullptr);

    // root
    auto cps_6_3 = make_shared<CPS_6_3> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126), CPS::E (127), CPS::F (128));
    cps_6_3->setShouldComputeSubsets (true);
    cps_6_3->update();
    //time  = logRelativeTime ("constructor complete", time);

    // recursively walk this cps
    //walkCPSTuningBase (cps_6_3);
    //walkCPSTuningBase2 (cps_6_3);
    //walkCPSTuningBase3 (cps_6_3, "");
    //walkCPSTuningBase4 (cps_6_3, "EulerGenus6");
    //walkCPSTuningBase5 (cps_6_3, "EulerGenus6");
    //walkCPSTuningBase6 (cps_6_3, "EulerGenus6 [selection]");
    //walkCPSTuningBase7 (cps_6_3, "EulerGenus6 [selection]");
    walkCPSTuningBase8 (cps_6_3, "EulerGenus6 [selection]");

    //
    cout << "END TEST: testCPS_6_3_DAW_Automation() ---------------------\n\n";
}

void TuningTests::testCPS_6_4_DAW_Automation()
{
    // Test EulerGenus_1
    cout << "BEGIN TEST: testCPS_6_4_DAW_Automation() ---------------------\n\n";

    // construct
    //cout << "CPS_6_4 constructor:-----------------\n";
    //auto time = logRelativeTime ("start", nullptr);

    // root
    auto cps_6_4 = make_shared<CPS_6_4> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126), CPS::E (127), CPS::F (128));

    cps_6_4->setShouldComputeSubsets (true);
    cps_6_4->update();
    //time  = logRelativeTime ("constructor complete", time);

    // recursively walk this cps
    //walkCPSTuningBase (cps_6_4);
    //walkCPSTuningBase2 (cps_6_4);
    //walkCPSTuningBase3 (cps_6_4, "");
    //walkCPSTuningBase4 (cps_6_4, "EulerGenus6");
    //walkCPSTuningBase5 (cps_6_4, "EulerGenus6");
    //walkCPSTuningBase6 (cps_6_4, "EulerGenus6");
    //walkCPSTuningBase7 (cps_6_4, "EulerGenus6");
    walkCPSTuningBase8 (cps_6_4, "EulerGenus6");

    //
    cout << "END TEST: testCPS_6_4_DAW_Automation() ---------------------\n\n";
}

void TuningTests::testCPS_6_5_DAW_Automation()
{
    // Test EulerGenus_1
    cout << "BEGIN TEST: testCPS_6_5_DAW_Automation() ---------------------\n\n";

    // construct
    //cout << "CPS_6_5 constructor:-----------------\n";
    //auto time = logRelativeTime ("start", nullptr);

    // root
    auto cps_6_5 = make_shared<CPS_6_5> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126), CPS::E (127), CPS::F (128));
    cps_6_5->setShouldComputeSubsets (true);
    cps_6_5->update();
    //time  = logRelativeTime ("constructor complete", time);

    // recursively walk this cps
    //walkCPSTuningBase (cps_6_5);
    //walkCPSTuningBase2 (cps_6_5);
    //walkCPSTuningBase3 (cps_6_5, "");
    //walkCPSTuningBase4 (cps_6_5, "EulerGenus6");
    //walkCPSTuningBase5 (cps_6_5, "EulerGenus6");
    //walkCPSTuningBase6 (cps_6_5, "EulerGenus6");
    //walkCPSTuningBase7 (cps_6_5, "EulerGenus6");
    walkCPSTuningBase8 (cps_6_5, "EulerGenus6");

    //
    cout << "END TEST: testCPS_6_5_DAW_Automation() ---------------------\n\n";
}

// TODO: no subsets = terminal condition
void TuningTests::testCPS_6_6_DAW_Automation()
{
    // Test EulerGenus_1
    cout << "BEGIN TEST: testCPS_6_6_DAW_Automation() ---------------------\n\n";

    // construct
    //cout << "CPS_6_6 constructor:-----------------\n";
    //auto time = logRelativeTime ("start", nullptr);

    // root
    auto cps_6_6 = make_shared<CPS_6_6> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126), CPS::E (127), CPS::F (128));
    cps_6_6->setShouldComputeSubsets (true);
    cps_6_6->update();
    //time  = logRelativeTime ("constructor complete", time);

    // recursively walk this cps
    //walkCPSTuningBase (cps_6_6);
    //walkCPSTuningBase2 (cps_6_6);
    //walkCPSTuningBase3 (cps_6_6, "");
    //walkCPSTuningBase4 (cps_6_6, "EulerGenus6");
    //walkCPSTuningBase5 (cps_6_6, "EulerGenus6");
    //walkCPSTuningBase6 (cps_6_6, "EulerGenus6");
    //walkCPSTuningBase7 (cps_6_6, "EulerGenus6");
    walkCPSTuningBase8 (cps_6_6, "EulerGenus6");

    //
    cout << "END TEST: testCPS_6_6_DAW_Automation() ---------------------\n\n";
}

#pragma mark - recursive subsets: filtering and logging variants

// recursively prints tuning description and it's subsets
void TuningTests::walkCPSTuningBase (shared_ptr<CPSTuningBase> cpst)
{
    // no lazy loading
    cpst->setShouldComputeSubsets (true);
    cpst->update();

    // log
    cout << cpst->getTuningName() << endl;

    // the recursive terminal conditions are the empty subsets

    for (auto cpsts0 : cpst->getSubsets0())
    {
        TuningTests::walkCPSTuningBase (cpsts0);
    }
    for (auto cpsts1 : cpst->getSubsets1())
    {
        TuningTests::walkCPSTuningBase (cpsts1);
    }

}

// variant in print format
void TuningTests::walkCPSTuningBase2 (shared_ptr<CPSTuningBase> cpst)
{
    // no lazy loading
    cpst->setShouldComputeSubsets (true);
    cpst->update();

    // log
    //cout << cpst->getTuningName() << endl;
    cout << cpst->getTuningNameAsSymbols() << endl;

    //
    cout << "\tSubsets 0:" << endl;
    for (auto cpsts0 : cpst->getSubsets0())
    {
        //cout << "\t" << cpsts0->getTuningName() << endl;
        cout << "\t" << cpsts0->getTuningNameAsSymbols() << endl;
    }
    cout << "\tSubsets 1:" << endl;
    for (auto cpsts1 : cpst->getSubsets1())
    {
        //cout << "\t" << cpsts1->getTuningName() << endl;
        cout << "\t" << cpsts1->getTuningNameAsSymbols() << endl;
    }

    cout << endl;

    // the recursive terminal conditions are the empty subsets

    for (auto cpsts0 : cpst->getSubsets0())
    {
        TuningTests::walkCPSTuningBase2 (cpsts0);
    }
    for (auto cpsts1 : cpst->getSubsets1())
    {
        TuningTests::walkCPSTuningBase2 (cpsts1);
    }

}

// variant in print format...tabbing per level
void TuningTests::walkCPSTuningBase3 (shared_ptr<CPSTuningBase> cpst, const string in_tab)
{
    auto out_tab = in_tab + "\t";

    // no lazy loading
    cpst->setShouldComputeSubsets (true);
    cpst->update();

    // if not subsets: return
    if (cpst->getSubsets0().size() == 0 && cpst->getSubsets1().size() == 0)
    {
        return;
    }

    // log
    cout << cpst->getTuningNameAsSymbols() << endl;

    //
    cout << out_tab << "Subsets 0:" << endl;
    for (auto cpsts0 : cpst->getSubsets0())
    {
        cout << out_tab << cpsts0->getTuningNameAsSymbols() << endl;
    }
    cout << out_tab << "Subsets 1:" << endl;
    for (auto cpsts1 : cpst->getSubsets1())
    {
        cout << out_tab << cpsts1->getTuningNameAsSymbols() << endl;
    }

    cout << endl;

    // the recursive terminal conditions are the empty subsets

    for (auto cpsts0 : cpst->getSubsets0())
    {
        TuningTests::walkCPSTuningBase3 (cpsts0, out_tab);
    }
    for (auto cpsts1 : cpst->getSubsets1())
    {
        TuningTests::walkCPSTuningBase3 (cpsts1, out_tab);
    }

}

// variant in print format: print one row per UI state including selection, and back index
void TuningTests::walkCPSTuningBase4 (shared_ptr<CPSTuningBase> cpst, const string back)
{
    // no lazy loading
    cpst->setShouldComputeSubsets (true);
    cpst->update();

    // terminanl condition: no subsets
    if (cpst->getSubsets0().size() == 0 && cpst->getSubsets1().size() == 0)
    {
        return;
    }

    auto logp = [](string tuning, string back_string)
    {
        cout << tuning << ", " << back_string << endl;
    };

    // print this tuning and it's subsets
    auto subset_back = cpst->getTuningNameAsSymbols(); // i.e., this root tuning is the "back" for the subsets
    logp (subset_back, back);

    // print subsets and back
    for (auto cpsts0 : cpst->getSubsets0())
    {
        logp (cpsts0->getTuningNameAsSymbols(), subset_back);
    }
    for (auto cpsts1 : cpst->getSubsets1())
    {
        logp (cpsts1->getTuningNameAsSymbols(), subset_back);
    }

    // the recursive terminal conditions are the empty subsets
    for (auto cpsts0 : cpst->getSubsets0())
    {
        //TuningTests::walkCPSTuningBase4 (cpsts0, cpsts0->getTuningNameAsSymbols());
        TuningTests::walkCPSTuningBase4 (cpsts0, subset_back);
    }
    for (auto cpsts1 : cpst->getSubsets1())
    {
        //TuningTests::walkCPSTuningBase4 (cpsts1, cpsts1->getTuningNameAsSymbols());
        TuningTests::walkCPSTuningBase4 (cpsts1, subset_back);
    }
}

// variant in print format: print one row per UI state including selection, and back index, modifying keys to be unambiguous root and selection state
void TuningTests::walkCPSTuningBase5 (shared_ptr<CPSTuningBase> cpst, const string back)
{
    // no lazy loading
    cpst->setShouldComputeSubsets (true);
    cpst->update();

    // terminal condition: no subsets
    if (cpst->getSubsets0().size() == 0 && cpst->getSubsets1().size() == 0)
    {
        return;
    }

    auto logp = [](string tuning_name, string select_tuning_name, string back_tuning_name)
    {
        cout <<
        "selected: " << tuning_name <<
        ", drill: " << select_tuning_name <<
        ", back: " << back_tuning_name <<
        endl;
    };

    // print this tuning and it's subsets
    // i.e., this root tuning is the "back" for the subsets
    auto this_tuning_name = cpst->getTuningNameAsSymbols();
    logp (this_tuning_name + ":" + this_tuning_name + ":root",
          this_tuning_name + ":" + this_tuning_name + ":root",
          back + ":" + this_tuning_name);

    // print subsets and back
    // "back" equals parent, selected.  Only the parent can have a back with a new parent
    int index = 0;
    for (auto cpsts0 : cpst->getSubsets0())
    {
        auto selection_name = cpsts0->getTuningNameAsSymbols();
        logp (this_tuning_name + ":" + selection_name + ":s0[" + to_string(index) + "]",
              selection_name + ":" + selection_name + ":root",
              this_tuning_name + ":" + this_tuning_name + ":root");
        index++;
    }
    index = 0;
    for (auto cpsts1 : cpst->getSubsets1())
    {
        auto selection_name = cpsts1->getTuningNameAsSymbols();
        logp (this_tuning_name + ":" + selection_name + ":s1[" + to_string(index) + "]",
              selection_name + ":" + selection_name + ":root",
              this_tuning_name + ":" + this_tuning_name + ":root");
        index++;
    }

    // the recursive terminal conditions are the empty subsets
    for (auto cpsts0 : cpst->getSubsets0())
    {
        TuningTests::walkCPSTuningBase5 (cpsts0, this_tuning_name);
    }
    for (auto cpsts1 : cpst->getSubsets1())
    {
        TuningTests::walkCPSTuningBase5 (cpsts1, this_tuning_name);
    }
}

// NOW: pseudocode to execute this tree of computation
// variant in print format: print one row per UI state including selection, and back index, modifying keys to be unambiguous root and selection state
void TuningTests::walkCPSTuningBase6 (shared_ptr<CPSTuningBase> cpst, const string )
{
    // no lazy loading
    cpst->setShouldComputeSubsets (true);
    cpst->update();

    // terminal condition: no subsets
    if (cpst->getSubsets0().size() == 0 && cpst->getSubsets1().size() == 0)
    {
        return;
    }

    auto logp = [](string tuning_name, string , string )
    {
        cout <<
        tuning_name <<
        endl;
    };
    auto this_tuning_name = cpst->getTuningNameAsSymbols();
    logp (this_tuning_name, "", "");

    // the recursive terminal conditions are the empty subsets
    for (auto cpsts0 : cpst->getSubsets0())
    {
        TuningTests::walkCPSTuningBase6 (cpsts0, this_tuning_name);
    }
    for (auto cpsts1 : cpst->getSubsets1())
    {
        TuningTests::walkCPSTuningBase6 (cpsts1, this_tuning_name);
    }
}

// variant in print format: print one row per UI state including selection, and back index, modifying keys to be unambiguous root and selection state
void TuningTests::walkCPSTuningBase7 (shared_ptr<CPSTuningBase> cpst, const string back)
{
    // no lazy loading, order is important
    cpst->setShouldComputeSubsets (true);
    cpst->update();

    // terminal condition: no subsets
    if (cpst->getSubsets0().size() == 0 && cpst->getSubsets1().size() == 0)
    {
        return;
    }

    // logger
    auto logp = [&](string daw_key, string tuning_key, string daw_select_key, string daw_back_key)
    {
        cout <<
        "daw_key: " << daw_key <<
        ", tuning_key: " << tuning_key <<
        ", select_key: " << daw_select_key <<
        ", back_key: " << daw_back_key <<
        endl;
    };

    // print this tuning and it's subsets
    // i.e., this root tuning is the "back" for the subsets
    auto this_tuning_name = cpst->getTuningNameAsSymbols();
    logp (this_tuning_name + ":" + this_tuning_name + ":root",
          this_tuning_name,
          this_tuning_name + ":" + this_tuning_name + ":root",
          back + ":" + this_tuning_name);

    // print subsets and back
    // "back" equals parent, selected.  Only the parent can have a back with a new parent
    int index = 0;
    for (auto cpsts0 : cpst->getSubsets0())
    {
        auto selection_name = cpsts0->getTuningNameAsSymbols();
        logp (this_tuning_name + ":" + selection_name + ":s0[" + to_string(index) + "]",
              this_tuning_name,
              selection_name + ":" + selection_name + ":root",
              this_tuning_name + ":" + this_tuning_name + ":root");
        index++;
    }
    index = 0;
    for (auto cpsts1 : cpst->getSubsets1())
    {
        auto selection_name = cpsts1->getTuningNameAsSymbols();
        logp (this_tuning_name + ":" + selection_name + ":s1[" + to_string(index) + "]",
              this_tuning_name,
              selection_name + ":" + selection_name + ":root",
              this_tuning_name + ":" + this_tuning_name + ":root");
        index++;
    }

    cout << "-----------" << endl;

    // the recursive terminal conditions are the empty subsets
    for (auto cpsts0 : cpst->getSubsets0())
    {
        TuningTests::walkCPSTuningBase7 (cpsts0, this_tuning_name);
    }
    for (auto cpsts1 : cpst->getSubsets1())
    {
        TuningTests::walkCPSTuningBase7 (cpsts1, this_tuning_name);
    }
}

// variant in print format: print one row per UI state including selection, and back index, modifying keys to be unambiguous root and selection state
void TuningTests::walkCPSTuningBase8 (shared_ptr<CPSTuningBase> cpst, const string back)
{
    // no lazy loading, order is important
    cpst->setShouldComputeSubsets (true);
    cpst->update();

    // terminal condition: no subsets
    if (cpst->getSubsets0().size() == 0 && cpst->getSubsets1().size() == 0)
    {
        return;
    }

    // logger
    auto logp = [&](string daw_key, string tuning_key, string daw_select_key, string daw_back_key)
    {
        cout <<
        "daw_key: " << daw_key << endl <<
        "tuning_key: " << tuning_key << endl <<
        "select_key: " << daw_select_key << endl <<
        "back_key: " << daw_back_key << endl <<
        endl;
    };

    // print this tuning and it's subsets
    // i.e., this root tuning is the "back" for the subsets
    auto this_tuning_name = cpst->getTuningNameAsUnderscores();
    logp (this_tuning_name + "__" + this_tuning_name,
          this_tuning_name,
          this_tuning_name + "__" + this_tuning_name,
          back + "__" + this_tuning_name);

    // print subsets and back
    // "back" equals parent, selected.  Only the parent can have a back with a new parent
    int index = 0;
    for (auto cpsts0 : cpst->getSubsets0())
    {
        auto selection_name = cpsts0->getTuningNameAsUnderscores();
        logp (this_tuning_name + "__" + selection_name + "\n:s0[" + to_string(index) + "]",
              this_tuning_name,
              selection_name + "__" + selection_name,
              this_tuning_name + "__" + this_tuning_name);
        index++;
    }
    index = 0;
    for (auto cpsts1 : cpst->getSubsets1())
    {
        auto selection_name = cpsts1->getTuningNameAsUnderscores();
        logp (this_tuning_name + "__" + selection_name + "\n:s1[" + to_string(index) + "]",
              this_tuning_name,
              selection_name + "__" + selection_name,
              this_tuning_name + "__" + this_tuning_name);
        index++;
    }

    cout << "-----------" << endl;

    // the recursive terminal conditions are the empty subsets
    for (auto cpsts0 : cpst->getSubsets0())
    {
        TuningTests::walkCPSTuningBase8 (cpsts0, this_tuning_name);
    }
    for (auto cpsts1 : cpst->getSubsets1())
    {
        TuningTests::walkCPSTuningBase8 (cpsts1, this_tuning_name);
    }
}
