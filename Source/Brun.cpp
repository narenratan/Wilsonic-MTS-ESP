/**
 * @file Brun.cpp
 * @brief Contains the implementation of the Brun class.
 * @details This file was created on 14 Feb 2021 at 3:01:54pm by Marcus W. Hobbs.
 */

#include "Brun.h"
#include "BrunMicrotone.h"
#include "Microtone.h"

#pragma mark - statics

/**
 * @brief Display mode names.
 */
const StringArray Brun::__displayModeNames {
    "Cartesian",
    "Horogram",
    "Horogram Inverse",
    "Gral"
};

#pragma mark - lifecycle

/**
 * @brief Default constructor.
 */
Brun::Brun()
: Brun(absoluteMaxLevel, defaultLevel, defaultGenerator, defaultPeriod) {
}

/**
 * @brief Constructor with parameters.
 * @param maxLevel The maximum level.
 * @param level The level.
 * @param generator The generator.
 * @param period The period.
 */
Brun::Brun(unsigned long maxLevel, unsigned long level, float generator, float period)
: _maxLevel(maxLevel)
, _level(level)
, _levelGral(level)
, _generator(generator)
, _murchana(0)
, _displayMode(DisplayMode::Cartesian)
{
    setNPOOverride(12);
    setCanNPOOverride(true); // can NOT use Gral when NPO Override is enabled
    setNPOOverrideEnable(false);
    setCanUniquify(false);
    setUniquify(false);
    setCanSort(true);
    setSort(true);
    setOctaveReduce(true);
    setOctaveRepeat(true);
    setOctave(period); ///
    setNoteNumberMiddleC(60);
    setTuningName("MOS");
    setCanScala(true);

    // postProcess and update
    setPostProcessPreTuningUpdate([this](){TuningImp::_gralPostProcessBlockImp();});
    _brunUpdate();
}

#pragma mark - static

/**
 * @brief Returns a 2D array of Microtone pointers.
 * @param minLevel The minimum level.
 * @param maxLevel The maximum level.
 * @param zero The zero Microtone pointer.
 * @param one The one Microtone pointer.
 * @return A 2D array of Microtone pointers.
 *
 * This function generates a 2D array of Microtone pointers, where each row corresponds to a level and each column corresponds to a Microtone at that level.
 * The function starts with an initial array of two Microtones, zero and one, and then for each level, it generates a new array by inserting the freshman sum of each pair of adjacent Microtones in the previous array.
 * The function asserts that the minimum and maximum levels are within the absolute minimum and maximum levels.
 */
vector<vector<Microtone_p>> Brun::brunArray(unsigned long minLevel, unsigned long maxLevel, Microtone_p zero, Microtone_p one) {
    // Assert that the minimum and maximum levels are within the absolute minimum and maximum levels.
    jassert(minLevel >= absoluteMinLevel);
    jassert(maxLevel <= absoluteMaxLevel);

    // Initialize the 2D array of Microtone pointers and the initial and previous arrays.
    vector<vector<Microtone_p>> levelArray { {} };
    vector<Microtone_p> initialArray { {zero}, {one} };
    vector<Microtone_p> previousArray {initialArray};
    levelArray.push_back(previousArray);

    // For each level, generate a new array by inserting the freshman sum of each pair of adjacent Microtones in the previous array.
    for (unsigned long level = minLevel + 1; level <= maxLevel; level++) {
        vector<Microtone_p> workingArray {previousArray};
        for (unsigned long j = 0; j < workingArray.size() - 1; j += 2) {
            auto left = workingArray[j];
            auto right = workingArray[j + 1];
            auto freshmanSum = Microtone::freshmanSum(left, right);
            workingArray.insert(workingArray.begin() + (long)j + 1, freshmanSum);
        }
        levelArray.push_back(workingArray);
        previousArray = workingArray;
    }

    // Return the 2D array of Microtone pointers.
    return levelArray;
}

/**
 * @brief Static 2D array of Microtone pointers.
 */
vector<vector<Microtone_p>> Brun::__levelArray;

/**
 * @brief Returns the level array.
 * @return The level array.
 */
vector<vector<Microtone_p>> Brun::getLevelArray() {
    if (__levelArray.size() == 0) {
        Microtone_p zero = make_shared<Microtone>(0, 1);
        Microtone_p one = make_shared<Microtone>(1, 1);
        __levelArray = Brun::brunArray(absoluteMinLevel, absoluteMaxLevel, zero, one);
    }

    return __levelArray;
}

