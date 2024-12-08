/*
  ==============================================================================

    TuningTests+RecurrenceRelation.cpp
    Created: 21 Mar 2022 10:18:38pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "TuningTests.h"
#include "RecurrenceRelation.h"

void TuningTests::testRecurrenceRelation()
{
    cout << "BEGIN TEST: RecurrenceRelation() ---------------------" << endl;

    RecurrenceRelation scale {};

    cout << "END TEST: RecurrenceRelation() ---------------------" << endl;
}

void TuningTests::recurrenceRelationCodeGen()
{
    for (auto i = 1; i<10; i++)
    {
        for (auto j = 1; j<10; j++)
        {
            if (j<=i) continue;
//            cout << "make_tuple<String, int, int> (\"i:" << i << ", j:" << j << "\", " << i << ", " << j << ")," << endl;
//            cout << "make_tuple<String, int, int> (\"H[n] = H[n - " << i << "] + H[n - " << j << "]\", " << i << ", " << j << ")," << endl;
//            cout << "i:" << i << ", j:" << j << endl;
            cout << "\"H[n] = H[n - " << i << "] + H[n - " << j << "]\", " << endl;
        }
    }
//i:1, j:2
//i:1, j:3
//i:1, j:4
//i:1, j:5
//i:1, j:6
//i:1, j:7
//i:1, j:8
//i:1, j:9
//i:2, j:3
//i:2, j:4
//i:2, j:5
//i:2, j:6
//i:2, j:7
//i:2, j:8
//i:2, j:9
//i:3, j:4
//i:3, j:5
//i:3, j:6
//i:3, j:7
//i:3, j:8
//i:3, j:9
//i:4, j:5
//i:4, j:6
//i:4, j:7
//i:4, j:8
//i:4, j:9
//i:5, j:6
//i:5, j:7
//i:5, j:8
//i:5, j:9
//i:6, j:7
//i:6, j:8
//i:6, j:9
//i:7, j:8
//i:7, j:9
//i:8, j:9
}
