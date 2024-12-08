/*
  ==============================================================================

    DeltaSlider.cpp
    Created: 12 Sep 2021 3:17:18pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "DeltaSlider.h"
#include "AppExperiments.h"
#include "WilsonicProcessor.h"

#pragma mark - lifecycle

DeltaSlider::DeltaSlider (WilsonicProcessor& processor)
: WilsonicComponentBase (processor)
{
    addAndMakeVisible (_slider);
    _slider.setRange (_minValue, _maxValue, 1);
    _currentValue = _midValue;
    _slider.setValue (_currentValue, NotificationType::dontSendNotification);
    _slider.setIncDecButtonsMode (Slider::incDecButtonsDraggable_Vertical);
    _slider.onValueChange = [this] ()
    {
        if (isShowing())
        {
            auto value = _slider.getValue();

            if (value > this->_currentValue)
            {
                // increment
                if (onValueIncremented != nullptr)
                {
                    onValueIncremented();
                    _reset();
                }
            }
            else if (value <= this->_currentValue)
            {
                // decrement
                if (onValueDecremented != nullptr)
                {
                    onValueDecremented();
                    _reset();
                }
            }
        }
    };
}

DeltaSlider::~DeltaSlider()
{
    
}

#pragma mark - drawing

void DeltaSlider::paint (Graphics& g)
{
    g.fillAll (_processor.getAppSkin().getBgColor());

    if (AppExperiments::showDebugBoundingBox)
    {
        // DEBUG
        g.setColour (Colours::green);
        g.drawRect (getLocalBounds(), 2);

        // counter
        g.drawText (String (_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }
}

void DeltaSlider::resized()
{
    _slider.setBounds (getLocalBounds());
}

#pragma mark - private methods

void DeltaSlider::_reset()
{
    _slider.setValue (_currentValue, NotificationType::dontSendNotification);
    _currentValue = _midValue;
}
