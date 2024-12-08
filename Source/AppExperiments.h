/*
  ==============================================================================

    AppExperiments.h
    Created: 23 Jul 2021 8:15:31pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include <JuceHeader.h>

#pragma once

class AppExperiments
{

public:

    // error case for tuning computation
    static Colour frequencyOutOfRangeColor() {return Colours::red;}

    // draw debug bounding box around components
    static constexpr bool showDebugBoundingBox {false};

    // show proportional triads (dots actually, not chords) on the Pitch Wheel (does not work)
    static constexpr bool showProportionalTriadsOnPitchWheel {false};

    // for cps/EG tunings.  dims CPSMicrotone_t's that are not part of the processor's current tuning.
    static constexpr bool tuningRendererHighlightsCPSSubsets {true};

    // if enabled by above darken by this amount using Colour::darken which scales by (1 /(1+amount))
    static constexpr float tuningRendererCPSNonSubsetDarkenAmount {3}; // > 0.

    // render intervals as pitch wheel colors
    static constexpr bool tuningRendererCPSIntervalsAsPitchColor {true};

    // kill switch for rendering playing notes
    static constexpr bool tuningRendererPlayingNotes {true}; // true = huge cpu hit

    // kill switch for the simple synth
    static constexpr bool enableSimpleSynth {true}; // false = render 0's in audio callback

    // kill switch for keyboard animation rendering
    static constexpr bool renderSynthKeyboard {true}; // true = highlight notes with mouseover, false = don't do anything

    // default time framerate
    static constexpr int defaultTimerFrameRate {20};

    // NPO can sometimes roughly correlate to drawing complexity
    static int getFrameRateForNPO (unsigned long npo) {
        auto const hz0 = static_cast<float>(defaultTimerFrameRate);
        auto const hz1 = 1.f;
        auto const npo0 = 20.f;
        auto const npo1 = 64.f;
        if (npo > 0) {
            auto newNpo = (npo - npo0) / (npo1 - npo0);
            newNpo = newNpo < 0.f ? 0.f : newNpo;
            newNpo = newNpo > 1.f ? 1.f : newNpo;
            auto newHz = hz0 + newNpo * (hz1 - hz0);
            
            return static_cast<int>(newHz);
        }
        
        return 1;
    }
};

