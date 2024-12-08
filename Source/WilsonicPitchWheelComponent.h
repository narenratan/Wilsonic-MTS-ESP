/*
  ==============================================================================

    WilsonicPitchWheelComponent.h
    Created: 15 May 2021 4:34:18pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

/**
 * @file WilsonicPitchWheelComponent.h
 * @brief Contains the declaration of the WilsonicPitchWheelComponent class.
 */

#pragma once

#include <JuceHeader.h>
#include "AppTuningModel.h"
#include "TuningImp.h"
#include "Tuning_Include.h"
#include "WilsonicAppSkin.h"
#include "WilsonicComponentBase.h"
#include "WilsonicProcessor.h"

/**
 * @class WilsonicPitchWheelComponent
 * @brief A component that represents the pitch wheel of the Wilsonic application.
 * @details This class inherits from WilsonicComponentBase and Timer. It is responsible for managing and displaying the pitch wheel.
 */
class WilsonicPitchWheelComponent
: public WilsonicComponentBase
, private Timer
{
public:
    /**
     * @brief Constructor for the WilsonicPitchWheelComponent class.
     * @param WilsonicProcessor& - Reference to the WilsonicProcessor object.
     * @param bool - Boolean value to start the timer.
     */
    WilsonicPitchWheelComponent (WilsonicProcessor&, bool start_timer);
    
    /**
     * @brief Destructor for the WilsonicPitchWheelComponent class.
     */
    ~WilsonicPitchWheelComponent() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WilsonicPitchWheelComponent)

public:
    /**
     * @brief Paints the component.
     * @param Graphics& - Reference to the Graphics object.
     */
    void paint(Graphics&) override;
    
    /**
     * @brief Resizes the component.
     */
    void resized() override;

    /**
     * @brief Sets the tuning.
     * @param shared_ptr<Tuning> - Shared pointer to the Tuning object.
     */
    void setTuning(shared_ptr<Tuning>);
    
    /**
     * @brief Sets the update based on AppTuningSynthNotes.
     * @param bool - Boolean value to set the update.
     */
    void setUpdateBasedOnAppTuningSynthNotes(bool); // cpu intensive
    
    /**
     * @brief Sets the custom font scale.
     * @param float - Float value to set the scale.
     */
    void setCustomFontScale (float scale01); // 1 = default logic
    
    /**
     * @brief Sets the draw text.
     * @param bool - Boolean value to set the draw text.
     */
    void setDrawText(bool draw_text);

private:
    /**
     * @brief Private member variables.
     */
    shared_ptr<Tuning> _tuning {nullptr}; ///< Shared pointer to the Tuning object.
    bool _updateBasedOnAppTuningSynthNotes {true}; ///< Boolean value to set the update based on AppTuningSynthNotes.
    bool _drawText {true}; ///< Boolean value to set the draw text.
    float _customFontScale {2.2248f}; ///< Float value to set the custom font scale.

    /**
     * @brief Private methods.
     */
    void _paint04(Graphics&); ///< Paint method 04.
    
    /**
     * @brief Timer callback method.
     */
    void timerCallback() override;
    
    /**
     * @brief Timer helper method.
     */
    void _timerHelper();
};
