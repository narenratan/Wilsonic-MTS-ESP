/**
 * @file Persian17NorthIndianComponent.h
 * @brief Declaration of the Persian17NorthIndianComponent class.
 * @author Marcus W. Hobbs
 * @date Created: 19 Mar 2022 7:34:35pm
 * 
 * This file contains the declaration of the Persian17NorthIndianComponent class, which is a subclass of the WilsonicAppTuningComponent class.
 * It adds additional properties and methods specific to the Persian17NorthIndianComponent.
 * 
 * ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "AppTuningModel.h"
#include "BubbleDrawable.h"
#include "DeltaComboBox.h"
#include "WilsonicAppTuningComponent.h"
#include "WilsonicPitchWheelComponent.h"
#include "WilsonicProcessor.h"

/**
 * @brief The Persian17NorthIndianComponent class.
 * 
 * This class represents the Persian 17 North Indian component of the application.
 * It inherits from the WilsonicAppTuningComponent class and implements the ActionListener interface.
 */
class Persian17NorthIndianComponent 
: public WilsonicAppTuningComponent
, private ActionListener
{
public:
    // Lifecycle
    Persian17NorthIndianComponent(WilsonicProcessor&);
    ~Persian17NorthIndianComponent() override;

private:
    // Lifecycle
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Persian17NorthIndianComponent)

public:
    // UI
    void paint(Graphics&) override;
    void resized() override;

    // tuning title
    const string getAppTuningTitle() override;

private:
    void actionListenerCallback(const String&) override;

    // Tuning Preset
    BubbleDrawable _scaleBubble; ///< The scale bubble drawable.
    unique_ptr<DeltaComboBox> _scaleComboBox; ///< The scale combo box.

    // private methods
    void _tuningChangedUpdateUI();

    // private members
    unique_ptr<WilsonicPitchWheelComponent> _pitchWheelComponent; ///< The pitch wheel component.
    Rectangle<int> _paintBounds; ///< The paint bounds. Resize calculates this, paint draws in it.
};
