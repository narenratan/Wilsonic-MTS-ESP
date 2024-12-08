/*
 ==============================================================================
 
 TuningTests+Diamonds.cpp
 Created: 9 Jun 2023 8:07:54am
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "TuningTests.h"

// codegen actually
void TuningTests::testDiamonds()
{
    auto const terms = StringArray("A","B","C","D","E","F","G","H");
    String u = "_";
    String gfv = "->getFrequencyValue()";
    
    // _commonConstructorHelper()
    DBG ("commonConstructorHelper");
    for (auto& A : terms)
    {
        for (auto& B : terms)
        {
            if (A == B)
            {
                continue;
            }
            //     _A_B = CPSMicrotone_t::create (CPS::A_div_B (CPS::A (_A->getFrequencyValue()), CPS::B (_B->getFrequencyValue())), hpc (x1, y2));
            // _A_B =
            String r = u + A + u + B + " = ";
            
            // CPSMicrotone_t::create (CPS::A_div_B (CPS::A
            r += "CPSMicrotone_t::create (CPS::A_div_B (CPS::" + A + " (";
            
            //  (_A->getFrequencyValue()),
            r += "_" + A + gfv + "),";
            
            //  CPS::B (_B->getFrequencyValue())),
            r += " CPS::" + B + " (_" + B + gfv + ")), ";
            
            //  hpc (x1, y2));
            r += "hpc (x_, y_));";
            
            DBG (r);
        }
    }
    
#if 0
    
    //     _masterPtArray.push_back (_F_E);
    for (auto& A : terms)
    {
        for (auto& B : terms)
        {
            if (A == B)
            {
                continue;
            }
            String r = "_masterPtArray.push_back (" + u + A + u + B + ");";
            DBG (r);
        }
    }
    
    //    _labelArray.push_back (_C_B);
    for (auto& A : terms)
    {
        for (auto& B : terms)
        {
            if (A == B)
            {
                continue;
            }
            String r = "_labelArray.push_back (" + u + A + u + B + ");";
            DBG (r);
        }
    }
#endif
    
    
    // update()
    DBG ("");
    DBG ("update()");
    for (auto& A : terms)
    {
        for (auto& B : terms)
        {
            if (A == B)
            {
                continue;
            }
            //    _A_B->mt  = CPS::A_div_B (CPS::A (_A->getFrequencyValue()), CPS::B (_B->getFrequencyValue()));
            
            String r = u + A + u + B + "->mt  = CPS::A_div_B (CPS::" + A + " (" + u + A + gfv + "), CPS::" + B + " (" + u + B + gfv + "));";
            DBG (r);
        }
    }
    DBG("");
    
    
    //auto ma = MicrotoneArray();
    DBG ("auto ma = MicrotoneArray();");
    DBG ("ma.addMicrotone (_one->mt);");
    for (auto& A : terms)
    {
        for (auto& B : terms)
        {
            if (A == B)
            {
                continue;
            }
            String r = "ma.addMicrotone (_" + A + u + B + "->mt);";
            DBG (r);
        }
    }
    
#if 0
    // subsets block 3
    DBG ("");
    String setABCDEFGH = "setABC";
    int ssi = 0;
    for (int a = 0; a < terms.size(); a++)
    {
        auto& A = terms[a];
        for (int b = 0; b < terms.size(); b++)
        {
            auto& B = terms[b];
            auto& C = terms[(b+1)%terms.size()];
            if (A == B || A == C || B == C) // 3
            {
                continue;
            }
            String h = "   _harmonic_subset_" + String(ssi) + "->" + setABCDEFGH + " (_one->mt, " + u + B + u + A + "->mt, " + u + C + u + A + "->mt);";
            DBG (h);
            String s = "_subharmonic_subset_" + String(ssi) + "->" + setABCDEFGH + " (_one->mt, " + u + A + u + B + "->mt, " + u + A + u + C + "->mt);";
            DBG (s);
            
            ssi++;
            DBG ("");
        }
    }
    
    // subsets block 4
    DBG ("");
    String setABCDEFGH = "setABCD";
    int ssi = 0;
    for (int a = 0; a < terms.size(); a++)
    {
        auto& A = terms[a];
        for (int b = 0; b < terms.size(); b++)
        {
            auto& B = terms[b];
            auto& C = terms[(b+1)%terms.size()];
            auto& D = terms[(b+2)%terms.size()];
            if (A == B || A == C || A == D || B == C || B == D || C == D) // 4
            {
                continue;
            }
            String h = "   _harmonic_subset_" + String(ssi) + "->" + setABCDEFGH + " (_one->mt, " + u + B + u + A + "->mt, " + u + C + u + A + "->mt, " + u + D + u + A + "->mt);";
            DBG (h);
            String s = "_subharmonic_subset_" + String(ssi) + "->" + setABCDEFGH + " (_one->mt, " + u + A + u + B + "->mt, " + u + A + u + C + "->mt, " + u + A + u + D + "->mt);";
            DBG (s);
            
            ssi++;
            DBG ("");
        }
    }
#endif
    
#if 0
    // subsets block 5
    DBG ("");
    String setABCDEFGH = "setABCDE";
    int ssi = 0;
    for (int a = 0; a < terms.size(); a++)
    {
        auto& A = terms[a];
        for (int b = 0; b < terms.size(); b++)
        {
            auto& B = terms[b];
            auto& C = terms[(b+1)%terms.size()];
            auto& D = terms[(b+2)%terms.size()];
            auto& E = terms[(b+3)%terms.size()];
            if (A == B || A == C || A == D || A == E ||
                B == C || B == D || B == E ||
                C == D || C == E ||
                D == E) // 5
            {
                continue;
            }
            String h = "   _harmonic_subset_" + String(ssi) + "->" + setABCDEFGH + " (_one->mt, " + u + B + u + A + "->mt, " + u + C + u + A + "->mt, " + u + D + u + A + "->mt, " + u + E + u + A + "->mt);";
            DBG (h);
            String s = "_subharmonic_subset_" + String(ssi) + "->" + setABCDEFGH + " (_one->mt, " + u + A + u + B + "->mt, " + u + A + u + C + "->mt, " + u + A + u + D + "->mt, " + u + A + u + E +  "->mt);";
            DBG (s);
            
            ssi++;
            DBG ("");
        }
    }
#endif
    
#if 0
    // subsets block 6
    DBG ("");
    String setABCDEFGH = "setABCDEF";
    int ssi = 0;
    for (int a = 0; a < terms.size(); a++)
    {
        auto& A = terms[a];
        for (int b = 0; b < terms.size(); b++)
        {
            auto& B = terms[b];
            auto& C = terms[(b+1)%terms.size()];
            auto& D = terms[(b+2)%terms.size()];
            auto& E = terms[(b+3)%terms.size()];
            auto& F = terms[(b+4)%terms.size()];
            if (A == B || A == C || A == D || A == E || A == F ||
                B == C || B == D || B == E || B == F ||
                C == D || C == E || C == F ||
                D == E || D == F ||
                E == F) // 6
            {
                continue;
            }
            String h = "   _harmonic_subset_" + String(ssi) + "->" + setABCDEFGH + " (_one->mt, "
            + u + B + u + A + "->mt, "
            + u + C + u + A + "->mt, "
            + u + D + u + A + "->mt, "
            + u + E + u + A + "->mt, "
            + u + F + u + A + "->mt);";
            DBG (h);
            String s = "_subharmonic_subset_" + String(ssi) + "->" + setABCDEFGH + " (_one->mt, "
            + u + A + u + B + "->mt, "
            + u + A + u + C + "->mt, "
            + u + A + u + D + "->mt, "
            + u + A + u + E + "->mt, "
            + u + A + u + F + "->mt);";
            DBG (s);
            
            ssi++;
            DBG ("");
        }
    }
#endif
    
    
#if 0
    // subsets block 7
    DBG ("");
    String setABCDEFGH = "setABCDEFG";
    int ssi = 0;
    for (int a = 0; a < terms.size(); a++)
    {
        auto& A = terms[a];
        for (int b = 0; b < terms.size(); b++)
        {
            auto& B = terms[b];
            auto& C = terms[(b+1)%terms.size()];
            auto& D = terms[(b+2)%terms.size()];
            auto& E = terms[(b+3)%terms.size()];
            auto& F = terms[(b+4)%terms.size()];
            auto& G = terms[(b+5)%terms.size()];
            if (A == B || A == C || A == D || A == E || A == F || A == G ||
                B == C || B == D || B == E || B == F || B == G ||
                C == D || C == E || C == F || C == G ||
                D == E || D == F || D == G ||
                E == F || E == G ||
                F == G ) // 7
            {
                continue;
            }
            String h = "   _harmonic_subset_" + String(ssi) + "->" + setABCDEFGH + " (_one->mt, "
            + u + B + u + A + "->mt, "
            + u + C + u + A + "->mt, "
            + u + D + u + A + "->mt, "
            + u + E + u + A + "->mt, "
            + u + F + u + A + "->mt, "
            + u + G + u + A + "->mt);";
            DBG (h);
            String s = "_subharmonic_subset_" + String(ssi) + "->" + setABCDEFGH + " (_one->mt, "
            + u + A + u + B + "->mt, "
            + u + A + u + C + "->mt, "
            + u + A + u + D + "->mt, "
            + u + A + u + E + "->mt, "
            + u + A + u + F + "->mt, "
            + u + A + u + G + "->mt);";
            DBG (s);
            
            ssi++;
            DBG ("");
        }
    }
#endif
    
#if 1
    // subsets block 8
    DBG ("");
    String setABCDEFGH = "setABCDEFGH";
    int ssi = 0;
    for (int a = 0; a < terms.size(); a++)
    {
        auto& A = terms[a];
        for (int b = 0; b < terms.size(); b++)
        {
            auto& B = terms[b];
            auto& C = terms[(b+1)%terms.size()];
            auto& D = terms[(b+2)%terms.size()];
            auto& E = terms[(b+3)%terms.size()];
            auto& F = terms[(b+4)%terms.size()];
            auto& G = terms[(b+5)%terms.size()];
            auto& H = terms[(b+6)%terms.size()];
            if (A == B || A == C || A == D || A == E || A == F || A == G || A== H ||
                B == C || B == D || B == E || B == F || B == G || B == H ||
                C == D || C == E || C == F || C == G || C == H ||
                D == E || D == F || D == G || D == H ||
                E == F || E == G || E == H ||
                F == G || F == H ||
                G == H ) // 8
            {
                continue;
            }
            String h = "   _harmonic_subset_" + String(ssi) + "->" + setABCDEFGH + " (_one->mt, "
            + u + B + u + A + "->mt, "
            + u + C + u + A + "->mt, "
            + u + D + u + A + "->mt, "
            + u + E + u + A + "->mt, "
            + u + F + u + A + "->mt, "
            + u + G + u + A + "->mt, "
            + u + H + u + A + "->mt);";
            DBG (h);
            String s = "_subharmonic_subset_" + String(ssi) + "->" + setABCDEFGH + " (_one->mt, "
            + u + A + u + B + "->mt, "
            + u + A + u + C + "->mt, "
            + u + A + u + D + "->mt, "
            + u + A + u + E + "->mt, "
            + u + A + u + F + "->mt, "
            + u + A + u + G + "->mt, "
            + u + A + u + H + "->mt);";
            DBG (s);
            
            ssi++;
            DBG ("");
        }
    }
#endif
    
}
