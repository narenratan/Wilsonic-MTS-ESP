/*
 ==============================================================================

 DesignsModel.h
 Created: 1 Nov 2021 8:01:35pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "AppVersion.h"
#include "DesignsProtocol.h"
#include "ModelBase.h"
#include "Tuning_Include.h"

// ADD NEW SCALE DESIGN HERE

// forward declarations
class AppTuningModel;
class Brun2Model;
class CoPrimeModel;
class CPSModel;
class DesignsModel;
class DiamondsModel;
class EqualTemperamentModel;
class EulerGenusModel;
class FavoritesModelV2;
class MorphModel;
class PartchModel;
class Persian17NorthIndianModel;
class PresetsModel;
class RecurrenceRelationModel;
class ScalaModel;
class TritriadicModel;
class WilsonicProcessor;

/**
 * @brief Model for the scale designs of the app. The root parameter DesignsModel is the only model allowed to update the global app tuning.
 */
class DesignsModel final 
: public ModelBase
, public ActionBroadcaster
, private ActionListener
, private DesignsProtocol
{
public:
    static const ParameterID getDesignsParameterID() { return ParameterID ("DESIGNS", AppVersion::getVersionHint()); }
    static const String getDesignsParameterName() { return "Wilsonic|Designs"; }

    // ADD NEW SCALE DESIGN HERE

    // static methods for DesignProtocol Action Messages
    static const String getShowBrunTuningMessage() { return "showBrunTuning";}
    static const String getShowCoPrimeTuningMessage() { return "showCoPrimeTuning";}
    static const String getShowCPSTuningMessage() { return "showCPSTuning";}
    static const String getShowDiamondsTuningMessage() { return "showDiamondsTuning";}
    static const String getShowEqualTemperamentTuningMessage() { return "showEqualTemperamentTuning";}
    static const String getShowEulerGenusTuningMessage() { return "showEulerGenusTuning";}
    static const String getShowPartchTuningMessage() { return "showPartchTuning";}
    static const String getShowPersian17NorthIndianTuningMessage() { return "showPersian17NorthIndianTuning";}
    static const String getShowPresetsTuningMessage() { return "showPresetsTuning";}
    static const String getShowRecurrenceRelationTuningMessage() { return "showRecurrenceRelationTuning";}
    static const String getShowScalaTuningMessage() { return "showScalaTuning";}
    static const String getShowTritriadicTuningMessage() { return "showTritriadicTuning";}
    static const String getShowMorphTuningMessage() { return "showMorphTuning";}

    // ADD NEW SCALE DESIGN HERE

    // static methods for tuning changed action messages
    static const String getBrunTuningChangedActionMessage() { return "BrunTuningChangedActionMessage"; }
    static const String getCoPrimeTuningChangedActionMessage() { return "CoPrimeTuningChangedActionMessage"; }
    static const String getCPSTuningChangedActionMessage() { return "CPSTuningChangedActionMessage"; }
    static const String getDiamondsTuningChangedActionMessage() { return "DiamondsTuningChangedActionMessage";}
    static const String getEqualTemperamentTuningChangedActionMessage() { return "EqualTemperamentTuningChangedActionMessage"; }
    static const String getEulerGenusTuningChangedActionMessage() { return "EulerGenusTuningChangedActionMessage"; }
    static const String getPartchTuningChangedActionMessage() { return "PartchTuningChangedActionMessage";}
    static const String getPersian17NorthIndianTuningChangedActionMessage() { return "Persian17NorthIndianTuningChangedActionMessage"; }
    static const String getPresetsTuningChangedActionMessage() { return "PresetsTuningChangedActionMessage"; }
    static const String getRecurrenceRelationTuningChangedActionMessage() { return "RecurrenceRelationTuningChangedActionMessage"; }
    static const String getRecurrenceRelationTuningDivergedActionMessage() { return "RecurrenceRelationTuningDivergedActionMessage"; }
    static const String getScalaTuningChangedActionMessage() { return "ScalaTuningChangedActionMessage"; }
    static const String getTritriadicTuningChangedActionMessage() { return "TritriadicTuningChangedActionMessage"; }
    static const String getMorphTuningChangedActionMessage() { return "MorphTuningChangedActionMessage";}
    static const String getAppTuningChangedActionMessage() { return "AppTuningChangedActionMessage";} // UNUSED
    
    // lifecycle
    DesignsModel(WilsonicProcessor& processor);
    ~DesignsModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DesignsModel)

