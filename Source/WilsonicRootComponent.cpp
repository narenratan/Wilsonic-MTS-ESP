/*
  ==============================================================================

    WilsonicRootComponent.cpp
    Created: 11 Jul 2021 1:00:12pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

/**
 * @file WilsonicRootComponent.cpp
 * @brief This file contains the implementation of the WilsonicRootComponent class.
 */

#include <JuceHeader.h>
#include "WilsonicRootComponent.h"
#include "AppVersion.h"

/**
 * @section lifecycle
 */

/**
 * @brief Constructor for the WilsonicRootComponent class.
 * @param processor The WilsonicProcessor object.
 */
WilsonicRootComponent::WilsonicRootComponent(WilsonicProcessor& processor)
: WilsonicComponentBase(processor)
, _rootMenu(_processor)
{
    // root menu (header)
    // Add the root menu to the visible components and set this object as an action listener.
    addAndMakeVisible(_rootMenu);
    _rootMenu.addActionListener(this);

    // Set the size of the component to the window size defined in the app skin.
    setSize(_processor.getAppSkin().getWindowWidth(), _processor.getAppSkin().getWindowHeight());
}

/**
 * @brief Destructor for the WilsonicRootComponent class.
 */
WilsonicRootComponent::~WilsonicRootComponent()
{
    // Remove this object as an action listener from the root menu.
    _rootMenu.removeActionListener(this);
    // If the favorites component exists, remove this object as an action listener.
    if(_favoritesComponent != nullptr)
    {
        _favoritesComponent->removeActionListener(this);
    }
}

/**
 * @brief Method to paint the component.
 * @param g The Graphics object to draw on.
 */
void WilsonicRootComponent::paint(Graphics& g)
{
    // Fill the entire component with the background color defined in the app skin.
    g.fillAll(_processor.getAppSkin().getBgColor());

    // If the debug bounding box is enabled, draw a red rectangle around the component and a counter at the top right.
    if(AppExperiments::showDebugBoundingBox)
    {
        // DEBUG
        g.setColour(Colours::red);
        g.drawRect(getLocalBounds(), 2);

        // counter
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }
}

/**
 * @brief Method to resize the component.
 */
void WilsonicRootComponent::resized()
{
    // Define the minimum hitpoint size and margin from the app skin.
    auto const minHitpointSize = WilsonicAppSkin::minHitPointSize;
    auto const margin = WilsonicAppSkin::tuningComponentInteriorMargin;
    // Get the local bounds of the component.
    auto area = getLocalBounds();

    // Reserve the menu bar and current component
    // Set the bounds of the root menu to the top of the component.
    _rootMenu.setBounds(area.removeFromTop(static_cast<int>(minHitpointSize + 2 * margin)));
    // If the current tuning component exists, set its bounds to the remaining area.
    if(_currentTuningComponent != nullptr) // intentional
    {
        auto fc = dynamic_cast<Component*> (_favoritesComponent.get());
        // If the favorites component is a child of this component, set its bounds to the top half of the remaining area.
        if(isParentOf(fc))
        {
            auto const proportion = (1.f-0.618f); // 0.5f;
            auto favorites_area = area.removeFromTop(static_cast<int>(proportion * area.getHeight()));
            _favoritesComponent->setBounds(favorites_area);
        }
        // Set the bounds of the current tuning component to the remaining area.
        _currentTuningComponent->setBounds(area);
    }
}

/**
 * @brief Common method to show a tuning component.
 */
void WilsonicRootComponent::_commonShow()
{
    // Restore the view hierarchy after destroying it
    // Remove all child components.
    removeAllChildren();
    // Add the root menu and favorites component (if it exists) to the visible components.
    addAndMakeVisible(_rootMenu);
    if(_favoritesComponent != nullptr)
    {
        addAndMakeVisible (*_favoritesComponent);
    }
}

/**
 * @section DesignsProtocol
 */

// ADD NEW SCALE DESIGN HERE

/**
 * @brief Method to show the Brun tuning component.
 */
