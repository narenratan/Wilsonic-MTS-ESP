/*
 ==============================================================================

 AppRootComponent.cpp
 Created: 17 Mar 2021 8:23:57pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include <JuceHeader.h>
#include "AppRootComponent.h"
#include "AppExperiments.h"

#pragma mark - lifecycle

AppRootComponent::AppRootComponent(WilsonicProcessor& processor)
: WilsonicComponentBase(processor)
, _rootComponent(_processor)
, _keyboardContainerComponent(_processor, *this) {
    addAndMakeVisible(_rootComponent);
    addAndMakeVisible(_keyboardContainerComponent);
    setSize(_processor.getAppSkin().getWindowWidth(), _processor.getAppSkin().getWindowHeight());

    // listen for keyboard toggle messages
    _keyboardContainerComponent.addActionListener(this);
}

AppRootComponent::~AppRootComponent() {
    _keyboardContainerComponent.removeActionListener(this);
}

#pragma mark - drawing

void AppRootComponent::paint(Graphics& g) {
    g.fillAll(_processor.getAppSkin().getBgColor());
    if (AppExperiments::showDebugBoundingBox) {
        g.setColour(Colours::green);
        g.drawRect(getLocalBounds(), 2);
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }
}

// based on toggled keyboard
float AppRootComponent::_getKeyboardHeightMin() {
    return (_processor.restoreKeyboardVisible()) ? _keyboardHeight: __keyboardHeightMinNotShowing;
}

void AppRootComponent::resized() {
    // calculate/clamp height of the keyboard
    auto area = getLocalBounds();
    auto const h2 = 0.5f * area.getHeight();

    if (_processor.restoreKeyboardVisible()) {
        // support portrait and landscape
        if (h2 >= __keyboardHeightMinShowing) {
            _keyboardHeight = jlimit(__keyboardHeightMinShowing, h2, _keyboardHeight);
        } else {
            _keyboardHeight = jlimit(h2, __keyboardHeightMinShowing, _keyboardHeight);
        }
    } else {
        _keyboardHeight = __keyboardHeightMinNotShowing;
    }

    // set the root container and keyboard bounds
    _keyboardContainerComponent.setBounds(area.removeFromBottom(static_cast<int>(_keyboardHeight)));
    _keyboardContainerComponent.repaint();
    _rootComponent.setBounds(area);
}

// ADD NEW SCALE DESIGN HERE

#pragma mark - DesignsProtocol

void AppRootComponent::showBrunTuning() {
    _rootComponent.showBrunTuning();
}

void AppRootComponent::showCoPrimeTuning() {
    _rootComponent.showCoPrimeTuning();
}

void AppRootComponent::showCPSTuning() {
    _rootComponent.showCPSTuning();
}

void AppRootComponent::showDiamondsTuning() {
    _rootComponent.showDiamondsTuning();
}

void AppRootComponent::showEqualTemperamentTuning() {
    _rootComponent.showEqualTemperamentTuning();
}

void AppRootComponent::showEulerGenusV2Tuning() {
    _rootComponent.showEulerGenusV2Tuning();
}

void AppRootComponent::showMorphTuning() {
    _rootComponent.showMorphTuning();
}

void AppRootComponent::showPartchTuning() {
    _rootComponent.showPartchTuning();
}

void AppRootComponent::showPersian17NorthIndianTuning() {
    _rootComponent.showPersian17NorthIndianTuning();
}

void AppRootComponent::showPresetsTuning() {
    _rootComponent.showPresetsTuning();
}

void AppRootComponent::showRecurrenceRelationTuning() {
    _rootComponent.showRecurrenceRelationTuning();
}

void AppRootComponent::showScalaTuning() {
    _rootComponent.showScalaTuning();
}

void AppRootComponent::showTritriadicTuning() {
    _rootComponent.showTritriadicTuning();
}

#pragma mark - Pages

void AppRootComponent::showSynth() {
    _rootComponent.showSynth();
}

#pragma mark - DeltaChangeListener

void AppRootComponent::changeListenerCallback(ChangeBroadcaster* source) {
    if (auto* deltaBroadcaster = dynamic_cast<DeltaBroadcaster*>(source)) {
        // this particular broadcaster is the keyboard container
        const Point<int> delta = deltaBroadcaster->getDelta();
        _keyboardHeight -= delta.getY();
        _keyboardContainerComponent.adjustKeySizeFactorByDelta(static_cast<int>(delta.getX()));
        resized(); // resized will clamp _keyboardHeight
    }
}

#pragma mark - actionlistener

void AppRootComponent::actionListenerCallback(const String& message) {
    if (message == _keyboardContainerComponent.getToggleShowKeyBoardChangedMessage()) {
        resized();
    }
}

