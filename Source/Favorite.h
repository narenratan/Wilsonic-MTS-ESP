/*
  ==============================================================================

    Favorite.h
    Created: 26 Dec 2023 4:53:47pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"

struct FavoriteParam01 {
    String parameterName;
    float value;
    FavoriteParam01(String _parameterName, float _value);
};

// used to share a Favorite
struct Favorite {
    int ID = 0;
    shared_ptr<Image> iconImage;
    int designIndex = 0;
    String designDescription = "";
    int NPO = 1;
    String tuningDescription = "";
    vector<FavoriteParam01> parameters;
    
    Favorite();
    Favorite(int _ID, shared_ptr<Image> _iconImage, int _designIndex, String _designDescription, int _NPO, String _tuningDescription, vector<FavoriteParam01> _parameters);
};
