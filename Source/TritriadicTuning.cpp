/*
 ==============================================================================

 TritriadicTuning.cpp
 Created: 22 Sep 2021 4:33:39pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "TritriadicTuning.h"
#include "MicrotoneArray.h"

#pragma mark - lifecycle

TritriadicTuning::TritriadicTuning()
{
    _ttMicrotoneArray.push_back(make_shared<Microtone>(0 / 7.f, "", Microtone::Space::LogPeriod, TuningConstants::defaultPeriod));
    _ttMicrotoneArray.push_back(make_shared<Microtone>(1 / 7.f, "", Microtone::Space::LogPeriod, TuningConstants::defaultPeriod));
    _ttMicrotoneArray.push_back(make_shared<Microtone>(2 / 7.f, "", Microtone::Space::LogPeriod, TuningConstants::defaultPeriod));
    _ttMicrotoneArray.push_back(make_shared<Microtone>(3 / 7.f, "", Microtone::Space::LogPeriod, TuningConstants::defaultPeriod));
    _ttMicrotoneArray.push_back(make_shared<Microtone>(4 / 7.f, "", Microtone::Space::LogPeriod, TuningConstants::defaultPeriod));
    _ttMicrotoneArray.push_back(make_shared<Microtone>(5 / 7.f, "", Microtone::Space::LogPeriod, TuningConstants::defaultPeriod));
    _ttMicrotoneArray.push_back(make_shared<Microtone>(6 / 7.f, "", Microtone::Space::LogPeriod, TuningConstants::defaultPeriod));
    setCanNPOOverride(true);
    setMD(0.3219280917f, 0.5849625f);
}

TritriadicTuning::~TritriadicTuning()
{
    
}

#pragma mark - update

void TritriadicTuning::setMD (float m, float d)
{
    _mediant = (m < 0) ? 0 : ((m > 1) ? 1 : m);
    _dominant = (d < 0) ? 0 : ((d > 1) ? 1 : d);
    _helper();
}

void TritriadicTuning::setMediant (float m)
{
    _mediant = (m < 0) ? 0 : ((m > 1) ? 1 : m);
    _helper();
}

void TritriadicTuning::setDominant (float d)
{
    _dominant = (d < 0) ? 0 : ((d > 1) ? 1 : d);
    _helper();
}

const float TritriadicTuning::getDominantAsPitch()
{
    return _dominant;
}

const float TritriadicTuning::getDominantAsFrequency()
{
    return exp2 (_dominant);
}

const float TritriadicTuning::getDominantAsCents()
{
    return 1200 * _dominant;
}

const float TritriadicTuning::getMediantAsPitch()
{
    return _mediant;
}

const float TritriadicTuning::getMediantAsFrequency()
{
    return exp2 (_mediant);
}

const float TritriadicTuning::getMediantAsCents()
{
    return 1200 * _mediant;
}

void TritriadicTuning::_helper()
{
    // note that _mediant and _dominant are both on [0,1]
    // and that there are no assumptions that one is greater
    // than the other
    
    _ttMicrotoneArray[0]->setPitchValue01(0);
    _ttMicrotoneArray[0]->octaveReduce();
    _ttMicrotoneArray[0]->setShortDescriptionText("  0  ");

    _ttMicrotoneArray[1]->setPitchValue01(_mediant);
    _ttMicrotoneArray[1]->octaveReduce();
    _ttMicrotoneArray[1]->setShortDescriptionText("  M  ");

    _ttMicrotoneArray[2]->setPitchValue01(_dominant);
    _ttMicrotoneArray[2]->octaveReduce();
    _ttMicrotoneArray[2]->setShortDescriptionText("  D  ");

    _ttMicrotoneArray[3]->setPitchValue01(fmodf(_mediant + _dominant, 1));
    _ttMicrotoneArray[3]->octaveReduce();
    _ttMicrotoneArray[3]->setShortDescriptionText(" D+M ");

    _ttMicrotoneArray[4]->setPitchValue01(fmodf(2 * _dominant, 1));
    _ttMicrotoneArray[4]->octaveReduce();
    _ttMicrotoneArray[4]->setShortDescriptionText(" 2*D ");

    _ttMicrotoneArray[5]->setPitchValue01(1 - _dominant);
    _ttMicrotoneArray[5]->octaveReduce();
    _ttMicrotoneArray[5]->setShortDescriptionText(" 1-D ");

    // period reduce onto [0,1]
    auto md01 = _mediant - _dominant;
    if (md01 < 0) {
        md01 = 1 + md01; // octave reduce
    }
    jassert (md01 >= 0 && md01 <= 1);
    _ttMicrotoneArray[6]->setPitchValue01(md01);
    _ttMicrotoneArray[6]->octaveReduce();
    _ttMicrotoneArray[6]->setShortDescriptionText(" M-D ");

    // calls update with deep copy
    setMicrotoneArray(MicrotoneArray(_ttMicrotoneArray));
}

#pragma mark - Scala

String TritriadicTuning::defaultScalaName()
{
    // 0.5833 ==> 5833
    auto m = to_string (_mediant);
    string::size_type i = m.find ("0.");
    if (i != string::npos)
    {
        m.erase (i, 2); // len "0." == 2
    }

    // 0.5833 ==> 5833
    auto d = to_string (_dominant);
    string::size_type ii = d.find ("0.");
    if (ii != string::npos)
    {
        d.erase (ii, 2); // len "0." == 2
    }

    return String ("tritriadic_m_" + m + "_d_" + d + ".scl");
}

String TritriadicTuning::scalaComments()
{
    auto retVal = "! Tritriadic by John Chalmers\n! Mediant: " + to_string (_mediant) + "\n! Dominant: " + to_string (_dominant);

    for (auto i = 0UL; i < numTerms; i++)
    {
        auto mt = _ttMicrotoneArray[i];
        retVal += "! " + mt->getShortDescriptionText2() + "\n";
        retVal += "! " + mt->getShortDescriptionText() + "\n";
        retVal += "!\n";
    }

    return retVal;
}

