/*
  ==============================================================================

    Partch.h
    Created: 27 May 2024 1:53:24pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"
#include "PartchMicrotone.h"
#include "MicrotoneArray.h"
#include "TuningImp.h"

class Partch final : public TuningImp
{
public:
    enum class Scale {
        Partch43 = 0,
        DiamondMarimba43 = 1,
        DiamondMarimba = 2,
        QuadrangularisReversum = 3
    };

    // These must be indexed by enum Scale, and the order should never change
    static const StringArray __scaleNames; ///< Names of the scales.
    static const vector<Partch::Scale> all_scales; ///< All scales.
    static constexpr Scale default_scale = Scale::Partch43;
    static constexpr int num_scales = 4; ///< Number of scales.

    // Lifecycle
    Partch();
    ~Partch() override;

    // Public methods
    void setScale(Scale mode); ///< Set the scale.
    int const getScale(); ///< Get the scale. Returns int instead of Scale enum.
    void setGralHexScale(float newScale); // Sets the scale of the Gral hexagon.
    float getGralHexScale(); // Returns the scale of the Gral hexagon.
    void setGralHexRotationRadians(float newRotationRadians); // Sets the rotation of the Gral hexagon in radians.
    float getGralHexRotationRadians(); // Returns the rotation of the Gral hexagon in radians.
    void setGralHexShearX(float newShearX); // Sets the shear of the Gral hexagon in the x direction.
    float getGralHexShearX(); // Returns the shear of the Gral hexagon in the x direction.
    void setGralHexOriginOffsetFactorX(float newOffsetX); // Sets the offset of the Gral hexagon origin in the x direction.
    float getGralHexOriginOffsetFactorX(); // Returns the offset of the Gral hexagon origin in the x direction.
    void setGralHexOriginOffsetFactorY(float newOffsetX); // Sets the offset of the Gral hexagon origin in the y direction.
    float getGralHexOriginOffsetFactorY(); // Returns the offset of the Gral hexagon origin in the y direction.
    AffineTransform _gralPaintTransform() override; // Returns an AffineTransform representing the transformation of the Gral display.
    void setNoteNumberMiddleC(unsigned long nn) override;
    void setO1(bool o1);
    bool getO1() const;
    void setU1(bool u1);
    bool getU1() const;
    void setO3(bool o3);
    bool getO3() const;
    void setU3(bool u3);
    bool getU3() const;
    void setO5(bool o5);
    bool getO5() const;
    void setU5(bool u5);
    bool getU5() const;
    void setO7(bool o7);
    bool getO7() const;
    void setU7(bool u7);
    bool getU7() const;
    void setO9(bool o9);
    bool getO9() const;
    void setU9(bool u9);
    bool getU9() const;
    void setO11(bool o11);
    bool getO11() const;
    void setU11(bool u11);
    bool getU11() const;

    // Drawing
    bool canPaintTuning() override; ///< Check if the tuning can be painted.
    void paint(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds) override; ///< Paint the tuning.
    int nnForDeviceSpace(Point<int> xy) override; // Returns the note number for a given device space, updated in paint()

private:
    // Private methods
    void _partchUpdate(); // updates Gral, before TuningImp::update
    void _paintPartch(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds);
    void _paintNPOOverride(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds);

    // Private members
    Scale _scale = Scale::Partch43; ///< The current scale.
    MicrotoneArray _partch43;
    MicrotoneArray _diamondMarimba43_60nn, _diamondMarimba43;
    MicrotoneArray _diamondMarimba;
    MicrotoneArray _reversum; // Quadrangularis Reversum
    bool _o1 = false, _u1 = false, _o3 = false, _u3 = false, _o5 = false, _u5 = false, _o7 = false, _u7 = false, _o9 = false, _u9 = false, _o11 = false, _u11 = false;
};
