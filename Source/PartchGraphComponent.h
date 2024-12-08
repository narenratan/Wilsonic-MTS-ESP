/*
  ==============================================================================

    PartchGraphComponent.h
    Created: 5 Jun 2024 8:47:51pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Partch.h"
#include "WilsonicComponentBase.h"
#include "WilsonicProcessor.h"

class PartchGraphComponent
: public WilsonicComponentBase
, private MidiKeyboardStateListener
, private ActionListener {
    // lifecycle
public:
    PartchGraphComponent(WilsonicProcessor&);
    ~PartchGraphComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PartchGraphComponent)

public:
    // drawing
    void paint(Graphics&) override;
    void resized() override;

private:
    // private members
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
