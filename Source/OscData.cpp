/*
  ==============================================================================

    OscData.cpp
    Created: 14 Feb 2021 6:51:17pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include "AppTuningModel.h"
#include "OscData.h"
#include "WilsonicProcessor.h"

OscData::OscData(WilsonicProcessor& processor)
: dsp::Oscillator<float>()
, _processor (processor)
{

}

OscData::OscData(WilsonicProcessor& processor, const function<NumericType (NumericType)>& /*function*/, size_t /*lookupTableNumPoints*/)
: dsp::Oscillator<float>()
, _processor (processor)
{

}

void OscData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    resetAll();
    
    dsp::ProcessSpec spec;
    spec.maximumBlockSize = (uint32)samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = (uint32)outputChannels;
    
    prepare (spec);
    fmOsc.prepare (spec);
    gain.prepare (spec);    
}

void OscData::setType(const int oscSelection)
{
    switch (oscSelection)
    {
        // Sine
        case 0:
            initialise([](float x) { return sinf (x); });
            break;
            
        // Saw
        case 1:
            initialise([] (float x) { return x / MathConstants<float>::pi; });
            break;
          
        // Square
        case 2:
            initialise([] (float x) { return x < 0.0f ? -1.0f : 1.0f; });
            break;
            
        default:
            // You shouldn't be here!
            jassertfalse;
            break;
    }
}

void OscData::setGain(const float levelInDecibels)
{
    gain.setGainDecibels(levelInDecibels);
}

void OscData::setOscPitch(const int pitch)
{
    lastPitch = static_cast<unsigned long>(pitch);
    auto const f = _processor.getAppTuningModel()->getTuningTableFrequency (lastMidiNote + lastPitch);
    setFrequency (f + fmModulator);
}

void OscData::setFreq(const int midiNoteNumber)
{
    auto const f = _processor.getAppTuningModel()->getTuningTableFrequency (static_cast<unsigned long>(midiNoteNumber) + lastPitch);
    setFrequency (f + fmModulator);
    lastMidiNote = static_cast<unsigned long>(midiNoteNumber);
}

void OscData::setFmOsc(const float freq, const float depth)
{
    fmDepth = depth;
    fmOsc.setFrequency(freq);
    auto const f = _processor.getAppTuningModel()->getTuningTableFrequency (lastMidiNote + lastPitch);
    setFrequency(f + fmModulator);
}

void OscData::renderNextBlock(dsp::AudioBlock<float>& audioBlock)
{
    jassert(audioBlock.getNumSamples() > 0);
    process(dsp::ProcessContextReplacing<float>(audioBlock));
    gain.process(dsp::ProcessContextReplacing<float>(audioBlock));
}

float OscData::processNextSample(float input)
{
    fmModulator = fmOsc.processSample(input) * fmDepth;
    return gain.processSample(processSample(input));
}

void OscData::setParams(const int oscChoice, const float oscGain, const int oscPitch, const float fmFreq, const float inFmDepth)
{
    setType(oscChoice);
    setGain(oscGain);
    setOscPitch(oscPitch);
    setFmOsc(fmFreq, inFmDepth);
}

void OscData::resetAll()
{
    reset();
    fmOsc.reset();
    gain.reset();
}
