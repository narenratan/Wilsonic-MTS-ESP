/*
  ==============================================================================

    MeterData.cpp
    Created: 27 Feb 2021 9:37:46pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include "MeterData.h"

const atomic<float>& MeterData::getRMS()
{
    return _rms;
}

const atomic<float>& MeterData::getPeak()
{
    return _peak;
}

void MeterData::process (AudioBuffer<float>& buffer)
{
    auto sum = 0.f;
    auto max = 0.f;

    for (auto ch = 0; ch < buffer.getNumChannels(); ++ch)
    {
        auto output = buffer.getReadPointer (ch);

        for (auto s = 0; s < buffer.getNumSamples(); ++s)
        {
            auto squaredSample = output[s] * output[s];
            sum+=squaredSample;

            auto mabs = abs (output[s]);
            if (mabs > max)
                max = mabs;
        }
        auto avg = sum / buffer.getNumSamples();
        _rms.store (sqrtf (avg));
        _peak.store (max);
    }
}
