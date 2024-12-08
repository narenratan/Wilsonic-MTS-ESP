/*
 ==============================================================================
 
 ScalaModel.cpp
 Created: 24 Sep 2022 3:57:05pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "ScalaModel.h"
#include "ScalaComponentMessageBus.h"

#pragma mark - statics
const StringArray ScalaModel::__libraryChoices {
    "Bundled",
    "User"
};

#pragma mark - lifecycle

ScalaModel::ScalaModel() {
    // current scala tuning...clobbered every time recallScala is called
    _scalaTuning = make_shared<ScalaTuningImp>();
    
#if 0
    // fresh start
    // 20240306: fresh start still works, since its first implementation
    {
        DBG("ScalaModel: Constructor: FRESH START");
        
        // bundle icon files
        auto bundle_icons = File(ScalaIconRenderer::getFullPathToScalaBundleIconDirectory());
        bundle_icons.deleteRecursively();
        
        // user library(xml) file
        auto user_library_xml = ScalaIconRenderer::getScalaLibraryUserFile();
        user_library_xml.deleteRecursively();
        
        // user icons
        auto user_icons = File(ScalaIconRenderer::getFullPathToScalaUserIconDirectory());
        user_icons.deleteRecursively();
        
        // user scala files
        auto user_files = ScalaIconRenderer::getScalaUserScalaDirectory();
        user_files.deleteRecursively();
    }
#endif
    
    // load bundled scala library
    auto bundle_icon_directory = ScalaIconRenderer::getFullPathToScalaBundleIconDirectory();
    _bundledScalaLibrary = make_unique<ScalaBundleModel>(bundle_icon_directory);
    
    // load/create user scala library
    auto user_library_xml = ScalaIconRenderer::getScalaLibraryUserFile();
    DBG("user scala library: " + user_library_xml.getFullPathName());
    auto user_scala_files_directory = ScalaIconRenderer::getScalaUserScalaDirectory();
    auto user_icon_directory = ScalaIconRenderer::getFullPathToScalaUserIconDirectory();
    _userScalaLibrary = make_unique<ScalaUserModel>(user_library_xml, user_scala_files_directory, user_icon_directory);
}

ScalaModel::~ScalaModel() {
    removeAllActionListeners();
    detachParameterListeners();
}

#pragma mark - public methods

shared_ptr<Tuning> ScalaModel::getTuning() {
    return _scalaTuning;
}

#pragma mark - processor processBlock

// called only once: on construction of processor

unique_ptr<AudioProcessorParameterGroup> ScalaModel::createParams() {
    // Tuning Params
    auto paramGroup = make_unique<AudioProcessorParameterGroup>
    (getGroupID(), getGroupName(), getSubgroupSeparator(),
     
     // Bundled or User
     make_unique<AudioParameterChoice>
     (ScalaModel::getScalaLibraryParameterID(),
      ScalaModel::getScalaUserOrBundledParameterName(),
      ScalaModel::getLibraryChoices(),
      0),
     
     // Bundled ID
     make_unique<AudioParameterInt>
     (ScalaModel::getScalaBundledTuningIDParameterID(),
      ScalaModel::getScalaBundledTuningIDParameterName(),
      ScalaModel::getScalaBundledMinID(),
      ScalaModel::getScalaBundledMaxID(),
      ScalaModel::getScalaBundledDefaultID()
      ),
     
     // User ID
     make_unique<AudioParameterInt>
     (ScalaModel::getScalaUserTuningIDParameterID(),
      ScalaModel::getScalaUserTuningIDParameterName(),
      ScalaModel::getScalaUserMinID(),
      ScalaModel::getScalaUserMaxID(),
      ScalaModel::getScalaUserDefaultID()
      )
     );
    
    return paramGroup;
}

String ScalaModel::getGroupID() {
    return "Scala";
}

String ScalaModel::getGroupName() {
    return "Scala";
}

String ScalaModel::getSubgroupSeparator() {
    return " | ";
}

// key for this design's Favorites array
ParameterID ScalaModel::getDesignParameterID() {
    return ParameterID("SCALA_PARAMETERID_DESIGNS", AppVersion::getVersionHint());
}

// used for Favorites
StringArray ScalaModel::getFavoritesParameterIDs() {
    
    return StringArray(getScalaLibraryParameterID().getParamID(),
                       getScalaBundledTuningIDParameterID().getParamID(),
                       getScalaUserTuningIDParameterID().getParamID()
                       );
}

// called only once: after assigning _avpts
void ScalaModel::attachParameterListeners() {
    jassert(_apvts != nullptr);
    for(auto pid : getFavoritesParameterIDs()) {
        _apvts->addParameterListener(pid, this);
    }
}

void ScalaModel::detachParameterListeners() {
    jassert(_apvts != nullptr);
    for(auto pid : getFavoritesParameterIDs()) {
        _apvts->removeParameterListener(pid, this);
    }
}

#pragma mark - parameterChanged

void ScalaModel::parameterChanged(const String& parameterID, float newValue) {
    // LIBRARY
    if(parameterID == getScalaLibraryParameterID().getParamID()) {
        _library = static_cast<ScalaModel::Library>(newValue);
        if(_library == ScalaModel::Library::Bundled) {
            auto ID = uiGetBundledID();
            auto tuning = _bundledScalaLibrary->getScalaTuningForID(ID);
            if(tuning != nullptr) {
                _scalaTuning = tuning;
                ScalaComponentMessageBus::getInstance().broadcastMessage("Selected bundled Scala file ID: " + String(ID));
            } else {
                DBG("ScalaModel::parameterChanged: Bundled tuning is nullptr for ID:" + String(ID));
                ScalaComponentMessageBus::getInstance().broadcastMessage("Error loading bundled tuning for ID: " + String(ID));
            }
        } else if(_library == ScalaModel::Library::User) {
            auto ID = uiGetUserID();
            auto tuning = _userScalaLibrary->getScalaTuningForID(ID);
            if(tuning != nullptr) {
                _scalaTuning = tuning;
                ScalaComponentMessageBus::getInstance().broadcastMessage("Selected user Scala file ID: " + String(ID));
            } else {
                DBG("ScalaModel::parameterChanged: User tuning is nullptr for ID:" + String(ID));
                ScalaComponentMessageBus::getInstance().broadcastMessage("Error loading user tuning for ID: " + String(ID));
            }
        } else {
            jassertfalse;
        }
    } else if(parameterID == getScalaBundledTuningIDParameterID().getParamID())
    {// BUNDLED ID
        auto val = jlimit(getScalaBundledMinID(), getScalaBundledMaxID(), static_cast<int>(newValue));
        if(val != static_cast<int>(newValue)) {
            DBG("ScalaModel::parameterChanged: host did not clamp bundled ID:" + String(static_cast<int>(newValue)) + ", clamping to:" + String(val));
            ScalaComponentMessageBus::getInstance().broadcastMessage("Host did not clamp bundled ID:" + String(static_cast<int>(newValue)) + ", clamping to:" + String(val));
        }
        
        // always recall the tuning, but don't set _scalaTuning unless we're in bundle library mode
        auto tuning = _bundledScalaLibrary->getScalaTuningForID(val);
        if(_library == ScalaModel::Library::Bundled && tuning != nullptr) {
            _scalaTuning = tuning;
            ScalaComponentMessageBus::getInstance().broadcastMessage("Selected bundled Scala file ID: " + String(val));
        } else if(_library == ScalaModel::Library::Bundled && tuning == nullptr) {
            //fatal error, to not be able to fetch a bundled scala tuning
            ScalaComponentMessageBus::getInstance().broadcastMessage("INSTALL ERROR: Can NOT fetch bundled scala tuning for ID: " + String(val));
        }
    } else if(parameterID == getScalaUserTuningIDParameterID().getParamID()) { // USER ID
        auto val = jlimit(getScalaUserMinID(), getScalaUserMaxID(), static_cast<int>(newValue));
        if(val != static_cast<int>(newValue)) {
            DBG("ScalaModel::parameterChanged: host did not clamp user ID:" + String(static_cast<int>(newValue)) + ", clamping to:" + String(val));
            ScalaComponentMessageBus::getInstance().broadcastMessage("Host did not clamp bundled ID:" + String(static_cast<int>(newValue)) + ", clamping to:" + String(val));
        }
        
        auto tuning = _userScalaLibrary->getScalaTuningForID(val);
        if(tuning == nullptr) {
            // means we're trying to access an ID that's been deleted
            ScalaComponentMessageBus::getInstance().broadcastMessage("Can't load User Scala for ID: " + String(val) + " because it has been deleted");
        } else if(_library == ScalaModel::Library::User) {
            _scalaTuning = tuning;
            ScalaComponentMessageBus::getInstance().broadcastMessage("Selected user Scala file ID: " + String(val));
        } else {
            //DBG("ScalaModel::parameterChanged: Recalled User scala tuning but did not set global tuning table because we're in Bundled mode");
            // this is not an error...this is because we get a stream of parameters
        }
    } else {
        jassertfalse;
    }
    
    // mark ui as needing update
    uiNeedsUpdate();
}

void ScalaModel::updateProperties() {
}

#pragma mark - update Designs model

void ScalaModel::_tuningChangedUpdateUI() {
    sendActionMessage(DesignsModel::getScalaTuningChangedActionMessage());
}

void ScalaModel::recallScalaByRow(int row_number) {
    const ScopedLock sl(_lock);
    if(_library == ScalaModel::Library::Bundled) {
        auto tuning = _bundledScalaLibrary->getScalaTuningForRow(row_number);
        uiSetBundledID(_bundledScalaLibrary->getSelectedID());
    } else {
        auto tuning = _userScalaLibrary->getScalaTuningForRow(row_number);
        uiSetUserID(_userScalaLibrary->getSelectedID());
    }
    
    // this triggers parameterChanged, which will assign the tuning and update ui
}

void ScalaModel::recallPreviousScala() {
    const ScopedLock sl(_lock);
    if(_library == ScalaModel::Library::Bundled) {
        auto tuning = _bundledScalaLibrary->recallPreviousScala();
        uiSetBundledID(_bundledScalaLibrary->getSelectedID());
    } else {
        auto tuning = _userScalaLibrary->recallPreviousScala();
        uiSetUserID(_userScalaLibrary->getSelectedID());
    }
    
    // this triggers parameterChanged, which will assign the tuning and update ui
}

void ScalaModel::recallNextScala() {
    const ScopedLock sl(_lock);
    if(_library == ScalaModel::Library::Bundled) {
        auto tuning = _bundledScalaLibrary->recallNextScala();
        uiSetBundledID(_bundledScalaLibrary->getSelectedID());
    } else {
        auto tuning = _userScalaLibrary->recallNextScala();
        uiSetUserID(_userScalaLibrary->getSelectedID());
    }
    
    // this triggers parameterChanged, which will assign the tuning and update ui
}

void ScalaModel::deleteScala(int row_number) {
    const ScopedLock sl(_lock);
    bool success = false;
    
    // BUNDLED
    if(_library == ScalaModel::Library::Bundled) {
        DBG("ScalaModel::deleteScala: can not delete read-only scala file");
        ScalaComponentMessageBus::getInstance().broadcastMessage("Can not delete read-only scala file");

        return;
    }
    // USER
    else {
        auto const ID = _userScalaLibrary->getIDForRow(row_number);
        if(ID == -1) {
            DBG("INTERNAL ERROR: Can NOT get ID for user Scala file at row: " + String(row_number));
            ScalaComponentMessageBus::getInstance().broadcastMessage("INTERNAL ERROR: Can NOT get ID for user Scala file at row: " + String(row_number));

            return;
        } else {
            success = _userScalaLibrary->deleteScalaTuningAtRow(row_number);
            if(success) {
                ScalaComponentMessageBus::getInstance().broadcastMessage("Deleted Scala file ID: " + String(ID) + " at row: "+ String(row_number));
                
                // broadcast message that a file from the user library was deleted
                sendActionMessage(ScalaModel::getScalaUserFileWasDeleted());
            } else {
                ScalaComponentMessageBus::getInstance().broadcastMessage("Could NOT delete Scala file ID: " + String(ID) + " at row: "+ String(row_number));
            }
        }
    }
    
    // select a new tuning
    if(success) {
        if(getNumRows() > 1) {
            // this triggers parameterChanged, which will assign the tuning and update ui
            auto const new_row =(row_number - 1 + getNumRows()) % getNumRows(); // Corrected calculation ChatGPT4
            recallScalaByRow(new_row);
        } else if(getNumRows() == 1) {
            // this triggers parameterChanged, which will assign the tuning and update ui
            recallScalaByRow(0);
        } else {
            // no user scales
        }
    }
}

bool ScalaModel::addTuningToScalaUserLibrary(shared_ptr<Tuning> current_tuning) {
    jassert(current_tuning != nullptr);
    
    // some tunings can't be represented as Scala files
    bool success = false;
    if(! current_tuning->getCanScala()) {
        DBG("ScalaModel::addTuningToScalaUserLibrary:  current tuning cannot be represented as Scala/Kbm files: " + current_tuning->getDebugDescription());
        ScalaComponentMessageBus::getInstance().broadcastMessage("Can not create scala file from current scale");

        return success;
    }
    
    // for those that can...
    auto const create_kbm = true;
    _userScalaLibrary->addScalaFromTuning(current_tuning, create_kbm);
    auto scala_name = current_tuning->getTuningName();
    ScalaComponentMessageBus::getInstance().broadcastMessage("Created Scala file: " + scala_name);

    //
    return success;
}


int ScalaModel::getSelectedRowNumber() {
    if(_library == ScalaModel::Library::Bundled) {
        
        return _bundledScalaLibrary->getSelectedRowNumber();
    } else {
        return _userScalaLibrary->getSelectedRowNumber();
    }
    
    jassertfalse;
}

// TODO: deal with .kbm throughout this whole thing
void ScalaModel::importUserScalaFiles(Array<File> file_array) {
    auto const sd = ScalaIconRenderer::getScalaUserScalaDirectory();
    for(auto f : file_array) {
        if(! f.hasFileExtension(".scl") && ! f.hasFileExtension(".kbm")) {
            DBG("ScalaModel::importUserScalaFiles: skipping files that don't have .scl or .kbm extensions: " + f.getFullPathName());
            continue;
        }
        
        // TODO: properly deal with .kbm
        auto const file_name = f.getFileName();
        auto const full_path = sd.getFullPathName() + "/" + file_name;
        auto const full_path_to_file = File(full_path);
        if(full_path_to_file.existsAsFile()) {
            DBG("ScalaModel::importUserScalaFiles: file already exists: NOP: " + full_path);
            ScalaComponentMessageBus::getInstance().broadcastMessage("Will not import Scala file because it already exists: " + file_name);
            
            continue;
        } else {
            // copy file
            auto const success = f.copyFileTo(full_path_to_file);
            if(success) {
                auto const add_success = _userScalaLibrary->addScalaKbm(full_path_to_file, File()); // TODO: handle .kbm here
                if(!add_success) {
                    DBG("ScalaModel::importUserScalaFiles: cannot add scala file to user database: " + full_path_to_file.getFullPathName());
                    ScalaComponentMessageBus::getInstance().broadcastMessage("Can not add Scala file to user database: " + file_name);
                } else {
                    // select last row(depending on sort order could be the new file)
                    auto const num_rows = _userScalaLibrary->getNumRows();
                    recallScalaByRow(num_rows - 1); // also updates ui
                }
            } else {
                DBG("ScalaModel::importUserScalaFiles: cannot copy scala file to: " + full_path_to_file.getFullPathName());
                ScalaComponentMessageBus::getInstance().broadcastMessage("Error saving scala file: " + file_name);
            }
        }
    }
}

// either bundle or user

void ScalaModel::uiSetLibrary(ScalaModel::Library library) {
    auto key = getScalaLibraryParameterID();
    auto range = _apvts->getParameterRange(key.getParamID());
    auto const value01 = range.convertTo0to1(static_cast<unsigned long>(library));
    auto param = _apvts->getParameter(key.getParamID());
    param->setValueNotifyingHost(value01);
}

ScalaModel::Library ScalaModel::uiGetLibrary() {
    auto& param = *_apvts->getRawParameterValue( getScalaLibraryParameterID().getParamID());
    _library =(ScalaModel::Library)param.load();
    
    return _library;
}

void ScalaModel::uiSetBundledID(int bundle_id) {
    // Get the parameter range for the bundled tuning ID parameter
    auto paramRange = _apvts->getParameterRange(getScalaBundledTuningIDParameterID().getParamID());
    
    // Validate the input bundle_id against the parameter range
    if(bundle_id < paramRange.start || bundle_id > paramRange.end) {
        // don't update, just refresh to set the id back to its current value
        _tuningChangedUpdateUI();
        return;
    }
    
    // Use the convertTo0to1 function to normalize the bundle_id
    float i01 = paramRange.convertTo0to1(bundle_id);
    
    DBG("ScalaModel::uiSetBundledID: setting Bundled ID to: " + String(bundle_id));
    
    // Get the parameter and set the normalized value
    auto param = _apvts->getParameter(getScalaBundledTuningIDParameterID().getParamID());
    param->setValueNotifyingHost(i01);
}

int ScalaModel::uiGetBundledID() {
    auto& param = *_apvts->getRawParameterValue(getScalaBundledTuningIDParameterID().getParamID());
    
    return static_cast<int>(param.load());
}

void ScalaModel::uiSetUserID(int user_id) {
    // Get the parameter range for the bundled tuning ID parameter
    auto paramRange = _apvts->getParameterRange(getScalaUserTuningIDParameterID().getParamID());
    
    // Validate the input bundle_id against the parameter range
    if(user_id < paramRange.start || user_id > paramRange.end) {
        // don't update, just refresh UI
        _tuningChangedUpdateUI();
        
        return;
    }
    
    // Use the convertTo0to1 function to normalize the bundle_id
    float i01 = paramRange.convertTo0to1(user_id);
    
    //DBG("ScalaModel::uiSetUserID: setting User ID to: " + String(user_id));
    
    // Get the parameter and set the normalized value
    auto param = _apvts->getParameter(getScalaUserTuningIDParameterID().getParamID());
    param->setValueNotifyingHost(i01);
}

int ScalaModel::uiGetUserID() {
    auto& param = *_apvts->getRawParameterValue( getScalaUserTuningIDParameterID().getParamID());
    
    return static_cast<int>(param.load());
}

Font ScalaModel::getFont() {
    // both bundle and user have the same font
    return _userScalaLibrary->getFont();
}

#pragma mark - TableListBoxModel delegates

int ScalaModel::getNumRows() {
    const ScopedLock sl(_lock);
    if(_library == ScalaModel::Library::Bundled) {
        return _bundledScalaLibrary->getNumRows();
    } else {
        return _userScalaLibrary->getNumRows();
    }
    
    jassertfalse;
    return 0;
}

String ScalaModel::getCellTooltip(int row_number, int column_id) {
    if(column_id == 7 || column_id == 8 || column_id == 9) {
        if(_library == ScalaModel::Library::Bundled) {
            return _bundledScalaLibrary->getText(row_number, column_id);
        } else {
            return _userScalaLibrary->getText(row_number, column_id);
        }
    }
    
    return {};
}

int ScalaModel::getColumnAutoSizeWidth(int columnId) {
    const ScopedLock sl(_lock);
    if(_library == ScalaModel::Library::Bundled) {
        return _bundledScalaLibrary->getColumnAutoSizeWidth(columnId);
    } else {
        return _userScalaLibrary->getColumnAutoSizeWidth(columnId);
    }
    
    jassertfalse;
    return 0;
}

void ScalaModel::sortOrderChanged(int newSortColumnId, bool isForwards) {
    const ScopedLock sl(_lock);
    if(_library == ScalaModel::Library::Bundled) {
        _bundledScalaLibrary->sortOrderChanged(newSortColumnId, isForwards);
        return;
    } else {
        _userScalaLibrary->sortOrderChanged(newSortColumnId, isForwards);
        return;
    }
    
    jassertfalse;
}

String ScalaModel::getText(int rowNumber, int columnId) {
    const ScopedLock sl(_lock);
    if(_library == ScalaModel::Library::Bundled) {
        return _bundledScalaLibrary->getText(rowNumber, columnId);
    } else {
        return _userScalaLibrary->getText(rowNumber, columnId);
    }
    
    jassertfalse;
    return String();
}

void ScalaModel::setText(String columnName, const int rowNumber, const String& newText) {
    const ScopedLock sl(_lock);
    if(_library == ScalaModel::Library::Bundled) {
        jassertfalse; // remove when you're confident
    } else {
        _userScalaLibrary->setText(columnName, rowNumber, newText);
    }
}

int ScalaModel::getIsSelectedForRow(const int rowNumber) const {
    const ScopedLock sl(_lock);
    if(_library == ScalaModel::Library::Bundled) {
        return _bundledScalaLibrary->getIsSelectedForRow(rowNumber);
    } else {
        return _userScalaLibrary->getIsSelectedForRow(rowNumber);
    }
    
    jassertfalse;
    return 0;
}

void ScalaModel::selectRow(const int rowNumber) {
    const ScopedLock sl(_lock);
    if(_library == ScalaModel::Library::Bundled) {
        _bundledScalaLibrary->selectRow(rowNumber);
        return;
    } else {
        _userScalaLibrary->selectRow(rowNumber);
        return;
    }
    
    jassertfalse;
}

vector<Columns> ScalaModel::getColumns() {
    // in dev bundled and user xml can get out of sync because the bundle scl is here:
    // /Users/marcushobbs/IPHONE_PRODUCTION/Wilsonic_2021_juce/Wilsonic/Builds/MacOSX/build/Debug/Wilsonic.app/Contents/Resources/scl
    //
    // so just use the user: it's either a fresh install, or it's in /Users/me/Library/WilsonicMTSESP
    return _userScalaLibrary->getColumns();
}

shared_ptr<Image> ScalaModel::getIcon(int row_number) {
    const ScopedLock sl(_lock);
    if(_library == ScalaModel::Library::Bundled) {
        // lazily creates icon
        auto image = _bundledScalaLibrary->getIcon(row_number);
        jassert(image != nullptr);
        
        return image;
    } else {
        // lazily creates icon
        auto image = _userScalaLibrary->getIcon(row_number);
        jassert(image != nullptr);
        
        return image;
    }
    
    jassertfalse;
    return nullptr;
}

#pragma mark - morph helper

shared_ptr<ScalaTuningImp> ScalaModel::getMorphFor(ScalaModel::Library library, int library_id) {
    if(library == ScalaModel::Library::Bundled) {
        return _bundledScalaLibrary->getScalaTuningForID(library_id);
    } else if(library == ScalaModel::Library::User) {
        // reminder: due to host automation it's normal for users to refer to IDs they've deleted...this can be nullptr
        return _userScalaLibrary->getScalaTuningForID(library_id);
    }
    
    jassertfalse;
    return nullptr;
}

#pragma mark - integrity

unordered_map<int, int> ScalaModel::getIntegrityCheck() {
    // we only return the user library integrity check
    return _userScalaLibrary->getIntegrityCheck();
}

