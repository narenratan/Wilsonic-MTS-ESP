/*
  ==============================================================================

    WilsonicLookAndFeel.cpp
    Created: 10 Nov 2022 8:30:20am
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "WilsonicLookAndFeel.h"
#include "WilsonicAppSkin.h"

WilsonicLookAndFeel::WilsonicLookAndFeel() {
    // global color scheme
    //setColourScheme (LookAndFeel_V4().getMidnightColourScheme());
    setColourScheme(LookAndFeel_V4().getDarkColourScheme());
    //setColourScheme (LookAndFeel_V4().getGreyColourScheme());
    //setColourScheme (LookAndFeel_V4().getLightColourScheme());

    // This doesn't work:
    // default Font
    //setDefaultSansSerifTypefaceName ("American Typewriter");

    // Set up custom properties, colors, etc.
    setColour(Slider::thumbColourId, Colours::cornflowerblue);
    //setColour (Slider::trackColourId, Colours::blue);
    //setColour (Slider::backgroundColourId, Colours::transparentBlack);
}

WilsonicLookAndFeel::~WilsonicLookAndFeel() {

}

#pragma mark -

