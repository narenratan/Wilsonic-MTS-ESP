/*
  ==============================================================================

    TuningTests+Persian17NorthIndian.cpp
    Created: 20 Mar 2022 2:04:18pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "TuningTests.h"
#include "Persian17NorthIndian.h"

void TuningTests::testPersian17NorthIndian()
{
#if 0
    persian17NorthIndianCodeGen();
    return;
#endif

    // Test Persian 17
    cout << "BEGIN TEST: Persian17NorthIndian() ---------------------" << endl;

    Persian17NorthIndian scale {};
    for (auto s : Persian17NorthIndian::all_scales)
    {
        scale.setScale (s);
        cout << "Scale: " << scale.getTuningName() << endl;
        auto pa = scale.getProcessedArray();
        for (unsigned long i = 0; i < pa.count(); i++)
        {
            auto mti0 = pa.microtoneAtIndex (i);
            auto mti1 = (i == (pa.count() - 1)) ? make_shared<Microtone> (2, 1) : pa.microtoneAtIndex (i+1);
            auto interval = mti1->divide (mti0);
            // this works
            cout << i << ": " << interval->getShortDescriptionText() << endl;
        }

    }

    cout << "END TEST: Persian17NorthIndian() ---------------------" << endl;
}

void TuningTests::persian17NorthIndianCodeGen()
{
    Persian17NorthIndian scale {};
    for (auto s : Persian17NorthIndian::all_scales)
    {
        scale.setScale (s);
        cout << "{ ";
        auto pa = scale.getProcessedArray();
        for (unsigned long i = 0; i < pa.count(); i++)
        {
            auto mti0 = pa.microtoneAtIndex (i);
            cout << mti0->getPitchValue01();
            if (i < pa.count() - 1) cout << ", ";
        }
        cout << " }," << endl;
    }

    for (auto s : Persian17NorthIndian::all_scales)
    {
        scale.setScale (s);
        cout << "{ ";
        auto pa = scale.getProcessedArray();
        for (unsigned long i = 0; i < pa.count(); i++)
        {
            auto mti0 = pa.microtoneAtIndex (i);
            auto mti1 = (i == (pa.count() - 1)) ? make_shared<Microtone> (2, 1) : pa.microtoneAtIndex (i+1);
            auto interval = mti1->divide (mti0);
            cout << "\"" << interval << "\"";
            if (i < pa.count() - 1) cout << ", ";
        }
        cout << " }," << endl;
    }


}
