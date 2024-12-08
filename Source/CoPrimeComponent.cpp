/*
 ==============================================================================

 CoPrimeComponent.cpp
 Created: 23 Apr 2023 12:41:21pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "CoPrimeComponent.h"
#include "CoPrime.h"
#include "CoPrimeModel.h"
#include "DesignsModel.h"

CoPrimeComponent::CoPrimeComponent(WilsonicProcessor& processor)
: WilsonicAppTuningComponent(processor)
{
    auto const cm = _processor.getCoPrimeModel();

    // drawing mode combobox
    _displayModeComboBox = make_unique<DeltaComboBox>(_processor, true);
    _displayModeComboBox->addItemList(CoPrime::getDisplayModeNames(), 1);
    auto const selectedDrawingModeIndex = cm->uiGetDisplayMode();
    _displayModeComboBox->setSelectedItemIndex(selectedDrawingModeIndex, NotificationType::dontSendNotification);
    _displayModeComboBox->setToolTip("Drawing Mode of the CoPrime Grid");
    auto onChange = [this, &cm]() {
        // set new preset
        auto const selectedDisplayModeIndex = (CoPrime::DisplayMode)_displayModeComboBox->getSelectedItemIndex();
        cm->uiSetDisplayMode(selectedDisplayModeIndex);
    };
    _displayModeComboBox->setOnChange(onChange);
    addAndMakeVisible(*_displayModeComboBox);


    // bubbles
    _aBubble = make_unique<BubbleDrawable>(BubblePlacement::left, "A", "A/B");
    _bBubble = make_unique<BubbleDrawable>(BubblePlacement::left, "B", "A/B");
    _cBubble = make_unique<BubbleDrawable>(BubblePlacement::left, "C", "C/D");
    _dBubble = make_unique<BubbleDrawable>(BubblePlacement::left, "D", "C/D");
    _sBubble = make_unique<BubbleDrawable>(BubblePlacement::left, "S", "The horizontal offset of terms");
    _tBubble = make_unique<BubbleDrawable>(BubblePlacement::left, "T", "The vertical offset of terms");
    _xBubble = make_unique<BubbleDrawable>(BubblePlacement::left, "X", "The number of terms left to right");
    _yBubble = make_unique<BubbleDrawable>(BubblePlacement::left, "Y", "The number of terms bottom to top");
    addAndMakeVisible(*_aBubble);
    addAndMakeVisible(*_bBubble);
    addAndMakeVisible(*_cBubble);
    addAndMakeVisible(*_dBubble);
    addAndMakeVisible(*_sBubble);
    addAndMakeVisible(*_tBubble);
    addAndMakeVisible(*_xBubble);
    addAndMakeVisible(*_yBubble);

    // sliders
    float const step = 1;
    _aSlider = make_unique<SeedSlider>(_processor, "A", CoPrime::getMinA(), cm->uiGetA(), CoPrime::getMaxA(), step, [cm](float a) {cm->uiSetA(static_cast<float>(a));});
    _bSlider = make_unique<SeedSlider>(_processor, "B", CoPrime::getMinB(), cm->uiGetB(), CoPrime::getMaxB(), step, [cm](float b) {cm->uiSetB(static_cast<float>(b));});
    _cSlider = make_unique<SeedSlider>(_processor, "C", CoPrime::getMinC(), cm->uiGetC(), CoPrime::getMaxC(), step, [cm](float c) {cm->uiSetC(static_cast<float>(c));});
    _dSlider = make_unique<SeedSlider>(_processor, "D", CoPrime::getMinD(), cm->uiGetD(), CoPrime::getMaxD(), step, [cm](float d) {cm->uiSetD(static_cast<float>(d));});
    _sSlider = make_unique<SeedSlider>(_processor, "S", CoPrime::getMinS(), cm->uiGetS(), CoPrime::getMaxS(), step, [cm](float s) {cm->uiSetS(static_cast<float>(s));});
    _tSlider = make_unique<SeedSlider>(_processor, "T", CoPrime::getMinT(), cm->uiGetT(), CoPrime::getMaxT(), step, [cm](float t) {cm->uiSetT(static_cast<float>(t));});
    _xSlider = make_unique<SeedSlider>(_processor, "X", CoPrime::getMinX(), cm->uiGetX(), CoPrime::getMaxX(), step, [cm](float x) {cm->uiSetX(static_cast<float>(x));});
    _ySlider = make_unique<SeedSlider>(_processor, "Y", CoPrime::getMinY(), cm->uiGetY(), CoPrime::getMaxY(), step, [cm](float y) {cm->uiSetY(static_cast<float>(y));});
    addAndMakeVisible(*_aSlider);
    addAndMakeVisible(*_bSlider);
    addAndMakeVisible(*_cSlider);
    addAndMakeVisible(*_dSlider);
    addAndMakeVisible(*_sSlider);
    addAndMakeVisible(*_tSlider);
    addAndMakeVisible(*_xSlider);
    addAndMakeVisible(*_ySlider);

    _coPrimeGrid = make_unique<CoPrimeGridComponent>(_processor);
    addAndMakeVisible(*_coPrimeGrid);

    // default window size
    setSize(_processor.getAppSkin().getWindowWidth(), _processor.getAppSkin().getWindowHeight());

    cm->addActionListener(this);
    _processor.getAppTuningModel()->addActionListener(this);

    _tuningChangedUpdateUI();
    
    // start timer
    _timerHelper();
}

CoPrimeComponent::~CoPrimeComponent() {
    stopTimer();
    _processor.getCoPrimeModel()->removeActionListener(this);
    _processor.getAppTuningModel()->removeActionListener(this);
}

// UI

#pragma mark - paint

void CoPrimeComponent::paint(Graphics& g) {
    g.fillAll(_processor.getAppSkin().getBgColor());
    if (AppExperiments::showDebugBoundingBox) {
        g.setColour(Colours::green);
        g.drawRect(getLocalBounds(), 2);
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }
    
    // don't repaint grid...it's on a timer
}

#pragma mark - resized

void CoPrimeComponent::resized() {
    auto const slider_height = static_cast<int>(WilsonicAppSkin::seedSliderHeight);
    auto const bubble_width = static_cast<int>(WilsonicAppSkin::minHitPointSize);
    auto const seed_slider_width = static_cast<int>(WilsonicAppSkin::seedSliderHeight);
    auto const margin = WilsonicAppSkin::tuningComponentInteriorMargin;
    auto area = getLocalBounds().reduced(static_cast<int>(margin));
    auto const num_sliders_x = 5; // 4 sliders + 1 combobox
    auto const slider_width = static_cast<int>(static_cast<float>(area.getWidth()) / static_cast<float>(num_sliders_x));

    // numerator row
    auto numerator_row = area.removeFromTop(slider_height);
    // display mode combobox
    auto display_mode_box = numerator_row.removeFromLeft(slider_width);
    display_mode_box = display_mode_box.removeFromBottom(static_cast<int>(WilsonicAppSkin::comboBoxHeight));
    _displayModeComboBox->setBounds(display_mode_box);
    
    // A
    auto sa0 = numerator_row.removeFromLeft(slider_width);
    auto sa1 = sa0.withSizeKeepingCentre(seed_slider_width + bubble_width, sa0.getHeight());
    auto sab = sa1.removeFromLeft(bubble_width);
    _aBubble->setBounds(sab);
    auto sa = sa1.removeFromLeft(slider_width);
    _aSlider->setBounds(sa);

    // C
    auto sc0 = numerator_row.removeFromLeft(slider_width);
    auto sc1 = sc0.withSizeKeepingCentre(seed_slider_width + bubble_width, sc0.getHeight());
    auto scb = sc1.removeFromLeft(bubble_width);
    _cBubble->setBounds(scb);
    auto sc = sc1.removeFromLeft(slider_width);
    _cSlider->setBounds(sc);

    // S
    auto ss0 = numerator_row.removeFromLeft(slider_width);
    auto ss1 = ss0.withSizeKeepingCentre(seed_slider_width + bubble_width, ss0.getHeight());
    auto ssb = ss1.removeFromLeft(bubble_width);
    _sBubble->setBounds(ssb);
    auto ss = ss1.removeFromLeft(slider_width);
    _sSlider->setBounds(ss);

    // X
    auto sx0 = numerator_row.removeFromLeft(slider_width);
    auto sx1 = sx0.withSizeKeepingCentre(seed_slider_width + bubble_width, sx0.getHeight());
    auto sxb = sx1.removeFromLeft(bubble_width);
    _xBubble->setBounds(sxb);
    auto sx = sx1.removeFromLeft(slider_width);
    _xSlider->setBounds(sx);

    // denominator row
    auto denominator_row = area.removeFromTop(slider_height);
    denominator_row.removeFromLeft(slider_width);//combobox
    
    // B
    auto sb0 = denominator_row.removeFromLeft(slider_width);
    auto sb1 = sb0.withSizeKeepingCentre(seed_slider_width + bubble_width, sb0.getHeight());
    auto sbb = sb1.removeFromLeft(bubble_width);
    _bBubble->setBounds(sbb);
    auto sb = sb1.removeFromLeft(slider_width);
    _bSlider->setBounds(sb);

    // D
    auto sd0 = denominator_row.removeFromLeft(slider_width);
    auto sd1 = sd0.withSizeKeepingCentre(seed_slider_width + bubble_width, sd0.getHeight());
    auto sdb = sd1.removeFromLeft(bubble_width);
    _dBubble->setBounds(sdb);
    auto sd = sd1.removeFromLeft(slider_width);
    _dSlider->setBounds(sd);

    // T
    auto st0 = denominator_row.removeFromLeft(slider_width);
    auto st1 = st0.withSizeKeepingCentre(seed_slider_width + bubble_width, st0.getHeight());
    auto stb = st1.removeFromLeft(bubble_width);
    _tBubble->setBounds(stb);
    auto st = st1.removeFromLeft(slider_width);
    _tSlider->setBounds(st);

    // Y
    auto sy0 = denominator_row.removeFromLeft(slider_width);
    auto sy1 = sy0.withSizeKeepingCentre(seed_slider_width + bubble_width, sy0.getHeight());
    auto syb = sy1.removeFromLeft(bubble_width);
    _yBubble->setBounds(syb);
    auto sy = sy1.removeFromLeft(slider_width);
    _ySlider->setBounds(sy);

    // the rest is the coprime grid
    _coPrimeGrid->setBounds(area);
}

// tuning title
const string CoPrimeComponent::getAppTuningTitle() {
    return "CoPrime Grid";
}


#pragma mark - private methods

// ActionListener callback
void CoPrimeComponent::actionListenerCallback(const String& message) {
    if (message == DesignsModel::getCoPrimeTuningChangedActionMessage()) {
        _tuningChangedUpdateUI();
        _timerHelper(); // npo changes timer rate
    } else if (message ==  AppTuningModel::getAppTuningModelChangedMessage()) {
        // don't repaint...we're on a timer
        // this is kept here in case there are other child components that might need to be redrawn.
    }
}

void CoPrimeComponent::_tuningChangedUpdateUI() {
    auto const cm = _processor.getCoPrimeModel();
    auto const selectedDisplayMode = cm->uiGetDisplayMode();
    _displayModeComboBox->setSelectedItemIndex(selectedDisplayMode, NotificationType::dontSendNotification);
    _aSlider->setValue(cm->uiGetA(), dontSendNotification);
    _bSlider->setValue(cm->uiGetB(), dontSendNotification);
    _cSlider->setValue(cm->uiGetC(), dontSendNotification);
    _dSlider->setValue(cm->uiGetD(), dontSendNotification);
    _sSlider->setValue(cm->uiGetS(), dontSendNotification);
    _tSlider->setValue(cm->uiGetT(), dontSendNotification);
    _xSlider->setValue(cm->uiGetX(), dontSendNotification);
    _ySlider->setValue(cm->uiGetY(), dontSendNotification);

    // don't repaint grid here...it's on a timer
    
    // draw
    resized();
}

#pragma mark - Timer

void CoPrimeComponent::timerCallback() {
    if (isShowing()) {
        _coPrimeGrid->repaint();
    }
}

void CoPrimeComponent::_timerHelper() {
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
