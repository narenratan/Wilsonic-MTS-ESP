///*
// ==============================================================================
//
// CPSRootComponent.cpp
// Created: 25 Aug 2021 3:31:57pm
// Author:  Marcus W. Hobbs
//
// ==============================================================================
// */
//
//// TODO: Deprecate in favor of EulerGenus6Component
//
//#include "CPSRootComponent.h"
//#include "AppExperiments.h"
//#include "CPS_4_2.h"
//#include "CPS_5_2.h"
//#include "CPS_6_2.h"
//#include "CPS_6_3.h"
//
//#pragma mark - lifecycle
//
//// populate with a default cps
//
//CPSRootComponent::CPSRootComponent(WilsonicProcessor& processor)
//: WilsonicAppTuningComponent (processor)
//{
//    //_addHexanyElement();
//    //_addDekanyElement();
//    //_addPentadekanyElement();
//    _addEikosanyElement();
//
//    // default window size
//    setSize (_processor.getAppSkin().getWindowWidth(), _processor.getAppSkin().getWindowHeight());
//}
//
//// populate with a given cps
//
//CPSRootComponent::CPSRootComponent(WilsonicProcessor& processor,
//                                   shared_ptr<CPSTuningBase> cpsTuning)
//: WilsonicAppTuningComponent (processor)
//{
//    assert (cpsTuning != nullptr);
//
//    _setCPSComponent (cpsTuning);
//
//    // default window size
//    setSize (_processor.getAppSkin().getWindowWidth(), _processor.getAppSkin().getWindowHeight());
//}
//
//CPSRootComponent::~CPSRootComponent()
//{
//
//}
//
//#pragma mark - drawing
//
//void CPSRootComponent::paint (Graphics& g)
//{
//    // BG
//    g.fillAll (_processor.getAppSkin().getBgColor());
//
//    if (AppExperiments::showDebugBoundingBox)
//    {
//        // DEBUG
//        g.setColour (Colours::lightgreen);
//        g.drawRect (getLocalBounds(), 1);
//    }
//}
//
//void CPSRootComponent::resized()
//{
//    // lock
//    const ScopedLock sl (_lock);
//
//    // | main element area 80% | subset0 10% | subset1 10% |
//
//    // Keep the main area the same size even if there are no subsets
//    auto area = getLocalBounds().reduced (WilsonicAppSkin::verticalSpacing);
//    auto const mainWidthProportion = 0.6f;
//    auto const singleSubsetWidthProportion = 0.5f * (1.f - mainWidthProportion);
//    auto const columnWidth = area.getWidth() * singleSubsetWidthProportion; // calc first
//    auto const pitchWheelFontSizeMagic = 1.5 * 1.0f;
//    auto const subsetPitchWheelFontSizeMagic = 0.55f;
//
//    // main element area
//    auto mainArea = area.removeFromLeft (area.getWidth() * mainWidthProportion);
//    _mainElement->setBounds (mainArea);
//    _mainElement->setCustomFontScale (pitchWheelFontSizeMagic);
//
//    // subset columns
//    auto numSubsetColumns = (_subsets0.size() > 0 ? 1 : 0) + (_subsets1.size() > 0 ? 1 : 0);
//    if (numSubsetColumns == 0)
//    {
//        // no subsets
//        return;
//    }
//
//    // number of rows in subsets
//    auto const numSubsetRows = float (_subsets0.size()); // subsets 0 and 1 are the same count
//    auto const rowHeight = area.getHeight() / numSubsetRows;
//
//    // if there is 1 set of subsets it will be in subset 0, and subset 1 will be empty
//    if (numSubsetColumns == 1)
//    {
//        for (auto e : _subsets0)
//        {
//            auto sa = area.removeFromTop (rowHeight);
//            e->setBounds (sa);
//            e->setCustomFontScale (subsetPitchWheelFontSizeMagic);
//        }
//    }
//    else if (numSubsetColumns == 2)
//    {
//        for (auto i = 0; i < numSubsetRows; i++)
//        {
//            auto sa = area.removeFromTop (rowHeight);
//            auto s0Area = sa.withTrimmedRight (columnWidth).reduced (3);
//            auto s0 = _subsets0[i];
//            s0->setBounds (s0Area);
//            auto s1Area = sa.withTrimmedLeft (columnWidth).reduced (3);
//            auto s1 = _subsets1[i];
//            s1->setBounds (s1Area);
//            s0->setCustomFontScale (subsetPitchWheelFontSizeMagic);
//            s1->setCustomFontScale (subsetPitchWheelFontSizeMagic);
//        }
//    }
//    else
//    {
//        // numSubsetColumns can only be 0, 1, or 2
//        jassertfalse;
//    }
//}
//
//#pragma mark - components
//
//void CPSRootComponent::_addHexanyElement()
//{
////    auto hexany = make_shared<CPS_4_2> (CPS::A (1), CPS::B (3), CPS::C (5), CPS::D (7));
//    auto hexany = make_shared<CPS_4_2> (CPS::A (3), CPS::B (5), CPS::C (7), CPS::D (11));
////    auto hexany = make_shared<CPS_4_2> (CPS::A (1), CPS::B (45), CPS::C (135), CPS::D (225));
//
//    _setCPSComponent (hexany);
//}
//
//void CPSRootComponent::_addDekanyElement()
//{
//    //auto dekany = make_shared<CPS_5_2> (CPS::A (1), CPS::B (3), CPS::C (5), CPS::D (121), CPS::E (81));
//    auto dekany = make_shared<CPS_5_2> (CPS::A (1), CPS::B (3), CPS::C (5), CPS::D (7), CPS::E (11));
//    _setCPSComponent (dekany);
//}
//
//void CPSRootComponent::_addPentadekanyElement()
//{
//    auto pentadekany = make_shared<CPS_6_2> (CPS::A (45), CPS::B (135), CPS::C (225), CPS::D (6075), CPS::E (10125), CPS::F (30375));
//    _setCPSComponent (pentadekany);
//}
//
//void CPSRootComponent::_addEikosanyElement()
//{
//#if 0
//    // 1 3 7 9 11 15
//    auto eikosany = make_shared<CPS_6_3> (CPS::A (1), CPS::B (3), CPS::C (7), CPS::D (9), CPS::E (11), CPS::F (15));
//
//    // 1 3 5 7 9 11
//    auto eikosany = make_shared<CPS_6_3> (CPS::A (1), CPS::B (3), CPS::C (5), CPS::D (7), CPS::E (9), CPS::F (11));
//
//    // 9, 25, 49, 81, 11, 27
//    auto eikosany = make_shared<CPS_6_3> (CPS::A (9), CPS::B (25), CPS::C (49), CPS::D (81), CPS::E (11), CPS::F (27));
//
//    // 1, 3, 5, 7, 9, 11
//    // canonical d'allessandro
//    auto eikosany = make_shared<CPS_6_3> (CPS::A (1), CPS::B (3), CPS::C (5), CPS::D (7), CPS::E (9), CPS::F (11));
//
//    // 1, 45, 135, 225, 315, 405
//    // badass marcus
//    auto eikosany = make_shared<CPS_6_3> (CPS::A (1), CPS::B (45), CPS::C (135), CPS::D (225), CPS::E (315), CPS::F (405));
//
//    // 1, 75, 19, 5, 3, 15
//    auto eikosany = make_shared<CPS_6_3> (CPS::A (1), CPS::B (75), CPS::C (19), CPS::D (5), CPS::E (3), CPS::F (15));
//#endif
//
//    // 1, 9, 21, 3, 25, 15
//    auto eikosany = make_shared<CPS_6_3> (CPS::A (1), CPS::B (9), CPS::C (21), CPS::D (3), CPS::E (25), CPS::F (15));
//
//    _setCPSComponent (eikosany);
//}
//
//// logic of stacks of tunings for navigation spread throughout other methods
//void CPSRootComponent::_setCPSComponent (shared_ptr<CPSTuningBase> newTuning)
//{
//    assert (newTuning != nullptr);
//
//    // lock
//    const ScopedLock sl (_lock);
//
//    // push tuning on to stack
//    _tuningStack.push (newTuning);
//
//    // tear down existing components
//    removeAllChildren();
//    _subsets0.clear();
//    _subsets1.clear();
//    auto idIndex = int (0);
//
//    // main element
//    _mainElement = make_shared<CPSElementComponent> (_processor);
//    addAndMakeVisible (*_mainElement);
//    auto mainElementTuning = _tuningStack.top();
//    mainElementTuning->setShouldComputeSubsets (true); // calls update
//    _mainElement->setTuning (mainElementTuning);
//    auto idStr = String (idIndex++);
//    _selectedElementID = idStr; // default selected to main element
//    _mainElement->setComponentID (idStr);
//    _mainElement->setSingleClickCompletionBlock ([&](auto s) {singleClickElementID (s);});
//    _mainElement->setDoubleClickCompletionBlock ([&](auto s) {doubleClickElementID (s);});
//    _mainElement->setCommandClickCompletionBlock ([&](auto s) {commandClickElement (s);});
//
//    // Subsets 0
//    for (auto s0 : _tuningStack.top()->getSubsets0())
//    {
//        s0->setShouldComputeSubsets (false); // key lazy optimization
//        auto subsetElement = make_shared<CPSElementComponent> (_processor);
//        addAndMakeVisible (*subsetElement);
//        subsetElement->setTuning (s0);
//        auto idStr0 = String (idIndex++);
//        subsetElement->setComponentID (idStr0);
//        subsetElement->setSingleClickCompletionBlock ([&](auto s) {singleClickElementID (s);});
//        subsetElement->setDoubleClickCompletionBlock ([&](auto s) {doubleClickElementID (s);});
//        subsetElement->setCommandClickCompletionBlock ([&](auto s) {commandClickElement (s);});
//        _subsets0.push_back (subsetElement);
//    }
//
//    // Subsets 1
//    for (auto s1 : _tuningStack.top()->getSubsets1())
//    {
//        s1->setShouldComputeSubsets (false); // key lazy optimization
//        auto subsetElement = make_shared<CPSElementComponent>(_processor);
//        addAndMakeVisible (*subsetElement);
//        subsetElement->setTuning (s1);
//        auto idStr1 = String (idIndex++);
//        subsetElement->setComponentID (idStr1);
//        subsetElement->setSingleClickCompletionBlock ([&](auto s) {singleClickElementID (s);});
//        subsetElement->setDoubleClickCompletionBlock ([&](auto s) {doubleClickElementID (s);});
//        subsetElement->setCommandClickCompletionBlock ([&](auto s) {commandClickElement (s);});
//        _subsets1.push_back (subsetElement);
//    }
//
//    // update ui and set app tuning
//    singleClickElementID (_selectedElementID);
//    resized();
//
//    //
//    updateAppTuning();
//}
//
//#pragma mark - Mouse handling
//
//// "single-click" selects main or subset and sets app tuning
//
//void CPSRootComponent::singleClickElementID (String elementID)
//{
//    // lock
//    const ScopedLock sl (_lock);
//
//    // main element
//    _mainElement->setIsSelected (_mainElement->getComponentID() == elementID);
//
//    // subsets 0
//    for (auto s0 : _subsets0)
//    {
//        s0->setIsSelected (s0->getComponentID() == elementID);
//    }
//
//    // subsets 1
//    for (auto s1 : _subsets1)
//    {
//        s1->setIsSelected (s1->getComponentID() == elementID);
//    }
//
//    updateAppTuning();
//}
//
//// "double-click" makes the subset the main element if possible
//
//void CPSRootComponent::doubleClickElementID (String elementID)
//{
//    // lock
//    const ScopedLock sl (_lock);
//
//    // main element
//    if (_mainElement->getComponentID() == elementID)
//    {
//        // don't do anything
//        return;
//    }
//
//    // subsets
//    for (auto s0 : _subsets0)
//    {
//        if (s0->getComponentID() == elementID)
//        {
//            auto tuning = s0->getTuning();
//            if (tuning != nullptr)
//            {
//                _setCPSComponent (tuning);
//                return;
//            }
//            else
//            {
//                jassertfalse;
//            }
//        }
//    }
//
//    for (auto s1 : _subsets1)
//    {
//        if (s1->getComponentID() == elementID)
//        {
//            auto tuning = s1->getTuning();
//            if (tuning != nullptr)
//            {
//                _setCPSComponent (tuning);
//                return;
//            }
//        }
//    }
//}
//
//// command-click = "back button"
//
//void CPSRootComponent::commandClickElement (String)
//{
//    // lock
//    const ScopedLock sl (_lock);
//
//    if (_tuningStack.size() == 0)
//    {
//        // This should not happen...we should always have 1 element on the stack
//        jassertfalse;
//    }
//    else if (_tuningStack.size() == 1)
//    {
//        // the stack should always have at least one tuning on the stack:
//        // this means to dismiss the CPSRootComponent
//        if (_dismissCompletionBlock != nullptr)
//        {
//            _dismissCompletionBlock();
//        }
//        return;
//    }
//    else if (_tuningStack.size() > 1)
//    {
//        // weird pattern: we pop the top component because _setCPSTuningComponent is pushing it back on the stack
//        _tuningStack.pop();
//        auto t = _tuningStack.top();
//        _tuningStack.pop();
//        _setCPSComponent (t);
//    }
//}
//
//void CPSRootComponent::setDismissCompletionBlock (function<void()> cb)
//{
//    _dismissCompletionBlock = cb;
//}
//
//#pragma mark - App Tuning
//
//// update app tuning with selected element
//
//void CPSRootComponent::updateAppTuning()
//{
//    // lock
//    const ScopedLock sl (_lock);
//
//    // main element
//    if (_mainElement->getIsSelected())
//    {
//        _mainElement->updateAppTuning();
//        return;
//    }
//
//    // subsets
//    for (auto s0 : _subsets0)
//    {
//        if (s0->getIsSelected())
//        {
//            s0->updateAppTuning();
//            return;
//        }
//    }
//
//    for (auto s1 : _subsets1)
//    {
//        if (s1->getIsSelected())
//        {
//            s1->updateAppTuning();
//            return;
//        }
//    }
//}
//
//#pragma mark - App Tuning Title
//
//const string CPSRootComponent::getAppTuningTitle()
//{
//    // figure out tuning title for this
//    return "CPS";
//}
