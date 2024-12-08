/*
 ==============================================================================
 
 ScalaModel.h
 Created: 24 Sep 2022 3:57:05pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "Columns.h"
#include "DesignsModel.h"
#include "ModelBase.h"
#include "ScalaBundleModel.h"
#include "ScalaIconRenderer.h"
#include "ScalaUserModel.h"
#include "ScalaTuningImp.h"
#include "Tuning_Include.h"


// ScalaModel has to abstract both the static bundled library
// and the dynamic user library.
// So there's an extra level of abstraction: ScalaUserModel
// which implements the XML representation to reduce duplicate code.
// In contrast with the FavoritesModelV2, which only has to maintain
// the dynamic user library.

class ScalaModel final
: public ModelBase
, public ActionBroadcaster
{
public:
    // enum
    enum Library // if you change this you will break automation
    {
        Bundled = 0,
        User = 1
    };
    
    // static
    static const ParameterID getScalaLibraryParameterID() { return ParameterID ("SCALALIBRARY", AppVersion::getVersionHint()); }
    static const String getScalaUserOrBundledParameterName() { return "Scala|Library"; }
    static const ParameterID getScalaBundledTuningIDParameterID() { return ParameterID ("SCALABUNDLEDTUNINGID", AppVersion::getVersionHint()); }
    static const String getScalaBundledTuningIDParameterName() { return "Scala|Bundled Tuning ID"; }
    static const ParameterID getScalaUserTuningIDParameterID() { return ParameterID ("SCALAUSERTUNINGID", AppVersion::getVersionHint()); }
    static const String getScalaUserTuningIDParameterName() { return "Scala|User Tuning ID"; }
    static const String getScalaUserFileWasDeleted() { return "ScalaUserFileWasDeleted"; }
    static constexpr int getScalaBundledMinID() {return 1;}
    static constexpr int getScalaBundledMaxID() {return 5300;}
    static constexpr int getScalaBundledDefaultID() {return 1;}
    static constexpr int getScalaUserMinID() {return 1;}
    static constexpr int getScalaUserMaxID() {return 8192;}
    static constexpr int getScalaUserDefaultID() {return 1;}
    static StringArray getLibraryChoices() {return __libraryChoices;}
    static int getNumberOfLibraryChoices() {return 2;}
    
private:
    static const StringArray __libraryChoices;
    
public:
    // lifecycle
    ScalaModel();
    ~ScalaModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScalaModel)
    
public:
    // ModelBase (public)
    unique_ptr<AudioProcessorParameterGroup> createParams() override;
    String getGroupID() override;
    String getGroupName() override;
    String getSubgroupSeparator() override;
    ParameterID getDesignParameterID() override; // key for this design's Favorites array
    StringArray getFavoritesParameterIDs() override; // used for Favorites
    void attachParameterListeners() override; // called only once: when assigning _avpts
    void parameterChanged(const String& parameterID, float newValue) override;
    void updateProperties() override;
    shared_ptr<Tuning> getTuning() override;
    
    // public methods
    void recallScalaByRow(int row);
    void recallPreviousScala();
    void recallNextScala();
    void deleteScala(int favorite_index); // sends message if successful
    bool addTuningToScalaUserLibrary(shared_ptr<Tuning> current_tuning);
    int getSelectedRowNumber();
    void importUserScalaFiles(Array<File> file_array);
    shared_ptr<ScalaTuningImp> getMorphFor(ScalaModel::Library library, int library_id);
    unordered_map<int, int> getIntegrityCheck();

    // ui/host
    ScalaModel::Library uiGetLibrary();
    void uiSetLibrary(ScalaModel::Library library);
    void uiSetBundledID(int bundle_id);
    int uiGetBundledID();
    void uiSetUserID(int user_id);
    int uiGetUserID();
    
    //
    Font getFont(); // passthrough of librarymodel
    
    // TableListBoxModel delegates
    int getNumRows();
    String getCellTooltip(int rowNumber, int columnId);
    int getColumnAutoSizeWidth(int columnId);
    void sortOrderChanged(int newSortColumnId, bool isForwards);
    String getText(int rowNumber, int columnId);
    void setText(String columnName, const int rowNumber, const String& newText);
    int getIsSelectedForRow(const int rowNumber) const;
    void selectRow(const int rowNumber); // sets selectedID
    vector<Columns> getColumns();
    shared_ptr<Image> getIcon(int rowNumber);
    
protected:
    void detachParameterListeners() override;
    
private:
    // private members
    shared_ptr<ScalaTuningImp> _scalaTuning;
    ScalaModel::Library _library = ScalaModel::Library::Bundled;
    unique_ptr<ScalaBundleModel> _bundledScalaLibrary;
    unique_ptr<ScalaUserModel> _userScalaLibrary;
    
    // private methods
    void _tuningChangedUpdateUI() override;
};
