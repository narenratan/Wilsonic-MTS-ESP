/*
  ==============================================================================

    FavoritesIconRenderer.cpp
    Created: 30 Jul 2022 12:55:56pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "FavoritesIconRenderer.h"

const String FavoritesIconRenderer::__relativePathToIconDirectory = "icon_cache";

/**
 * @brief Creates a favorites icon for a given hash code.
 * @param processor The WilsonicProcessor instance.
 * @param hash_code The hash code for the favorite.
 * @param tuning The tuning for the favorite.
 */
void FavoritesIconRenderer::createFavoritesIconForHashcode(WilsonicProcessor& processor, int hash_code, std::shared_ptr<Tuning> tuning)
{
    // if we have a valid icon just return
    auto const dont_need_icon = __favoritesIconExistsForHashcode(hash_code);
    if (dont_need_icon)
    {
        DBG ("Icon exists for hash code: " + String(hash_code));
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
    paintFavoritesPitchWheel(processor, g, tuning, bounds);

    // file path
    auto path = __getFullPathToFavoritesImageForHashcode(hash_code);

    // file output stream
    FileOutputStream fstream((File(path)));

    //
    PNGImageFormat png_writer;
    auto const success = png_writer.writeImageToStream(icon_image, fstream);

    //
    if(!success)
    {
        DBG("Error writing icon: " + path);
    }
}

/**
 * @brief Gets the favorites icon image for a given hash code.
 * @param hash_code The hash code for the favorite.
 * @return A shared pointer to the image.
 */
shared_ptr<Image> FavoritesIconRenderer::getFavoritesIconImageForHashcode(int hash_code)
{
    // if image exists return it
    auto const file_name = __getFullPathToFavoritesImageForHashcode(hash_code);
    auto const image = ImageFileFormat::loadFrom(File(file_name));
    if (image.isValid())
    {
        return make_shared<Image>(std::move(image));
    }
    else
    {
        DBG ("FavoritesIconRenderer::getFavoritesIconImageForHashcode: no image for hashcode:" + String(hash_code) + ": " + file_name);
        return nullptr;
    }
}

/**
 * @brief Deletes all favorites icons (for debugging purposes).
 */
void FavoritesIconRenderer::debugDeleteAllFavoritesIcons()
{
    // TODO: duplicate code from _getFullPathToImageDirectory()

    // ~/Library/WilsonicMTSESP/icon_cache/
    File tunings_root = WilsonicProcessor::appLibraryDir().getChildFile(__relativePathToIconDirectory);
    auto const result = tunings_root.createDirectory();
    if (result.failed())
    {
        DBG ("DEBUG: creating icon_cache directory failed: " << result.getErrorMessage());
    }
    else // result did not fail
    {
        DBG ("DEBUG: moving icon_cache to trash");
        tunings_root.moveToTrash();
    }
}

/**
 * @brief Checks if a favorites icon exists for a given hash code.
 * @param hash_code The hash code for the favorite.
 * @return True if the icon exists, false otherwise.
 */
bool FavoritesIconRenderer::__favoritesIconExistsForHashcode(int hash_code)
{
    auto const file_name = __getFullPathToFavoritesImageForHashcode(hash_code);
    auto const image = ImageFileFormat::loadFrom(File(file_name));

    return image.isValid();
}

/**
 * @brief Gets the full path to the favorites icon directory.
 * @return The full path to the directory.
 */
const String FavoritesIconRenderer::__getFullPathToFavoritesIconDirectory()
{
    // ~/Library/WilsonicMTSESP/icon_cache/
    File tunings_root = WilsonicProcessor::appLibraryDir().getChildFile(__relativePathToIconDirectory);
    auto const result = tunings_root.createDirectory();
    if (result.failed())
    {
        DBG ("DEBUG: " << result.getErrorMessage());
        jassertfalse;
    }
    auto const tunings_root_filename = tunings_root.getFullPathName();

    return tunings_root_filename;
}

/**
 * @brief Gets the full path to the favorites image for a given hash code.
 * @param hash_code The hash code for the favorite.
 * @return The full path to the image.
 */
const String FavoritesIconRenderer::__getFullPathToFavoritesImageForHashcode(int hash_code)
{
    // <image directory>/<hash>.png
    auto const tunings_root_filename = __getFullPathToFavoritesIconDirectory();
    auto const icon_base_filename = String(tunings_root_filename + "/" + String(hash_code) + ".png");
    
    return icon_base_filename;
}

void FavoritesIconRenderer::paintFavoritesPitchWheel(WilsonicProcessor& processor, Graphics& g, shared_ptr<Tuning> tuning, Rectangle<int> bounds)
{
    // BG
    //g.fillAll(Colours::black);

    // null tuning = NOP
    if (tuning == nullptr)
    {
        return;
    }

    // copy tuning's processedArray
    auto ma = MicrotoneArray(tuning->getProcessedArrayNPO());

    // empty tuning is a "null" symbol
    if (ma.count() == 0)
    {
        g.setColour(Colours::grey);
        g.drawText ("0", bounds, Justification::centred);
        return;
    }

    // Layout
    auto const x0 = bounds.getX() + 0.5f * bounds.getWidth();
    auto const y0 = bounds.getY() + 0.5f * bounds.getHeight();
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
    auto draw = [&](auto& mt)
    {
        // get colour based on microtone pitch
        auto const p = mt->getPitchValue01();
        auto const colour = processor.getAppTuningModel()->colorForPitch01(p);
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

    // draw a constant line+dot for each microtone (min line width)
    for (unsigned long i = 0; i < ma.count(); i++)
    {
        auto const mt = ma.microtoneAtIndex(i);
        draw(mt);
    }
}

