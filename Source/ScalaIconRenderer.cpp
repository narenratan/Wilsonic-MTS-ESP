/*
 ==============================================================================
 
 ScalaIconRenderer.cpp
 Created: 18 Sep 2022 2:48:30pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "AppTuningModel.h"
#include "MicrotoneArray.h"
#include "ScalaIconRenderer.h"
#include "ScalaUserModel.h"
#include "ScalaTuningImp.h"
#include "WilsonicProcessor.h"

#pragma mark - static defs

// TODO: plan is to use "scala_bundle_00_v0.xml" as the "binary resource", no need for a folder of 5k files
// TODO: this will work for both Mac and Windows
// TODO: the "Scala" field of the xml has text, with a weird encoding:
//            Scala="! iter26.scl&#10;!&#10;E Scale                                                                         &#10; 17&#10;!&#10; 54/53&#10; 41/39&#10; 19/18&#10; 50/47&#10; 51/47&#10; 63/55&#10; 22/19&#10; 13/11&#10; 91/73&#10; 13/9&#10; 76/51&#10; 74/47&#10; 31/17&#10; 80/43&#10; 25/13&#10; 19/9&#10; 87/32&#10;"

// only used on
//const String ScalaIconRenderer::__relativePathToScalaFileBundleDirectory = "/Contents/Resources/scl";
const String ScalaIconRenderer::__relativePathToScalaFileUserDirectory   = "scala_user_files";
const String ScalaIconRenderer::__relativePathToScalaBundleIconDirectory = "scala_bundle_icon_cache";
const String ScalaIconRenderer::__relativePathToScalaUserIconDirectory   = "scala_user_icon_cache";
const String ScalaIconRenderer::__relativePathToScalaCodegenIconDirectory = "scala_codegen_icon_cache";

#pragma mark - Bundled

//File ScalaIconRenderer::getScalaLibraryBundleFile()
//{
//    // bundle/Contents/Resources/scl
//    auto library_directory = getScalaBundleScalaDirectory();
//    auto library_directory_filename = library_directory.getFullPathName();
//    File scalaLibraryBundleFile = File(library_directory_filename + "/scala_bundle_00_v0.xml");
//
//    return scalaLibraryBundleFile;
//}

//File ScalaIconRenderer::getScalaBundleScalaDirectory()
//{
//    // bundle/Contents/Resources/scl
//    File scalaBundleScalaDirectory = File(File::getSpecialLocation(File::currentApplicationFile).getFullPathName() + __relativePathToScalaFileBundleDirectory);
//
//    return scalaBundleScalaDirectory;
//}

shared_ptr<Image> ScalaIconRenderer::getScalaBundleIconForFilename(String& filename)
{
    // if image exists return it
    auto const file_name = __getFullPathToScalaBundleIconForFilename(filename);
    auto const image = ImageFileFormat::loadFrom(File(file_name));
    if(image.isValid())
    {
        return make_shared<Image> (std::move(image));
    }
    else
    {
        DBG ("ScalaIconRenderer::getScalaBundleIconForFilename: no valid image for filename:" + filename);
        
        return nullptr;
    }
}

void ScalaIconRenderer::createScalaBundleIconForFilename(String& filename, shared_ptr<Tuning> tuning)
{
    // if we have a valid icon just return
    auto const dont_need_icon = __scalaBundleIconExistsForFilename(filename);
    if(dont_need_icon)
    {
        DBG ("ScalaIconRenderer::createScalaBundleIconForFilename: Icon exists for filename: " + filename + ": NOP");
        return;
    }
    
    // must have a valid tuning
    jassert(tuning != nullptr);
    
    // create bounds for icon
    auto const bounds = Rectangle<int> (0, 0, icon_dimension_render, icon_dimension_render);
    
    // create image
    Image icon_image(Image::ARGB, icon_dimension_render, icon_dimension_render, true);
    
    // create graphics context from image
    Graphics g(icon_image);
    
    // paint pitch wheel onto graphics context
    paintPitchWheel(g, tuning, bounds);
    
    // file path
    auto path = __getFullPathToScalaBundleIconForFilename(filename);
    
    // file output stream
    FileOutputStream fstream ((File(path)));
    
    // write png
    PNGImageFormat png_writer;
    auto const success = png_writer.writeImageToStream(icon_image, fstream);
    
    //
    if (! success)
    {
        DBG ("ScalaIconRenderer::createScalaBundleIconForFilename::Error writing icon: " + path);
    }
}

bool ScalaIconRenderer::__scalaBundleIconExistsForFilename(String& filename)
{
    auto const full_path = __getFullPathToScalaBundleIconForFilename(filename);
    auto const image = ImageFileFormat::loadFrom(File(full_path));
    
    return image.isValid();
}

const String ScalaIconRenderer::getFullPathToScalaBundleIconDirectory()
{
    // ~/Library/WilsonicMTSESP/scala_bundle_icon_cache/
    File tunings_root = WilsonicProcessor::appLibraryDir().getChildFile(__relativePathToScalaBundleIconDirectory);
    auto const result = tunings_root.createDirectory();
    if(result.failed())
    {
        DBG ("ScalaIconRenderer::__getFullPathToScalaBundleIconDirectory: ERROR: " << result.getErrorMessage());
        jassertfalse;
    }
    jassert(tunings_root.isDirectory());
    auto const tunings_root_filename = tunings_root.getFullPathName();
    
    return tunings_root_filename;
}

// returns fullpath including .png extension, whether the directory/file exists or not
const String ScalaIconRenderer::__getFullPathToScalaBundleIconForFilename(String& filename)
{
    auto const tunings_root_filename = getFullPathToScalaBundleIconDirectory();
    auto const icon_base_filename = String(tunings_root_filename + "/" + String(filename) + ".png");
    
    return icon_base_filename;
}


#pragma mark - User

File ScalaIconRenderer::getScalaLibraryUserFile()
{
    // ~/Library/WilsonicMTSESP/scala_user_00_v0.xml
    File scalaLibraryUserFile = WilsonicProcessor::appLibraryDir().getChildFile ("scala_user_00_v0.xml");
    
    return scalaLibraryUserFile;
}

File ScalaIconRenderer::getScalaUserScalaDirectory()
{
    File scalaUserDir = WilsonicProcessor::appLibraryDir().getChildFile(__relativePathToScalaFileUserDirectory);
    auto const result = scalaUserDir.createDirectory();
    if(result.failed())
    {
        DBG ("ScalaIconRenderer::getScalaUserScalaDirectory: ERROR: " << result.getErrorMessage());
        jassertfalse;
    }
    
    return scalaUserDir;
}

shared_ptr<Image> ScalaIconRenderer::getScalaUserIconForFilename(String& filename)
{
    // if image exists return it
    auto const file_name = __getFullPathToScalaUserIconForFilename(filename);
    auto const image = ImageFileFormat::loadFrom(File(file_name));
    if(image.isValid())
    {
        return make_shared<Image>(std::move(image));
    }
    else
    {
        DBG ("ScalaIconRenderer::getScalaUserIconForFilename: no valid image for filename:" + filename);
        
        return nullptr;
    }
}

void ScalaIconRenderer::createScalaUserIconForFilename(String& filename, shared_ptr<Tuning> tuning)
{
    // if we have a valid icon just return
    auto const dont_need_icon = __scalaUserIconExistsForFilename(filename);
    if(dont_need_icon)
    {
        DBG ("ScalaIconRenderer::createScalaUserIconForFilename: Icon exists for filename: " + filename + ": NOP");
        return;
    }
    
    // must have a valid tuning
    jassert(tuning != nullptr);
    
    // create bounds for icon
    auto const bounds = Rectangle<int> (0, 0, icon_dimension_render, icon_dimension_render);
    
    // create image
    Image icon_image(Image::ARGB, icon_dimension_render, icon_dimension_render, true);
    
    // create graphics context from image
    Graphics g(icon_image);
    
    // paint pitch wheel onto graphics context
    paintPitchWheel(g, tuning, bounds);
    
    // file path
    auto path = __getFullPathToScalaUserIconForFilename(filename);
    
    // file output stream
    FileOutputStream fstream ((File(path)));
    
    // write png
    PNGImageFormat png_writer;
    auto const success = png_writer.writeImageToStream(icon_image, fstream);
    
    //
    if (! success)
    {
        DBG ("ScalaIconRenderer::createScalaUserIconForFilename::Error writing icon: " + path);
    }
}

bool ScalaIconRenderer::__scalaUserIconExistsForFilename(String& filename)
{
    auto const full_path = __getFullPathToScalaUserIconForFilename(filename);
    auto const image = ImageFileFormat::loadFrom(File(full_path));
    
    return image.isValid();
}

const String ScalaIconRenderer::getFullPathToScalaUserIconDirectory()
{
    // ~/Library/WilsonicMTSESP/icon_cache/
    File tunings_root = WilsonicProcessor::appLibraryDir().getChildFile(__relativePathToScalaUserIconDirectory);
    auto const result = tunings_root.createDirectory();
    if(result.failed())
    {
        DBG ("ScalaIconRenderer::__getFullPathToScalaUserIconDirectory: ERROR: " << result.getErrorMessage());
        jassertfalse;
    }
    jassert(tunings_root.isDirectory());
    auto const tunings_root_filename = tunings_root.getFullPathName();
    
    return tunings_root_filename;
}

// returns fullpath including .png extension, whether the directory/file exists or not
const String ScalaIconRenderer::__getFullPathToScalaUserIconForFilename(String& filename)
{
    auto const tunings_root_filename = getFullPathToScalaUserIconDirectory();
    auto const icon_base_filename = String(tunings_root_filename + "/" + String(filename) + ".png");
    
    return icon_base_filename;
}

#pragma mark - codegen

#if 0
// update 20230404: i've removed Mac bundling of scl files
// so this code will not work anymore.

// update 20221106: 5,100 scala file icons ~ 21 MB:
// Way too big to bundle.  This was more than just a good educational
// exercise: I needed to create the xml anyways.
// Going to pivot to NOT USE CODEGEN DIRS and instead lazily
// render icons, just like Favorites.  Going to copy the scala
// file reading/parsing/Tuning creation to ScalaUserModel.
// "bundled"/"user" will literally behave the same except bundled
// will be read-only.
#define RENDER_ICONS 0

void ScalaIconRenderer::__codegen_build_better_batch_scala()
{
#if false
    DBG ("ScalaIconRenderer::__codegen_build_better_batch_scala: DELETING ALL ICONS");
    __debugDeleteAllIcons();
#else
    DBG ("ScalaIconRenderer::__codegen_build_better_batch_scala: DID NOT delete icons");
#endif
    
    // this is the bundle directory, where the .scl files are stored.
    // codegen = create the xml in __getFullPathToScalaCodegenIconDirectory, then move to bundle directory
    File bundled_scala_file_directory = File(File::getSpecialLocation(File::currentApplicationFile).getFullPathName() + __relativePathToScalaFileBundleDirectory);
    jassert(bundled_scala_file_directory.isDirectory());
    
    // create test library (.xml) in writable directory.  move to bundle directory later
    auto const codegen_icon_directory_name = __getFullPathToScalaCodegenIconDirectory();
    auto const codegen_data_base_name = String(codegen_icon_directory_name + "/scala_bundle_00_v0.xml");
    auto database_file = File(codegen_data_base_name);
    database_file.moveToTrash();
    auto database = ScalaUserModel(database_file, bundled_scala_file_directory, codegen_icon_directory_name);
    
    // ls
    auto children = bundled_scala_file_directory.findChildFiles(int(2), //File::TypesOfFileToFind::findFiles,
                                                                false,   //searchRecursively
                                                                "*.scl", // wildCardPattern
                                                                File::FollowSymlinks::no //followSymlinks
                                                                );
    
    // iterate over files, throttle for dev
    auto const throttle_number_of_scales = 5200; // 50
    auto throttle_count = 0;
    DBG ("ScalaIconRenderer::__codegen_build_better_batch_scala:");
    //DBG ("----------------------------------");
    //DBG ("");
    //DBG ("");
    for(auto file : children) // File
    {
        //DBG ("----------------------------------");
        
        auto file_name = file.getFileName(); // String
        //DBG(file_name);
        //DBG ("");
        
        auto full_path_file_name = file.getFullPathName();
        //        DBG(full_path_file_name);
        //        DBG ("");
        //
        auto scala_file_contents = file.loadFileAsString();
        //DBG(scala_file_contents);
        //DBG ("");
        
        // use factory method to create tuning
        auto scala_tuning = ScalaTuningImp::createScalaTuningFromSclKbm(full_path_file_name, full_path_file_name);
        if(scala_tuning == nullptr)
        {
            continue;
        }
        
#if RENDER_ICONS
        // create icon
        createScalaCodegenIconForFilename(file_name, scala_tuning);
#endif
        // enter the file into the database
        database.addScalaKbm(file, File());
        
        // throttle
        throttle_count++;
        if(throttle_count > throttle_number_of_scales)
        {
            DBG ("ScalaIconRenderer::__codegen_build_better_batch_scala: THROTTLING to " + String(throttle_number_of_scales));
            break;
        }
    }
}
#endif


void ScalaIconRenderer::createScalaCodegenIconForFilename(String& filename, shared_ptr<Tuning> tuning)
{
    // if we have a valid icon just return
    auto const dont_need_icon = __scalaCodegenIconExistsForFilename(filename);
    if(dont_need_icon)
    {
        DBG ("ScalaIconRenderer::__codegen_build_better_batch_scala::Icon exists for filename: " + filename);
        return;
    }
    
    // must have a valid tuning
    jassert(tuning != nullptr);
    
    // create bounds for icon
    auto const bounds = Rectangle<int> (0, 0, icon_dimension_render, icon_dimension_render);
    
    // create image
    Image icon_image(Image::ARGB, icon_dimension_render, icon_dimension_render, true);
    
    // create graphics context from image
    Graphics g(icon_image);
    
    // paint pitch wheel onto graphics context
    paintPitchWheel(g, tuning, bounds);
    
    // file path
    auto path = __getFullPathToScalaCodegenIconForFilename(filename);
    
    // file output stream
    FileOutputStream fstream ((File(path)));
    
    // write png
    PNGImageFormat png_writer;
    auto const success = png_writer.writeImageToStream(icon_image, fstream);
    
    //
    if (! success)
    {
        DBG ("ScalaIconRenderer::__codegen_build_better_batch_scala::Error writing icon: " + path);
    }
    else
    {
        DBG ("ScalaIconRenderer::__codegen_build_better_batch_scala::Wrote png to: " + path);
    }
}


bool ScalaIconRenderer::__scalaCodegenIconExistsForFilename(String& filename)
{
    auto const file_name = __getFullPathToScalaCodegenIconForFilename(filename);
    auto const image = ImageFileFormat::loadFrom(File(file_name));
    
    return image.isValid();
}

const String ScalaIconRenderer::__getFullPathToScalaCodegenIconDirectory()
{
    // ~/Library/WilsonicMTSESP/icon_cache/
    File tunings_root = WilsonicProcessor::appLibraryDir().getChildFile(__relativePathToScalaCodegenIconDirectory);
    auto const result = tunings_root.createDirectory();
    if(result.failed())
    {
        DBG ("ScalaIconRenderer::__getFullPathToScalaCodegenIconDirectory: " << result.getErrorMessage());
        jassertfalse;
    }
    jassert(tunings_root.isDirectory());
    auto const tunings_root_filename = tunings_root.getFullPathName();
    
    return tunings_root_filename;
    
}

const String ScalaIconRenderer::__getFullPathToScalaCodegenIconForFilename(String& filename)
{
    auto const codegen_icon_directory_name = __getFullPathToScalaCodegenIconDirectory();
    auto const icon_base_filename = String(codegen_icon_directory_name + "/" + filename + ".png");
    
    return icon_base_filename;
}

#pragma mark - debug/codegen

void ScalaIconRenderer::__debugDeleteAllIcons()
{
    {
        // ~/Library/WilsonicMTSESP/scala_bundle_icon_cache/
        File tunings_root = WilsonicProcessor::appLibraryDir().getChildFile(__relativePathToScalaBundleIconDirectory);
        auto const result = tunings_root.createDirectory();
        if(result.failed())
        {
            DBG ("ScalaIconRenderer::__debugDeleteAllIcons: creating user scala_bundle_icon_cache directory failed: " << result.getErrorMessage());
        }
        else // result did not fail
        {
            DBG ("ScalaIconRenderer::__debugDeleteAllIcons: moving user scala_bundle_icon_cache to trash");
            tunings_root.moveToTrash();
        }
    }
    
    {
        // ~/Library/WilsonicMTSESP/scala_user_icon_cache/
        File tunings_root = WilsonicProcessor::appLibraryDir().getChildFile(__relativePathToScalaUserIconDirectory);
        auto const result = tunings_root.createDirectory();
        if(result.failed())
        {
            DBG ("ScalaIconRenderer::__debugDeleteAllIcons: creating user scala_user_icon_cache directory failed: " << result.getErrorMessage());
        }
        else // result did not fail
        {
            DBG ("ScalaIconRenderer::__debugDeleteAllIcons: moving user scala_user_icon_cache to trash");
            tunings_root.moveToTrash();
        }
    }
    
    {
        // codegen
        File tunings_root = File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile(__relativePathToScalaCodegenIconDirectory);
        auto const result = tunings_root.createDirectory();
        if(result.failed())
        {
            DBG ("ScalaIconRenderer::__debugDeleteAllIcons: creating codegen scala_icon_cache directory failed: " << result.getErrorMessage());
        }
        else // result did not fail
        {
            DBG ("ScalaIconRenderer::__debugDeleteAllIcons: moving codegen scala_icon_cache to trash");
            tunings_root.moveToTrash();
        }
    }
}

#pragma mark - drawing

void ScalaIconRenderer::paintPitchWheel(Graphics& g, shared_ptr<Tuning> tuning, Rectangle<int> bounds)
{
    // null tuning = NOP
    if(tuning == nullptr)
    {
        return;
    }
    
    // copy tuning's processedArray
    auto ma = MicrotoneArray(tuning->getProcessedArray());
    
    // empty tuning is a "null" symbol
    if(ma.count() == 0)
    {
        g.setColour(Colours::grey);
        g.drawText ("0", bounds, Justification::centred);
        return;
    }
    
    // Layout
    auto const x0 = 0.5f * bounds.getWidth();
    auto const y0 = 0.5f * bounds.getHeight();
    auto const dimension = jmin(bounds.getWidth(), bounds.getHeight());
    auto const margin = 0.7f;
    auto const radius = 0.5f * margin * dimension;
    auto const lineThickness = 1.5f;
    auto const dotSmallRadius = 8.f;
    constexpr float pi = 3.14159265358979323846f;
    auto const pitchOffset = -1.f * pi;
    
    // LAMBDA for sin/cos
    auto sx = [&](auto r, auto pitch)
    {
        return x0 + r * sinf(2.f * pi * -pitch + pitchOffset);
    };
    
    auto cy = [&](auto r, auto pitch)
    {
        return y0 + r * cosf(2.f * pi * -pitch + pitchOffset);
    };
    
    // LAMBDA for drawing a line from origin to the dot
    auto draw = [&](Microtone_p mt)
    {
        // get colour based on microtone pitch
        auto const p = mt->getPitchValue01();
        auto const colour = AppTuningModel::colorForPitchNoOffset(p);
        g.setColour(colour);
        
        // draw line
        auto const x1 = sx(radius, p);
        auto const y1 = cy(radius, p);
        g.drawLine(x0, y0, x1, y1, lineThickness);
        
        // draw dot at end of line
        auto r = Rectangle<float>();
        r.setSize(dotSmallRadius, dotSmallRadius);
        r.setCentre(Point<float> (x1, y1));
        g.fillEllipse(r);
    };
    
    // draw a constant line+dot for each microtone(min line width)
    for (unsigned long i = 0; i < ma.count(); i++)
    {
        Microtone_p mt = ma.microtoneAtIndex(i);
        draw(mt);
    }
}
