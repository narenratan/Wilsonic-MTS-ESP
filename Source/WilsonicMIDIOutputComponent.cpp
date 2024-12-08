/*
  =============================================================================

    WilsonicMIDIOutputComponent.cp
    Created: 26 Aug 2023 4:55:46p
    Author:  Marcus W. Hobb

  =============================================================================
*/
//
//#include "WilsonicMIDIOutputComponent.h"
//#include "MIDIOutputRowComponent.h"
//
//WilsonicMIDIOutputComponent::WilsonicMIDIOutputComponent()
//{
//    addAndMakeVisible(_listBox);
//    _listBox.setModel(this);
//    refreshDevices();
//}
//
//void WilsonicMIDIOutputComponent::refreshDevices()
//{
//    _devices = MidiOutput::getAvailableDevices();
//    _listBox.updateContent();
//}
//
//int WilsonicMIDIOutputComponent::getNumRows()
//{
//    return static_cast<int>(_devices.size());
//}
//
//void WilsonicMIDIOutputComponent::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
//{
//    // This is needed only if you want to do custom painting of the listbox.
//}
//
//juce::Component* WilsonicMIDIOutputComponent::refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
//{
//    if (rowNumber < static_cast<int>(_devices.size()))
//    {
//        if (existingComponentToUpdate == nullptr)
//            existingComponentToUpdate = new MIDIOutputRowComponent(_devices[rowNumber]);
//
//        return existingComponentToUpdate;
//    }
//
//    return nullptr;
//}
//
//void WilsonicMIDIOutputComponent::resized()
//{
//    _listBox.setBounds(getLocalBounds());
//}
