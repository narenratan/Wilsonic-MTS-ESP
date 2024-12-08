/**
 * @file Persian17NorthIndianComponent.cpp
 * @brief Implementation of the Persian17NorthIndianComponent class.
 * @author Marcus W. Hobbs
 * @date Created: 19 Mar 2022 7:34:35pm
 * 
 * This file contains the implementation of the Persian17NorthIndianComponent class, which is a subclass of the WilsonicAppTuningComponent class.
 * It adds additional properties and methods specific to the Persian17NorthIndianComponent.
 * 
 * ==============================================================================
 */

#include "DesignsModel.h"
#include "Persian17NorthIndian.h"
#include "Persian17NorthIndianModel.h"
#include "Persian17NorthIndianComponent.h"

#pragma mark - lifecycle

Persian17NorthIndianComponent::Persian17NorthIndianComponent(WilsonicProcessor& processor)
: WilsonicAppTuningComponent(processor)
, _scaleBubble(BubblePlacement::below, "S", "Persian 17 North Indian Scales")
{
    // Model
    auto p17nimm = _processor.getPersian17NorthIndianModel();
    
    // Get the tuning from the scales
    auto tuning = p17nimm->getTuning();

    // Set the paint bounds to the local bounds
    _paintBounds = getLocalBounds();

    // Add the scale bubble to the visible components
    addAndMakeVisible(_scaleBubble);

    // Create the scale combo box
    _scaleComboBox = make_unique<DeltaComboBox>(_processor, true);
    
    // Add the scale names to the combo box
    _scaleComboBox->addItemList(p17nimm->getScaleNames(), 1);
    
    // Get the selected preset index from the scales
    auto const selectedPresetIndex = p17nimm->uiGetSelectedScaleIndex();
    
    // Set the selected item index in the combo box
    _scaleComboBox->setSelectedItemIndex(selectedPresetIndex, NotificationType::dontSendNotification);
    // Set the tool tip for the combo box
    
    _scaleComboBox->setToolTip("Persian 17 tone scale containing North Indian scales");

    // Create the on change callback
    auto onChange = [this, p17nimm]()
    {
        // Get the selected item index from the combo box
        auto const selectedItemIndex = _scaleComboBox->getSelectedItemIndex();
        
        // Set the scale in the scales object
        p17nimm->uiSetScale(selectedItemIndex);
    };
    // Set the on change callback for the combo box
    _scaleComboBox->setOnChange(onChange);

    // Add the combo box to the visible components
    addAndMakeVisible(*_scaleComboBox);

    // Create the pitch wheel component
    _pitchWheelComponent = make_unique<WilsonicPitchWheelComponent>(_processor, AppExperiments::tuningRendererPlayingNotes);
    
    // Set the tuning for the pitch wheel component
    _pitchWheelComponent->setTuning(tuning);
    
    // Set the custom font scale for the pitch wheel component
    _pitchWheelComponent->setCustomFontScale(WilsonicAppSkin::defaultPitchWheelFontScale);
    
    // Add the pitch wheel component to the visible components
    addAndMakeVisible(*_pitchWheelComponent);

    // Add this as a listener to the model in the processor
    p17nimm->addActionListener(this);

    // Add this as a listener to the global app tuning (for color offset changes)
    p17nimm->addActionListener(this);
}

Persian17NorthIndianComponent::~Persian17NorthIndianComponent() {
    _processor.getPersian17NorthIndianModel()->removeActionListener(this);
    _processor.getAppTuningModel()->removeActionListener(this);
}

#pragma mark - Drawing

void Persian17NorthIndianComponent::paint(Graphics& g) {
    g.fillAll(_processor.getAppSkin().getBgColor());
    if (AppExperiments::showDebugBoundingBox) {
        g.setColour(Colours::lightgreen);
        g.drawRect(getLocalBounds(), 1);
        g.drawRect(_scaleBubble.getBounds(), 1);
        g.drawRect(_scaleComboBox->getBounds(), 1);
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }

    // Get the scale from the model in the processor
    auto scale = _processor.getPersian17NorthIndianModel()->getTuning();
    
    // If the scale is not null
    if (scale != nullptr) {
        scale->paint(_processor, g, _paintBounds);
    } else {
        // Draw a message that the tuning is null
        g.drawFittedText("Can't Draw Persian17NorthIndian because Tuning is null", getLocalBounds(), Justification::centred, 0);
        
        // Assert false
        jassertfalse;
    }
}

void Persian17NorthIndianComponent::resized() {
    auto const margin = static_cast<int>(WilsonicAppSkin::tuningComponentInteriorMargin);
    auto const componentHeight = static_cast<int>(WilsonicAppSkin::comboBoxHeight);
    auto const componentWidth = static_cast<int>(WilsonicAppSkin::comboBoxWidth);
    auto const bubble_width = static_cast<int>(WilsonicAppSkin::minHitPointSize);
    auto area = getLocalBounds().reduced(margin);
    auto topArea = area.removeFromTop(componentHeight);
    
    // Get the width, height, x, and y for the top area
    auto const w = componentWidth;
    auto const h = topArea.getHeight();
    auto const x = topArea.getX() + WilsonicAppTuningComponent::getFirstComboBoxInset();
    auto const y = topArea.getY();
    
    // Create a rectangle for the combo box
    auto topArea0 = Rectangle<int>(x, y, w, h); // combo box

    // Remove the left area for the scale bubble from the top area
    auto sba = topArea0.removeFromLeft(bubble_width);
    
    // Set the bounds for the scale bubble
    _scaleBubble.setBounds(sba);
    
    // Set the bounds for the combo box
    _scaleComboBox->setBounds(topArea0);

    // Remove the top area from the area
    area.removeFromTop(static_cast<int>(margin));

    // Get the left and right areas
    auto const left_right_01 = 0.75f;
    auto p_area = area.withTrimmedRight(static_cast<int>(left_right_01 * area.getWidth()));
    auto l_area = area.withTrimmedLeft(static_cast<int>((1 - left_right_01) * area.getWidth()));

    // Set the bounds for the pitch wheel component
    _pitchWheelComponent->setBounds(p_area);

    // Get the tuning area

    // Get the height for the tuning area
    auto const t_h = 2.f * 50.f;
    
    // Get the distance for the tuning area
    auto const t_h_d = 0.5f * (l_area.getHeight() - t_h);
    
    // Remove the top and bottom areas from the tuning area
    l_area.removeFromTop(static_cast<int>(t_h_d));
    l_area.removeFromBottom(static_cast<int>(t_h_d));
    
    // Set the paint bounds to the tuning area
    _paintBounds = l_area;
}

#pragma mark - App Tuning Title

const string Persian17NorthIndianComponent::getAppTuningTitle() {
    return "Persian 17 North Indian";
}

#pragma mark - tuning changed

void Persian17NorthIndianComponent::_tuningChangedUpdateUI() {
    auto scales = _processor.getPersian17NorthIndianModel();
    auto tuning = scales->getTuning();
    auto const selectedPresetIndex = scales->uiGetSelectedScaleIndex();
    _scaleComboBox->setSelectedItemIndex(selectedPresetIndex, NotificationType::dontSendNotification);
    resized();
    repaint();
}

#pragma mark - ActionListener

void Persian17NorthIndianComponent::actionListenerCallback(const String& message) {
    if (message == DesignsModel::getPersian17NorthIndianTuningChangedActionMessage()) {
        _tuningChangedUpdateUI();
    } else if (message == AppTuningModel::getAppTuningModelChangedMessage()) {
        // color changed
        repaint();
    }
}
