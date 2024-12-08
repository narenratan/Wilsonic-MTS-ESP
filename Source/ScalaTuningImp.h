/*
 ==============================================================================
 
 ScalaTuningImp.h
 Created: 17 Sep 2022 4:16:35pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "AppExperiments.h"
#include "Microtone.h"
#include "MicrotoneArray.h"
#include "Tuning.h"
#include "TuningConstants.h"
#include "TuningTableImp.h"
#include "WilsonicProcessorConstants.h"

// lots of duplicate code from TuningImp, but no good way to redesign TuningImp

class ScalaTuningImp
: public Tuning
{
public:
    // static factory methods...returns nullptr if invalid
    static shared_ptr<ScalaTuningImp> createScalaTuningFromSclKbm(String full_path_to_scl, String full_path_to_kbm);
    static shared_ptr<ScalaTuningImp> createScalaTuningFromSclString(String scl_string);
    
    // lifecycle
    ScalaTuningImp();
    ScalaTuningImp(const ScalaTuningImp& t);
    ~ScalaTuningImp() noexcept override = default;
    
    // TuningTable
    const float getSampleRate() override;
    void setSampleRate(float sampleRate) override;
    void setTuningTable(float frequency, unsigned long index) override;
    const float getTuningTableFrequency(unsigned long index) override;
    
    // Tuning
    void setMicrotoneArrayFromHarmonics(vector<float> harmonics) override;
    void setMicrotoneArray(MicrotoneArray ma) override;
    
    // the MicrotoneArray that is the basis for the tuning
    MicrotoneArray getMicrotoneArray() override;
    unsigned long getMicrotoneArrayCount() override;
    
    // processed microtoneArray
    MicrotoneArray getProcessedArray() override;
    unsigned long getProcessedArrayCount() override;
    
    // processedArray adjusted for NPO override
    MicrotoneArray getProcessedArrayNPO() override;
    unsigned long getProcessedArrayNPOCount() override;
    
    const vector<PythagoreanMeans> getProportionalTriads() override; // "major", sum tones
    const vector<PythagoreanMeans> getGeometricTriads() override; // geometric mean
    const vector<PythagoreanMeans> getSubcontraryTriads() override; // "minor"
    const vector<PythagoreanMeans> getAllTriads() override; // all of them
    void setMicrotoneAtNoteNumber(Microtone_p microtone, unsigned long nn) override;
    Microtone_p microtoneAtNoteNumber(unsigned long nn) override;
    
    // block will be called after microtones are processed, but before onTuningUpdate
    void setPostProcessPreTuningUpdate(function<void()> postProcessBlock) override;
    void callPostProcessBlock() override;
    
    // block will be called at end of tuning update
    void setOnTuningUpdate(function<void()> completionBlock) override;
    void callOnTuningUpdate() override;
    
    // mode
    int getMode() override;
    void setMode(int) override;
    
    // midi note number at middle c
    unsigned long getNoteNumberMiddleC() override;
    void setNoteNumberMiddleC(unsigned long nn) override;
    unsigned long getNoteNumberMiddleCMin() override;
    unsigned long getNoteNumberMiddleCMax() override;
    
    // frequency of note number at middle c
    float getFrequencyMiddleC() override;
    void setFrequencyMiddleC(float f) override;
    float getFrequencyMiddleCMin() override;
    float getFrequencyMiddleCMax() override;
    
    //
    int getOctaveMiddleC() override;
    void setOctaveMiddleC(int o) override;
    int getOctaveMiddleCMin() override;
    int getOctaveMiddleCMax() override;
    
    // does tuning support npo override?
    bool getCanNPOOverride() override;
    void setCanNPOOverride(bool) override;

    // notes per octave "npo" override
    int getNPOOverride() override;
    void setNPOOverride(int) override;
    int getNPOOverrideMin() override;
    int getNPOOverrideMax() override;
    bool getNPOOverrideEnable() override;
    void setNPOOverrideEnable(bool) override;

    //
    float getOctave() override;
    void setOctave(float o) override;
    float getOctaveMin() override;
    float getOctaveMax() override;
    float getRepeatingInterval();
    void setRepeatingInterval(float ri);
    
    //
    bool getOctaveReduce() override;
    void setOctaveReduce(bool o) override;
    
    // unused for Scala files...use repeatingInterval instead
    bool getOctaveRepeat() override;
    void setOctaveRepeat(bool o) override;
    
    //
    bool getSort() override;
    void setSort(bool s) override;
    
    //
    bool getCanSort() override;
    void setCanSort(bool s) override;
    
    //
    bool getUniquify() override;
    void setUniquify(bool u) override;
    
    //
    bool getCanUniquify() override;
    void setCanUniquify(bool u) override;
    
    //
    const string getTuningName() override;
    void setTuningName(string name) override;
    
    //
    const string getTuningDescription() override;
    void setTuningDescription(string description) override;
    
    // scala content
    const string getScalaContent();
    void setScalaContent(string sc);
    
    // scala filename
    const string getScalaFileName();
    void setScalaFilename(string fn);
    
    //
    const string getDebugDescription() override;
    
    //
    const string getUserDescription() override;
    void setUserDescription(string comment) override;
    const string getParameterDescription() override;
    
    //
    bool getCanFavorite() override;
    
    // Scala
    bool getCanScala() override;
    void setCanScala(bool can_scala) override;
    ScalaFile tuningAsScala() override;
    String defaultScalaName() override;
    String scalaComments() override;
    
    
    // drawing
    bool canPaintTuning() override;
    void paint(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds) override;
    
    // string helper
    friend ostream& operator <<(ostream&, ScalaTuningImp& m);
    
private:
    // keep as int
    int _mode {-1}; // _mode=-1=NOP, _mode >= 0: normalize by processedArray[mode]
    unsigned long _noteNumberMiddleC {Tuning::noteNumberMiddleCDefault};
    unsigned long _noteNumberMiddleCMin {Tuning::noteNumberMiddleCMin};
    unsigned long _noteNumberMiddleCMax {WilsonicProcessorConstants::numMidiNotes - 1};
    
    //
    float _frequencyMiddleC {Tuning::frequencyMiddleCDefault};
    float _frequencyMiddleCMin {Tuning::frequencyMiddleCMin};
    float _frequencyMiddleCMax {Tuning::frequencyMiddleCMax};
    
    //
    int _octaveMiddleC {Tuning::octaveMiddleCDefault}; // keep as int
    int _octaveMiddleCMin {Tuning::octaveMiddleCMin}; // keep as int
    int _octaveMiddleCMax {Tuning::octaveMiddleCMax}; // keep as int
    
    //
    bool _canNPOOverride = false;

    // keep as int
    // notes per octave "npo" override
    int _npoOverride = Tuning::npoOverrideDefault;
    int _npoOverrideMin = Tuning::npoOverrideMin;
    int _npoOverrideMax = Tuning::npoOverrideMax;
    bool _npoOverrideEnable = Tuning::npoOverrideEnableDefault;

    //
    float _octave {TuningConstants::defaultOctave};
    float _octaveMin {TuningConstants::minPeriod};
    float _octaveMax {TuningConstants::maxPeriod};
    float _repeatingInterval {TuningConstants::defaultPeriod};
    
    // unused for Scala files...use repeatingInterval instead
    bool _octaveReduce = false;
    bool _octaveRepeat = true;
    
    //
    bool _sort = false;
    bool _canSort = false;
    
    //
    bool _uniquify = false;
    
    // some tunings should not uniquify, i.e., CPG, Pascal, Peirce
    bool _canUniquify = false;
    
    // note: need to encode UTF8...no special characters.
    // *short* human-readable title...i.e., "MOS", "Hexany", "Co-Prime Grid"
    string _tuningName {""};
    
    // *short* human-readable desc.., i.e., "G=0.5833", "A=3,B=5,C=7,D=9"
    string _tuningDescription {""};
    
    // 140 char limit...utf8 encoded.
    string _tuningUserDescription {""};
    
    // scala content
    string _scalaContent {""};
    
    // scala filename
    string _scalaFileName {""};
    
    // Some tunings cannot be represented by Favorites...i.e., arbitrary scala files
    bool _canFavorite = true;
    
    // some tunings cannot be represented by scala, i.e., CPG, Pascal
    bool _canScala = true;
    ScalaFile _scalaFile;
    
    // pitch class
    MicrotoneArray _microtoneArray;
    
    // pitch class after being reduced, sorted, and uniquified
    MicrotoneArray _processedArray {};
    MicrotoneArray _processedArrayNPO {};
    map<int, int> _processedArrayNPOMap {}; // npo indices -> npo override indices

    // arrays of triads from this processed master set
    vector<PythagoreanMeans> _proportionalTriads {};
    vector<PythagoreanMeans> _geometricTriads {};
    vector<PythagoreanMeans> _subcontraryTriads {};
    vector<PythagoreanMeans> _allTriads {};
    
    // Maps midi note numbers to the source microtone
    array<Microtone_p, WilsonicProcessorConstants::numMidiNotes> _microtoneNN {};
    
    // completion handlers
    function<void()> _postProcessBlock;
    function<void()> _completionBlock;
    
    // "has-a" TuningTable
    TuningTableImp _tuningTable {};
    
    // lock
    CriticalSection _lock;
    
    // private methods
    void _update() override;
    
    // only works for scales with rational microtones
    void _analyzeIntervals();
    
    // works for any octave-based processed array of microtones
    void _analyzeProportionalTriads();
};
