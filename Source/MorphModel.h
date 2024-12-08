/*
  ==============================================================================

    MorphModel.h
    Created: 17 Dec 2023 1:41:54pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppVersion.h"
#include "ModelBase.h"
#include "Tuning_Include.h"

class AppTuningModel;
class Morph;
class MorphABModel;
class Tuning;
class WilsonicProcessor;

/**
 * @class MorphModel
 * @brief The MorphModel class inherits from ModelBase and ActionBroadcaster.
 */
class MorphModel final
: public ModelBase
, public ActionBroadcaster
{
public:
    /**
     * @brief Static methods for getting parameter IDs and names.
     */
    static const ParameterID getMorphFavoriteAParameterID() { return ParameterID("MORPHFAVORITEAID", AppVersion::getVersionHint()); }
    static const String getMorphFavoriteAParameterName() { return "Morph|Favorite A ID"; }
    
    static const ParameterID getMorphFavoriteBParameterID() { return ParameterID("MORPHFAVORITEBID", AppVersion::getVersionHint()); }
    static const String getMorphFavoriteBParameterName() { return "Morph|Favorite B ID"; }

    static const int getMorphDefaultID();

    static const ParameterID getMorphInterpolationParameterID() { return ParameterID("MORPHINTERPOLATIONVALUE", AppVersion::getVersionHint()); }
    static const String getMorphInterpolationParameterName() { return "Morph|Interpolation Value"; }
    static constexpr float morphInterpolationParameterMin = 0.f;
    static constexpr float morphInterpolationParameterMax = 1.f;

    static const ParameterID getMorphInterpolationTypeParameterID() { return ParameterID("MORPHINTERPOLATIONTYPE", AppVersion::getVersionHint()); }
    static const String getMorphInterpolationTypeParameterName() { return "Morph|Interpolation Type"; }
    
    
    /**
     * @brief Lifecycle methods.
     */
public:
    MorphModel(WilsonicProcessor& processor);
    ~MorphModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MorphModel)

public:
    /**
     * @brief Public methods.
     */
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

    //
    void uiSetID_A(int ID_A);
    int uiGetID_A();
    void uiSetID_B(int ID_B);
    int uiGetID_B();
    void uiSetInterpolationValue(float x);
    float uiGetInterpolationValue();
    void uiSetInterpolationTypeIndex(int i);
    int uiGetInterpolationTypeIndex();
    void uiSwapTunings();
    
protected:
    /**
     * @brief Protected methods.
     */
    void detachParameterListeners() override;

private:
    /**
     * @brief Private members and methods.
     */
    WilsonicProcessor& _processor;
    int _ID_A = 0; // "source" favorites ID
    shared_ptr<MorphABModel> _A; // the "source" tuning
    int _ID_B = 0; // "target" favorites ID
    shared_ptr<MorphABModel> _B; // the "target" tuning
    shared_ptr<Morph> _morph; // the final interpolated tuning
    void _tuningChangedUpdateUI() override;
};
