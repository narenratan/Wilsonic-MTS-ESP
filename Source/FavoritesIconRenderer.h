/**
  * @file FavoritesIconRenderer.h
  * @brief This file contains the FavoritesIconRenderer class.
  * @author Marcus W. Hobbs
  * @date Created: 30 Jul 2022 12:55:56pm
  */

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"
#include "WilsonicProcessor.h"

/**
  * @class FavoritesIconRenderer
  * @brief This class is responsible for rendering the favorites icon.
  */
class FavoritesIconRenderer
{
public:
    static constexpr int icon_dimension = 64; ///< The dimension of the icon.
    static constexpr int icon_dimension_render = 64; ///< The dimension of the rendered icon.
    static constexpr int tableviewHeight = icon_dimension / 2; /// height of tableviews that use these icons

    /**
     * @brief Creates a favorites icon for a given hash code.
     * @param processor The WilsonicProcessor instance.
     * @param hash_code The hash code.
     * @param tuning The tuning.
     */
    static void createFavoritesIconForHashcode(WilsonicProcessor& processor, int hash_code, std::shared_ptr<Tuning> tuning);
    
    /**
     * @brief Gets the favorites icon image for a given hash code.
     * @param hash_code The hash code.
     * @return A shared pointer to the image.
     */
    static shared_ptr<Image> getFavoritesIconImageForHashcode(int hash_code);
    
    /**
     * @brief Deletes all favorites icons (for debugging purposes).
     */
    static void debugDeleteAllFavoritesIcons();
    
    /**
     * @brief Paints the favorites pitch wheel.
     * @param processor The WilsonicProcessor instance.
     * @param g The graphics.
     * @param tuning The tuning.
     * @param bounds The bounds.
     */
    static void paintFavoritesPitchWheel(WilsonicProcessor& processor, Graphics& g, shared_ptr<Tuning> tuning, Rectangle<int> bounds);

private:
    static const String __relativePathToIconDirectory; ///< The relative path to the icon directory.
    
    /**
     * @brief Checks if a favorites icon exists for a given hash code.
     * @param hash_code The hash code.
     * @return True if the icon exists, false otherwise.
     */
    static bool __favoritesIconExistsForHashcode(int hash_code);

    /**
     * @brief Gets the full path to the favorites icon directory.
     * @return The full path to the directory.
     */
    static const String __getFullPathToFavoritesIconDirectory();

    /**
     * @brief Gets the full path to the favorites image for a given hash code.
     * @param hash_code The hash code.
     * @return The full path to the image.
     */
    static const String __getFullPathToFavoritesImageForHashcode(int hash_code);
};
