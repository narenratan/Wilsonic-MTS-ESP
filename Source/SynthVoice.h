/*
  ==============================================================================

    SynthVoice.h
    Created: 9 Mar 2021 8:35:47pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AdsrData.h"
#include "FilterData.h"
#include "MeterData.h"
#include "OscData.h"
#include "SynthSound.h"
#include "VoiceState.h"
#include "TuningConstants.h"
#include "WilsonicProcessorConstants.h"

// forward
class WilsonicProcessor;

//
class SynthVoice
: public SynthesiserVoice
{
    
public:
    SynthVoice(WilsonicProcessor&);
    ~SynthVoice() override;

    bool canPlaySound(SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    void reset();
    array<OscData, WilsonicProcessorConstants::numChannelsToProcess>& getOscillator1() { return _osc1; }
    array<OscData, WilsonicProcessorConstants::numChannelsToProcess>& getOscillator2() { return _osc2; }
    AdsrData& getAdsr() { return _adsr; }
    AdsrData& getFilterAdsr() { return _filterAdsr; }
    float getFilterAdsrOutput() { return _filterAdsrOutput; }
    const atomic<float>& getRMS();
    const atomic<float>& getPeak();
    void updateModParams (const float sampleRate, const int filterType, const float filterCutoff, const float filterResonance, const float adsrDepth, const float lfoFreq, const float lfoDepth);
    VoiceState getVoiceState();
    
private:
    WilsonicProcessor& _processor;
    array<OscData, WilsonicProcessorConstants::numChannelsToProcess> _osc1;
    array<OscData, WilsonicProcessorConstants::numChannelsToProcess> _osc2;
    array<FilterData, WilsonicProcessorConstants::numChannelsToProcess> _filter {};
    array<dsp::Oscillator<float>, WilsonicProcessorConstants::numChannelsToProcess> _lfo {};
    AdsrData _adsr {};
    AdsrData _filterAdsr {};
    MeterData _voiceMeter {};
    AudioBuffer<float> _synthBuffer {};
    float _filterAdsrOutput {0.f};
    dsp::Gain<float> _gain;
    bool _isPrepared {false};
    VoiceState _voiceState {TuningConstants::middleCNoteNumber, TuningConstants::middleCFrequency, 1.f, 0.f, 0.f};
};
