/**
 * @file TuningRendererComponent.h
 * @author Marcus W. Hobbs
 * @date 3 Feb 2022
 * @brief This file contains the TuningRendererComponent class.
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
 * @class TuningRendererComponent
 * @brief This class is responsible for rendering the tuning.
 * @details It extends the WilsonicComponentBase and implements a Timer.
 */
class TuningRendererComponent
: public WilsonicComponentBase
, private Timer
{
    // lifecycle
public:
    /**
     * @brief Constructor for TuningRendererComponent.
     * @param WilsonicProcessor& - Reference to the WilsonicProcessor.
     * @param bool - Whether to start the timer.
     */
    TuningRendererComponent(WilsonicProcessor&, bool start_timer);
    
    /**
     * @brief Destructor for TuningRendererComponent.
     */
    ~TuningRendererComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TuningRendererComponent)

public:
    // drawing
    void paint(Graphics&) override;
    void resized() override;

    // public methods
    /**
     * @brief Set the tuning.
     * @param shared_ptr<Tuning> - The tuning to set.
     */
    void setTuning(shared_ptr<Tuning>);
    
    /**
     * @brief Set whether to update based on AppTuningSynthNotes.
     * @param bool - Whether to update.
     * @details This is CPU intensive.
     */
    void setUpdateBasedOnAppTuningSynthNotes(bool); // cpu intensive
    
    /**
     * @brief Set the custom font scale.
     * @param float - The scale to set.
     * @details 1 = default logic.
     */
    void setCustomFontScale(float scale01); // 1 = default logic

private:
    // private members
    shared_ptr<Tuning> _tuning = nullptr;
    bool _updateBasedOnAppTuningSynthNotes = true;
    float _customFontScale = 2.2248f;

    // private methods
    void _paint04(Graphics&);
    void timerCallback() override;
    void _timerHelper();
};
