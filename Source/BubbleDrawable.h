/*
  ==============================================================================

    BubbleDrawable.h
    Created: 18 May 2022 12:15:11pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WilsonicComponentBase.h"
#include "Tuning_Include.h"

using BubblePlacement = BubbleComponent::BubblePlacement;

class BubbleDrawable 
: public Component
{

public:

    BubbleDrawable (const BubblePlacement placement = BubblePlacement::left, const String& singleCharacter = "", const String& bubbleMessage = "");

    BubbleDrawable (const BubblePlacement placement = BubblePlacement::left, shared_ptr<Image> icon = nullptr, const String& bubbleMessage = "");

    ~BubbleDrawable() override;

    void paint (Graphics&) override;
    
    void resized() override;

    const String& getBubbleMessage();

    void setBubbleMessage (String newMessage);

    void setIcon (shared_ptr<Image> icon);

    const BubblePlacement getBubblePlacement();

    void mouseEnter (const MouseEvent&) override;

private:

    const BubblePlacement _placement;

    const String _singleCharacter;

    String _bubbleMessage;

    shared_ptr<Image> _icon = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BubbleDrawable)
};
