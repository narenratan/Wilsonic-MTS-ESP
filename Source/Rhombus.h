/*
  ==============================================================================

    Rhombus.h
    Created: 24 Apr 2023 1:22:35pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"

struct Rhombus
{
    // member variables

    Point<float> px0y0;

    Point<float> px0y1;

    Point<float> px1y0;

    Point<float> px1y1;

    // static methods methods

    static Rhombus make (float x0, float y0, float x1, float y1); // factory

    static Rhombus make (Point<float> px0y0, Point<float> px0y1, Point<float> px1y0, Point<float> px1y1); // factory

    static bool rectContainsPoint (Rectangle<int> rect, Point<float> point);

    static bool rectContainsRhombus (Rectangle<int> rect, Rhombus rhombus);

    // member functions

    bool isRhombusNAN (const Rhombus& r);

    Rhombus applyAffineTransform (const AffineTransform& t) const;

    void strokeRhombus (Graphics& g, float lineThickness = 1.f);

    void fillRhombus (Graphics& g);

    Point<float> getMidpoint();

    Rhombus transformedBy (const AffineTransform& transform) const;

};
