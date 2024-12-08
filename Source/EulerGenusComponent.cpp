///*
// ==============================================================================
//
// EulerGenusComponent.cpp
// Created: 2 Sep 2021 8:28:54pm
// Author:  Marcus W. Hobbs
//
// ==============================================================================
// */
//
//// TODO: Deprecate in favor of EulerGenusComponentV2
//
//#include "EulerGenusComponent.h"
//#include "EulerGenus_1.h"
//#include "EulerGenus_2.h"
//#include "EulerGenus_3.h"
//#include "EulerGenus_4.h"
//#include "EulerGenus_5.h"
//#include "EulerGenus_6.h"
//#include "AppExperiments.h"
//
//#pragma mark - lifecycle
//
//EulerGenusComponent::EulerGenusComponent (WilsonicProcessor& processor)
//: WilsonicAppTuningComponent (processor)
//{
//    // euler genus delta combo box
//    _eulerGenusComboBox = make_unique<DeltaComboBox> (_processor, true);
//    addAndMakeVisible (*_eulerGenusComboBox);
//
//    // presets combo box
//    _presetsComboBox = make_unique<DeltaComboBox> (_processor, true);
//    addAndMakeVisible (*_presetsComboBox);
//
//    // euler genus delta combo box callback
//    // TODO: abstract this to a model
//    _eulerGenusComboBox->clear (NotificationType::dontSendNotification);
//    _eulerGenusComboBox->addItem ("Euler Genus 1", 1);
//    _eulerGenusComboBox->addItem ("Euler Genus 2", 2);
//    _eulerGenusComboBox->addItem ("Euler Genus 3", 3);
//    _eulerGenusComboBox->addItem ("Euler Genus 4", 4);
//    _eulerGenusComboBox->addItem ("Euler Genus 5", 5);
//    _eulerGenusComboBox->addItem ("Euler Genus 6", 6);
//    auto onChange = [this]()
//    {
//        if (isShowing())
//        {
//            auto const selectedItemIndex = _eulerGenusComboBox->getSelectedItemIndex();
//            switch (selectedItemIndex)
//            {
//                case 0: _addEulerGenus1Component(); break;
//                case 1: _addEulerGenus2Component(); break;
//                case 2: _addEulerGenus3Component(); break;
//                case 3: _addEulerGenus4Component(); break;
//                case 4: _addEulerGenus5Component(); break;
//                case 5: default: _addEulerGenus6Component(); break;
//            }
//        }
//    };
//    _eulerGenusComboBox->setOnChange (onChange);
//
//    // seed slider
//    _seedSliderComponent = make_unique<SeedSliderComponent> (_processor);
//    addAndMakeVisible (*_seedSliderComponent);
//
//    // default
//    _eulerGenusComboBox->setSelectedItemIndex (5, NotificationType::sendNotificationAsync); // euler genus 6
//
//    // default window size
//    setSize (_processor.getAppSkin().getWindowWidth(), _processor.getAppSkin().getWindowHeight());
//}
//
//EulerGenusComponent::~EulerGenusComponent()
//{
//
//}
//
//#pragma mark - drawing
//
//void EulerGenusComponent::paint (Graphics& g)
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
//void EulerGenusComponent::resized()
//{
//    // lock
//    const ScopedLock sl (_lock);
//
//    // | euler genus combo box - margin - presets combo box - |
//    // | - seeds                                            - |
//    // | subset 0 | subset 1 | ... | subset n               - |
//
//    // Keep the main area the same size even if there are no subsets
//    auto const margin = WilsonicAppSkin::verticalSpacing;
//    auto const comboBoxHeight = WilsonicAppSkin::comboBoxHeight;
//    auto const comboBoxWidth = 350.f - 100 + 50;
//    auto area = getLocalBounds().reduced (margin);
//    auto const minX = area.getX();
//    auto const maxX = area.getX() + area.getWidth();
//    auto const magicSelectedProportion = 0.85f;
//    auto const magicUnselectedHeightProportion = 0.75f;
//    auto const magicSelectedFontScale = 1.5f;
//    auto const magicUnselectedFontScale = 0.6f;
//
//    // euler genus deltaComboBox
//    auto egComboBoxArea = area.removeFromTop (comboBoxHeight);
//    egComboBoxArea.setWidth(jmin (comboBoxWidth, float(egComboBoxArea.getWidth())));
//    _eulerGenusComboBox->setBounds (egComboBoxArea);
//
//    // presets combobox: make same size, offset by x margin from EG
//    auto presetsComboBoxArea = egComboBoxArea;
//    presetsComboBoxArea.setX(egComboBoxArea.getX() + egComboBoxArea.getWidth() + margin);
//    _presetsComboBox->setBounds (presetsComboBoxArea);
//
//    // y margin between combo box and seeds
//    area.removeFromTop (10);
//
//    // Seeds
//    auto seedsArea = area.removeFromTop (WilsonicAppSkin::seedSliderHeight);
//    _seedSliderComponent->setBounds (seedsArea);
//
//    // y margin between seeds and genus
//    area.removeFromTop (10);
//
//    // if cpsComponent is defined show it
//    if (_cpsComponent != nullptr)
//    {
//        _cpsComponent->setBounds (area);
//    }
//    else
//    {
//        // root EG display
//        auto const numberOfColumns = float (_subsets0.size());
//        auto const columnWidth = area.getWidth() / numberOfColumns;
//
//        // render subsets
//        for (auto eg : _subsets0)
//        {
//            // bounds
//            auto sa = area.removeFromLeft (columnWidth);
//
//            // increase size for selected element
//            if (eg->getIsSelected())
//            {
//                eg->toFront (true);
//                auto mx = magicSelectedProportion * jmax (float(sa.getWidth()), float(sa.getHeight()));
//                mx = jmin (mx, float (sa.getHeight())); // don't grow so big you bust out into seeds
//                mx *= 0.9f; // magic shrink
//                sa = sa.withSizeKeepingCentre (mx, mx); // make it square
//
//                // make sure elements have positive x coords
//                sa.setX (jmax (sa.getX(), int(minX)));
//
//                // make sure elements have x + w < bounds width
//                auto const sax = sa.getX() + sa.getWidth();
//                if (sax > maxX)
//                {
//                    sa.setX (sa.getX() - (sax - maxX)); // tricky
//                }
//                eg->setCustomFontScale (magicSelectedFontScale);
//            }
//            else
//            {
//                // decrease size for the rest
//                eg->toBack();
//                sa = sa.withSizeKeepingCentre (sa.getWidth(), magicUnselectedHeightProportion * sa.getHeight());
//                eg->setCustomFontScale (magicUnselectedFontScale);
//            }
//            eg->setBounds (sa);
//        }
//    }
//}
//
//// changes view
//void EulerGenusComponent::_setEulerGenus (shared_ptr<CPSTuningBase> newEulerGenus)
//{
//    //
//    assert (newEulerGenus != nullptr);
//
//    // lock
//    const ScopedLock sl (_lock);
//
//    // tear down existing components
//    removeAllChildren(); // this removes the combo boxes and the seedslider
//    addAndMakeVisible (*_eulerGenusComboBox);
//    addAndMakeVisible (*_presetsComboBox); // add it back
//    addAndMakeVisible (*_seedSliderComponent); // add it back
//
//    _cpsComponent = nullptr;
//    _currentEulerGenus = newEulerGenus;
//    _subsets0.clear();
//    auto idIndex = int (0);
//
//    // add (n, 0) ["null"] first
//    // TODO: Make (n,0)...will need to update middleElement below
//
//    // note use of subsets is different at euler genus level
//    // tunings in euler genus
//    for (auto s0 : _currentEulerGenus->getSubsets0())
//    {
//        s0->setShouldComputeSubsets (false); // do not compute subsets during euler genus
//        auto subsetElement = make_shared<CPSElementComponent> (_processor);
//        addAndMakeVisible (*subsetElement);
//        subsetElement->setTuning (s0);
//        auto idStr = String (idIndex++);
//        subsetElement->setComponentID (idStr);
//        subsetElement->setSingleClickCompletionBlock  ([&](auto s) { singleClickElementID (s); });
//        subsetElement->setDoubleClickCompletionBlock  ([&](auto s) { doubleClickElementID (s); });
//        subsetElement->setCommandClickCompletionBlock ([&](auto ) {  } );
//        subsetElement->setCustomFontScale (0.75f * 0.7f);
//        _subsets0.push_back (subsetElement);
//    }
//
//    // default is first subset...
//    auto middleElement = int (_subsets0.size() / 2);
//    if (_subsets0.size() % 2 == 0 && middleElement > 0)
//    {
//        --middleElement;
//    }
//    jassert (middleElement >= 0 && middleElement < _subsets0.size());
//    _selectedElementID = _subsets0[middleElement]->getComponentID();
//    singleClickElementID (_selectedElementID);
//    resized();
//}
//
//const shared_ptr<CPSTuningBase> EulerGenusComponent::_getEulerGenus()
//{
//    return _currentEulerGenus;
//}
//
//#pragma mark - Mouse handling
//
//// "single-click" selects element and sets app tuning
//
//void EulerGenusComponent::singleClickElementID (String elementID)
//{
//    // lock
//    const ScopedLock sl (_lock);
//
//    // subsets
//    for (auto s0 : _subsets0)
//    {
//        auto const isSelected = (s0->getComponentID() == elementID);
//        s0->setIsSelected (isSelected);
//    }
//
//    // set app tuning to the selected element
//    updateAppTuning();
//    resized(); // because of zooming
//}
//
//// "double-click" makes the subset the main element if possible
//
//void EulerGenusComponent::doubleClickElementID (String elementID)
//{
//    // lock
//    const ScopedLock sl (_lock);
//
//    // subsets
//    for (auto s0 : _subsets0)
//    {
//        if (s0->getComponentID() == elementID)
//        {
//            auto tuning = s0->getTuning();
//            if (tuning != nullptr)
//            {
//                removeAllChildren();
//
//                // this is to support seed slider in subsets.
//                // crash when changing seeds deep in the subset hierarchy around "is visible"
//                // for now, set as "disabled" to render the components off-color with no interaction
//                addAndMakeVisible (*_seedSliderComponent);
//                _seedSliderComponent->setEnabled (false);
//
//                // optimization
//                tuning->setShouldComputeSubsets (true);
//                _cpsComponent = make_shared<CPSRootComponent> (_processor, tuning);
//                _cpsComponent->setDismissCompletionBlock ([&]() {dismissCPSRootComponent();});
//                addAndMakeVisible (*_cpsComponent);
//                _cpsComponent->updateAppTuning();
//                resized();
//                return;
//            }
//            else
//            {
//                // component must have tuning set
//                assert (false);
//            }
//        }
//    }
//}
//
//// dismiss and set to nullptr
//
//void EulerGenusComponent::dismissCPSRootComponent()
//{
//    // lock
//    const ScopedLock sl (_lock);
//
//    //
//    if (_cpsComponent != nullptr)
//    {
//        removeAllChildren();
//        
//        _cpsComponent = nullptr; // important
//        _setEulerGenus (_currentEulerGenus);
//
//        // enable seed slider for top-level euler genus only
//        _seedSliderComponent->setEnabled (true);
//    }
//}
//
//
//#pragma mark - App Tuning
//
//// update app tuning with selected element
//
//void EulerGenusComponent::updateAppTuning()
//{
//    // lock
//    const ScopedLock sl (_lock);
//
//    // if cps component is presented set its tuning
//    if (_cpsComponent != nullptr && _cpsComponent->isVisible())
//    {
//        _cpsComponent->updateAppTuning();
//        return;
//    }
//
//    // otherwise set selected subset
//    for (auto s0 : _subsets0)
//    {
//        if (s0->getIsSelected())
//        {
//            s0->updateAppTuning();
//            return;
//        }
//    }
//}
//
//#pragma mark - App Tuning Title
//
//const string EulerGenusComponent::getAppTuningTitle()
//{
//    return "Euler Genus (deprecated)";
//}
