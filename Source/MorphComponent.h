/*
  ==============================================================================

    MorphComponent.h
    Created: 17 Dec 2023 1:42:18pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppTuningModel.h"
#include "DeltaComboBox.h"
#include "MorphComponentMessageBus.h"
#include "Tuning_Include.h"
#include "WilsonicAppTuningComponent.h"
#include "WilsonicProcessor.h"

class MorphFavoritesAComponent;
class MorphFavoritesBComponent;
class MorphTuningComponent;

class MorphComponent
: public WilsonicAppTuningComponent
, private ActionListener
, private Button::Listener
, private MorphComponentMessageListener
{
public:
    MorphComponent(WilsonicProcessor&);
    ~MorphComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MorphComponent)

public:
    // drawing
    void paint(Graphics&) override;
    void resized() override;
    
    // MessageListener
    void handleMessage(const String& message) override;

    //
    const string getAppTuningTitle() override;
    
private:
    // ActionListener callback
    /**
     * @brief ActionListener callback method for the Persian17NorthIndianComponent class.
     * @param const String& The action string.
     */
    void actionListenerCallback(const String&) override;

    void buttonClicked(Button*) override;

    /**
     * @brief Update UI when tuning changes.
     */
    void _tuningChangedUpdateUI();

    // private members
    unique_ptr<MorphFavoritesAComponent> _tableA;
    unique_ptr<TextButton> _swapButton;
    unique_ptr<MorphFavoritesBComponent> _tableB;
    unique_ptr<MorphTuningComponent> _tuningComponent;
    Slider _interpolationValueSlider {Slider::SliderStyle::LinearHorizontal, Slider::TextEntryBoxPosition::TextBoxLeft};
    unique_ptr<DeltaComboBox> _interpolationTypeComboBox;
    Label _statusLabel;
};
