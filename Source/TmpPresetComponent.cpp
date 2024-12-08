/*
 ==============================================================================

 TmpPresetComponent.cpp
 Created: 24 Apr 2021 4:51:49pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "AppExperiments.h"
#include "DesignsModel.h"
#include "MicrotoneArray.h"
#include "TmpPresetComponent.h"

#pragma mark - lifecycle

TmpPresetComponent::TmpPresetComponent(WilsonicProcessor& processor)
: WilsonicAppTuningComponent(processor)
, _presetBubble(BubblePlacement::below, "P", "Curated Presets")
, _pitchWheelComponent(_processor, AppExperiments::tuningRendererPlayingNotes)
{
    //
    auto presets = _processor.getPresetsModel();

    // PRESET Delta Combo Box
    _tuningPresetsComboBox = make_unique<DeltaComboBox>(_processor, true);
    _tuningPresetsComboBox->addItemList(presets->getTuningPresetNames(), 1);
    auto const selectedPresetIndex = static_cast<int>(presets->uiGetSelectedPresetIndex());
    _tuningPresetsComboBox->setSelectedItemIndex(selectedPresetIndex, NotificationType::dontSendNotification);
    _tuningPresetsComboBox->setToolTip("Curated presets by Erv Wilson and friends");
    
    // on change callback
    auto onChange = [this]()
    {
        // set new preset
        auto const selectedItemIndex = static_cast<unsigned long>(_tuningPresetsComboBox->getSelectedItemIndex());
        _processor.getPresetsModel()->uiSetPreset(selectedItemIndex);

        // update pitch wheel, also updated in action listener
        auto presetTuning = _processor.getPresetsModel()->getTuning();
        _pitchWheelComponent.setTuning(presetTuning);
    };
    _tuningPresetsComboBox->setOnChange(onChange);

    // order is important...setting the attachment calls the callback to properly init
    addAndMakeVisible(*_tuningPresetsComboBox);
    _tuningPresetsComboBox->setComboBoxAttachment(_processor.getApvts(), PresetsModel::getPresetsParameterID().getParamID());

    // Preset Bubble
    addAndMakeVisible(_presetBubble);

    // Pitch Wheel
    addAndMakeVisible(_pitchWheelComponent);
    _pitchWheelComponent.setTuning(presets->getTuning());
    _pitchWheelComponent.setCustomFontScale(WilsonicAppSkin::defaultPitchWheelFontScale);

    // add this as listener to model
    _processor.getPresetsModel()->addActionListener(this);
}

TmpPresetComponent::~TmpPresetComponent()
{
    _processor.getPresetsModel()->removeActionListener(this);
}

#pragma mark - drawing

void TmpPresetComponent::paint(Graphics& g)
{
    // BG
    g.fillAll(_processor.getAppSkin().getBgColor());

    if (AppExperiments::showDebugBoundingBox)
    {
        // DEBUG
        g.setColour(Colours::lightgreen);
        g.drawRect(getLocalBounds(), 1);
        g.drawRect(_presetBubble.getBounds(), 1);

        // counter
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }
}

void TmpPresetComponent::resized()
{
    auto const margin = static_cast<int>(WilsonicAppSkin::tuningComponentInteriorMargin);
    auto const componentHeight = static_cast<int>(WilsonicAppSkin::comboBoxHeight);
    auto const bubble_width = static_cast<int>(WilsonicAppSkin::minHitPointSize);

    // Global
    auto area = getLocalBounds().reduced(margin);
    FlexBox mainFlex;
    mainFlex.flexDirection = FlexBox::Direction::column;

    // Top Area: Presets Label, Bubble, and ComboBox
    FlexBox topAreaFlex;
    topAreaFlex.flexDirection = FlexBox::Direction::row;
    topAreaFlex.items.add(FlexItem(_presetBubble).withWidth(bubble_width).withHeight(componentHeight));
    topAreaFlex.items.add(FlexItem(*_tuningPresetsComboBox).withWidth(WilsonicAppSkin::comboBoxWidth).withHeight(componentHeight));

    // No flex-grow for topAreaFlex, it should occupy fixed space
    mainFlex.items.add(FlexItem(topAreaFlex).withMargin(margin).withHeight(componentHeight));

    // Pitch Wheel Component
    // Flex-grow is set to 1 to make it occupy all remaining space
    auto pitchWheelFlex = FlexItem(_pitchWheelComponent).withFlex(1);
    mainFlex.items.add(pitchWheelFlex);

    mainFlex.performLayout(area);
}

#pragma mark - App Tuning Title

const string TmpPresetComponent::getAppTuningTitle()
{
    return "Wilson's Garden";
}

#pragma mark - ActionListener

void TmpPresetComponent::actionListenerCallback(const String& message)
{
    if (message == DesignsModel::getPresetsTuningChangedActionMessage())
    {
        auto presetTuning = _processor.getPresetsModel()->getTuning();
        _pitchWheelComponent.setTuning(presetTuning);
    }
}