void WilsonicRootComponent::showBrunTuning()
{
    // Call the common show method.
    _commonShow();

    // If the Brun component does not exist, create it.
    if(_brunComponent == nullptr)
    {
        _brunComponent = make_shared<BrunRootComponent> (_processor);
    }
    // Set the current tuning component to the Brun component.
    _currentTuningComponent = _brunComponent;
    // Add the current tuning component to the visible components.
    addAndMakeVisible (*_currentTuningComponent);
    // Resize the component.
    resized();
    // Call the favorites focus helper method.
    _favoritesFocusHelper();
}

/**
 * @brief Method to show the CoPrime tuning component.
 */
void WilsonicRootComponent::showCoPrimeTuning()
{
    // Call the common show method.
    _commonShow();

    // If the CoPrime component does not exist, create it.
    if(_coPrimeComponent == nullptr)
    {
        _coPrimeComponent = make_shared<CoPrimeComponent> (_processor);
    }
    // Set the current tuning component to the CoPrime component.
    _currentTuningComponent = _coPrimeComponent;
    // Add the current tuning component to the visible components.
    addAndMakeVisible (*_coPrimeComponent);
    // Resize the component.
    resized();
    // Call the favorites focus helper method.
    _favoritesFocusHelper();
}

/**
 * @brief Method to show the Diamonds tuning component.
 */
void WilsonicRootComponent::showDiamondsTuning()
{
    // Call the common show method.
    _commonShow();

    // If the Diamonds component does not exist, create it.
    if(_diamondsComponent == nullptr)
    {
        _diamondsComponent = make_shared<DiamondsComponent> (_processor);
    }
    // Set the current tuning component to the Diamonds component.
    _currentTuningComponent = _diamondsComponent;
    // Add the current tuning component to the visible components.
    addAndMakeVisible (*_currentTuningComponent);
    // Resize the component.
    resized();
    // Call the favorites focus helper method.
    _favoritesFocusHelper();
}

/**
 * @brief Method to show the Equal Temperament tuning component.
 */
void WilsonicRootComponent::showEqualTemperamentTuning()
{
    // Call the common show method.
    _commonShow();

    // If the Equal Temperament component does not exist, create it.
    if(_equalTemperamentComponent == nullptr)
    {
        _equalTemperamentComponent = make_shared<EqualTemperamentComponent> (_processor);
    }
    // Set the current tuning component to the Equal Temperament component.
    _currentTuningComponent = _equalTemperamentComponent;
    // Add the current tuning component to the visible components.
    addAndMakeVisible (*_currentTuningComponent);
    // Resize the component.
    resized();
    // Call the favorites focus helper method.
    _favoritesFocusHelper();
}

/**
 * @brief Method to show the Euler Genus V2 tuning component.
 */
void WilsonicRootComponent::showEulerGenusV2Tuning()
{
    // Call the common show method.
    _commonShow();

    // If the Euler Genus V2 component does not exist, create it.
    if(_eulerGenusComponentV2 == nullptr)
    {
        _eulerGenusComponentV2 = make_shared<EulerGenusComponentV2> (_processor);
    }
    // Set the current tuning component to the Euler Genus V2 component.
    _currentTuningComponent = _eulerGenusComponentV2;
    // Add the current tuning component to the visible components.
    addAndMakeVisible (*_currentTuningComponent);
    // Resize the component.
    resized();
    // Call the favorites focus helper method.
    _favoritesFocusHelper();
}

/**
 * @brief Method to show the Morph tuning component.
 */
void WilsonicRootComponent::showMorphTuning()
{
    // Call the common show method.
    _commonShow();

    // If the Euler Genus V2 component does not exist, create it.
    if(_morphComponent == nullptr)
    {
        _morphComponent = make_shared<MorphComponent>(_processor);
    }
    // Set the current tuning component to the Morph component.
    _currentTuningComponent = _morphComponent;
    // Add the current tuning component to the visible components.
    addAndMakeVisible(*_currentTuningComponent);
    // Resize the component.
    resized();
    // Call the favorites focus helper method.
    _favoritesFocusHelper();
}

/**
 * @brief Method to show the CPS tuning component.
 */
