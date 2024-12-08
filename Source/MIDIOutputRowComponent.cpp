/*
 =============================================================================

 MIDIOutputRowComponent.cp
 Created: 26 Aug 2023 4:51:42p
 Author:  Marcus W. Hobb

 =============================================================================
 */

#include "MIDIOutputRowComponent.h"

MIDIOutputRowComponent::MIDIOutputRowComponent(const MidiDeviceInfo& deviceInfo)
: _deviceInfo(deviceInfo)
{
    addAndMakeVisible(_checkBox);
    _checkBox.onClick = [] { /* handle selection change */ };
}

void MIDIOutputRowComponent::resized()
{
    _checkBox.setBounds(getLocalBounds());
}

void MIDIOutputRowComponent::paint(juce::Graphics& g)
{
    g.drawText(_deviceInfo.name, getLocalBounds(), Justification::centredLeft);
}
