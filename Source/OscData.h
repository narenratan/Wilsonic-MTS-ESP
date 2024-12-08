/*
  ==============================================================================

    OscData.h
    Created: 14 Feb 2021 6:51:17pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppTuningModel.h"

class WilsonicProcessor;

class OscData 
: public dsp::Oscillator<float>
{

public:
    OscData(WilsonicProcessor&);
    OscData(WilsonicProcessor&, const function<NumericType (NumericType)>& function, size_t lookupTableNumPoints = 0);

    void setAppTuning();
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void setType(const int oscSelection);
    void setGain(const float levelInDecibels);
    void setOscPitch(const int pitch);
    void setFreq(const int midiNoteNumber);
    void setFmOsc(const float freq, const float depth);
    void renderNextBlock(dsp::AudioBlock<float>& audioBlock);
    float processNextSample(float input);
    void setParams(const int oscChoice, const float oscGain, const int oscPitch, const float fmFreq, const float fmDepth);
    void resetAll();

private:
    WilsonicProcessor& _processor;
    dsp::Oscillator<float> fmOsc { [](float x) { return sinf (x); }};
    dsp::Gain<float> gain;
    unsigned long lastPitch { 0 };
    unsigned long lastMidiNote { 0 };
    float fmDepth { 0.0f };
    float fmModulator { 0.0f };
};