void WilsonicRootComponent::showCPSTuning()
{
    // Call the common show method.
    _commonShow();

    // If the CPS V2 component does not exist, create it.
    if(_cpsComponentV2 == nullptr)
    {
        _cpsComponentV2 = make_shared<CPSRootComponentV2> (_processor);
    }
    // Set the current tuning component to the CPS V2 component.
    _currentTuningComponent = _cpsComponentV2;
    // Add the current tuning component to the visible components.
    addAndMakeVisible (*_currentTuningComponent);
    // Resize the component.
    resized();
    // Call the favorites focus helper method.
    _favoritesFocusHelper();
}

void WilsonicRootComponent::showPartchTuning() {
    _commonShow();
    if(_partchComponent == nullptr) {
        _partchComponent = make_shared<PartchComponent>(_processor);
    }
    _currentTuningComponent = _partchComponent;
    addAndMakeVisible (*_currentTuningComponent);
    resized();
    _favoritesFocusHelper();
}

/**
 * @brief Method to show the Persian 17 North Indian tuning component.
 */
void WilsonicRootComponent::showPersian17NorthIndianTuning()
{
    // Call the common show method.
    _commonShow();

    // If the Persian 17 North Indian component does not exist, create it.
    if(_persian17NorthIndianComponent == nullptr)
    {
        _persian17NorthIndianComponent = make_shared<Persian17NorthIndianComponent> (_processor);
    }
    // Set the current tuning component to the Persian 17 North Indian component.
    _currentTuningComponent = _persian17NorthIndianComponent;
    // Add the current tuning component to the visible components.
    addAndMakeVisible (*_currentTuningComponent);
    // Resize the component.
    resized();
    // Call the favorites focus helper method.
    _favoritesFocusHelper();
}

/**
 * @brief Method to show the Presets tuning component.
 */
void WilsonicRootComponent::showPresetsTuning()
{
    // Call the common show method.
    _commonShow();
    
    // If the temporary preset component does not exist, create it.
    if(_tmpPresetComponent == nullptr)
    {
        _tmpPresetComponent = make_shared<TmpPresetComponent> (_processor);
    }
    // Set the current tuning component to the temporary preset component.
    _currentTuningComponent = _tmpPresetComponent;
    // Add the current tuning component to the visible components.
    addAndMakeVisible (*_currentTuningComponent);
    // Resize the component.
    resized();
    // Call the favorites focus helper method.
    _favoritesFocusHelper();
}

/**
 * @brief Method to show the Recurrence Relation tuning component.
 */
void WilsonicRootComponent::showRecurrenceRelationTuning()
{
    // Call the common show method.
    _commonShow();

    // If the Recurrence Relation component does not exist, create it.
    if(_recurrenceRelationComponent == nullptr)
    {
        _recurrenceRelationComponent = make_shared<RecurrenceRelationComponent> (_processor);
    }
    // Set the current tuning component to the Recurrence Relation component.
    _currentTuningComponent = _recurrenceRelationComponent;
    // Add the current tuning component to the visible components.
    addAndMakeVisible (*_currentTuningComponent);
    // Resize the component.
    resized();
    // Call the favorites focus helper method.
    _favoritesFocusHelper();
}

/**
 * @brief Method to show the Scala tuning component.
 */
void WilsonicRootComponent::showScalaTuning()
{
    // Call the common show method.
    _commonShow();

    // If the Scala component does not exist, create it.
    if(_scalaComponent == nullptr)
    {
        _scalaComponent = make_shared<ScalaComponent> (_processor);
    }
    // Set the current tuning component to the Scala component.
    _currentTuningComponent = _scalaComponent;
    // Add the current tuning component to the visible components.
    addAndMakeVisible (*_currentTuningComponent);
    // Resize the component.
    resized();
    // Call the favorites focus helper method.
    _favoritesFocusHelper();
}

/**
 * @brief Method to show the Tritriadic tuning component.
 */
