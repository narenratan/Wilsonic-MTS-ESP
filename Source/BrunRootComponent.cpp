/*
 ==============================================================================

 BrunRootComponent.cpp
 Created: 7 Mar 2021 1:36:51pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "AppExperiments.h"
#include "Brun2Model.h"
#include "BrunRootComponent.h"
#include "DesignsModel.h"
#include "FavoritesModelV2.h"

#pragma mark - lifecycle

BrunRootComponent::BrunRootComponent(WilsonicProcessor& processor)
: WilsonicAppTuningComponent(processor)
, _frequencyBubble(BubblePlacement::right, "F", "Generator in Frequency Space.\nRange is 1.0 to Period.")
, _centsBubble(BubblePlacement::left, "C", "Generator in Cents.\nRange is 0 to 1200 when Period=2 (the octave)")
, _generatorBubble(BubblePlacement::right, "G", "Generator:\nFor this Level, repeat this generating interval against the period until there are only 2 interval sizes: A small and a large.\nUnits are in Log-base period (i.e., log2 when Period=2).\nRange is always 0 to 1.\nHold down Option while dragging for precision.")
, _periodBubble(BubblePlacement::right, "P", "Period:\nThe default period is the Octave (2), it is the most common.\nYou can explore other values.\nUnits are in Frequency.\nHold down Option while dragging for precision.")
, _murchanaBubble(BubblePlacement::right, "M", "Murchana:\nCenter the chain at this degree (default is 0).\nThis starts the chain at a new position;\nwhich rotates the disjunction.\nClick on the checkbox next to display mode to always center the chain.")
, _levelBubble(BubblePlacement::right, "L", "Level:\nNumber of iterations on the Generator against this Period.\nThe Generator is 'numerator' steps of Period 'denominator'\nand are always co-prime.")
, _levelGralBubble(BubblePlacement::right, "K", "Level for Gral Keyboard:\nLays out the Gral Keyboard\nwith the number of columns\nof the generator being the numerator,\nand the octave the denominator.")
{
    // Hook up UI to tuning
    auto const btm = _processor.getBrun2Model();
    auto const btmt = static_pointer_cast<Brun>(btm->getTuning());

    // Bubble: Generator as Frequency
    addAndMakeVisible(_frequencyBubble);

    // Label: Generator as Frequency
    addAndMakeVisible(_frequencyGLabel);
    _frequencyGLabel.setEditable(true);
    _frequencyGLabel.setText(String(btm->uiGetGeneratorAsFrequency()), dontSendNotification);
    _frequencyGLabel.setKeyboardType(CodeEditorComponent::decimalKeyboard);
    _frequencyGLabel.addListener(this);

    // Bubble: Generator as Cents
    addAndMakeVisible(_centsBubble);

    // Label: Generator as Cents
    addAndMakeVisible(_centsGLabel);
    _centsGLabel.setEditable(true);
    _centsGLabel.setText(String(btm->uiGetGeneratorAsCents()), dontSendNotification);
    _centsGLabel.setKeyboardType(CodeEditorComponent::decimalKeyboard);
    _centsGLabel.addListener(this);

    // Bubble: Generator as Log-base Period
    addAndMakeVisible(_generatorBubble);

    // Slider: Generator
    addAndMakeVisible(_generatorSlider);
    _generatorSlider.setRange(Brun::minGenerator, Brun::maxGenerator, 0);
    _generatorSlider.setValue(btm->uiGetGenerator());
    _generatorSlider.setTooltip("Generator");
    _generatorSlider.setNumDecimalPlacesToDisplay(6);
    _generatorSlider.onValueChange = [this, btm] {
        btm->uiSetGenerator(static_cast<float>(_generatorSlider.getValue()));
    };

    // Bubble: Period
    addAndMakeVisible(_periodBubble);

    // Slider: Period
    addAndMakeVisible(_periodSlider);
    _periodSlider.setRange(TuningConstants::minPeriod, TuningConstants::maxPeriod, 0);
    _periodSlider.setValue(btm->uiGetPeriod());
    _periodSlider.setTooltip("Period");
    _periodSlider.setNumDecimalPlacesToDisplay(6);
    _periodSlider.onValueChange = [this, btm] {
        btm->uiSetPeriod(static_cast<float>(_periodSlider.getValue()));
    };

    // display mode (property, not automation)
    _displayModeComboBox = make_unique<ComboBox>("Display Mode");
    addAndMakeVisible(*_displayModeComboBox);
    _displayModeComboBox->addItemList(Brun::__displayModeNames, 1);
    auto const mode = btm->uiGetDisplayMode(_processor);
    btm->uiSetDisplayMode(_processor, mode); // i hate this pattern
    _displayModeComboBox->setSelectedItemIndex(static_cast<int>(mode), dontSendNotification);
    _displayModeComboBox->onChange = [this, btm]() {
        auto item = _displayModeComboBox->getSelectedItemIndex();
        btm->uiSetDisplayMode(_processor, item);
    };

    // Bubble: Murchana
    addAndMakeVisible(_murchanaBubble);

    // Slider: Murchana
    addAndMakeVisible(_murchanaSlider);
    _murchanaSlider.setRange(Brun::minMurchana, Brun::maxMurchana, 1);
    _murchanaSlider.setValue(btm->uiGetMurchana());
    _murchanaSlider.setTooltip("Murchana");
    _murchanaSlider.onValueChange = [this, btm] {
        btm->uiSetMurchana(static_cast<float>(_murchanaSlider.getValue()));
    };

    // Bubble: Level
    addAndMakeVisible(_levelBubble);

    // LevelComponent
    auto getSelectedIndex = [btmt]() {
        return btmt->getLevel();
    };
    auto setLevel01 = [btm](float l01) {
        btm->uiSetLevel01(l01);
    };
    _levelComponent = make_unique<BrunLevelComponent>(_processor, getSelectedIndex, setLevel01);
    addAndMakeVisible(*_levelComponent);

    // Bubble: Level for Gral Keyboard
    addAndMakeVisible(_levelGralBubble);

    // LevelComponent for Gral Keyboard
    auto getSelectedIndexGral = [btmt]() {
        return btmt->getLevelGral();
    };
    auto setLevel01Gral = [btm](float l01) {
        btm->uiSetLevelGral01(l01);
    };
    _levelGralComponent = make_unique<BrunLevelComponent>(_processor, getSelectedIndexGral, setLevel01Gral);
    addAndMakeVisible(*_levelGralComponent);

    // Toggle for auto-murchana for gral
    addAndMakeVisible(_autoMurchanaToggle);
    _autoMurchanaToggle.setHelpText("Automatically make Murchana the 0 in the middle of the chain");
    _autoMurchanaToggle.setToggleState(btm->uiGetAutoMurchana(), dontSendNotification);
    auto onClick = [this, btm]() {
        btm->uiSetAutoMurchana(_autoMurchanaToggle.getToggleState());
    };
    _autoMurchanaToggle.onClick = onClick;

    // Slider: gral hex angle
    addAndMakeVisible(_gralHexAngleSlider);
    _gralHexAngleSlider.setRange(-MathConstants<float>::pi, MathConstants<float>::pi, 0);
    _gralHexAngleSlider.setValue(btm->uiGetGralHexRotationRadians());
    _gralHexAngleSlider.setDoubleClickReturnValue(true, 0.f);
    _gralHexAngleSlider.setTooltip("Gral Keyboard Rotation");
    _gralHexAngleSlider.onValueChange = [this, btm] {
        btm->uiSetGralHexRotationRadians(static_cast<float>(_gralHexAngleSlider.getValue()));
    };

    // Slider: Gral Keyboard Scale
    addAndMakeVisible(_gralHexScaleSlider);
    _gralHexScaleSlider.setRange(0.1f, 5.f, 0);
    _gralHexScaleSlider.setValue(btm->uiGetGralHexScale());
    _gralHexScaleSlider.setDoubleClickReturnValue(true, 0.75f);
    _gralHexScaleSlider.setTooltip("Gral Hex Size");
    _gralHexScaleSlider.onValueChange = [this, btm] {
        btm->uiSetGralHexScale(static_cast<float>(_gralHexScaleSlider.getValue()));
    };

    // Slider: Gral Hex Shear X
    addAndMakeVisible(_gralHexShearXSlider);
    _gralHexShearXSlider.setRange(-1.f, 1.f, 0);
    _gralHexShearXSlider.setValue(btm->uiGetGralHexShearX());
    _gralHexShearXSlider.setDoubleClickReturnValue(true, 0.f);
    _gralHexShearXSlider.setTooltip("Gral Hex Shear X");
    _gralHexShearXSlider.onValueChange = [this, btm] {
        btm->uiSetGralHexShearX(static_cast<float>(_gralHexShearXSlider.getValue()));
    };

    // Slider: Gral Hex Offset Factor X
    addAndMakeVisible(_gralHexOriginOffsetFactorXSlider);
    _gralHexOriginOffsetFactorXSlider.setRange(-2.f, 2.f, 0);
    _gralHexOriginOffsetFactorXSlider.setValue(btm->uiGetGralHexOriginOffsetFactorX());
    _gralHexOriginOffsetFactorXSlider.setDoubleClickReturnValue(true, 0.f);
    _gralHexOriginOffsetFactorXSlider.setTooltip("Gral Hex Offset Factor X");
    _gralHexOriginOffsetFactorXSlider.onValueChange = [this, btm] {
        btm->uiSetGralHexOriginOffsetFactorX(static_cast<float>(_gralHexOriginOffsetFactorXSlider.getValue()));
    };

    // Slider: Gral Hex Offset Factor Y
    addAndMakeVisible(_gralHexOriginOffsetFactorYSlider);
    _gralHexOriginOffsetFactorYSlider.setRange(-2.f, 2.f, 0);
    _gralHexOriginOffsetFactorYSlider.setValue(btm->uiGetGralHexOriginOffsetFactorY());
    _gralHexOriginOffsetFactorYSlider.setDoubleClickReturnValue(true, 0.f);
    _gralHexOriginOffsetFactorYSlider.setTooltip("Gral Hex Offset Factor Y");
    _gralHexOriginOffsetFactorYSlider.onValueChange = [this, btm] {
        btm->uiSetGralHexOriginOffsetFactorY(static_cast<float>(_gralHexOriginOffsetFactorYSlider.getValue()));
    };

    // graph
    _brunGraph = make_unique<BrunGraphComponent>(_processor);
    addAndMakeVisible(*_brunGraph);

    // default window size
    setSize(_processor.getAppSkin().getWindowWidth(), _processor.getAppSkin().getWindowHeight());

    // add self as action listener to model
    btm->addActionListener(this);

    // add this as listener of the global app tuning (for color offset changes)
    _processor.getAppTuningModel()->addActionListener(this);

    // resize
    resized();

    _tuningChangedUpdateUI();

    // start timer
    _timerHelper();
}

BrunRootComponent::~BrunRootComponent() {
    stopTimer();
    _processor.getAppTuningModel()->removeActionListener(this);
    _processor.getBrun2Model()->removeActionListener(this);
    _frequencyGLabel.removeListener(this);
    _centsGLabel.removeListener(this);
}

#pragma mark - paint

void BrunRootComponent::paint(Graphics& g) {
    g.fillAll(_processor.getAppSkin().getBgColor());
    if (AppExperiments::showDebugBoundingBox) {
        g.setColour(Colours::lightgreen);
        g.drawRect(getLocalBounds(), 1);
        g.drawRect(_frequencyGLabel.getBounds(), 1);
        g.drawRect(_centsGLabel.getBounds(), 1);
        g.drawRect(_gralHexAngleSlider.getBounds(), 1);
        g.drawRect(_gralHexScaleSlider.getBounds(), 1);
        g.drawRect(_gralHexShearXSlider.getBounds(), 1);
        g.drawRect(_gralHexOriginOffsetFactorXSlider.getBounds(), 1);
        g.drawRect(_gralHexOriginOffsetFactorYSlider.getBounds(), 1);
        g.drawRect(_periodSlider.getBounds(), 1);
        g.drawRect(_murchanaSlider.getBounds(), 1);
        g.drawRect(_autoMurchanaToggle.getBounds(), 1);
        g.drawRect(_generatorSlider.getBounds(), 1);
        g.drawRect(_levelComponent->getBounds(), 1);
        g.drawRect(_levelGralComponent->getBounds(), 1);
        g.drawRect(_centsBubble.getBounds(), 1);
        g.drawRect(_frequencyGLabel.getBounds(), 1);
        g.drawRect(_generatorBubble.getBounds(), 1);
        g.drawRect(_murchanaBubble.getBounds(), 1);
        g.drawRect(_levelBubble.getBounds(), 1);
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }
}

#pragma mark - resized

void BrunRootComponent::resized() {
    // layout
    auto const sliderHeight = WilsonicAppSkin::sliderHeight;
    auto const verticalSpacing = WilsonicAppSkin::verticalSpacing;
    auto const margin = WilsonicAppSkin::tuningComponentInteriorMargin;
    auto const bubbleWidth = WilsonicAppSkin::minHitPointSize;
    auto const levelWidth = 92;
    auto area = getLocalBounds().reduced(static_cast<int>(margin));
    auto const btm = _processor.getBrun2Model();

    // generator as frequency and cents
    auto gca = area.removeFromTop(static_cast<int>(sliderHeight));
    gca = gca.removeFromRight(area.getWidth() - levelWidth - 15); // offset the bubbles
    auto gfa = gca.removeFromLeft(static_cast<int>(area.getWidth()/2.f)); // split row in half
    auto gfab = gfa.removeFromLeft(static_cast<int>(bubbleWidth));
    _frequencyBubble.setBounds(gfab);
    gfa.setWidth(static_cast<int>(levelWidth));
    _frequencyGLabel.setBounds(gfa);
    auto gcab = gca.removeFromLeft(static_cast<int>(bubbleWidth));
    _centsBubble.setBounds(gcab);
    gca.setWidth(static_cast<int>(levelWidth));
    _centsGLabel.setBounds(gca);

    // spacing
    area.removeFromTop(static_cast<int>(verticalSpacing));

    // horizontal generator slider
    auto gsa = area.removeFromTop(static_cast<int>(sliderHeight));
    auto gsb = gsa.removeFromLeft(static_cast<int>(bubbleWidth));
    _generatorSlider.setBounds(gsa);
    _generatorBubble.setBounds(gsb);

    // spacing
    area.removeFromTop(static_cast<int>(verticalSpacing));

    // horizontal period slider
    auto psa = area.removeFromTop(static_cast<int>(sliderHeight));
    auto psb = psa.removeFromLeft(static_cast<int>(bubbleWidth));
    _periodSlider.setBounds(psa);
    _periodBubble.setBounds(psb);

    // spacing
    area.removeFromTop(static_cast<int>(verticalSpacing));

    // horizontal murchana slider, gral sliders, and display mode
    auto const gral_proportion = 2.f;
    auto msa = area.removeFromTop(static_cast<int>(gral_proportion*sliderHeight));
    auto const drawModeWidth = static_cast<int>(0.5f * WilsonicAppSkin::comboBoxWidth);
    auto dma = msa.removeFromRight(drawModeWidth);
    _displayModeComboBox->setBounds(dma);
    auto const displayMode = static_cast<Brun::DisplayMode>(btm->uiGetDisplayMode(_processor));
    auto const gralSliderWidth = static_cast<int>(gral_proportion * sliderHeight);
    auto ghAutoMurchanaA = msa.removeFromRight(gralSliderWidth);
    _autoMurchanaToggle.setBounds(ghAutoMurchanaA);

    if (displayMode == Brun::DisplayMode::Gral) {
        auto const gral_slider_padding = 20;

        msa.removeFromRight(gral_slider_padding);
        auto ghOriginOffsetFactorYA = msa.removeFromRight(gralSliderWidth);
        _gralHexOriginOffsetFactorYSlider.setBounds(ghOriginOffsetFactorYA);

        msa.removeFromRight(gral_slider_padding);
        auto ghOriginOffsetFactorXA = msa.removeFromRight(gralSliderWidth);
        _gralHexOriginOffsetFactorXSlider.setBounds(ghOriginOffsetFactorXA);

        msa.removeFromRight(gral_slider_padding);
        auto ghShearXA = msa.removeFromRight(gralSliderWidth);
        _gralHexShearXSlider.setBounds(ghShearXA);

        msa.removeFromRight(gral_slider_padding);
        auto ghAngleA = msa.removeFromRight(gralSliderWidth);
        _gralHexAngleSlider.setBounds(ghAngleA);

        msa.removeFromRight(gral_slider_padding);
        auto ghScaleA = msa.removeFromRight(gralSliderWidth);
        _gralHexScaleSlider.setBounds(ghScaleA);

        msa.removeFromRight(gral_slider_padding);
    } else {
        // push off screen
        auto offscreen = Rectangle<int>(getLocalBounds().getWidth(), getLocalBounds().getHeight(), static_cast<int>(sliderHeight), static_cast<int>(sliderHeight));
        _gralHexOriginOffsetFactorYSlider.setBounds(offscreen);
        _gralHexOriginOffsetFactorXSlider.setBounds(offscreen);
        _gralHexShearXSlider.setBounds(offscreen);
        _gralHexAngleSlider.setBounds(offscreen);
        _gralHexScaleSlider.setBounds(offscreen);
    }
    
    auto msb = msa.removeFromLeft(static_cast<int>(bubbleWidth));
    _murchanaSlider.setBounds(msa);
    _murchanaBubble.setBounds(msb);

    // spacing
    area.removeFromTop(static_cast<int>(verticalSpacing));

    // vertical level component
    auto levelArea = area.removeFromLeft(static_cast<int>(bubbleWidth + levelWidth));
    auto la = levelArea.removeFromLeft(static_cast<int>(bubbleWidth));
    _levelBubble.setBounds(la);
    _levelComponent->setBounds(levelArea);

    // level, gral level, and
    if (displayMode == Brun::DisplayMode::Gral) {
        auto levelGralArea = area.removeFromLeft(static_cast<int>(bubbleWidth + levelWidth));
        auto lga = levelGralArea.removeFromLeft(static_cast<int>(bubbleWidth));
        _levelGralBubble.setBounds(lga);
        _levelGralComponent->setBounds(levelGralArea);
    } else {
        // push offscreen
        _levelGralBubble.setBounds(Rectangle<int>(getLocalBounds().getWidth(), la.getY(), static_cast<int>(bubbleWidth), la.getHeight()));
        _levelGralComponent->setBounds(Rectangle<int>(getLocalBounds().getWidth(), levelArea.getY(), levelWidth, levelArea.getHeight()));
    }

    // leftover graph
    _brunGraph->setBounds(area);

    repaint();
}


#pragma mark - App Tuning Title

const string BrunRootComponent::getAppTuningTitle() {
    return "Moments of Symmetry (Brun2)";
}

#pragma mark - tuning changed

void BrunRootComponent::_tuningChangedUpdateUI() {
    auto const btm = _processor.getBrun2Model();
    _frequencyGLabel.setText(String(btm->uiGetGeneratorAsFrequency()), dontSendNotification);
    _centsGLabel.setText(String(btm->uiGetGeneratorAsCents()), dontSendNotification);
    _generatorSlider.setValue(btm->uiGetGenerator(), dontSendNotification);
    _periodSlider.setValue(btm->uiGetPeriod(), dontSendNotification);
    _murchanaSlider.setValue(btm->uiGetMurchana(), dontSendNotification);
    _autoMurchanaToggle.setToggleState(btm->uiGetAutoMurchana(), dontSendNotification);
    _gralHexAngleSlider.setValue(btm->uiGetGralHexRotationRadians(), dontSendNotification);
    _gralHexScaleSlider.setValue(btm->uiGetGralHexScale(), dontSendNotification);
    _gralHexShearXSlider.setValue(btm->uiGetGralHexShearX(), dontSendNotification);
    _gralHexOriginOffsetFactorXSlider.setValue(btm->uiGetGralHexOriginOffsetFactorX(), dontSendNotification);
    _gralHexOriginOffsetFactorYSlider.setValue(btm->uiGetGralHexOriginOffsetFactorY(), dontSendNotification);
    _levelComponent->repaint();
    _levelGralComponent->repaint();

    // don't repaint _brunGraph here...it's repainted on a timer

    // properties
    auto const mode = static_cast<int>(btm->uiGetDisplayMode(_processor));
    _displayModeComboBox->setSelectedItemIndex(mode, dontSendNotification);

    // layout
    resized();
}

#pragma mark - ActionListener

void BrunRootComponent::actionListenerCallback(const String& message) {
    if (message == DesignsModel::getBrunTuningChangedActionMessage()) {
        _tuningChangedUpdateUI();
        _timerHelper(); // npo changes timer rate
    } else if (message == AppTuningModel::getAppTuningModelChangedMessage()) {
        // don't repaint grid because it is drawn on a timer
        // this is kept here in case there are other child components that might need to be redrawn.
    }
}

void BrunRootComponent::labelTextChanged(Label* labelThatHasChanged) {
    if (labelThatHasChanged == &_frequencyGLabel) {
        String gs = _frequencyGLabel.getText();
        float g = gs.getFloatValue();
        auto bm = _processor.getBrun2Model();
        bm->uiSetGeneratorAsFrequency(g);
    } else if (labelThatHasChanged == &_centsGLabel) {
        String cs = _centsGLabel.getText();
        float c = cs.getFloatValue();
        auto bm = _processor.getBrun2Model();
        bm->uiSetGeneratorAsCents(c);
    } else {
        jassertfalse;
    }
}

#pragma mark - Timer

void BrunRootComponent::timerCallback() {
    if (isShowing()) {
        _brunGraph->repaint();
    }
}

void BrunRootComponent::_timerHelper() {
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
