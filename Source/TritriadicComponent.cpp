/*
 ==============================================================================

 TritriadicComponent.cpp
 Created: 22 Sep 2021 2:12:31pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "DesignsModel.h"
#include "MicrotoneArray.h"
#include "TritriadicComponent.h"

#pragma mark - lifecycle

TritriadicComponent::TritriadicComponent(WilsonicProcessor& processor)
: WilsonicAppTuningComponent(processor)
, _mediantBubble(BubblePlacement::left, "M", "Mediant.\nHold down Option while dragging for precision.")
, _dominantBubble(BubblePlacement::left, "D", "Dominant.\nHold down Option while dragging for precision.")
{
    // tuning
    auto const ttm = _processor.getTritriadicModel();
    auto const tuning = ttm->getTuning();

    // pitch wheel
    _pitchWheel = make_unique<WilsonicPitchWheelComponent>(_processor, AppExperiments::tuningRendererPlayingNotes);
    _pitchWheel->setTuning(tuning);
    _pitchWheel->setInterceptsMouseClicks(false, false); // pass mouse events up the chain
    _pitchWheel->setCustomFontScale(WilsonicAppSkin::defaultPitchWheelFontScale);
    addAndMakeVisible(*_pitchWheel);

    // bubble: mediant
    addAndMakeVisible(_mediantBubble);

    // mediant slider
    addAndMakeVisible(_mediantSlider);
    _mediantSlider.setRange(TritriadicTuning::mediantMin, TritriadicTuning::mediantMax, 0);
    _mediantSlider.setValue(ttm->uiGetMediant());
    _mediantSlider.setTooltip("Mediant");
    _mediantSlider.onValueChange = [this, ttm] {
        ttm->uiSetMediant((float)_mediantSlider.getValue());
    };

    // bubble: dominant
    addAndMakeVisible(_dominantBubble);

    // dominant slider
    addAndMakeVisible(_dominantSlider);
    _dominantSlider.setRange(TritriadicTuning::dominantMin, TritriadicTuning::dominantMax, 0);
    _dominantSlider.setValue(ttm->uiGetDominant());
    _dominantSlider.setTooltip("Dominant");
    _dominantSlider.onValueChange = [this, ttm] {
        ttm->uiSetDominant((float)_dominantSlider.getValue());
    };

    // text editor
    _textEditor = make_unique<TextEditor>();
    _textEditor->setReadOnly(true);
    _textEditor->setMultiLine(true);
    _textEditor->setColour(TextEditor::ColourIds::backgroundColourId, _processor.getAppSkin().getBgColor());
    _textEditor->setText(_createText());
    addAndMakeVisible(*_textEditor);

    // default size
    setSize(_processor.getAppSkin().getWindowWidth(), _processor.getAppSkin().getWindowHeight());

    _tuningChangedUpdateUI();

    // add self as action listener to model
    _processor.getTritriadicModel()->addActionListener(this);
}

TritriadicComponent::~TritriadicComponent() {
    _processor.getTritriadicModel()->removeActionListener(this);
}

#pragma mark - drawing

void TritriadicComponent::paint(Graphics& g) {
    g.fillAll(_processor.getAppSkin().getBgColor());
    if(AppExperiments::showDebugBoundingBox) {
        g.setColour(Colours::lightgreen);
        g.drawRect(getLocalBounds(), 1);
        g.drawRect(_mediantBubble.getBounds(), 1);
        g.drawRect(_mediantSlider.getBounds(), 1);
        g.drawRect(_dominantBubble.getBounds(), 1);
        g.drawRect(_dominantSlider.getBounds(), 1);
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }
}

void TritriadicComponent::resized() {
    // layout
    // | - pitch wheel    - mediant slider  - |
    // | - pitch wheel    - dominant slider - |
    // | - pitch wheel    - text editor     - |
    auto const sliderHeight = static_cast<int>(WilsonicAppSkin::sliderHeight);
    auto const bubble_width = static_cast<int>(WilsonicAppSkin::minHitPointSize);
    auto const verticalSpacing = static_cast<int>(WilsonicAppSkin::verticalSpacing);
    auto const margin = static_cast<int>(WilsonicAppSkin::tuningComponentInteriorMargin);
    Rectangle<int> area = getLocalBounds().reduced(margin);
    auto const left_proportion = 0.33333333f;
    auto const left_width = static_cast<int>(left_proportion * area.getWidth());
    auto left_area = area.removeFromLeft(left_width); // area is now right area
    _pitchWheel->setBounds(left_area.reduced(margin));

    // horizontal mediant slider
    auto msa = area.removeFromTop(sliderHeight);
    auto mba = msa.removeFromLeft(bubble_width);
    _mediantBubble.setBounds(mba);
    _mediantSlider.setBounds(msa);
    area.removeFromTop(verticalSpacing);

    // horizontal dominant slider
    auto dsa = area.removeFromTop(sliderHeight);
    auto dba = dsa.removeFromLeft(bubble_width);
    _dominantBubble.setBounds(dba);
    _dominantSlider.setBounds(dsa);
    area.removeFromTop(verticalSpacing);

    // leftover graph
    area.removeFromLeft(bubble_width);
    _textEditor->setBounds(area);
}

#pragma mark - tuning changed

void TritriadicComponent::_tuningChangedUpdateUI() {
    auto const ttm = _processor.getTritriadicModel();
    auto const tuning = ttm->getTuning();

    // update tuning for child components
    _pitchWheel->setTuning(tuning);

    // sliders
    _mediantSlider.setValue(ttm->uiGetMediant(), NotificationType::dontSendNotification);
    _dominantSlider.setValue(ttm->uiGetDominant(), NotificationType::dontSendNotification);
    
    // text editor
    _textEditor->setText(_createText());
}

#pragma mark - App Tuning Title

const string TritriadicComponent::getAppTuningTitle() {
    return "Tritriadic";
}

#pragma mark - ActionListener

void TritriadicComponent::actionListenerCallback (const String& message) {
    if(message == DesignsModel::getTritriadicTuningChangedActionMessage()) {
        _tuningChangedUpdateUI();
    }
}

#pragma mark - helper

const string TritriadicComponent::_createText() {
    auto const ttm = _processor.getTritriadicModel();

    // mediant
    string text = "Mediant: P:" + to_string(ttm->uiGetMediantAsPitch()) +
    ", F:" + to_string(ttm->uiGetMediantAsFrequency()) +
    ", C:" + to_string(ttm->uiGetMediantAsCents());
    text += "\n";

    // dominant
    text += "Dominant: P:" + to_string(ttm->uiGetDominantAsPitch()) +
    ", F:" + to_string(ttm->uiGetDominantAsFrequency()) +
    ", C:" + to_string(ttm->uiGetDominantAsCents());
    text += "\n";

    return text;
}
