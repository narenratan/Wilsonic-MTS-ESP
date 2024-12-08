/*
  ==============================================================================

    EqualTemperamentComponent.cpp
    Created: 25 May 2022 8:00:37pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "DesignsModel.h"
#include "EqualTemperament.h"
#include "EqualTemperamentModel.h"
#include "EqualTemperamentComponent.h"

#pragma mark - Lifecycle

EqualTemperamentComponent::EqualTemperamentComponent(WilsonicProcessor& processor)
: WilsonicAppTuningComponent(processor)
, _npoBubble(BubblePlacement::left, "N", "Notes per Period.\nHold down Option while dragging for precision.")
, _periodBubble(BubblePlacement::left, "P", "Period (Octave = 2).\nHold down Option while dragging for precision.")
{
    auto const etm = _processor.getEqualTemperamentModel();

    _paintBounds = getLocalBounds();

    // add bubble
    addAndMakeVisible(_npoBubble);

    // NPO
    addAndMakeVisible(_npoSlider);
    _npoSlider.setRange(EqualTemperament::minNPO, EqualTemperament::maxNPO, 1);
    _npoSlider.setValue(etm->uiGetNPO());
    _npoSlider.setNumDecimalPlacesToDisplay(0);
    _npoSlider.onValueChange = [this, etm] {
        etm->uiSetNPO(static_cast<int>(_npoSlider.getValue()));
    };

    // add bubble
    addAndMakeVisible(_periodBubble);

    // Period
    addAndMakeVisible(_periodSlider);
    _periodSlider.setRange(TuningConstants::minPeriod, TuningConstants::maxPeriod);
    _periodSlider.setValue(etm->uiGetPeriod());
    _periodSlider.setNumDecimalPlacesToDisplay(6);
    _periodSlider.onValueChange = [this, etm] {
        etm->uiSetPeriod(static_cast<float>(_periodSlider.getValue()));
    };

    // pitch wheel
    _pitchWheelComponent = make_unique<WilsonicPitchWheelComponent>(_processor, AppExperiments::tuningRendererPlayingNotes);
    _pitchWheelComponent->setTuning(etm->getTuning());
    _pitchWheelComponent->setCustomFontScale(WilsonicAppSkin::defaultPitchWheelFontScale);
    addAndMakeVisible(*_pitchWheelComponent);

    // add this as listener to model
    _processor.getEqualTemperamentModel()->addActionListener(this);

    // add this as listener of the global app tuning (for color offset changes)
    _processor.getAppTuningModel()->addActionListener(this);
}

EqualTemperamentComponent::~EqualTemperamentComponent() {
    _processor.getAppTuningModel()->removeActionListener(this);
    _processor.getEqualTemperamentModel()->removeActionListener(this);
}

#pragma mark - UI

void EqualTemperamentComponent::paint(Graphics& g) {
    g.fillAll(_processor.getAppSkin().getBgColor());
    if (AppExperiments::showDebugBoundingBox) {
        g.setColour(Colours::lightgreen);
        g.drawRect(getLocalBounds(), 1);
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }

    // ET knows how to paint itself
    auto scale = _processor.getEqualTemperamentModel()->getTuning();
    if (scale != nullptr) {
        scale->paint(_processor, g, _paintBounds);
    } else {
        g.drawFittedText("Can't Draw Equal Temperament because Tuning is null", getLocalBounds(), Justification::centred, 0);
        jassertfalse;
    }

}

void EqualTemperamentComponent::resized() {
    auto const margin = static_cast<int>(WilsonicAppSkin::tuningComponentInteriorMargin);
    auto const componentHeight = static_cast<int>(WilsonicAppSkin::sliderHeight);
    auto const bubbleWidth = static_cast<int>(WilsonicAppSkin::minHitPointSize);
    auto area = getLocalBounds().reduced(margin);

    // spacer
    area.removeFromTop(static_cast<int>(margin));

    // left right
    auto const left_right_01 = 0.75f;
    auto p_area = area.withTrimmedRight(static_cast<int>(left_right_01 * area.getWidth()));
    auto right_area = area.withTrimmedLeft(static_cast<int>((1 - left_right_01) * area.getWidth()));

    // pitch wheel
    _pitchWheelComponent->setBounds(p_area);

    // tuning area

    // npo slider
    auto npo_area = right_area.removeFromTop(componentHeight);
    auto npo_bubble_area = npo_area.removeFromLeft(bubbleWidth);
    _npoBubble.setBounds(npo_bubble_area);
    _npoSlider.setBounds(npo_area);

    // pad
    right_area.removeFromTop(static_cast<int>(margin));

    // Period slider
    auto period_area = right_area.removeFromTop(componentHeight);
    auto period_bubble_area = period_area.removeFromLeft(bubbleWidth);
    _periodBubble.setBounds(period_bubble_area);
    _periodSlider.setBounds(period_area);

    // pad
    right_area.removeFromTop(static_cast<int>(margin));

    // ET graph
    auto const t_h = 80.f;
    auto t_h_d = 0.5f * (right_area.getHeight() - t_h);
    if (t_h_d < 20.f) {
        t_h_d = 20.f;
    }
    right_area.removeFromTop(static_cast<int>(t_h_d));
    right_area.removeFromBottom(static_cast<int>(t_h_d));
    _paintBounds = right_area;
}

const string EqualTemperamentComponent::getAppTuningTitle() {
    return "Equal Temperament";
}

// ActionListener callback

void EqualTemperamentComponent::actionListenerCallback(const String& message) {
    if (message == DesignsModel::getEqualTemperamentTuningChangedActionMessage()) {
        _tuningChangedUpdateUI();
    } else if (message == AppTuningModel::getAppTuningModelChangedMessage()) { // root color changed
        repaint();
    }
}

#pragma mark - tuning changed

void EqualTemperamentComponent::_tuningChangedUpdateUI() {
    auto const etm = _processor.getEqualTemperamentModel();
    _npoSlider.setValue(etm->uiGetNPO(), dontSendNotification);
    _periodSlider.setValue(etm->uiGetPeriod(), dontSendNotification);
    repaint();
}
