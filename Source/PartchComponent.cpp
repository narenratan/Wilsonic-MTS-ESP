/*
  ==============================================================================

    PartchComponent.cpp
    Created: 27 May 2024 1:53:49pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "DesignsModel.h"
#include "Partch.h"
#include "PartchModel.h"
#include "PartchComponent.h"

#pragma mark - lifecycle

PartchComponent::PartchComponent(WilsonicProcessor& processor)
: WilsonicAppTuningComponent(processor)
, _scaleBubble(BubblePlacement::below, "P", "Partch Scales")
{
    auto const pm = _processor.getPartchModel();
    auto const tuning = pm->getTuning();
    
    // bubble
    addAndMakeVisible(_scaleBubble);

    // combo box
    _scaleComboBox = make_unique<DeltaComboBox>(_processor, true);
    _scaleComboBox->addItemList(pm->getScaleNames(), 1);
    auto const selectedPresetIndex = pm->uiGetSelectedScaleIndex();
    _scaleComboBox->setSelectedItemIndex(selectedPresetIndex, NotificationType::dontSendNotification);
    _scaleComboBox->setToolTip("Partch 43 and Partch Lambdoma");
    auto onChange = [this, pm]() {
        auto const selectedItemIndex = _scaleComboBox->getSelectedItemIndex();
            pm->uiSetScale(selectedItemIndex);
    };
    _scaleComboBox->setOnChange(onChange);
    addAndMakeVisible(*_scaleComboBox);

    // Slider: gral hex angle
    addAndMakeVisible(_gralHexAngleSlider);
    _gralHexAngleSlider.setRange(-MathConstants<float>::pi, MathConstants<float>::pi, 0);
    _gralHexAngleSlider.setValue(pm->uiGetGralHexRotationRadians());
    _gralHexAngleSlider.setDoubleClickReturnValue(true, 0.f);
    _gralHexAngleSlider.setTooltip("Gral Keyboard Rotation");
    _gralHexAngleSlider.onValueChange = [this, pm] {
        pm->uiSetGralHexRotationRadians(static_cast<float>(_gralHexAngleSlider.getValue()));
    };

    // Slider: Gral Keyboard Scale
    addAndMakeVisible(_gralHexScaleSlider);
    _gralHexScaleSlider.setRange(0.1f, 5.f, 0);
    _gralHexScaleSlider.setValue(pm->uiGetGralHexScale());
    _gralHexScaleSlider.setDoubleClickReturnValue(true, 0.75f);
    _gralHexScaleSlider.setTooltip("Gral Hex Size");
    _gralHexScaleSlider.onValueChange = [this, pm] {
        pm->uiSetGralHexScale(static_cast<float>(_gralHexScaleSlider.getValue()));
    };

    // Slider: Gral Hex Shear X
    addAndMakeVisible(_gralHexShearXSlider);
    _gralHexShearXSlider.setRange(-1.f, 1.f, 0);
    _gralHexShearXSlider.setValue(pm->uiGetGralHexShearX());
    _gralHexShearXSlider.setDoubleClickReturnValue(true, 0.f);
    _gralHexShearXSlider.setTooltip("Gral Hex Shear X");
    _gralHexShearXSlider.onValueChange = [this, pm] {
        pm->uiSetGralHexShearX(static_cast<float>(_gralHexShearXSlider.getValue()));
    };

    // Slider: Gral Hex Offset Factor X
    addAndMakeVisible(_gralHexOriginOffsetFactorXSlider);
    _gralHexOriginOffsetFactorXSlider.setRange(-2.f, 2.f, 0);
    _gralHexOriginOffsetFactorXSlider.setValue(pm->uiGetGralHexOriginOffsetFactorX());
    _gralHexOriginOffsetFactorXSlider.setDoubleClickReturnValue(true, 0.f);
    _gralHexOriginOffsetFactorXSlider.setTooltip("Gral Hex Offset Factor X");
    _gralHexOriginOffsetFactorXSlider.onValueChange = [this, pm] {
        pm->uiSetGralHexOriginOffsetFactorX(static_cast<float>(_gralHexOriginOffsetFactorXSlider.getValue()));
    };

    // Slider: Gral Hex Offset Factor Y
    addAndMakeVisible(_gralHexOriginOffsetFactorYSlider);
    _gralHexOriginOffsetFactorYSlider.setRange(-2.f, 2.f, 0);
    _gralHexOriginOffsetFactorYSlider.setValue(pm->uiGetGralHexOriginOffsetFactorY());
    _gralHexOriginOffsetFactorYSlider.setDoubleClickReturnValue(true, 0.f);
    _gralHexOriginOffsetFactorYSlider.setTooltip("Gral Hex Offset Factor Y");
    _gralHexOriginOffsetFactorYSlider.onValueChange = [this, pm] {
        pm->uiSetGralHexOriginOffsetFactorY(static_cast<float>(_gralHexOriginOffsetFactorYSlider.getValue()));
    };

    // the otonal and utonal toggle buttons
    _o1 = make_unique<ToggleButton>("1");
    _o1->setToggleState(pm->uiGetO1(), dontSendNotification);
    _o1->setTooltip("Highlight Otonal 1 pitches");
    addAndMakeVisible(*_o1);
    _o1->addListener(this);

    _u1 = make_unique<ToggleButton>("/1");
    _u1->setToggleState(pm->uiGetU1(), dontSendNotification);
    _u1->setTooltip("Highlight Utonal 1 pitches");
    addAndMakeVisible(*_u1);
    _u1->addListener(this);

    _o3 = make_unique<ToggleButton>("3");
    _o3->setToggleState(pm->uiGetO3(), dontSendNotification);
    _o3->setTooltip("Highlight Otonal 3 pitches");
    addAndMakeVisible(*_o3);
    _o3->addListener(this);

    _u3 = make_unique<ToggleButton>("/3");
    _u3->setToggleState(pm->uiGetU3(), dontSendNotification);
    _u3->setTooltip("Highlight Utonal 3 pitches");
    addAndMakeVisible(*_u3);
    _u3->addListener(this);

    _o5 = make_unique<ToggleButton>("5");
    _o5->setToggleState(pm->uiGetO5(), dontSendNotification);
    _o5->setTooltip("Highlight Otonal 5 pitches");
    addAndMakeVisible(*_o5);
    _o5->addListener(this);

    _u5 = make_unique<ToggleButton>("/5");
    _u5->setToggleState(pm->uiGetU5(), dontSendNotification);
    _u5->setTooltip("Highlight Utonal 5 pitches");
    addAndMakeVisible(*_u5);
    _u5->addListener(this);

    _o7 = make_unique<ToggleButton>("7");
    _o7->setToggleState(pm->uiGetO7(), dontSendNotification);
    _o7->setTooltip("Highlight Otonal 7 pitches");
    addAndMakeVisible(*_o7);
    _o7->addListener(this);

    _u7 = make_unique<ToggleButton>("/7");
    _u7->setToggleState(pm->uiGetU7(), dontSendNotification);
    _u7->setTooltip("Highlight Utonal 7 pitches");
    addAndMakeVisible(*_u7);
    _u7->addListener(this);

    _o9 = make_unique<ToggleButton>("9");
    _o9->setToggleState(pm->uiGetO9(), dontSendNotification);
    _o9->setTooltip("Highlight Otonal 9 pitches");
    addAndMakeVisible(*_o9);
    _o9->addListener(this);

    _u9 = make_unique<ToggleButton>("/9");
    _u9->setToggleState(pm->uiGetU9(), dontSendNotification);
    _u9->setTooltip("Highlight Utonal 9 pitches");
    addAndMakeVisible(*_u9);
    _u9->addListener(this);

    _o11 = make_unique<ToggleButton>("11");
    _o11->setToggleState(pm->uiGetO11(), dontSendNotification);
    _o11->setTooltip("Highlight Otonal 11 pitches");
    addAndMakeVisible(*_o11);
    _o11->addListener(this);

    _u11 = make_unique<ToggleButton>("/11");
    _u11->setToggleState(pm->uiGetU11(), dontSendNotification);
    _u11->setTooltip("Highlight Utonal 11 pitches");
    addAndMakeVisible(*_u11);
    _u11->addListener(this);
    // graph
    _partchGraph = make_unique<PartchGraphComponent>(_processor);
    addAndMakeVisible(*_partchGraph);
    
    //
    pm->addActionListener(this);
    _processor.getAppTuningModel()->addActionListener(this);
    
    resized();
    _tuningChangedUpdateUI();

    // start timer
    _timerHelper();
}

PartchComponent::~PartchComponent() {
    stopTimer();
    _processor.getPartchModel()->removeActionListener(this);
    _processor.getAppTuningModel()->removeActionListener(this);
    _o1->removeListener(this);
    _u1->removeListener(this);
    _o3->removeListener(this);
    _u3->removeListener(this);
    _o5->removeListener(this);
    _u5->removeListener(this);
    _o7->removeListener(this);
    _u7->removeListener(this);
    _o9->removeListener(this);
    _u9->removeListener(this);
    _o11->removeListener(this);
    _u11->removeListener(this);
}

void PartchComponent::paint(Graphics& g) {
    g.fillAll(_processor.getAppSkin().getBgColor());
    if(AppExperiments::showDebugBoundingBox) {
        g.setColour(Colours::lightgreen);
        g.drawRect(getLocalBounds(), 1);
        g.drawRect(_scaleBubble.getBounds(), 2);
        g.drawRect(_scaleComboBox->getBounds(), 2);
        g.drawRect(_gralHexAngleSlider.getBounds(), 1);
        g.drawRect(_gralHexScaleSlider.getBounds(), 1);
        g.drawRect(_gralHexShearXSlider.getBounds(), 1);
        g.drawRect(_gralHexOriginOffsetFactorXSlider.getBounds(), 1);
        g.drawRect(_gralHexOriginOffsetFactorYSlider.getBounds(), 1);
        g.drawRect(_o1->getBounds(), 1);
        g.drawRect(_u1->getBounds(), 1);
        g.drawRect(_o3->getBounds(), 1);
        g.drawRect(_u3->getBounds(), 1);
        g.drawRect(_o5->getBounds(), 1);
        g.drawRect(_u5->getBounds(), 1);
        g.drawRect(_o7->getBounds(), 1);
        g.drawRect(_u7->getBounds(), 1);
        g.drawRect(_o9->getBounds(), 1);
        g.drawRect(_u9->getBounds(), 1);
        g.drawRect(_o11->getBounds(), 1);
        g.drawRect(_u11->getBounds(), 1);
        g.drawRect(_partchGraph->getBounds(), 1);
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }
    // don't repaint grid...it's on a timer
}

void PartchComponent::resized() {
    auto const margin = static_cast<int>(WilsonicAppSkin::tuningComponentInteriorMargin);
    auto const componentHeight = static_cast<int>(2.f * WilsonicAppSkin::comboBoxHeight);
    auto const componentWidth = static_cast<int>(WilsonicAppSkin::comboBoxWidth);
    auto const bubble_width = static_cast<int>(WilsonicAppSkin::minHitPointSize);
    auto area = getLocalBounds().reduced(margin);
    auto topArea = area.removeFromTop(componentHeight);
    
    // Remove the left area for the scale bubble from the top area
    auto sba = topArea.removeFromLeft(bubble_width);
    _scaleBubble.setBounds(sba);

    // Create a rectangle for the combo box
    auto cba = topArea.removeFromLeft(static_cast<int>(0.85f * componentWidth));
    _scaleComboBox->setBounds(cba.reduced(0, cba.getHeight()/4));

    // sliders
    auto const gral_slider_padding = 20;
    auto const gralSliderWidth = jmax(static_cast<int>(topArea.getWidth() / 5.f - gral_slider_padding), gral_slider_padding);
    auto ghOriginOffsetFactorYA = topArea.removeFromRight(gralSliderWidth);
    _gralHexOriginOffsetFactorYSlider.setBounds(ghOriginOffsetFactorYA);

    topArea.removeFromRight(gral_slider_padding);
    auto ghOriginOffsetFactorXA = topArea.removeFromRight(gralSliderWidth);
    _gralHexOriginOffsetFactorXSlider.setBounds(ghOriginOffsetFactorXA);

    topArea.removeFromRight(gral_slider_padding);
    auto ghShearXA = topArea.removeFromRight(gralSliderWidth);
    _gralHexShearXSlider.setBounds(ghShearXA);

    topArea.removeFromRight(gral_slider_padding);
    auto ghAngleA = topArea.removeFromRight(gralSliderWidth);
    _gralHexAngleSlider.setBounds(ghAngleA);

    topArea.removeFromRight(gral_slider_padding);
    auto ghScaleA = topArea.removeFromRight(gralSliderWidth);
    _gralHexScaleSlider.setBounds(ghScaleA);

    // Remove the top area from the area
    area.removeFromTop(static_cast<int>(margin));

    // 
    auto const toggleButtonPadding = 10;
    auto const toggleButtonWidth = jmax(static_cast<int>(area.getWidth() / 6.f) - 2 * toggleButtonPadding, toggleButtonPadding);
    auto const toggleButtonWidthReduction = jmax(toggleButtonWidth/4, toggleButtonPadding/2);
    auto const toggleButtonHeight = static_cast<int>(WilsonicAppSkin::minHitPointSize);

    // Create a new toggleArea by removing it from area
    auto toggleArea = area.removeFromTop(toggleButtonHeight * 2);

    // Create areas for otonal and utonal buttons
    auto toggleOtonalArea = toggleArea.removeFromTop(toggleButtonHeight);
    auto toggleUtonalArea = toggleArea.removeFromTop(toggleButtonHeight);

    // First row: _oN ToggleButtons
    toggleOtonalArea.removeFromLeft(toggleButtonPadding);
    auto o1Area = toggleOtonalArea.removeFromLeft(toggleButtonWidth);
    _o1->setBounds(o1Area.reduced(toggleButtonWidthReduction, 0));
    toggleOtonalArea.removeFromLeft(toggleButtonPadding);

    toggleOtonalArea.removeFromLeft(toggleButtonPadding);
    auto o3Area = toggleOtonalArea.removeFromLeft(toggleButtonWidth);
    _o3->setBounds(o3Area.reduced(toggleButtonWidthReduction, 0));
    toggleOtonalArea.removeFromLeft(toggleButtonPadding);

    toggleOtonalArea.removeFromLeft(toggleButtonPadding);
    auto o5Area = toggleOtonalArea.removeFromLeft(toggleButtonWidth);
    _o5->setBounds(o5Area.reduced(toggleButtonWidthReduction, 0));
    toggleOtonalArea.removeFromLeft(toggleButtonPadding);

    toggleOtonalArea.removeFromLeft(toggleButtonPadding);
    auto o7Area = toggleOtonalArea.removeFromLeft(toggleButtonWidth);
    _o7->setBounds(o7Area.reduced(toggleButtonWidthReduction, 0));
    toggleOtonalArea.removeFromLeft(toggleButtonPadding);

    toggleOtonalArea.removeFromLeft(toggleButtonPadding);
    auto o9Area = toggleOtonalArea.removeFromLeft(toggleButtonWidth);
    _o9->setBounds(o9Area.reduced(toggleButtonWidthReduction, 0));
    toggleOtonalArea.removeFromLeft(toggleButtonPadding);

    toggleOtonalArea.removeFromLeft(toggleButtonPadding);
    auto o11Area = toggleOtonalArea.removeFromLeft(toggleButtonWidth);
    _o11->setBounds(o11Area.reduced(toggleButtonWidthReduction, 0));

    // Second row: _uN ToggleButtons
    toggleUtonalArea.removeFromLeft(toggleButtonPadding);
    auto u1Area = toggleUtonalArea.removeFromLeft(toggleButtonWidth);
    _u1->setBounds(u1Area.reduced(toggleButtonWidthReduction, 0));
    toggleUtonalArea.removeFromLeft(toggleButtonPadding);

    toggleUtonalArea.removeFromLeft(toggleButtonPadding);
    auto u3Area = toggleUtonalArea.removeFromLeft(toggleButtonWidth);
    _u3->setBounds(u3Area.reduced(toggleButtonWidthReduction, 0));
    toggleUtonalArea.removeFromLeft(toggleButtonPadding);

    toggleUtonalArea.removeFromLeft(toggleButtonPadding);
    auto u5Area = toggleUtonalArea.removeFromLeft(toggleButtonWidth);
    _u5->setBounds(u5Area.reduced(toggleButtonWidthReduction, 0));
    toggleUtonalArea.removeFromLeft(toggleButtonPadding);

    toggleUtonalArea.removeFromLeft(toggleButtonPadding);
    auto u7Area = toggleUtonalArea.removeFromLeft(toggleButtonWidth);
    _u7->setBounds(u7Area.reduced(toggleButtonWidthReduction, 0));
    toggleUtonalArea.removeFromLeft(toggleButtonPadding);

    toggleUtonalArea.removeFromLeft(toggleButtonPadding);
    auto u9Area = toggleUtonalArea.removeFromLeft(toggleButtonWidth);
    _u9->setBounds(u9Area.reduced(toggleButtonWidthReduction, 0));
    toggleUtonalArea.removeFromLeft(toggleButtonPadding);

    toggleUtonalArea.removeFromLeft(toggleButtonPadding);
    auto u11Area = toggleUtonalArea.removeFromLeft(toggleButtonWidth);
    _u11->setBounds(u11Area.reduced(toggleButtonWidthReduction, 0));
    
    //
    _partchGraph->setBounds(area);
}

#pragma mark - App Tuning Title

const string PartchComponent::getAppTuningTitle() {
    return "Partch";
}

#pragma mark - tuning changed

void PartchComponent::_tuningChangedUpdateUI() {
    auto scales = _processor.getPartchModel();
    auto tuning = scales->getTuning();
    auto const selectedPresetIndex = scales->uiGetSelectedScaleIndex();
    _scaleComboBox->setSelectedItemIndex(selectedPresetIndex, NotificationType::dontSendNotification);
    resized();
    repaint();
}

#pragma mark - ActionListener

void PartchComponent::actionListenerCallback(const String& message) {
    if (message == DesignsModel::getPartchTuningChangedActionMessage()) {
        _tuningChangedUpdateUI();
    } else if (message == AppTuningModel::getAppTuningModelChangedMessage()) {
        // don't repaint...we're on a timer
        // this is kept here in case there are other child components that might need to be redrawn.
    }
}

#pragma mark - Timer

void PartchComponent::timerCallback() {
    if (isShowing()) {
        _partchGraph->repaint();
    }
}

void PartchComponent::_timerHelper() {
    // TODO: I'm broken
    
    /*
    auto const displayMode = static_cast<Brun::DisplayMode>(_processor.getBrun2Model()->uiGetDisplayMode(_processor));

    if (displayMode != Brun::DisplayMode::Gral)
    {
        stopTimer();
        return;
    }
*/


