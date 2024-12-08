/*
 ==============================================================================

 SeedSlider.cpp
 Created: 20 Sep 2021 3:48:56pm my mom's birthday
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include <JuceHeader.h>
#include "SeedSlider.h"
#include "AppExperiments.h"
#include "WilsonicProcessor.h"

#pragma mark - lifecycle

SeedSlider::SeedSlider (WilsonicProcessor& processor,
                       string label,
                       float min,
                       float val,
                       float max,
                       float step,
                       function<void(float)>onValueChange)
: _processor(processor)
{
    jassert(label.size() > 0 &&
            val >= min && val <= max &&
            onValueChange != nullptr);

    // slider
    _A = make_unique<Slider>(Slider::SliderStyle::IncDecButtons, Slider::TextEntryBoxPosition::TextBoxAbove);
    _A->setIncDecButtonsMode(Slider::incDecButtonsDraggable_Vertical);
    _A->setVelocityBasedMode(true);
    _A->setVelocityModeParameters(0.1, 1, 0);
    _A->setRange(min, max, step);
    _A->setValue(val);
    _A->onValueChange = [this, onValueChange]() {onValueChange ((float)this->_A->getValue());};
    _A->addKeyListener(this);

    // label
    _ALabel = make_unique<Label>(label, label);
    _ALabel->setJustificationType(Justification::centred);

    // add to view hierarchy
    addAndMakeVisible(*_A);
    addAndMakeVisible(*_ALabel);

    // default window size
    setSize(_processor.getAppSkin().getWindowWidth(), _processor.getAppSkin().getWindowHeight());
}

SeedSlider::~SeedSlider() {
    _A->removeKeyListener(this);
}

#pragma mark - methods

void SeedSlider::setValue(float value, NotificationType type) {
    _A->setValue (value, type);
}

void SeedSlider::setOnValueChangedF(function<void(float)> onValueChangeF) {
    jassert (onValueChangeF != nullptr);
    _A->onValueChange = [this, onValueChangeF] () {onValueChangeF ((float)_A->getValue());};
}

void SeedSlider::setSliderAttachment(shared_ptr<AudioProcessorValueTreeState> stateToUse, const String& parameterID) {
    _sliderAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(*stateToUse, parameterID, *_A);
}

void SeedSlider::setText(string newText) {
    _ALabel->setText(newText, NotificationType::dontSendNotification);
}

void SeedSlider::setIsSelected(bool isSelected) {
    _isSelected = isSelected;
    repaint();
}

bool SeedSlider::getIsSelected () {
    return _isSelected;
}

void SeedSlider::grabFocus() {
    _A->setWantsKeyboardFocus(true);
    _A->grabKeyboardFocus();
}

void SeedSlider::setOnTabReturnCallback(function<void(void)> callback) {
    _onTabReturnCallback = callback;
}

bool SeedSlider::keyPressed (const KeyPress& key, Component* originatingComponent) {
    if (dynamic_cast<Slider*>(originatingComponent) == _A.get()) {
        if (key == KeyPress::tabKey || key == KeyPress::returnKey) {
            if (_onTabReturnCallback != nullptr) {
                _onTabReturnCallback();

                return true;
            }
        }
    }

    return false;
}

#pragma mark - drawing

void SeedSlider::paint(Graphics& g) {
    g.fillAll(_processor.getAppSkin().getBgColor());

    // DEBUG
    if (AppExperiments::showDebugBoundingBox) {
        g.setColour(Colours::purple);
        g.drawRect(getLocalBounds(), 1);
        g.setColour(Colours::mediumpurple);
        auto const gb = _A->getBounds();
        g.drawRect(gb, 2.f);
    }

    if (_isSelected) {
        g.setColour(_processor.getAppSkin().getSelectedComponentColor());
        g.drawRect(getLocalBounds(), 2);
    }
}

// |-labelArea_-| << label
// |----[80]----| << slider
void SeedSlider::resized() {
    auto const vertical_margin = WilsonicAppSkin::tuningComponentInteriorMargin;
    auto area = getLocalBounds();
    auto labelArea = area.removeFromTop(static_cast<int>(vertical_margin));
    _ALabel->setBounds(labelArea);

    // unusual layout: only resize if greater than min width
    auto const sliderWidth = static_cast<int>(area.getWidth());
    auto const minSliderWidth = static_cast<int>(WilsonicAppSkin::seedSliderHeight);
    if (sliderWidth > minSliderWidth) {
        auto const nw = 0.5f * (sliderWidth - minSliderWidth);
        area.setWidth(minSliderWidth);
        area.setX(area.getX() + static_cast<int>(nw));
    }
    area.removeFromBottom(static_cast<int>(vertical_margin / 2));
    _A->setBounds (area);
}
