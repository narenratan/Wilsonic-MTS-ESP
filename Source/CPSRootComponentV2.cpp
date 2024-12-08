/*
  ==============================================================================

    CPSRootComponentV2.cpp
    Created: 19 May 2022 4:43:52pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CPSRootComponentV2.h"
#include "DesignsModel.h"

#pragma mark - lifecycle

CPSRootComponentV2::CPSRootComponentV2(WilsonicProcessor& processor)
: WilsonicAppTuningComponent(processor)
{
    // model
    auto const cm = _processor.getCPSModel();

    // combo box
    _comboBox = make_unique<DeltaComboBox>(_processor, true);
    _comboBox->addItemList(cm->getScaleNames(), 1);
    _comboBox->setSelectedItemIndex(static_cast<int>(CPSModel::Scale::CPS_4_2), NotificationType::dontSendNotification);
    auto onChange = [cm, this]() {
        auto const selectedItemIndex = static_cast<unsigned long>(_comboBox->getSelectedItemIndex());
        cm->uiSetScale(selectedItemIndex);
    };
    _comboBox->setOnChange(onChange);
    addAndMakeVisible(*_comboBox);

    // seed slider
    _seedSliderComponent = make_unique<SeedSliderComponent> (_processor);
    addAndMakeVisible (*_seedSliderComponent);
    _seedSliderComponent->setSliderAtIndex(0, "A", cm->uiGetA(), [cm] (float f) {cm->uiSetA (f);});
    _seedSliderComponent->setSliderAtIndex(1, "B", cm->uiGetB(), [cm] (float f) {cm->uiSetB (f);});
    _seedSliderComponent->setSliderAtIndex(2, "C", cm->uiGetC(), [cm] (float f) {cm->uiSetC (f);});
    _seedSliderComponent->setSliderAtIndex(3, "D", cm->uiGetD(), [cm] (float f) {cm->uiSetD (f);});
    _seedSliderComponent->setSliderAtIndex(4, "E", cm->uiGetE(), [cm] (float f) {cm->uiSetE (f);});
    _seedSliderComponent->setSliderAtIndex(5, "F", cm->uiGetF(), [cm] (float f) {cm->uiSetF (f);});
    _seedSliderComponent->setSliderAtIndex(6, "G", 1.f, [] (float ) {;});
    _seedSliderComponent->setSliderAtIndex(7, "H", 1.f, [] (float ) {;});

    // pitch
    _pitchWheel = make_unique<WilsonicPitchWheelComponent>(_processor, AppExperiments::tuningRendererPlayingNotes);
    _pitchWheel->setCustomFontScale(WilsonicAppSkin::defaultPitchWheelFontScale);
    addAndMakeVisible(*_pitchWheel);

    // main
    _mainElement = make_unique<CPSElementComponentV2> (_processor);
    addAndMakeVisible(*_mainElement);

    // default window size
    setSize(_processor.getAppSkin().getWindowWidth(), _processor.getAppSkin().getWindowHeight());

    // initialize the ui. [confirmed we need this here]
    _tuningChangedUpdateUI();

    // add self as action listener to model
    cm->addActionListener(this);

    // add this as listener of the global app tuning (for color offset changes)
    _processor.getAppTuningModel()->addActionListener(this);
}

CPSRootComponentV2::~CPSRootComponentV2() {
    _processor.getAppTuningModel()->removeActionListener(this);
    _processor.getCPSModel()->removeActionListener(this);
}

#pragma mark - draw

void CPSRootComponentV2::paint(Graphics& g) {
    g.fillAll(_processor.getAppSkin().getBgColor());
    if (AppExperiments::showDebugBoundingBox) {
        g.setColour(Colours::lightgreen);
        g.drawRect(getLocalBounds(), 1);
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }
}

void CPSRootComponentV2::resized() {
    // layout
    auto const margin = static_cast<int>(WilsonicAppSkin::tuningComponentInteriorMargin);
    auto const componentHeight = static_cast<int>(WilsonicAppSkin::comboBoxHeight);
    auto const componentWidth = static_cast<int>(0.5f * WilsonicAppSkin::comboBoxWidth);
    auto const verticalSpacing = static_cast<int>(WilsonicAppSkin::verticalSpacing);
    auto const sliderHeight = static_cast<int>(WilsonicAppSkin::seedSliderHeight);

    // Global
    auto area = getLocalBounds().reduced(margin);

    // CPS combobox
    auto tuningsArea = area.removeFromTop(componentHeight);
    tuningsArea.setWidth(componentWidth);
    tuningsArea.setX(tuningsArea.getX() + WilsonicAppTuningComponent::getFirstComboBoxInset());
    _comboBox->setBounds(tuningsArea);

    // spacing
    area.removeFromTop(verticalSpacing);

    // Seeds
    auto seedsArea = area.removeFromTop(sliderHeight);
    _seedSliderComponent->setBounds(seedsArea);

    // spacing
    area.removeFromTop(verticalSpacing);

    // pitch wheel on the left and cps on the right
    auto const left_proportion = 0.3333f;
    auto const left_width = left_proportion * area.getWidth();
    auto left_area = area.removeFromLeft(static_cast<int>(left_width)); // area is now right area
    _pitchWheel->setBounds(left_area);

    // cps on the right
    _mainElement->setBounds(area);
}

#pragma mark - App Tuning Title

const string CPSRootComponentV2::getAppTuningTitle() {
    return "CPS";
}

#pragma mark - ActionListener

void CPSRootComponentV2::actionListenerCallback (const String& message) {
    if (message == DesignsModel::getCPSTuningChangedActionMessage()) {
        _tuningChangedUpdateUI();
    } else if (message == AppTuningModel::getAppTuningModelChangedMessage()) { // pitch color changed
        // CPSElementComponentV2 and WilsonicPitchWheelComponent are listening to this message...let them repaint themselves
    }
}

#pragma mark - tuning changed

void CPSRootComponentV2::_tuningChangedUpdateUI() {
    // tuning model is updated...need to update UI
    // do NOT send notifications to update the model
    auto cm = _processor.getCPSModel();
    auto cmt = cm->getCPSTuning();
    _comboBox->setSelectedItemIndex(static_cast<int>(cm->uiGetSelectedScaleIndex()), dontSendNotification);
    
    // Update sliders and values
    _seedSliderComponent->showNumberOfSliders(cm->getNumberOfSeeds());
    _seedSliderComponent->setABCDEF(cm->uiGetA(), cm->uiGetB(), cm->uiGetC(), cm->uiGetD(), cm->uiGetE(), cm->uiGetF(), dontSendNotification);

    // Pitch wheel
    _pitchWheel->setTuning(cmt);

    // Main element
    _mainElement->setTuning(cmt);
}