/**
 * @brief Static MicrotoneArray for harmonic limit Cartesian.
 */
MicrotoneArray Brun::__harmonicLimitCartesian {};

/**
 * @brief Returns the harmonic limit Cartesian.
 * @param period The period.
 * @return The harmonic limit Cartesian.
 */
MicrotoneArray Brun::getHarmonicLimitCartesian(float period) {
    if ( __harmonicLimitCartesian.count() == 0 ) {
        __harmonicLimitCartesian = MicrotoneArray::microtoneArrayHarmonicLimit(12, period);
    }

    return __harmonicLimitCartesian;
}

/**
 * @brief Static MicrotoneArray for harmonic limit Horogram.
 */
MicrotoneArray Brun::__harmonicLimitHorogram {};

/**
 * @brief Returns the harmonic limit Horogram.
 * @param period The period.
 * @return The harmonic limit Horogram.
 */
MicrotoneArray Brun::getHarmonicLimitHorogram(float period) {
    if (__harmonicLimitHorogram.count() == 0) {
        __harmonicLimitHorogram = MicrotoneArray::microtoneArrayHarmonicLimit (12, period);
    }

    return __harmonicLimitHorogram;
}

/**
 * @brief Static MicrotoneArray for harmonic limit Horogram Inverse.
 */
MicrotoneArray Brun::__harmonicLimitHorogramInverse {};

/**
 * @brief Returns the harmonic limit Horogram Inverse.
 * @param period The period.
 * @return The harmonic limit Horogram Inverse.
 */
MicrotoneArray Brun::getHarmonicLimitHorogramInverse(float period) {
    if (__harmonicLimitHorogramInverse.count() == 0) {
        __harmonicLimitHorogramInverse = MicrotoneArray::microtoneArrayHarmonicLimit (12, period);
    }

    return __harmonicLimitHorogramInverse;
}

/**
 * @brief Returns a MicrotoneArray.
 * @param level The level.
 * @param g The generator.
 * @return A MicrotoneArray.
 */
MicrotoneArray Brun::brunArray(unsigned long level, float g) {
    return brunArray(level, g, absoluteMinLevel, absoluteMaxLevel);
}

/**
 * @brief Returns a MicrotoneArray.
 * @param level The level.
 * @param g The generator.
 * @param minBrunLevel The minimum Brun level.
 * @param maxBrunLevel The maximum Brun level.
 * @return A MicrotoneArray.
 * 
 * This function generates a MicrotoneArray based on the provided parameters. 
 * It uses the Brun algorithm to generate the array.
 * The level and generator parameters are clamped within the range of absoluteMinLevel and absoluteMaxLevel.
 * The function then iterates over the level, adding Microtones to the array.
 * The Microtones are generated using a zigzag algorithm.
 */
MicrotoneArray Brun::brunArray(unsigned long level, float g, unsigned long minBrunLevel, unsigned long maxBrunLevel) {
    // Assert that the level and generator are within the valid range
    jassert(level >= absoluteMinLevel && level <= absoluteMaxLevel);
    jassert(g >= 0.f && g <= 1.f);

    // Clamp the level within the range of minBrunLevel and maxBrunLevel
    unsigned long l = clamp(level, minBrunLevel, maxBrunLevel);

    // Initialize variables for the Brun algorithm
    // mosA and mosB are the two numbers we are comparing in the algorithm
    // mosX1, mosX2, mosY1, mosY2 are used for the zigzag algorithm
    // num and den are the numerator and denominator of the fraction we are calculating
    // tmpf and tmpui are temporary variables used for swapping values
    float mosA = 1.f;
    float mosB = g;
    unsigned long mosX1 = 1;
    unsigned long mosX2 = 0;
    unsigned long mosY1 = 0;
    unsigned long mosY2 = 1;
    unsigned long i = 0;
    unsigned long num = 1;
    unsigned long den = 1;
    float tmpf = 0.f;
    unsigned long tmpui = 0;

    // Initialize the return value
    // This will be a MicrotoneArray, which is a collection of Microtones
    MicrotoneArray retVal;

    // Iterate over the level
    // The level is the depth of the Brun algorithm
    // Each iteration adds a new Microtone to the array
    for (i = 0; i < l + 1; i++) {
        // Add a new Microtone to the array
        retVal.addMicrotone(make_shared<Microtone>(num, den));

        // Update the variables for the next iteration
        // This is the core of the Brun algorithm
        num = 2 * mosY1 + mosY2;
        den = 2 * mosX1 + mosX2;
        mosA = mosA - mosB;
        mosX2 = mosX1 + mosX2;
        mosY2 = mosY1 + mosY2;

        // Zigzag algorithm
        // If mosB is greater than mosA, swap the values of mosA and mosB, mosX1 and mosX2, mosY1 and mosY2
        // This ensures that the algorithm always compares the smaller number to the larger number
        if (mosB > mosA) {
            tmpf = mosA;   mosA = mosB;   mosB = tmpf;
            tmpui = mosX1; mosX1 = mosX2; mosX2 = tmpui;
            tmpui = mosY1; mosY1 = mosY2; mosY2 = tmpui;
        }
    }

    // Return the generated MicrotoneArray
    return retVal;
}

