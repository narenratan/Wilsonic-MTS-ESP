/**
 * @file WilsonicEditor.h
 * @brief This file contains the WilsonicEditor class.
 *
 * The WilsonicEditor class is responsible for managing the user interface of the plugin.
 * It inherits from the AudioProcessorEditor and DesignsProtocol classes.
 * It provides methods for drawing the interface, resizing it, and showing different tunings.
 * It also provides a method for showing a synth and a bubble message.
 * The class contains a reference to the WilsonicProcessor, an instance of the AppRootComponent,
 * a TooltipWindow, and a unique pointer to a BubbleMessageComponent.
 */

#pragma once

#include <JuceHeader.h>
#include "AppRootComponent.h"
#include "AppTuningModel.h"
#include "BubbleDrawable.h"
#include "DesignsProtocol.h"

// forward
class WilsonicProcessor;

/**
 * @class WilsonicEditor
 * @brief This class manages the user interface of the plugin.
 */
class WilsonicEditor
: public AudioProcessorEditor
, public DesignsProtocol
{
public:
    /**
     * @brief Constructor for the WilsonicEditor class.
     * @param WilsonicProcessor& - A reference to the WilsonicProcessor.
     */
    WilsonicEditor(WilsonicProcessor&);
    
    /**
     * @brief Destructor for the WilsonicEditor class.
     */
    ~WilsonicEditor() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WilsonicEditor)

public:
    /**
     * @brief Method for drawing the interface.
     * @param Graphics& - A reference to the Graphics object.
     */
    void paint(Graphics&) override;
    
    /**
     * @brief Method for resizing the interface.
     */
    void resized() override;

    // ADD NEW SCALE DESIGN HERE

    // DesignsProtocol
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

    /**
     * @brief Method for showing a synth.
     */
    void showSynth();

    /**
     * @brief Method for showing a bubble message.
     * @param BubbleDrawable& - A reference to the BubbleDrawable object.
     */
    static void showBubbleMessage(BubbleDrawable& targetComponent);
    void showAudioDeviceSettings();

private:
    WilsonicProcessor& _processor;
    AppRootComponent _appRootComponent; // OWNER
    TooltipWindow tooltipWindow;
    static unique_ptr<BubbleMessageComponent> __bubbleMessageComponent;
    
};

