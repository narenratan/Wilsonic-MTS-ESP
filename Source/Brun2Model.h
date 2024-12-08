/**
 * @file Brun2Model.h
 * @brief Contains the Brun2Model class.
 * @author Marcus W. Hobbs
 * @date Created: 3 Nov 2021 8:26:41pm
 */

#pragma once

#include <JuceHeader.h>
#include "AppVersion.h"
#include "Brun.h"
#include "ModelBase.h"
#include "TuningImp.h"
#include "Tuning_Include.h"

/**
 * @class Brun2Model
 * @brief The Brun2Model class inherits from ModelBase and ActionBroadcaster.
 */
class Brun2Model final
: public ModelBase
, public ActionBroadcaster
{
public:
    static const ParameterID getBrun2GeneratorParameterID() { return ParameterID ("BRUN2GENERATOR", AppVersion::getVersionHint()); }
    static const String getBrun2GeneratorParameterName() { return "Brun2|Generator"; }

    static const ParameterID getBrun2PeriodParameterID() { return ParameterID ("BRUN2PERIOD", AppVersion::getVersionHint()); }
    static const String getBrun2PeriodParameterName() { return "Brun2|Period"; }

    static const ParameterID getBrun2LevelParameterID() { return ParameterID ("BRUN2LEVEL", AppVersion::getVersionHint()); }
    static const String getBrun2LevelParameterName() { return "Brun2|Level"; }

    static const ParameterID getBrun2LevelGralParameterID() { return ParameterID ("BRUN2LEVELGRAL", AppVersion::getVersionHint()); }
    static const String getBrun2LevelGralParameterName() { return "Brun2|Level Gral Keyboard"; }

    static const ParameterID getBrun2MurchanaParameterID() { return ParameterID ("BRUN2MURCHANA", AppVersion::getVersionHint()); }
    static const String getBrun2MurchanaParameterName() { return "Brun2|Murchana"; }

    static const ParameterID getBrun2AutoMurchanaParameterID() { return ParameterID ("BRUN2AUTOMURCHANA", AppVersion::getVersionHint()); }
    static const String getBrun2AutoMurchanaParameterName() { return "Brun2|Auto Murchana"; }

    // lifecycle
    Brun2Model();
    ~Brun2Model() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Brun2Model)

public:
    // public methods
    shared_ptr<Tuning> getTuning() override;

    // called only once: on construction of processor
    unique_ptr<AudioProcessorParameterGroup> createParams() override;
    String getGroupID() override;
    String getGroupName() override;
    String getSubgroupSeparator() override;
    ParameterID getDesignParameterID() override; // key for this design's Favorites array
    StringArray getFavoritesParameterIDs() override; // used for Favorites
    void attachParameterListeners() override;// called only once: when assigning _avpts
    void parameterChanged(const String& parameterID, float newValue) override;
    void updateProperties() override;

    // ui methods
    void uiSetGenerator(float newGenerator);
    float uiGetGenerator();
    void uiSetGeneratorAsFrequency(float newGenerator);
    float uiGetGeneratorAsFrequency();
    void uiSetGeneratorAsCents(float newGenerator);
    float uiGetGeneratorAsCents();
    void uiSetPeriod(float newPeriod);
    float uiGetPeriod();
    vector<string> uiGetLabelArray();
    void uiSetLevel01(float newLevel); // named this way because custom component y-axis is normalized
    float uiGetLevel01();
    void uiSetLevelGral01(float newLevel); // named this way because custom component y-axis is normalized
    float uiGetLevelGral01();
    void uiSetMurchana(float newMurchana);
    float uiGetMurchana();
    void uiSetAutoMurchana(bool autoMurchana);
    bool uiGetAutoMurchana();
    void uiSetGralHexScale(float newScale);
    float uiGetGralHexScale();
    void uiSetGralHexRotationRadians(float newRotationRadians);
    float uiGetGralHexRotationRadians();
    void uiSetGralHexShearX(float newHexShearX);
    float uiGetGralHexShearX();
    void uiSetGralHexOriginOffsetFactorX(float newOffsetX);
    float uiGetGralHexOriginOffsetFactorX();
    void uiSetGralHexOriginOffsetFactorY(float newOffsetY);
    float uiGetGralHexOriginOffsetFactorY();
    int nnForDeviceSpace(Point<int> xy);

    // properties
    void uiSetDisplayMode(WilsonicProcessor& processor, int displayMode);
    int uiGetDisplayMode(WilsonicProcessor& processor);

protected:
    void detachParameterListeners() override;

private:
    shared_ptr<Brun> _brun;
    void _tuningChangedUpdateUI() override;
};

