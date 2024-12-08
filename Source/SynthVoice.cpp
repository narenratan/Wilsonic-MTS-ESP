/*
  ==============================================================================

    SynthVoice.cpp
    Created: 9 Mar 2021 8:35:47pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "SynthVoice.h"
#include "WilsonicProcessor.h"

SynthVoice::SynthVoice(WilsonicProcessor& processor)
: SynthesiserVoice()
, _processor (processor)
, _osc1( {OscData (_processor), OscData (_processor)} )
, _osc2( {OscData (_processor), OscData (_processor)} )
{

}

SynthVoice::~SynthVoice()
{

}

bool SynthVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound */*sound*/, int )
{
    for (unsigned long i = 0; i < WilsonicProcessorConstants::numChannelsToProcess; i++)
    {
        _osc1[i].setFreq(midiNoteNumber);
        _osc2[i].setFreq(midiNoteNumber);
    }
    
    _adsr.noteOn();
    _filterAdsr.noteOn();

    // update voice state
    _voiceState.nn = static_cast<unsigned long>(midiNoteNumber);
    _voiceState.frequency = _processor.getAppTuningModel()->getTuningTableFrequency(static_cast<unsigned long>(midiNoteNumber));
    _voiceState.velocity = velocity;
}

void SynthVoice::stopNote (float /* velocity */, bool allowTailOff)
{
    _adsr.noteOff();
    _filterAdsr.noteOff();
    
    if (! allowTailOff || ! _adsr.isActive())
        clearCurrentNote();
}

void SynthVoice::controllerMoved (int , int )
{
    
}

void SynthVoice::pitchWheelMoved (int )
{
    
}

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    reset();
    
    _adsr.setSampleRate (sampleRate);
    _filterAdsr.setSampleRate (sampleRate);
    
    dsp::ProcessSpec spec;
    spec.maximumBlockSize = (uint32)samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = (uint32)outputChannels;
    
    for (unsigned long ch = 0; ch < WilsonicProcessorConstants::numChannelsToProcess; ch++)
    {
        _osc1[ch].prepareToPlay (sampleRate, samplesPerBlock, outputChannels);
        _osc2[ch].prepareToPlay (sampleRate, samplesPerBlock, outputChannels);
        _filter[ch].prepareToPlay (sampleRate, samplesPerBlock, outputChannels);
        _lfo[ch].prepare (spec);
        _lfo[ch].initialise ([](float x) { return sinf (x); });
    }
    
    _gain.prepare (spec);
    _gain.setGainLinear (0.07f);
    
    _isPrepared = true;
}

void SynthVoice::renderNextBlock(AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    jassert(_isPrepared);

    if(!AppExperiments::enableSimpleSynth)
    {
        return;
    }

    if(!isVoiceActive())
    {
        _voiceState.peak = 0.f;
        _voiceState.rms = 0.f;
        _voiceState.velocity = 0.f;

        return;
    }
    
    _synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    _filterAdsr.applyEnvelopeToBuffer(_synthBuffer, 0, _synthBuffer.getNumSamples());
    _filterAdsrOutput = _filterAdsr.getNextSample();
    _synthBuffer.clear();
    
    for (int ch = 0; ch < _synthBuffer.getNumChannels(); ++ch)
    {
        auto* buffer = _synthBuffer.getWritePointer (ch, 0);
        for (int s = 0; s < _synthBuffer.getNumSamples(); ++s)
        {
            buffer[s] = _osc1[static_cast<unsigned long>(ch)].processNextSample (buffer[s]) + _osc2[static_cast<unsigned long>(ch)].processNextSample (buffer[s]);
            buffer[s] *= _voiceState.velocity;
        }
    }
    
    dsp::AudioBlock<float> audioBlock { _synthBuffer };
    _gain.process(dsp::ProcessContextReplacing<float> (audioBlock));
    _adsr.applyEnvelopeToBuffer(_synthBuffer, 0, _synthBuffer.getNumSamples());
    
    for(int ch = 0; ch < _synthBuffer.getNumChannels(); ++ch)
    {
        auto* buffer = _synthBuffer.getWritePointer (ch, 0);
        for(int s = 0; s < _synthBuffer.getNumSamples(); ++s)
        {
            buffer[s] = _filter[static_cast<unsigned long>(ch)].processNextSample (ch, _synthBuffer.getSample (ch, s));
        }
    }
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom (channel, startSample, _synthBuffer, channel, 0, numSamples);
        if (! _adsr.isActive())
        {
            clearCurrentNote();
        }
    }

    // update voice meter
    _voiceMeter.process (outputBuffer);

    // update voice state
    _voiceState.peak = _voiceMeter.getPeak();
    _voiceState.rms = _voiceMeter.getRMS();
}

void SynthVoice::reset()
{
    _gain.reset();
    _adsr.reset();
    _filterAdsr.reset();
}

VoiceState SynthVoice::getVoiceState()
{
    return _voiceState; // copy
}

const atomic<float>& SynthVoice::getRMS()
{
    return _voiceMeter.getRMS();
}

const atomic<float>& SynthVoice::getPeak()
{
    return _voiceMeter.getPeak();
}

void SynthVoice::updateModParams (const float sampleRate, const int filterType, const float filterCutoff, const float filterResonance, const float adsrDepth, const float /*lfoFreq*/, const float /*lfoDepth*/)
{
    auto cutoff = (adsrDepth * _filterAdsrOutput) + filterCutoff;
    cutoff = clamp<float> (cutoff, 20.0f, 0.5f * 0.9f * sampleRate);

    for (unsigned long ch = 0; ch < WilsonicProcessorConstants::numChannelsToProcess; ++ch)
    {
        _filter[ch].setParams (filterType, cutoff, filterResonance);
    }
}
