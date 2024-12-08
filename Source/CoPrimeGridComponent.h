/*
  ==============================================================================

    CoPrimeGridComponent.h
    Created: 27 Apr 2023 9:24:42pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"
#include "WilsonicComponentBase.h"
#include "WilsonicProcessor.h"

// this component only draws the processor's coprime tuning's paint method, which always exists.
// it draws debug bounding box and debug frame counter
// layout is handled by the parent.

class CoPrimeGridComponent
: public WilsonicComponentBase
, private MidiKeyboardStateListener
, private ActionListener {
public:
    // lifecycle
    CoPrimeGridComponent(WilsonicProcessor& processor);
    ~CoPrimeGridComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CoPrimeGridComponent)

public:
    // drawing
    void paint(Graphics&) override;
    void resized() override;
    
private:
    // private member variables
    int _midiChannel = 1;
    bool _shouldCheckState = false;
    Array<int> _mouseOverNotes;
    Array<int> _mouseDownNotes;

    // private methods
    void mouseMove(const MouseEvent&) override;
    void mouseDrag(const MouseEvent&) override;
    void mouseDown(const MouseEvent&) override;
    void mouseUp(const MouseEvent&) override;
    void mouseEnter(const MouseEvent&) override;
    void mouseExit(const MouseEvent& event) override;
    bool mouseDraggedToKey(int midiNoteNumber, const MouseEvent& e);
    bool mouseDownOnKey(int midiNoteNumber, const MouseEvent& e);
    void mouseUpOnKey(int midiNoteNumber,const MouseEvent& e);
    void mouseWheelMove(const MouseEvent&, const MouseWheelDetails&) override;
    void handleNoteOn(MidiKeyboardState* source,  int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override;
    void _resetAnyKeysInUse();
    void _updateNoteUnderMouse(Point<float>, bool isDown, int fingerNum);
    void _updateNoteUnderMouse(const MouseEvent&, bool isDown);
    void _repaintNote(int midiNoteNumber);
    
    void actionListenerCallback(const String& message) override;
};
