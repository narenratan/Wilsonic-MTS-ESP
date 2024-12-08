/*
  ==============================================================================

    DeltaComboBox.cpp
    Created: 12 Sep 2021 3:53:28pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "DeltaComboBox.h"
#include "AppExperiments.h"
#include "WilsonicProcessor.h"

#pragma mark - lifecycle

DeltaComboBox::DeltaComboBox(WilsonicProcessor& processor, bool showDelta)
: WilsonicComponentBase(processor)
, _deltaSlider(_processor)
, _showDelta(showDelta)
{
    addAndMakeVisible(_comboBox);
    if(_showDelta) {
        addAndMakeVisible(_deltaSlider);
        _deltaSlider.onValueIncremented = [this] { _incrementSelection(); };
        _deltaSlider.onValueDecremented = [this] { _decrementSelection(); };
    }
}

DeltaComboBox::~DeltaComboBox() {

}

#pragma mark - drawing

void DeltaComboBox::paint(Graphics& g) {
    g.fillAll(_processor.getAppSkin().getBgColor());
    if (AppExperiments::showDebugBoundingBox) {
        g.setColour(Colours::darkgrey);
        g.drawRect(getLocalBounds(), 2);
        g.setColour(Colours::red);
        g.drawRect(_comboBox.getBounds(), 2);
        if(_showDelta) {
            g.setColour(Colours::green);
            g.drawRect(_deltaSlider.getBounds(), 2);
        }
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }

    if(_isSelected) {
        g.setColour(_processor.getAppSkin().getSelectedComponentColor());
        g.drawRect(getLocalBounds(), 2);
    }
}

void DeltaComboBox::resized() {
    // | combo box | delta Slider |
    auto area = getLocalBounds();
    area.reduce(4, 4);
    if(_showDelta) {
        auto const comboSliderProportion = 0.3f;
        auto const cbw = comboSliderProportion * area.getWidth();
        auto const dsa = clamp<float>(cbw, 40.f, 80.f);
        auto deltaSliderArea = area.removeFromRight(static_cast<int>(dsa));
        auto comboBoxArea = area;
        _comboBox.setBounds(comboBoxArea);
        _deltaSlider.setBounds(deltaSliderArea);
    } else {
        _comboBox.setBounds(area);
    }
}

#pragma mark - public methods

void DeltaComboBox::clear(const NotificationType notification) {
    _comboBox.clear(notification);
}

void DeltaComboBox::setSelectedItemIndex(const int index, const NotificationType notification) {
    _comboBox.setSelectedItemIndex(index, notification);
}

int DeltaComboBox::getSelectedItemIndex() const {
    return _comboBox.getSelectedItemIndex();
}

String DeltaComboBox::getSelectedItemText() {
    return _comboBox.getItemText(_comboBox.getSelectedItemIndex());
}

String DeltaComboBox::getSelectedItemText(int index) {
    return _comboBox.getItemText(index);
}

int DeltaComboBox::getNumItems() const noexcept {
    return _comboBox.getNumItems();
}

void DeltaComboBox::addItem(const String& newItemText, int newItemId) {
    _comboBox.addItem(newItemText, newItemId);
}

void DeltaComboBox::addItemList(const StringArray& itemsToAdd, int firstItemID) {
    _comboBox.addItemList(itemsToAdd, firstItemID);
}

void DeltaComboBox::setOnChange(function<void()> lambda) {
    _comboBox.onChange = lambda;
}

void DeltaComboBox::setComboBoxAttachment(shared_ptr<AudioProcessorValueTreeState> stateToUse, const String& parameterID) {
    _comboBoxAttachment = make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(*stateToUse, parameterID, _comboBox);
}

void DeltaComboBox::setIsSelected(bool isSelected) {
    _isSelected = isSelected;
    repaint();
}

bool DeltaComboBox::getIsSelected() {
    return _isSelected;
}

void DeltaComboBox::setToolTip(const String& newTooltip) {
    _comboBox.setTooltip(newTooltip);
}

#pragma mark - private methods

void DeltaComboBox::_incrementSelection() {
    if (onValueIncremented != nullptr) {
        onValueIncremented();
    } else {
        if(isShowing()) {
            auto const count = _comboBox.getNumItems();
            if(count == 0) {
                // this is not a fatal error
                return;
            }
            auto const selectedItemIndex = _comboBox.getSelectedItemIndex();
            auto const incItemIndex = (selectedItemIndex + 1) % count;
            _comboBox.setSelectedItemIndex(incItemIndex, NotificationType::sendNotificationSync); // will call onChange
        }
    }
}

void DeltaComboBox::_decrementSelection() {
    if(onValueDecremented != nullptr) {
        onValueDecremented();
    } else {
        if(isShowing()) {
            auto const count = _comboBox.getNumItems();
            if(count == 0) {
                // this is not a fatal error
                return;
            }
            auto selectedItemIndex = _comboBox.getSelectedItemIndex();
            auto decItemIndex = selectedItemIndex - 1;
            if(decItemIndex < 0) {
                decItemIndex = count - 1;
            }
            decItemIndex = decItemIndex % count;
            _comboBox.setSelectedItemIndex(decItemIndex, NotificationType::sendNotificationSync); // will call onChange
        }
    }
}
