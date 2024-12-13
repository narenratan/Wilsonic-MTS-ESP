/*
  ==============================================================================

    Rhombus.cpp
    Created: 24 Apr 2023 1:22:35pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "Rhombus.h"

bool Rhombus::isRhombusNAN (const Rhombus& r)
{
    bool const retVal =
    std::isnan (r.px0y0.x) || std::isinf (r.px0y0.x) ||
    std::isnan (r.px0y0.y) || std::isinf (r.px0y0.y) ||
    std::isnan (r.px0y1.x) || std::isinf (r.px0y1.x) ||
    std::isnan (r.px0y1.y) || std::isinf (r.px0y1.y) ||
    std::isnan (r.px1y0.x) || std::isinf (r.px1y0.x) ||
    std::isnan (r.px1y0.y) || std::isinf (r.px1y0.y) ||
    std::isnan (r.px1y1.x) || std::isinf (r.px1y1.x) ||
    std::isnan (r.px1y1.y) || std::isinf (r.px1y1.y);

    return retVal;
}

Rhombus Rhombus::make (float x0, float y0, float x1, float y1)
{
    Rhombus r;

    if (x1 < x0)
        x1 = x0;
    if (y1 < y0)
        y1 = y0;

    r.px0y0 = Point (x0, y0);
    r.px0y1 = Point (x0, y1);
    r.px1y0 = Point (x1, y0);
    r.px1y1 = Point (x1, y1);

    return r;
}

Rhombus Rhombus::make (Point<float> px0y0, Point<float> px0y1, Point<float> px1y0, Point<float> px1y1)
{
    Rhombus rhombus;

    rhombus.px0y0 = px0y0;
    rhombus.px0y1 = px0y1;
    rhombus.px1y0 = px1y0;
    rhombus.px1y1 = px1y1;

    return rhombus;
}

Rhombus Rhombus::applyAffineTransform (const AffineTransform& t) const
{
    Point<float> dx0y0 = px0y0.transformedBy (t);
    Point<float> dx0y1 = px0y1.transformedBy (t);
    Point<float> dx1y0 = px1y0.transformedBy (t);
    Point<float> dx1y1 = px1y1.transformedBy (t);

    Rhombus retVal = {dx0y0, dx0y1, dx1y0, dx1y1};

    return retVal;
}

void Rhombus::strokeRhombus (Graphics& g, float lineThickness)
{
    g.drawLine (px0y0.x, px0y0.y, px1y0.x, px1y0.y, lineThickness);
    g.drawLine (px1y0.x, px1y0.y, px1y1.x, px1y1.y, lineThickness);
    g.drawLine (px1y1.x, px1y1.y, px0y1.x, px0y1.y, lineThickness);
    g.drawLine (px0y1.x, px0y1.y, px0y0.x, px0y0.y, lineThickness);
}

void Rhombus::fillRhombus (Graphics& g)
{
    Path path;

    path.startNewSubPath (px0y0.x, px0y0.y);
    path.lineTo (px0y1.x, px0y1.y);
    path.lineTo (px1y1.x, px1y1.y);
    path.lineTo (px1y0.x, px1y0.y);
    path.closeSubPath();

    g.fillPath(path);
}

Point<float> Rhombus::getMidpoint()
{
    float const x = 0.25f * (px0y0.x + px0y1.x + px1y0.x + px1y1.x);
    float const y = 0.25f * (px0y0.y + px0y1.y + px1y0.y + px1y1.y);

    return Point<float>(x, y);
}

bool Rhombus::rectContainsPoint (Rectangle<int> rect, Point<float> point)
{
    bool retVal = false;

    if ((point.x >= rect.getX()) &&
        (point.x <= rect.getRight()) &&
        (point.y >= rect.getY()) &&
        (point.y <= rect.getBottom()))
    {
        retVal = true;
    }
    
    return retVal;
}

bool Rhombus::rectContainsRhombus (Rectangle<int> rect, Rhombus rhombus)
{
    bool retVal = true;

    retVal &= rectContainsPoint (rect, rhombus.px0y0);
    retVal &= rectContainsPoint (rect, rhombus.px0y1);
    retVal &= rectContainsPoint (rect, rhombus.px1y0);
    retVal &= rectContainsPoint (rect, rhombus.px1y1);

    return retVal;
}

Rhombus Rhombus::transformedBy (const AffineTransform& transform) const
{
    Point<float> transformedPx0y0 = px0y0;
    Point<float> transformedPx0y1 = px0y1;
    Point<float> transformedPx1y0 = px1y0;
    Point<float> transformedPx1y1 = px1y1;

    transform.transformPoint (transformedPx0y0.x, transformedPx0y0.y);
    transform.transformPoint (transformedPx0y1.x, transformedPx0y1.y);
    transform.transformPoint (transformedPx1y0.x, transformedPx1y0.y);
    transform.transformPoint (transformedPx1y1.x, transformedPx1y1.y);

    return Rhombus::make (transformedPx0y0, transformedPx0y1, transformedPx1y0, transformedPx1y1);
}