/**
 * @brief Returns a Microtone pointer.
 * @param level The level.
 * @param generator The generator.
 * @return A Microtone pointer.
 */
Microtone_p Brun::brun(unsigned long level, float generator) {
    jassert(level >= absoluteMinLevel && level <= absoluteMaxLevel);
    jassert(generator >= 0.f && generator <= 1.f);

    float mosA = 1.f;
    float mosB = generator;
    unsigned long mosX1 = 1;
    unsigned long mosX2 = 0;
    unsigned long mosY1 = 0;
    unsigned long mosY2 = 1;
    unsigned long i;
    unsigned long num = 1;
    unsigned long den = 1;
    float tmpf = 0.f;
    unsigned long tmpui = 0;

    for (i = 0; i < level; i++) {
        num = 2 * mosY1 + mosY2;
        den = 2 * mosX1 + mosX2;
        mosA = mosA - mosB;
        mosX2 = mosX1 + mosX2;
        mosY2 = mosY1 + mosY2;
        if (mosB > mosA) {
            tmpf = mosA;   mosA = mosB;   mosB = tmpf;
            tmpui = mosX1; mosX1 = mosX2; mosX2 = tmpui;
            tmpui = mosY1; mosY1 = mosY2; mosY2 = tmpui;
        }
    }

    return make_shared<Microtone>(static_cast<unsigned long>(num), static_cast<unsigned long>(den));
}

/**
 * @brief Returns a MicrotoneArray.
 * @param l The level.
 * @param g01 The generator.
 * @param inMurchana The Murchana.
 * @return A MicrotoneArray.
 */
MicrotoneArray Brun::_microtoneArrayBrun(unsigned long l, float g01, unsigned long inMurchana) {
    jassert(l >= absoluteMinLevel && l <= absoluteMaxLevel);
    jassert(g01 >= 0.f && g01 <= 1.f);
    // don't need to assert murchana because we'll clamp it below

    //
    MicrotoneArray scaleDegrees;
    auto brunArray = Brun::brunArray(l, g01);
    auto brun = Brun::brun(l, g01);
    auto const numScaleDegrees = brun->getDenominator();
    auto level = absoluteMinLevel;
    unsigned long brunIndex = 0;

    // this is an unusual pattern...auto set and display mode are not automated but murchana is.
    if (_autoSetMurchana) {
        _murchana = numScaleDegrees / 2;
        inMurchana = _murchana;
    }
    auto const murchana = static_cast<float>(inMurchana % numScaleDegrees);

    for (unsigned long i = 0; i < numScaleDegrees; i++) {
        auto degree = static_cast<int>(static_cast<float>(i) - murchana);
        auto p = static_cast<float>(degree) * g01;
        jassert(!std::isnan(p) && !std::isinf(p));
        while (p < 0.f) {
            p += 1.f;
        }
        while (p > 1.f) {
            p -= 1.f;
        }
        jassert(p >= 0.f && p <= 1.f);
        auto m = make_shared<BrunMicrotone>(p, degree, level);
        scaleDegrees.addMicrotone(m);

        // don't advance "level" at the end of the scale
        if (i == numScaleDegrees - 1)
            break;

        // advance "level" if we have passed the number of notes in the denominator of the current level
        auto const brunNumber = brunArray.microtoneAtIndex(brunIndex);
        auto const den = brunNumber->getDenominator();
        if (i + 1 == den) {
            level++;
            brunIndex++;
            brunIndex = min(brunIndex, brunArray.count() - 1);
        }
    }

    return scaleDegrees;
}

#pragma mark - instance methods