//    auto const npo = _processor.getBrun2Model()->getTuning()->getProcessedArrayNPO().count();
//    auto const hz = AppExperiments::getFrameRateForNPO(npo);
    auto const hz = 20;
    if (hz > 0) {
        startTimerHz(hz);
    } else {
        stopTimer();
    }
}

#pragma mark - Button handler

void PartchComponent::buttonClicked(Button* button) {
    auto const pm = _processor.getPartchModel();
    
    // _o1
    auto o1 = dynamic_cast<ToggleButton*>(_o1.get());
    if(o1 == button) {
        auto const state = o1->getToggleState();
        pm->uiSetO1(state);
        
        return;
    }
    
    // _u1
    auto u1 = dynamic_cast<ToggleButton*>(_u1.get());
    if(u1 == button) {
        auto const state = u1->getToggleState();
        pm->uiSetU1(state);
        
        return;
    }
    
    // _o3
    auto o3 = dynamic_cast<ToggleButton*>(_o3.get());
    if(o3 == button) {
        auto const state = o3->getToggleState();
        pm->uiSetO3(state);
        
        return;
    }
    
    // _u3
    auto u3 = dynamic_cast<ToggleButton*>(_u3.get());
    if(u3 == button) {
        auto const state = u3->getToggleState();
        pm->uiSetU3(state);
        
        return;
    }
    
    // _o5
    auto o5 = dynamic_cast<ToggleButton*>(_o5.get());
    if(o5 == button) {
        auto const state = o5->getToggleState();
        pm->uiSetO5(state);
        
        return;
    }
    
    // _u5
    auto u5 = dynamic_cast<ToggleButton*>(_u5.get());
    if(u5 == button) {
        auto const state = u5->getToggleState();
        pm->uiSetU5(state);
        
        return;
    }
    
    // _o7
    auto o7 = dynamic_cast<ToggleButton*>(_o7.get());
    if(o7 == button) {
        auto const state = o7->getToggleState();
        pm->uiSetO7(state);
        
        return;
    }
    
    // _u7
    auto u7 = dynamic_cast<ToggleButton*>(_u7.get());
    if(u7 == button) {
        auto const state = u7->getToggleState();
        pm->uiSetU7(state);
        
        return;
    }
    
    // _o9
    auto o9 = dynamic_cast<ToggleButton*>(_o9.get());
    if(o9 == button) {
        auto const state = o9->getToggleState();
        pm->uiSetO9(state);
        
        return;
    }
    
    // _u9
    auto u9 = dynamic_cast<ToggleButton*>(_u9.get());
    if(u9 == button) {
        auto const state = u9->getToggleState();
        pm->uiSetU9(state);
        
        return;
    }
    
    // _o11
    auto o11 = dynamic_cast<ToggleButton*>(_o11.get());
    if(o11 == button) {
        auto const state = o11->getToggleState();
        pm->uiSetO11(state);
        
        return;
    }
    
    // _u11
    auto u11 = dynamic_cast<ToggleButton*>(_u11.get());
    if(u11 == button) {
        auto const state = u11->getToggleState();
        pm->uiSetU11(state);
        
        return;
    }
}
