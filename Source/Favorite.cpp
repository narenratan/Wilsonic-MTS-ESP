/*
  ==============================================================================

    Favorite.cpp
    Created: 26 Dec 2023 4:53:47pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "Favorite.h"

Favorite::Favorite() {
    // see defaults in header
}

Favorite::Favorite(int _ID, shared_ptr<Image> _iconImage, int _designIndex, String _designDescription, int _NPO, String _tuningDescription, vector<FavoriteParam01> _parameters) {
    ID = _ID;
    iconImage = _iconImage;
    designIndex = _designIndex;
    designDescription = _designDescription;
    NPO = _NPO;
    tuningDescription = _tuningDescription;
    parameters = _parameters;
}

FavoriteParam01::FavoriteParam01(String _parameterName, float _value) {
    parameterName = _parameterName;
    value = _value;
}
