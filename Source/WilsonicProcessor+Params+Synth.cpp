/*
 ==============================================================================

 WilsonicProcessor+Params+Synth.cpp
 Created: 30 Oct 2021 8:04:43pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include <algorithm>
#include "WilsonicEditor.h"
#include "WilsonicProcessor.h"

// do NOT use the JucePlugin_IsSynth macro in this file

#pragma mark - synth params

// do NOT use the JucePlugin_IsSynth macro here
unique_ptr<AudioProcessorParameterGroup> WilsonicProcessor::_createSynthParams()
{
    auto synthParamGroup = make_unique<AudioProcessorParameterGroup>
    ("Synth", "Synth", " | ",

     // OSC select
     make_unique<AudioParameterChoice> (ParameterID ("SYNTHOSC1", AppVersion::getVersionHint()), "Synth|Oscillator 1", StringArray { "Sine", "Saw", "Square" }, 0),
     make_unique<AudioParameterChoice> (ParameterID ("SYNTHOSC2", AppVersion::getVersionHint()), "Synth|Oscillator 2", StringArray { "Sine", "Saw", "Square" }, 0),

     // OSC Gain
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHOSC1GAIN", AppVersion::getVersionHint()), "Synth|Oscillator 1 Gain", NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, 0.1f, "dB"),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHOSC2GAIN", AppVersion::getVersionHint()), "Synth|Oscillator 2 Gain", NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, 0.1f, "dB"),

     // OSC Pitch val
     make_unique<AudioParameterInt> (ParameterID ("SYNTHOSC1PITCH", AppVersion::getVersionHint()), "Synth|Oscillator 1 Pitch", -48, 48, 0),
     make_unique<AudioParameterInt> (ParameterID ("SYNTHOSC2PITCH", AppVersion::getVersionHint()), "Synth|Oscillator 2 Pitch", -48, 48, 0),

     // FM Osc Freq
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHOSC1FMFREQ", AppVersion::getVersionHint()), "Synth|Oscillator 1 FM Frequency", NormalisableRange<float> { 0.0f, 1000.0f, 0.1f }, 0.0f, "Hz"),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHOSC2FMFREQ", AppVersion::getVersionHint()), "Synth|Oscillator 1 FM Frequency", NormalisableRange<float> { 0.0f, 1000.0f, 0.1f }, 0.0f, "Hz"),

     // FM Osc Depth
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHOSC1FMDEPTH", AppVersion::getVersionHint()), "Synth|Oscillator 1 FM Depth", NormalisableRange<float> { 0.0f, 100.0f, 0.1f }, 0.0f, ""),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHOSC2FMDEPTH", AppVersion::getVersionHint()), "Synth|Oscillator 2 FM Depth", NormalisableRange<float> { 0.0f, 100.0f, 0.1f }, 0.0f, ""),

     // LFO
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHLFO1FREQ", AppVersion::getVersionHint()), "Synth|LFO1 Frequency", NormalisableRange<float> { 0.0f, 20.0f, 0.1f }, 0.0f, "Hz"),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHLFO1DEPTH", AppVersion::getVersionHint()), "Synth|LFO1 Depth", NormalisableRange<float> { 0.0f, 10000.0f, 0.1f, 0.3f }, 0.0f, ""),

     //Filter
     make_unique<AudioParameterChoice> (ParameterID ("SYNTHFILTERTYPE", AppVersion::getVersionHint()), "Synth|Filter Type", StringArray { "Low Pass", "Band Pass", "High Pass" }, 0),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHFILTERCUTOFF", AppVersion::getVersionHint()), "Synth|Filter Cutoff", NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 20000.0f, "Hz"),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHFILTERRESONANCE", AppVersion::getVersionHint()), "Synth|Filter Resonance", NormalisableRange<float> { 0.1f, 2.0f, 0.1f }, 0.1f, ""),

     // ADSR
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHATTACK", AppVersion::getVersionHint()), "Synth|Attack", NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHDECAY", AppVersion::getVersionHint()), "Synth|Decay", NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHSUSTAIN", AppVersion::getVersionHint()), "Synth|Sustain", NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHRELEASE", AppVersion::getVersionHint()), "Synth|Release", NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f),

     make_unique<AudioParameterFloat> (ParameterID ("SYNTHFILTERADSRDEPTH", AppVersion::getVersionHint()), "Synth|Filter ADSR Depth", NormalisableRange<float> { 0.0f, 10000.0f, 0.1f, 0.3f }, 10000.0f, ""),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHFILTERATTACK", AppVersion::getVersionHint()), "Synth|Filter Attack", NormalisableRange<float> { 0.0f, 1.0f, 0.01f }, 0.01f),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHFILTERDECAY", AppVersion::getVersionHint()), "Synth|Filter Decay", NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 0.1f),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHFILTERSUSTAIN", AppVersion::getVersionHint()), "Synth|Filter Sustain", NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 1.0f),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHFILTERRELEASE", AppVersion::getVersionHint()), "Synth|Filter Release", NormalisableRange<float> { 0.0f, 3.0f, 0.1f }, 0.1f),

     // Reverb
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHREVERBSIZE", AppVersion::getVersionHint()), "Synth|Reverb Size", NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 0.0f, ""),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHREVERBWIDTH", AppVersion::getVersionHint()), "Synth|Reverb Width", NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 1.0f, ""),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHREVERBDAMPING", AppVersion::getVersionHint()), "Synth|Reverb Damping", NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 0.5f, ""),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHREVERBDRY", AppVersion::getVersionHint()), "Synth|Reverb Dry", NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 1.0f, ""),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHREVERBWET", AppVersion::getVersionHint()), "Synth|Reverb Wet", NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 0.0f, ""),
     make_unique<AudioParameterFloat> (ParameterID ("SYNTHREVERBFREEZE", AppVersion::getVersionHint()), "Synth|Reverb Freeze", NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 0.0f, "")
     );

    return synthParamGroup;
}

// called within process
void WilsonicProcessor::_setSynthParams()
{
    // do NOT use the JucePlugin_IsSynth macro here
    _setSynthVoiceParams();
    _setSynthFilterParams();
    _setSynthReverbParams();
}

// called within process
void WilsonicProcessor::_setSynthVoiceParams() {
    // do NOT use the JucePlugin_IsSynth macro here
    for (int i = 0; i < _synth.getNumVoices(); ++i) {
        if (auto voice = dynamic_cast<SynthVoice*>(_synth.getVoice(i))) {
            auto& attack = *_apvts->getRawParameterValue ("SYNTHATTACK");
            auto& decay = *_apvts->getRawParameterValue ("SYNTHDECAY");
            auto& sustain = *_apvts->getRawParameterValue ("SYNTHSUSTAIN");
            auto& release = *_apvts->getRawParameterValue ("SYNTHRELEASE");

            //
            auto& osc1Choice = *_apvts->getRawParameterValue ("SYNTHOSC1");
            auto& osc2Choice = *_apvts->getRawParameterValue ("SYNTHOSC2");
            auto& osc1Gain = *_apvts->getRawParameterValue ("SYNTHOSC1GAIN");
            auto& osc2Gain = *_apvts->getRawParameterValue ("SYNTHOSC2GAIN");
            auto& osc1Pitch = *_apvts->getRawParameterValue ("SYNTHOSC1PITCH");
            auto& osc2Pitch = *_apvts->getRawParameterValue ("SYNTHOSC2PITCH");
            auto& osc1FmFreq = *_apvts->getRawParameterValue ("SYNTHOSC1FMFREQ");
            auto& osc2FmFreq = *_apvts->getRawParameterValue ("SYNTHOSC2FMFREQ");
            auto& osc1FmDepth = *_apvts->getRawParameterValue ("SYNTHOSC1FMDEPTH");
            auto& osc2FmDepth = *_apvts->getRawParameterValue ("SYNTHOSC2FMDEPTH");

            //
            auto& filterAttack = *_apvts->getRawParameterValue ("SYNTHFILTERATTACK");
            auto& filterDecay = *_apvts->getRawParameterValue ("SYNTHFILTERDECAY");
            auto& filterSustain = *_apvts->getRawParameterValue ("SYNTHFILTERSUSTAIN");
            auto& filterRelease = *_apvts->getRawParameterValue ("SYNTHFILTERRELEASE");

            //
            auto& osc1 = voice->getOscillator1();
            auto& osc2 = voice->getOscillator2();

            //
            auto& adsr = voice->getAdsr();
            auto& filterAdsr = voice->getFilterAdsr();

            //
            for (unsigned long ii = 0; ii < (unsigned long)getTotalNumOutputChannels(); ii++) {
                osc1[ii].setParams(static_cast<int>(osc1Choice), osc1Gain, static_cast<int>(osc1Pitch), osc1FmFreq, osc1FmDepth);
                osc2[ii].setParams(static_cast<int>(osc2Choice), osc2Gain, static_cast<int>(osc2Pitch), osc2FmFreq, osc2FmDepth);
            }

            //
            adsr.update (attack.load(), decay.load(), sustain.load(), release.load());
            filterAdsr.update (filterAttack, filterDecay, filterSustain, filterRelease);
        }
    }
}

// called within process
void WilsonicProcessor::_setSynthFilterParams() {
    // do NOT use the JucePlugin_IsSynth macro here

    auto sampleRate = getSampleRate();
    auto& filterType = *_apvts->getRawParameterValue ("SYNTHFILTERTYPE");
    auto& filterCutoff = *_apvts->getRawParameterValue ("SYNTHFILTERCUTOFF");
    auto& filterResonance = *_apvts->getRawParameterValue ("SYNTHFILTERRESONANCE");
    auto& adsrDepth = *_apvts->getRawParameterValue ("SYNTHFILTERADSRDEPTH");
    auto& lfoFreq = *_apvts->getRawParameterValue ("SYNTHLFO1FREQ");
    auto& lfoDepth = *_apvts->getRawParameterValue ("SYNTHLFO1DEPTH");

    for (int i = 0; i < _synth.getNumVoices(); ++i) {
        if (auto voice = dynamic_cast<SynthVoice*>(_synth.getVoice(i))) {
            voice->updateModParams(static_cast<float>(sampleRate), static_cast<int>(filterType), filterCutoff, filterResonance, adsrDepth, lfoFreq, lfoDepth);
        }
    }
}

// called within process
void WilsonicProcessor::_setSynthReverbParams() {
    // do NOT use the JucePlugin_IsSynth macro here

    _reverbParams.roomSize = *_apvts->getRawParameterValue ("SYNTHREVERBSIZE");
    _reverbParams.width = *_apvts->getRawParameterValue ("SYNTHREVERBWIDTH");
    _reverbParams.damping = *_apvts->getRawParameterValue ("SYNTHREVERBDAMPING");
    _reverbParams.dryLevel = *_apvts->getRawParameterValue ("SYNTHREVERBDRY");
    _reverbParams.wetLevel = *_apvts->getRawParameterValue ("SYNTHREVERBWET");
    _reverbParams.freezeMode = *_apvts->getRawParameterValue ("SYNTHREVERBFREEZE");
    _reverb.setParameters (_reverbParams);
}

// used for Favorites
StringArray WilsonicProcessor::getSynthParameterIDs() {
    // do NOT use the JucePlugin_IsSynth macro here

    return StringArray ("SYNTHOSC1",
                        "SYNTHOSC2",
                        "SYNTHOSC1GAIN",
                        "SYNTHOSC2GAIN",
                        "SYNTHOSC1PITCH",
                        "SYNTHOSC2PITCH",
                        "SYNTHOSC1FMFREQ",
                        "SYNTHOSC2FMFREQ",
                        "SYNTHOSC1FMDEPTH",
                        "SYNTHOSC2FMDEPTH",
                        "SYNTHLFO1FREQ",
                        "SYNTHLFO1DEPTH",
                        "SYNTHFILTERTYPE",
                        "SYNTHFILTERCUTOFF",
                        "SYNTHFILTERRESONANCE",
                        "SYNTHATTACK",
                        "SYNTHDECAY",
                        "SYNTHSUSTAIN",
                        "SYNTHRELEASE",
                        "SYNTHFILTERADSRDEPTH",
                        "SYNTHFILTERATTACK",
                        "SYNTHFILTERDECAY",
                        "SYNTHFILTERSUSTAIN",
                        "SYNTHFILTERRELEASE",
                        "SYNTHREVERBSIZE",
                        "SYNTHREVERBWIDTH",
                        "SYNTHREVERBDAMPING",
                        "SYNTHREVERBDRY",
                        "SYNTHREVERBWET",
                        "SYNTHREVERBFREEZE"
                        );
}
