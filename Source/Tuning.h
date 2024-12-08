/*
 ==============================================================================

 Tuning.h
 Created: 21 Feb 2021 3:23:19pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#pragma once

#include "ScalaFile.h"
#include "PythagoreanMeans.h"
#include "TuningConstants.h"
#include "TuningTable.h"
#include "WilsonicProcessorConstants.h"

// forward
class Microtone;
using Microtone_p = shared_ptr<Microtone>;
class MicrotoneArray;
class WilsonicProcessor;

//
class Tuning
: public TuningTable
{
public:
    // parameter ranges/defaults

    // see TuningConstants for period ("octave") constants
    static constexpr unsigned long noteNumberMiddleCMin = 0;
    static constexpr unsigned long noteNumberMiddleCDefault = 60;
    static constexpr unsigned long noteNumberMiddleCMax = WilsonicProcessorConstants::numMidiNotes - 1;
    
    static constexpr float frequencyMiddleCMin = 0.5f * TuningConstants::middleCFrequency;
    static constexpr float frequencyMiddleCDefault = TuningConstants::middleCFrequency;
    static constexpr float frequencyMiddleCMax = 1.5f * TuningConstants::middleCFrequency;
    
    static constexpr int octaveMiddleCMin = -7;
    static constexpr int octaveMiddleCDefault = 0;
    static constexpr int octaveMiddleCMax = 7;
    
    static constexpr int npoOverrideMin = 1; // 1-128
    static constexpr int npoOverrideMax = 128;
    static constexpr int npoOverrideDefault = 12; // default 12
    static constexpr bool npoOverrideEnableDefault = false;
    
    virtual ~Tuning() noexcept = default;

    // sample rate / 2 = nyquist: used to clamp frequencies
    virtual const float getSampleRate() = 0;
    virtual void setSampleRate(float sampleRate) = 0;

    //
    virtual MicrotoneArray getMicrotoneArray() = 0;
    virtual unsigned long getMicrotoneArrayCount() = 0;
    virtual MicrotoneArray getProcessedArray() = 0;
    virtual unsigned long getProcessedArrayCount() = 0;
    virtual MicrotoneArray getProcessedArrayNPO() = 0;
    virtual unsigned long getProcessedArrayNPOCount() = 0;
    
    //
    virtual const vector<PythagoreanMeans> getProportionalTriads() = 0; // "major", sum tones
    virtual const vector<PythagoreanMeans> getGeometricTriads() = 0; // geometric triads
    virtual const vector<PythagoreanMeans> getSubcontraryTriads() = 0; // "minor" harmonic mean
    virtual const vector<PythagoreanMeans> getAllTriads() = 0; // all of them
    virtual void setMicrotoneArray(MicrotoneArray ma) = 0;
    virtual void setMicrotoneArrayFromHarmonics(vector<float> harmonics) = 0;
    virtual void setMicrotoneAtNoteNumber(Microtone_p microtone, unsigned long nn) = 0;
    virtual Microtone_p microtoneAtNoteNumber(unsigned long nn) = 0;
    virtual void setPostProcessPreTuningUpdate(function<void()> postProcessBlock) = 0;
    virtual void callPostProcessBlock() = 0;
    virtual void setOnTuningUpdate(function<void()> completionBlock) = 0;
    virtual void callOnTuningUpdate() = 0;
    
    // Mode (net new to MTS-ESP wilsonic...normalizes around processedArray[0])
    virtual int getMode() = 0;
    virtual void setMode(int) = 0;

    // MIDI Note number for Middle C
    virtual unsigned long getNoteNumberMiddleC() = 0;
    virtual void setNoteNumberMiddleC(unsigned long) = 0;
    virtual unsigned long getNoteNumberMiddleCMin() = 0;
    virtual unsigned long getNoteNumberMiddleCMax() = 0;

    // Frequency for Middle C
    virtual float getFrequencyMiddleC() = 0;
    virtual void setFrequencyMiddleC(float) = 0;
    virtual float getFrequencyMiddleCMin() = 0;
    virtual float getFrequencyMiddleCMax() = 0;

    // Int octave at Middle C.  i.e., -2, -1, 0, 1, 2, etc.
    virtual int getOctaveMiddleC() = 0;
    virtual void setOctaveMiddleC(int) = 0;
    virtual int getOctaveMiddleCMin() = 0;
    virtual int getOctaveMiddleCMax() = 0;

    // notes per octave "npo" override
    virtual bool getCanNPOOverride() = 0; // does tuning support npo override?
    virtual void setCanNPOOverride(bool) = 0;
    virtual int getNPOOverride() = 0;
    virtual void setNPOOverride(int) = 0;
    virtual int getNPOOverrideMin() = 0;
    virtual int getNPOOverrideMax() = 0;
    virtual bool getNPOOverrideEnable() = 0;
    virtual void setNPOOverrideEnable(bool) = 0;

    // the value of the octave
    virtual float getOctave() = 0;
    virtual void setOctave(float) = 0;
    virtual float getOctaveMin() = 0;
    virtual float getOctaveMax() = 0;

    // octave reduce
    virtual bool getOctaveReduce() = 0;
    virtual void setOctaveReduce(bool) = 0;

    // octave repeat
    virtual bool getOctaveRepeat() = 0;
    virtual void setOctaveRepeat(bool) = 0;

    // sort
    virtual bool getSort() = 0;
    virtual void setSort(bool) = 0;

    // is scale capable of sorting?
    virtual bool getCanSort() = 0;
    virtual void setCanSort(bool) = 0;

    // uniquify
    virtual bool getUniquify() = 0;
    virtual void setUniquify(bool) = 0;

    // is scale capable of uniquifying?
    virtual bool getCanUniquify() = 0;
    virtual void setCanUniquify(bool) = 0;

    // name
    virtual const string getTuningName() = 0;
    virtual void setTuningName(string) = 0;

    // description
    virtual const string getTuningDescription() = 0; // settable
    virtual void setTuningDescription(string) = 0;

    // debug description (for logging)
    virtual const string getDebugDescription() = 0; // debug

    // user description
    virtual const string getUserDescription() = 0;
    virtual void setUserDescription(string) = 0;

    // parameter description
    virtual const string getParameterDescription() = 0; // used by favorites

    // is scale capable of being favorited?
    virtual bool getCanFavorite() = 0;

    // is scale capable of being represented as a scala file?
    virtual bool getCanScala() = 0;
    virtual void setCanScala(bool) = 0;
    virtual ScalaFile tuningAsScala() = 0;
    virtual String defaultScalaName() = 0;
    virtual String scalaComments() = 0;

    // drawing
    virtual bool canPaintTuning() = 0;
    virtual void paint(WilsonicProcessor&, Graphics&, Rectangle<int>) = 0;

protected:
    virtual void _update() = 0;
};
