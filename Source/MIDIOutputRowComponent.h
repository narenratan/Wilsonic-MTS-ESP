/*
 ==============================================================================

 MIDIOutputRowComponent.h
 Created: 26 Aug 2023 4:51:42pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>

class MIDIOutputRowComponent 
: public Component
{
public:
    MIDIOutputRowComponent(const MidiDeviceInfo& deviceInfo);
    ~MIDIOutputRowComponent() override;

    void resized() override;
    void paint(Graphics& g) override;
    
private:
    MidiDeviceInfo _deviceInfo;
    ToggleButton _checkBox;
};