/**
 * @brief Returns the maximum level.
 * @return The maximum level.
 */
unsigned long Brun::getMaxLevel() {
    return _maxLevel;
}

/**
 * @brief Sets the maximum level.
 * @param newMaxLevel The new maximum level.
 */
void Brun::setMaxLevel(unsigned long newMaxLevel) {
    // Lock
    const ScopedLock sl(_lock);

    auto const ml = min(absoluteMaxLevel, max(absoluteMinLevel, newMaxLevel));
    if (ml != _maxLevel) {
        _maxLevel = ml;
        _level = min(_level, _maxLevel);
        _levelGral = _validLevelGral(_level);
        _brunUpdate();
    }
}

/**
 * @brief Returns the level.
 * @return The level.
 */
unsigned long Brun::getLevel() {
    return _level;
}

/**
 * @brief Sets the level.
 * @param newLevel The new level.
 */
void Brun::setLevel(unsigned long newLevel) {
    // Lock
    const ScopedLock sl(_lock);

    auto l = min(newLevel, _maxLevel);
    l = max(l, absoluteMinLevel);
    if (l != _level) {
        _level = l;
        _levelGral = _validLevelGral(_levelGral);
        _brunUpdate();
    }
}

/**
 * @brief Returns the levelGral.
 * @return The levelGral.
 */
unsigned long Brun::getLevelGral() {
    return _levelGral;
}

/**
 * @brief Sets the levelGral.
 * @param newGralLevel The new levelGral.
 */
void Brun::setLevelGral(unsigned long newGralLevel) {
    // Lock
    const ScopedLock sl(_lock);

    if (newGralLevel != _levelGral) {
        _levelGral = _validLevelGral(newGralLevel);
        _brunUpdate();
    }
}

/**
 * @brief Assuming _level is valid, return a valid levelGral.
 * @param newLevelGral The new levelGral.
 * @return The valid levelGral.
 */
unsigned long Brun::_validLevelGral(unsigned long newLevelGral) {
    // Lock
    const ScopedLock sl(_lock);

    // Simplified code
    return min(max(newLevelGral, absoluteMinLevel), min(_level, _maxLevel));
}

/**
 * @brief Returns the label array.
 * @return The label array.
 */
vector<string> Brun::getLabelArray() {
    return _labelArray;
}

/**
 * @brief Returns the true number of notes per octave--i.e., it disregards whether NPO Override is enabled.
 * @return The notes per octave.
 */
unsigned long Brun::getNotesPerOctave() {
    return getProcessedArrayCount(); // do NOT use _processedArrayNPO...
}

/**
 * @brief Returns the display mode.
 * @return The display mode.
 */
Brun::DisplayMode Brun::getDisplayMode() {
    return _displayMode;
}

/**
 * @brief Sets the display mode.
 * @param newDisplayMode The new display mode.
 */
void Brun::setDisplayMode(DisplayMode newDisplayMode) {
    _displayMode = newDisplayMode;
    callOnTuningUpdate();
}

/**
 * @brief Returns the generator in pitch space [0,1).
 * @return The generator.
 */
float Brun::getGenerator() {
    return _generator;
}

/**
 * @brief Sets the generator.
 * @param newGenerator The new generator.
 */
void Brun::setGenerator(float newGenerator) {
    // Lock
    const ScopedLock sl(_lock);

    if(newGenerator >= minGenerator && newGenerator < maxGenerator) {
        if(WilsonicMath::floatsAreNotEqual(newGenerator, _generator)) {
            _generator = newGenerator;
            _brunUpdate();
        }
    }
}

/**
 * @brief Returns the generator with frequency.
 * @return The generator with frequency.
 */
float Brun::getGeneratorWithFrequency() {
    auto const f = powf(getOctave(), _generator);

    return f;
}

/**
 * @brief Returns the generator given frequency.
 * @param frequency The frequency.
 * @return The generator.
 */
float Brun::getGeneratorGivenFrequency(float frequency) {
    auto const f = jlimit(1.f, getOctave(), frequency);
    auto const g = logf(f) / logf(getOctave());

    return g;
}

/**
 * @brief Sets the generator with frequency.
 * @param frequency The frequency.
 */
void Brun::setGeneratorWithFrequency(float frequency) {
    // Lock
    const ScopedLock sl(_lock);

    if(frequency >= 1.f && frequency < getOctave()) {
        auto const p = logf(frequency) / logf(getOctave());
        if(WilsonicMath::floatsAreNotEqual(p, _generator)) {
            _generator = p;
            _brunUpdate();
        }
    }
}

