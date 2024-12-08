/*
  ==============================================================================

    WilsonicRootComponent.h
    Created: 11 Jul 2021 1:00:12pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

/**
 * @file WilsonicRootComponent.h
 * @brief This file contains the declaration of the WilsonicRootComponent class.
 */

#pragma once

// ADD NEW SCALE DESIGN HERE

#include <JuceHeader.h>
#include "BrunRootComponent.h"
#include "CoPrimeComponent.h"
#include "CPSRootComponentV2.h"
#include "DeltaComboBox.h"
#include "DesignsProtocol.h"
#include "DiamondsComponent.h"
#include "EqualTemperamentComponent.h"
#include "EulerGenusComponentV2.h"
#include "FavoritesComponent.h"
#include "MorphComponent.h"
#include "PartchComponent.h"
#include "Persian17NorthIndianComponent.h"
#include "RecurrenceRelationComponent.h"
#include "ScalaComponent.h"
#include "SynthComponent.h"
#include "TmpPresetComponent.h"
#include "TritriadicComponent.h"
#include "WilsonicAppTuningComponent.h"
#include "WilsonicArrowBaseComponent.h"
#include "WilsonicComponentBase.h"
#include "WilsonicKeyboardContainerComponent.h"
#include "WilsonicMenuComponent.h"
#include "WilsonicProcessor.h"

/**
 * @class WilsonicRootComponent
 * @brief This class is a child of AppRootComponent and owns the menus, and the container for all tunings UI.
 *
 * The architecture of the app is a wrapped plugin; the entire (automatable) state is
 * represented/persisted as the AudioProcessorValueTreeState owned by WilsonicProcessor.
 * In fact, the plugin should function as if there is no UI and every parameter is automatable by the host.
 * The UI reflects this state, and modifies this state, but is in no way a store of app state.
 * This is pretty different from iOS/Mac apps where lines blur and UI can own some persistent state.
 * This explains the product experience of so many plugins where they have primitive UI and limit complex navigation by crunching features onto as few pages as possible.
 */
class WilsonicRootComponent
: public WilsonicComponentBase
, public DesignsProtocol
, private ActionListener 
{
public:
    WilsonicRootComponent(WilsonicProcessor&);
    ~WilsonicRootComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WilsonicRootComponent)

public:
    // ADD NEW SCALE DESIGN HERE

    void paint(Graphics&) override;
    void resized() override;
    void showBrunTuning() override;
    void showCoPrimeTuning() override;
    void showCPSTuning() override;
    void showDiamondsTuning() override;
    void showEqualTemperamentTuning() override;
    void showEulerGenusV2Tuning() override;
    void showMorphTuning() override;
    void showPartchTuning() override;
    void showPersian17NorthIndianTuning() override;
    void showPresetsTuning() override;
    void showRecurrenceRelationTuning() override;
    void showScalaTuning() override;
    void showTritriadicTuning() override;
    void showSynth();

private:
    void _showFavorites();
    void _favoritesFocusHelper();
    void _dismissFavorites();
    void _toggleFavorites();

private:
    // ADD NEW SCALE DESIGN HERE

    WilsonicMenuComponent _rootMenu; // OWNER
    shared_ptr<WilsonicAppTuningComponent> _currentTuningComponent;
    shared_ptr<BrunRootComponent> _brunComponent;
    shared_ptr<TmpPresetComponent> _tmpPresetComponent;
    shared_ptr<SynthComponent> _synthComponent;
    shared_ptr<CoPrimeComponent> _coPrimeComponent;
    shared_ptr<CPSRootComponentV2> _cpsComponentV2;
    shared_ptr<DiamondsComponent> _diamondsComponent;    
    shared_ptr<EulerGenusComponentV2> _eulerGenusComponentV2;
    shared_ptr<MorphComponent> _morphComponent;
    shared_ptr<PartchComponent> _partchComponent;
    shared_ptr<Persian17NorthIndianComponent> _persian17NorthIndianComponent;
    shared_ptr<RecurrenceRelationComponent> _recurrenceRelationComponent;
    shared_ptr<EqualTemperamentComponent> _equalTemperamentComponent;
    shared_ptr<ScalaComponent> _scalaComponent;
    shared_ptr<TritriadicComponent> _tritriadicComponent;
    shared_ptr<FavoritesComponent> _favoritesComponent;

    void _commonShow();
    void actionListenerCallback(const String& message) override;
};
