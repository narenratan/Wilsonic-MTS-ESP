/*
  ==============================================================================

    TritriadicComponent.h
    Created: 22 Sep 2021 2:12:31pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppTuningModel.h"
#include "BubbleDrawable.h"
#include "Microtone.h"
#include "TritriadicTuning.h"
#include "Tuning_Include.h"
#include "TritriadicModel.h"
#include "WilsonicAppSkin.h"
#include "WilsonicAppTuningComponent.h"
#include "WilsonicIntervalMatrixComponent.h"
#include "WilsonicPitchWheelComponent.h"
#include "WilsonicProcessor.h"

class TritriadicComponent : public WilsonicAppTuningComponent, private ActionListener
{

    // lifecycle

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TritriadicComponent)

public:

    TritriadicComponent (WilsonicProcessor&);

    ~TritriadicComponent() override;

    // draw

    void paint (Graphics&) override;

    void resized() override;

    // app tuning title

    const string getAppTuningTitle() override;

    // ActionListener callback

    void actionListenerCallback (const String&) override;

private:

    // private members

    BubbleDrawable _mediantBubble;

    Slider _mediantSlider {Slider::SliderStyle::LinearHorizontal, Slider::TextEntryBoxPosition::TextBoxLeft};

    BubbleDrawable _dominantBubble;
    
    Slider _dominantSlider {Slider::SliderStyle::LinearHorizontal, Slider::TextEntryBoxPosition::TextBoxLeft};

    unique_ptr<TextEditor> _textEditor;

    unique_ptr<WilsonicPitchWheelComponent> _pitchWheel;

    // private methods

    void _tuningChangedUpdateUI();

    const string _createText();
};