float Brun::getGeneratorWithCents() {
    // _tuning.getOctave is actually the period.
    // cents assumes period of 2
    return 1200.f * _generator * getOctave() / 2.f;
}

float Brun::getGeneratorGivenCents(float cents) {
    auto const maxG = 1200.f * getOctave() / 2.f;
    auto const c = jlimit(0.f, maxG, cents);
    auto const g = c / maxG;

    return g;
}

void Brun::setGeneratorWithCents(float cents) {
    // Lock
    const ScopedLock sl(_lock);

    // _tuning.getOctave is actually the period.
    // cents assumes period of 2, so we divide out octave and multiply by period
    auto const maxG = 1200.f * getOctave() / 2.f;
    if (cents >= 0.f && cents < maxG) {
        auto p = cents / maxG;
        if(WilsonicMath::floatsAreNotEqual(p, _generator)) {
            _generator = p;
            _brunUpdate();
        }
    }
}

unsigned long Brun::getMurchana() {
    return _murchana;
}

// consider making murchana a float on [0,1)
// that would make it independent of _notesPerOctave, which has race conditions
// Also, mod'ing on npo doesn't work when you're rendering multiple levels in one graph
void Brun::setMurchana(unsigned long m) {
    // Lock
    const ScopedLock sl(_lock);

    jassert(getNotesPerOctave() > 0);
    auto const newMurchana = m % getNotesPerOctave();
    if (newMurchana != _murchana) {
        _murchana = newMurchana;
        _brunUpdate();
    }
}

bool Brun::getAutoMurchana() {
    return _autoSetMurchana;
}

void Brun::setAutoMurchana(bool autoMurchana) {
    // Lock
    const ScopedLock sl(_lock);

    if (_autoSetMurchana != autoMurchana) {
        _autoSetMurchana = autoMurchana;
        _brunUpdate();
    }
}

void Brun::setGralHexScale(float newScale) {
    // Lock
    const ScopedLock sl(_lock);

    newScale = jlimit(0.1f, 5.f, newScale);
    if(WilsonicMath::floatsAreNotEqual(newScale, _gralHexScale)) {
        _gralHexScale = newScale;
        _brunUpdate();
    }
}

float Brun::getGralHexScale() {
    return _gralHexScale;
}

void Brun::setGralHexRotationRadians(float newRotationRadians) {
    // Lock
    const ScopedLock sl(_lock);

    newRotationRadians = jlimit(-MathConstants<float>::pi, MathConstants<float>::pi, newRotationRadians);
    if(WilsonicMath::floatsAreNotEqual(newRotationRadians, _gralHexRotationRadians)) {
        _gralHexRotationRadians = newRotationRadians;
        _brunUpdate();
    }
}

float Brun::getGralHexRotationRadians() {
    return _gralHexRotationRadians;
}

void Brun::setGralHexShearX(float newShearX) {
    // Lock
    const ScopedLock sl(_lock);

    newShearX = jlimit(-1.f, 1.f, newShearX);
    if(WilsonicMath::floatsAreNotEqual(newShearX, _gralHexShearX)) {
        _gralHexShearX = newShearX;
        _brunUpdate();
    }
}

float Brun::getGralHexShearX() {
    return _gralHexShearX;
}

void Brun::setGralHexOriginOffsetFactorX (float newOffsetX) {
    // Lock
    const ScopedLock sl(_lock);

    newOffsetX = jlimit(-2.f, 2.f, newOffsetX);
    if (WilsonicMath::floatsAreNotEqual(newOffsetX, _gralHexOriginOffsetFactorX)) {
        _gralHexOriginOffsetFactorX = newOffsetX;
        _brunUpdate();
    }
}

float Brun::getGralHexOriginOffsetFactorX() {
    return _gralHexOriginOffsetFactorX;
}

void Brun::setGralHexOriginOffsetFactorY(float newOffsetY) {
    // Lock
    const ScopedLock sl(_lock);

    newOffsetY = jlimit(-2.f, 2.f, newOffsetY);
    if(WilsonicMath::floatsAreNotEqual(newOffsetY, _gralHexOriginOffsetFactorY)) {
        _gralHexOriginOffsetFactorY = newOffsetY;
        _brunUpdate();
    }
}

float Brun::getGralHexOriginOffsetFactorY() {
    return _gralHexOriginOffsetFactorY;
}