void WilsonicRootComponent::showTritriadicTuning()
{
    // Call the common show method.
    _commonShow();
    // If the Tritriadic component does not exist, create it.
    if(_tritriadicComponent == nullptr)
    {
        _tritriadicComponent = make_shared<TritriadicComponent> (_processor);
    }
    // Set the current tuning component to the Tritriadic component.
    _currentTuningComponent = _tritriadicComponent;
    // Add the current tuning component to the visible components.
    addAndMakeVisible (*_currentTuningComponent);
    // Resize the component.
    resized();
    // Call the favorites focus helper method.
    _favoritesFocusHelper();
}

/**
 * @section Pages
 */

/**
 * @brief Method to show the Synth component.
 */
void WilsonicRootComponent::showSynth()
{
    // Call the common show method.
    _commonShow();
    // If the Synth component does not exist, create it.
    if(_synthComponent == nullptr)
    {
        _synthComponent = make_shared<SynthComponent> (_processor);
    }
    // Set the current tuning component to the Synth component.
    _currentTuningComponent = _synthComponent;
    // Add the current tuning component to the visible components.
    addAndMakeVisible (*_currentTuningComponent);
    // Resize the component.
    resized();
}

/**
 * @brief Favorites is different from tuning and synth components.
 */

/**
 * @brief Method to show the Favorites component.
 */
void WilsonicRootComponent::_showFavorites()
{
    // If the Favorites component does not exist, create it and set this object as an action listener.
    if(_favoritesComponent == nullptr)
    {
        _favoritesComponent = make_shared<FavoritesComponent> (_processor);
        _favoritesComponent->addActionListener(this);
    }
    // Add the Favorites component to the visible components.
    addAndMakeVisible (*_favoritesComponent);
#if JUCE_IOS || JUCE_ANDROID
    // NOP
#else
    // If not on iOS or Android, grab keyboard focus for the Favorites component.
    _favoritesComponent->grabKeyboardFocus();
#endif

    // Resize the component.
    resized();
}

/**
 * @brief Method to help with focusing on the Favorites component.
 */
void WilsonicRootComponent::_favoritesFocusHelper()
{
    // If the Favorites component does not exist, return.
    if(_favoritesComponent == nullptr)
    {
        return;
    }
    else
    {
        auto fc = dynamic_cast<Component*> (_favoritesComponent.get());
        // If the Favorites component is a child of this component, grab keyboard focus for it (unless on iOS or Android).
        if(isParentOf(fc))
        {
#if JUCE_IOS || JUCE_ANDROID
            // NOP
#else
            _favoritesComponent->grabKeyboardFocus();
#endif
        }
    }
}

/**
 * @brief Method to dismiss the Favorites component.
 */
void WilsonicRootComponent::_dismissFavorites()
{
    // If the Favorites component does not exist, return.
    if(_favoritesComponent == nullptr)
    {
        return;
    }
    else
    {
        auto fc = dynamic_cast<Component*> (_favoritesComponent.get());
        // If the Favorites component is a child of this component, remove it, resize the component, and remove this object as an action listener.
        if(isParentOf(fc))
        {
            removeChildComponent(fc);
            resized();
            _favoritesComponent->removeActionListener(this);
            _favoritesComponent = nullptr;
        }
    }
}

/**
 * @brief Method to toggle the visibility of the Favorites component.
 */
void WilsonicRootComponent::_toggleFavorites()
{
    // If the Favorites component does not exist, show it.
    if(_favoritesComponent == nullptr)
    {
        _showFavorites();
    }
    else
    {
        auto fc = dynamic_cast<Component*> (_favoritesComponent.get());
        // If the Favorites component is a child of this component, dismiss it. Otherwise, show it.
        if(isParentOf(fc))
        {
            _dismissFavorites();
        }
        else
        {
            _showFavorites();
        }
    }
}

/**
 * @section Action Listener
 */

/**
 * @brief Method to handle action listener callbacks.
 * @param message The message from the action source.
 */
void WilsonicRootComponent::actionListenerCallback(const String& message)
{
    // If the message is to toggle the Favorites component, toggle it.
    if(message == WilsonicMenuComponent::getToggleFavoritesMessage())
    {
        _toggleFavorites();
    }
    else
    {
        // If the message is not handled, print a debug message.
        DBG ("WilsonicRoomComponent::actionListenerCallback: unhandled message: " + message);
    }
}

