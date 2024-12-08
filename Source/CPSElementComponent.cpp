///*
// ==============================================================================
//
// CPSElementComponent.cpp
// Created: 28 Aug 2021 10:43:13pm
// Author:  Marcus W. Hobbs
//
// ==============================================================================
// */
//
//// TODO: Deprecate in favor of EulerGenus6Component
//
//#include "AppExperiments.h"
//#include "CPSElementComponent.h"
//
//#pragma mark - lifecycle
//
//CPSElementComponent::CPSElementComponent (WilsonicProcessor& processor)
//: WilsonicAppTuningComponent (processor)
//{
//    // TODO: how to make experiments at compile time
//    // TODO: turning on timer is a performance hit
//    //_pitchWheel = make_unique<WilsonicPitchWheelComponent> (_processor, false); // no timer...constant time
//    _pitchWheel = make_unique<WilsonicPitchWheelComponent> (_processor, true); // set timer to drawing all "playing" notes...perf hit
//
//    _pitchWheel->setTuning (_tuning);
//    _pitchWheel->setInterceptsMouseClicks (false, false); // pass mouse events up the chain
//    addAndMakeVisible (*_pitchWheel);
//
//    // label on top of pitch wheel
//    _tuningNameLabel = make_unique<Label> ("tuning_name", "");
//    _tuningNameLabel->setJustificationType(Justification::topLeft);
//    _tuningNameLabel->setInterceptsMouseClicks (false, false);
//    addAndMakeVisible (*_tuningNameLabel);
//
//    // label below name label which shows the number of notes per octave
//    _tuningNPOLabel = make_unique<Label> ("tuning_npo", "");
//    _tuningNPOLabel->setJustificationType(Justification::topLeft);
//    _tuningNPOLabel->setInterceptsMouseClicks (false, false);
//    addAndMakeVisible (*_tuningNPOLabel);
//
//    // default window size
//    setSize (_processor.getAppSkin().getWindowWidth(), _processor.getAppSkin().getWindowHeight());
//}
//
//CPSElementComponent::~CPSElementComponent()
//{
//
//}
//
//#pragma mark - drawing
//
//void CPSElementComponent::paint (Graphics& g)
//{
//    // BG
//    g.fillAll (_processor.getAppSkin().getBgColor());
//
//    if (AppExperiments::showDebugBoundingBox)
//    {
//        // DEBUG
//        g.setColour (Colours::darkgrey);
//        g.drawRect (getLocalBounds(), 1);
//    }
//
//    if (_isSelected)
//    {
//        // DEBUG
//        g.setColour (_processor.getAppSkin().getSelectedComponentColor());
//        g.drawRect (getLocalBounds(), 2);
//    }
//
//    // update labels
//    _tuningNameLabel->setText (_tuning->getTuningName(), NotificationType::dontSendNotification);
//    _tuningNPOLabel->setText (String (_tuning->getProcessedArray().count()), NotificationType::dontSendNotification);
//}
//
//void CPSElementComponent::resized()
//{
//    // Global
//    auto area = getLocalBounds().reduced (4); // so selected outline shows
//
//    // pitch wheel
//    _pitchWheel->setBounds (area);
//
//    // font height as proportion of square window height
//    auto const fH = jmax (20.f, 0.025f * area.getHeight());
//
//    // tuning name label
//    _tuningNameLabel->setFont (Font (fH).withHorizontalScale (0.9));
//    auto nameLabelArea = Rectangle<int> (area.getX(), area.getY(), area.getWidth(), fH);
//    _tuningNameLabel->setBounds (nameLabelArea);
//
//    // tuning NPO label
//    _tuningNPOLabel->setFont (Font (2.f * fH).withHorizontalScale (0.9));
//    auto npoLabelArea = Rectangle<int> (area.getX(), nameLabelArea.getY() + nameLabelArea.getHeight(), 0.5f * area.getWidth(), 2.f * fH);
//    _tuningNPOLabel->setBounds (npoLabelArea);
//}
//
//#pragma mark - Tuning
//
//void CPSElementComponent::setTuning (shared_ptr<CPSTuningBase> inputTuning)
//{
//    // Tuning
//    _tuning = inputTuning;
//    _tuning->setOnTuningUpdate ([this] { _cpsTuningChanged();});
//    _pitchWheel->setTuning (_tuning);
//    _tuningNameLabel->setText (_tuning->getTuningName(), NotificationType::dontSendNotification);
//    _tuningNPOLabel->setText (String (_tuning->getProcessedArray().count()), NotificationType::dontSendNotification);
//    _cpsTuningChanged();
//}
//
//const shared_ptr<CPSTuningBase> CPSElementComponent::getTuning()
//{
//    return _tuning;
//}
//
//#pragma mark - completion handler
//
//void CPSElementComponent::setSingleClickCompletionBlock (function<void(String)> completionBlock)
//{
//    _singleClickCompletionBlock = completionBlock;
//}
//
//void CPSElementComponent::setDoubleClickCompletionBlock (function<void(String)> completionBlock)
//{
//    _controlClickCompletionBlock = completionBlock;
//}
//
//void CPSElementComponent::setCommandClickCompletionBlock (function<void(String)> completionBlock)
//{
//    _commandClickCompletionBlock = completionBlock;
//}
//
//#pragma mark - CPSTuningChanged
//
//void CPSElementComponent::_cpsTuningChanged()
//{
//    repaint();
//}
//
//// 1 = default logic
//void CPSElementComponent::setCustomFontScale (float scale01)
//{
//    _pitchWheel->setCustomFontScale (scale01);
//}
//
//#pragma mark - App Tuning Title
//
//const string CPSElementComponent::getAppTuningTitle()
//{
//    return "invalid";
//}
//
//#pragma mark - selection
//
//const bool CPSElementComponent::getIsSelected()
//{
//    return _isSelected;
//}
//
//void CPSElementComponent::setIsSelected (bool newValue)
//{
//    _isSelected = newValue;
//    repaint();
//}
//
//#pragma mark - click handlers
//
//void CPSElementComponent::mouseEnter (const MouseEvent& event)
//{
//    auto const shiftDown = event.mods.isShiftDown();
//    if (shiftDown)
//    {
//        _mouseHelper (event);
//    }
//}
//
//void CPSElementComponent::mouseDown (const MouseEvent& event)
//{
//    _mouseHelper (event);
//}
//
//void CPSElementComponent::mouseDoubleClick (const MouseEvent& event)
//{
//    _mouseHelper (event);
//}
//
//void CPSElementComponent::_mouseHelper (const MouseEvent& event)
//{
//    // give priority to shift, per componentid
//    auto const shiftDown = event.mods.isShiftDown();
//
//    if (shiftDown)
//    {
//        if (_singleClickCompletionBlock != nullptr)
//        {
//            _singleClickCompletionBlock (getComponentID());
//            //DBG (getTuning()->getDebugDescription());
//        }
//        else
//        {
//            assert (false);
//        }
//        return;
//    }
//
//    // then ctrl, per component id
//    auto const ctrlDown = event.mods.isCtrlDown();
//
//    if (ctrlDown)
//    {
//        if (_controlClickCompletionBlock != nullptr)
//        {
//            _controlClickCompletionBlock (getComponentID());
//        }
//        else
//        {
//            assert (false);
//        }
//        return;
//    }
//
//    // then "any" modifier, which on a mac equals "command"...not keyed off element
//    auto const commandDown = event.mods.isAnyModifierKeyDown();
//
//    if (commandDown)
//    {
//        if (_commandClickCompletionBlock != nullptr)
//        {
//            _commandClickCompletionBlock (getComponentID());
//        }
//        else
//        {
//            assert (false);
//        }
//        return;
//    }
//}
//
//#pragma mark -
//
//void CPSElementComponent::updateAppTuning()
//{
//    // TODO: temporary setting of global app tuning
//    _processor.getAppTuningModel()->setTuning (getTuning());
//}
