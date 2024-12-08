/*
  ==============================================================================

    TuningTests+PentatonicFlutes.cpp
    Created: 4 Jun 2023 1:59:47pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "TuningTests.h"
#include "AppTuningModel.h"
#include "WilsonicProcessor.h"


void TuningTests::testPentatonicFlutes(WilsonicProcessor& processor)
{
    
    // tmp test
    cout << "BEGIN: Test Pentatonic Flutes" << endl;

    //1 24/24,24/21,24/18,24/16,24/14     24/12
//    auto pfma00 = MicrotoneArray (vector<unsigned long>{8,7, 7,6, 9,8, 8,7, 7,6});

    //2 54/54,54/48,54/42,54/36,54/32
//    auto pfma00 = MicrotoneArray (vector<unsigned long>{9,8, 8,7, 7,6, 9,8, 32,27});

    //3 14/14,14/12,14/11,14/10,14/8
//    auto pfma00 = MicrotoneArray (vector<unsigned long>{7,6, 12,11, 11,10, 5,4, 8,7});

    //4 22/22,22/18,22/16,22/14,22/12
//    auto pfma00 = MicrotoneArray (vector<unsigned long>{11,9, 9,8, 8,7, 7,6, 12,11});

    //5 32/32, 32/27, 32/24, 32/22, 32,18
//    auto pfma00 = MicrotoneArray (vector<unsigned long>{32,27, 9,8, 12,11, 11,9, 9,8});

    //6 36/36, 36/30, 36/18, 36/24, 36/20  3*3*2*2
//    auto pfma00 = MicrotoneArray (vector<unsigned long>{6,5, 10,9, 9,8, 6,5, 10,9});

    //7 18/18, 18/15, 18/13, 18/12, 18/10
//    auto pfma00 = MicrotoneArray (vector<unsigned long>{6,5, 15,13, 13,12, 6,5, 10,9});

    //8 78/78, 78/66, 78/60, 78/54, 78/44
//    auto pfma00 = MicrotoneArray (vector<unsigned long>{13,11, 11,10, 10,9, 27,22, 44,39});

    //9 40/40, 40/33, 40/28, 40/26, 40/22
//    auto pfma00 = MicrotoneArray (vector<unsigned long>{40,33, 33,28, 14,13, 13,11, 11,10});

    //10 14/14, 14/12, 14/11, 14/10, 14/8
//    auto pfma00 = MicrotoneArray (vector<unsigned long>{7,6, 12,11, 11,10, 5,4, 8,7});

    //11 22/22, 22/18, 22/15, 22/14, 22/12
//    auto pfma00 = MicrotoneArray (vector<unsigned long>{11,9, 6,5, 15,14, 7,6, 12,11});

    //12 90/90, 90/78, 90/66, 90/60, 90/52
//    auto pfma00 = MicrotoneArray (vector<unsigned long>{15,13, 13,11, 11,10, 15,13, 52,45});

    //13 22/22, 22/18, 22/16, 22/15, 22/12
//    auto pfma00 = MicrotoneArray (vector<unsigned long>{11,9, 9,8, 16,15, 5,4, 12,11});

    //14 48/48, 48/42, 48/36, 48/33, 48/28  3*2*2*2*2
    auto pfma00 = MicrotoneArray (vector<unsigned long>{8,7, 7,6, 12,11, 33,28, 7,6});


    pfma00.insertMicrotone (make_shared<Microtone>(3,4), 0);
    auto tpfma00 = make_shared<TuningImp>();
    tpfma00->setSort (false);
    tpfma00->setOctaveReduce (false);
    tpfma00->setOctaveRepeat (true);
    tpfma00->setMicrotoneArray (pfma00);
    processor.getAppTuningModel()->setTuning(tpfma00);
    processor.getAppTuningModel()->setOverrideWithTuningTests();

    //auto input_info = pfma00.getDebugDescription();
    auto info = tpfma00->getDebugDescription();
    cout << "Pentatonic Flutes" << endl;
    //cout << "  Input: " << input_info << endl;
    cout << "  Output: " << info << endl << endl;

    cout << "ENG: Test Pentatonic Flutes" << endl;
}