public:
    /**
     * @brief Called only once: on construction of processor. Creates the parameters.
     * @return A unique pointer to the AudioProcessorParameterGroup.
     */
    unique_ptr<AudioProcessorParameterGroup> createParams() override;

    String getGroupID() override;
    String getGroupName() override;
    String getSubgroupSeparator() override;
    ParameterID getDesignParameterID() override; // key for this design's Favorites array: for DesignArray it's weird
    StringArray getFavoritesParameterIDs() override; // used for Favorites
    void attachParameterListeners() override;
    void parameterChanged(const String& parameterID, float newValue) override;
    void updateProperties() override;
    shared_ptr<Tuning> getTuning() override; // returns nullptr
    
    // ADD NEW SCALE DESIGN HERE

    // public methods
    shared_ptr<AppTuningModel> getAppTuningModel();
    shared_ptr<Brun2Model> getBrun2Model();
    shared_ptr<CoPrimeModel> getCoPrimeModel();
    shared_ptr<CPSModel> getCPSModel();
    shared_ptr<DiamondsModel> getDiamondsModel();
    shared_ptr<EqualTemperamentModel> getEqualTemperamentModel();
    shared_ptr<EulerGenusModel> getEulerGenusModel();
    shared_ptr<FavoritesModelV2> getFavoritesModelV2();
    shared_ptr<MorphModel> getMorphModel();
    shared_ptr<PartchModel> getPartchModel();
    shared_ptr<Persian17NorthIndianModel> getPersian17NorthIndianModel();
    shared_ptr<PresetsModel> getPresetsModel();
    shared_ptr<RecurrenceRelationModel> getRecurrenceRelationModel();
    shared_ptr<ScalaModel> getScalaModel();
    shared_ptr<TritriadicModel> getTritriadicModel();

    void setApvts(shared_ptr<AudioProcessorValueTreeState>);
    unsigned long getNumDesigns();
    const StringArray getDesignsNames();
    void uiSetDesign(unsigned long index = 0);
    void uiStoreScala(); // stores current design as a Scala file
    void uiStoreFavorite(); // stores current design and its params
    void favoritesSetDesign(unsigned long index = 0);
    void actionListenerCallback(const String&) override;

private:
    // private members
    WilsonicProcessor& _processor;

    // ADD NEW SCALE DESIGN HERE

#pragma mark - Tuning Models
    shared_ptr<Brun2Model> _brun2Model;
    shared_ptr<CoPrimeModel> _coPrimeModel;
    shared_ptr<CPSModel> _cpsModel;
    shared_ptr<DiamondsModel> _diamondsModel;
    shared_ptr<EqualTemperamentModel> _equalTemperamentModel;
    shared_ptr<EulerGenusModel> _eulerGenusModel;
    shared_ptr<Persian17NorthIndianModel> _persian17NorthIndianModel;
    shared_ptr<PresetsModel> _presetsModel;
    shared_ptr<RecurrenceRelationModel> _recurrenceRelationModel;
    shared_ptr<ScalaModel> _scalaModel;
    shared_ptr<TritriadicModel> _tritriadicModel;
    shared_ptr<FavoritesModelV2> _favoritesModelV2;
    shared_ptr<MorphModel> _morphModel;
    shared_ptr<PartchModel> _partchModel;
    shared_ptr<AppTuningModel> _appTuningModel;

#pragma mark - members
    StringArray _designsNames {};
    vector<function<void()>> _functionNames {};
    StringArray _tuningChangedActionMessage {};
    vector<function<void()>> _tuningChangedFunctionNames {};
    vector<String> _tuningDesignKeys {};
    vector<function<StringArray()>> _tuningParamIDsForFavorites {};

#pragma mark - methods
    // private methods
    void _checkDesignIndex(unsigned long index);
    void _selectDesign(unsigned long index);
    void _updateAppTuning(unsigned long index);

    // ADD NEW SCALE DESIGN HERE

    // DesignsProtocol (private)
    void showBrunTuning() override;
    void showCoPrimeTuning() override;
    void showCPSTuning() override;
    void showDiamondsTuning() override;
    void showEqualTemperamentTuning() override;
    void showEulerGenusV2Tuning() override;
    void showMorphTuning() override;
    void showPartchTuning() override;
    void showPersian17NorthIndianTuning() override;
    void showPresetsTuning() override;
    void showRecurrenceRelationTuning() override;
    void showScalaTuning() override;
    void showTritriadicTuning() override;
    
    // ModelBase
    void detachParameterListeners() override;
    void _tuningChangedUpdateUI() override;
};

