/*
 ==============================================================================
 
 Morph.cpp
 Created: 17 Dec 2023 1:41:35pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "Morph.h"
#include "Microtone.h"
#include "MicrotoneArray.h"
#include "TuningTableImp.h"
#include "WilsonicProcessor.h"

#pragma mark - lifecycle

const StringArray Morph::__interpolationTypes {
    "Linear",
    "Log2"
};

Morph::Morph() {
    // we do not want to use TuningImp::update, just the tuning table
    setTuningName("Morph");

    // Note that _A and _B CAN support NPO Override
    _A = make_shared<TuningImp>();
    _B = make_shared<TuningImp>();
    setCanNPOOverride(false); // calls update
    setCanScala(false);
    _interpolationType = Morph::InterpolationType::Linear;
    _interpolationValue = 0.f;
    Morph::_update();
}

void Morph::setA(shared_ptr<Tuning> A) {
    jassert(A != nullptr);
    _A = A;
    Morph::_update();
}

void Morph::setB(shared_ptr<Tuning> B) {
    jassert(B != nullptr);
    _B = B;
    Morph::_update();
}

float Morph::getInterpolationValue() {
    return _interpolationValue;
}

void Morph::setInterpolationValue(float value) {
    auto value01 = jlimit(getInterpolationMin(), getInterpolationMax(), value);
    if(WilsonicMath::floatsAreNotEqual(value01, _interpolationValue)) {
        _interpolationValue = value01;
        Morph::_update();
    }
}

Morph::InterpolationType Morph::getInterpolationType() {
    return _interpolationType;
}

void Morph::setInterpolationType(Morph::InterpolationType type) {
    jassert(type == Morph::InterpolationType::Linear || type == Morph::InterpolationType::Log2);
    if(type != _interpolationType) {
        _interpolationType = type;
        Morph::_update();
    }
}

#pragma mark - _update

void Morph::_update() {
    const ScopedLock sl(_lock);
    // Loop through each MIDI note number, morph frequency
    for (int i = 0; i < static_cast<int>(WilsonicProcessorConstants::numMidiNotes); i++) { // keep as int
        auto const il = static_cast<unsigned long>(i);
        auto const af = _A->getTuningTableFrequency(il);
        auto const bf = _B->getTuningTableFrequency(il);
        auto f = 0.f;
        if(_interpolationType == Morph::InterpolationType::Linear) {
            f = WilsonicMath::linearInterp(af, bf, _interpolationValue);
        } else if (_interpolationType == Morph::InterpolationType::Log2) {
            f = exp2f(WilsonicMath::linearInterp(log2f(af), log2f(bf), _interpolationValue));
        } else {
            jassertfalse;
        }
        setTuningTable(f, il); // this is asserting on nyquist
        auto tone = make_shared<Microtone>(f);
        setMicrotoneAtNoteNumber(tone, il);
    }
    
    // A and B use _processedArrayNPO
    auto const npoA = _A->getProcessedArrayNPOCount();
    auto const npoB = _B->getProcessedArrayNPOCount();
    auto const npo = jmax(npoA, npoB); // pick largest npo for pitch wheel
    auto const middleCNN = 60UL;
    auto const c = microtoneAtNoteNumber(middleCNN);
    auto const cf = c->getFrequencyValue();
    auto pa = MicrotoneArray();
    for(auto i = middleCNN; i < middleCNN + npo; i++) {
        auto mt = microtoneAtNoteNumber(i);
        auto mtf = mt->getFrequencyValue() / cf; // normalize  // TODO: this is why pitch wheel isn't working
        auto mtfmt = make_shared<Microtone>(mtf);
        pa.addMicrotone(mtfmt);
    }
    _processedArray = pa;
    _processedArrayNPO = pa;
    _microtoneArray = pa;
    
    // triads
    _analyzeProportionalTriads();
    
    // Call the post-process block
    callPostProcessBlock();
    
    // Call the completion block
    callOnTuningUpdate();
}

void Morph::setNoteNumberMiddleC(unsigned long nn) {
    TuningImp::setNoteNumberMiddleC(nn);
    _A->setNoteNumberMiddleC(nn);
    _B->setNoteNumberMiddleC(nn);
    Morph::_update();
}

void Morph::setFrequencyMiddleC(float f) {
    TuningImp::setFrequencyMiddleC(f);
    _A->setFrequencyMiddleC(f);
    _B->setFrequencyMiddleC(f);
    Morph::_update();
}

void Morph::setOctaveMiddleC(int o) {
    TuningImp::setOctaveMiddleC(o);
    _A->setOctaveMiddleC(o);
    _B->setOctaveMiddleC(o);
    Morph::_update();
}


#pragma mark - drawing

bool Morph::canPaintTuning() {
    return true;
}

void Morph::paint(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds) {
    g.fillAll(processor.getAppSkin().getBgColor());
    if(AppExperiments::showDebugBoundingBox) {
        g.setColour(Colours::green);
        g.drawRect(bounds, 2);
    }
    paint05(processor, g, bounds);
}


/**
    Paints the graphical representation of the Morph component.

    @param processor The WilsonicProcessor object.
    @param g The Graphics object used for drawing.
    @param bounds The bounds of the component.

    This function is responsible for painting the graphical representation of the Morph component.
    It uses various calculations and paths to create a smooth transition between different states.

    The layout code consists of the following steps:
    1. Calculate the dimensions and positions of the component based on the given bounds.
    2. Iterate over each MIDI note.
    3. Calculate the parameters for the A, Morph, and B states.
    4. Create paths for each state with smooth transitions.
    5. Set the colors and gradients for each path.
    6. Stroke the paths using the Graphics object.

    Note: The control point parameters for the smooth transitions can be experimented with to achieve desired visual effects.
*/
void Morph::paint05(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds) {
    const ScopedLock sl(_lock);
    g.saveState();

    // Define margins and calculate width and height based on component bounds
    auto const xMargin = 5;
    auto const w = bounds.getWidth() - 2 * xMargin;
    auto xw = [=](float x01) { return xMargin + w * x01;}; // Lambda to calculate x position based on a 0-1 range
    auto const yMargin = 5;
    auto const h = bounds.getHeight() - 2 * yMargin; 
    // Define vertical positions as proportions of the height
    auto const yp0 = 0.25f;
    auto const yp1 = 0.125f;
    auto const yp2 = 0.25f;
    auto const y0 = yMargin;
    auto const y1 = yMargin + h * (yp0);
    auto const y2 = yMargin + h * (yp0 + yp1);
    auto const y3 = yMargin + h * (yp0 + yp1 + yp2);
    auto const y4 = yMargin + h * (yp0 + yp1 + yp2 + yp1);
    auto const y5 = yMargin + h * (yp0 + yp1 + yp2 + yp1 + yp0);
    // Ensure the sum of proportions equals 1
    jassert(WilsonicMath::floatsAreEqual(yp0 + yp1 + yp2 + yp1 + yp0, 1.f, WilsonicMath::Epsilon::UI));
    auto const line_thickness = 4; // Define the thickness of the lines
    // Define pitch mapping range
    auto const pmin = 4.f;
    auto const pmax = 12.f;
    // Define interpolation values for color gradients
    auto const val_min = 0.2f;
    auto const val_max = 1.0f;
    auto const v01 = jmap(_interpolationValue, 0.f, 1.f, val_min, val_max);
    auto const v10 = jmap(1.0f - _interpolationValue, 0.f, 1.f, val_min, val_max);

    // Iterate over MIDI notes to draw paths
    for(auto nn = 0UL; nn < WilsonicProcessorConstants::numMidiNotes; nn++) {
        // Calculate parameters for A, Morph, and B states based on MIDI note frequencies
        auto const af = _A->getTuningTableFrequency(nn);
        auto const ap = log2f(af);
        auto const ax = jmap(ap, pmin, pmax, 0.f, 1.f);
        auto const ac = processor.getAppTuningModel()->colorForFrequency(af, v10);
        
        auto const mf = getTuningTableFrequency(nn);
        auto const mp = log2f(mf);
        auto const mx = jmap(mp, pmin, pmax, 0.f, 1.f);
        auto const mc = processor.getAppTuningModel()->colorForFrequency(mf, val_max);

        auto const bf = _B->getTuningTableFrequency(nn);
        auto const bp = log2f(bf);
        auto const bx = jmap(bp, pmin, pmax, 0.f, 1.f);
        auto const bc = processor.getAppTuningModel()->colorForFrequency(bf, v01);

        // Initialize paths for drawing
        Path aPath, axPath, morphPath, bxPath, bPath;

        // Draw vertical line for A state
        aPath.startNewSubPath(xw(ax), y0);
        aPath.lineTo(xw(ax), y1);
        g.setColour(ac);
        g.strokePath(aPath, PathStrokeType(line_thickness, PathStrokeType::curved, PathStrokeType::rounded));

        // Draw diagonal line with smooth transition for Ax state
        axPath.startNewSubPath(xw(ax), y1);
        float controlX_Ax = (xw(ax) + xw(mx)) / 2; // Midpoint for control X
        float controlY_Ax = (y1 + y2) / 2; // Midpoint for control Y
        axPath.quadraticTo(controlX_Ax, controlY_Ax, xw(mx), y2);
        ColourGradient Axgradient(ac, xw(ax), y1, mc, xw(mx), y2, false);
        g.setGradientFill(Axgradient);
        g.strokePath(axPath, PathStrokeType(line_thickness, PathStrokeType::curved, PathStrokeType::rounded));

        // Draw vertical line for Morph state
        morphPath.startNewSubPath(xw(mx), y2);
        morphPath.lineTo(xw(mx), y3);
        g.setColour(mc);
        g.strokePath(morphPath, PathStrokeType(line_thickness, PathStrokeType::curved, PathStrokeType::rounded));

        // Draw diagonal line with smooth transition for Bx state
        bxPath.startNewSubPath(xw(mx), y3);
        float controlX_Bx = (xw(mx) + xw(bx)) / 2; // Midpoint for control X
        float controlY_Bx = (y3 + y4) / 2; // Midpoint for control Y
        bxPath.quadraticTo(controlX_Bx, controlY_Bx, xw(bx), y4);
        ColourGradient Bxgradient(mc, xw(mx), y3, bc, xw(bx), y4, false);
        g.setGradientFill(Bxgradient);
        g.strokePath(bxPath, PathStrokeType(line_thickness, PathStrokeType::curved, PathStrokeType::rounded));

        // Draw vertical line for B state
        bPath.startNewSubPath(xw(bx), y4);
        bPath.lineTo(xw(bx), y5);
        g.setColour(bc);
        g.strokePath(bPath, PathStrokeType(line_thickness, PathStrokeType::curved, PathStrokeType::rounded));
    }
    
    g.restoreState();
}
