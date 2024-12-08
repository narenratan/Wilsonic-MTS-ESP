/*
 ==============================================================================
 
 ScalaIconRenderer.h
 Created: 18 Sep 2022 2:48:30pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"
#include "WilsonicProcessor.h"

// WARNING: much of this codegen file ended up being unused.
// WARNING: be careful when you read this file

// This is a factory for loading scala files, rendering icons, etc.
// It turns out the icons are too big to bundle, so I switched to
// dynamically creating them.  So much of its logic has been
// copied to ScalaUserModel

class ScalaIconRenderer
{
public:
    static constexpr int icon_dimension {64};
    static constexpr int icon_dimension_render {64};
    static constexpr int tableviewHeight = icon_dimension / 2; /// height of tableviews that use these icons
    
    // scala bundle
    static File getScalaLibraryBundleFile();
    static shared_ptr<Image> getScalaBundleIconForFilename(String& filename);
    static void createScalaBundleIconForFilename(String& filename, shared_ptr<Tuning> tuning);
    static const String getFullPathToScalaBundleIconDirectory();
    
    // scala user
    static File getScalaLibraryUserFile();
    static File getScalaUserScalaDirectory();
    static shared_ptr<Image> getScalaUserIconForFilename(String& filename);
    static void createScalaUserIconForFilename(String& filename, shared_ptr<Tuning> tuning);
    static const String getFullPathToScalaUserIconDirectory();
    
    // scala codegen
    static void createScalaCodegenIconForFilename(String& filename, shared_ptr<Tuning> tuning);
    //static void __codegen_build_better_batch_scala(); // called from tests
    
    // drawing
    static void paintPitchWheel(Graphics& g, shared_ptr<Tuning> tuning, Rectangle<int> bounds);
    
    // debug
    static void __debugDeleteAllIcons();// user and codegen icon dirs get moved to the trash
    
private:
    // scala bundle
    //    static const String __relativePathToScalaFileBundleDirectory; // scala files bundled within the app
    static const String __relativePathToScalaBundleIconDirectory;
    static bool __scalaBundleIconExistsForFilename(String& filename);
    static const String __getFullPathToScalaBundleIconForFilename(String& filename);
    
    // scala user
    static const String __relativePathToScalaFileUserDirectory; // user scala files(not bundled, in library)
    static const String __relativePathToScalaUserIconDirectory;
    static bool __scalaUserIconExistsForFilename(String& filename);
    static const String __getFullPathToScalaUserIconForFilename(String& filename);
    
    // scala codegen
    static const String __relativePathToScalaCodegenIconDirectory; // icons
    static bool __scalaCodegenIconExistsForFilename(String& filename);
    static const String __getFullPathToScalaCodegenIconDirectory();
    static const String __getFullPathToScalaCodegenIconForFilename(String& filename);
};
