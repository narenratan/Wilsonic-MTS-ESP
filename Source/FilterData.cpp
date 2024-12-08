/*
  ==============================================================================

    FilterData.cpp
    Created: 18 Feb 2021 9:26:23pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include "FilterData.h"

FilterData::FilterData()
{
    setType (dsp::StateVariableTPTFilterType::lowpass);
}

void FilterData::setParams (const int filterType, const float filterCutoff, const float filterResonance)
{
    selectFilterType (filterType);
    setCutoffFrequency (filterCutoff);
    setResonance (filterResonance);
}

void FilterData::setLfoParams (const float /*freq*/, const float /*depth*/)
{
//    lfoGain = Decibels::gainToDecibels (depth);
//    lfo.setFrequency (freq);
}

void FilterData::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    resetAll();
    dsp::ProcessSpec spec;
    spec.maximumBlockSize = (uint32)samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = (uint32)outputChannels;
    prepare (spec);
}


void FilterData::selectFilterType (const int filterType)
{    
    switch (filterType)
    {
        case 0:
            setType (dsp::StateVariableTPTFilterType::lowpass);
            break;
            
        case 1:
            setType (dsp::StateVariableTPTFilterType::bandpass);
            break;
            
        case 2:
            setType (dsp::StateVariableTPTFilterType::highpass);
            break;
            
        default:
            setType (dsp::StateVariableTPTFilterType::lowpass);
            break;
    }
}

void FilterData::processNextBlock(AudioBuffer<float>& buffer)
{
    dsp::AudioBlock<float> block { buffer };
    process (dsp::ProcessContextReplacing<float>(block));
}

float FilterData::processNextSample (int channel, float inputValue)
{
    return processSample (channel, inputValue);
}

void FilterData::resetAll()
{
    reset();
    lfo.reset();
}
