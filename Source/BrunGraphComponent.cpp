/*
  ==============================================================================

    BrunGraphComponent.cpp
    Created: 7 Mar 2021 5:43:39pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AppExperiments.h"
#include "Brun2Model.h"
#include "BrunGraphComponent.h"
#include "BrunMicrotone.h"

#pragma mark - lifecycle

BrunGraphComponent::BrunGraphComponent(WilsonicProcessor& processor) : WilsonicComponentBase(processor) {
    _mouseOverNotes.insertMultiple(0, -1, 32);
    _mouseDownNotes.insertMultiple(0, -1, 32);
    _processor.addActionListener(this);

    // parent has a timer that calls repaint
}

BrunGraphComponent::~BrunGraphComponent() {
    _processor.removeActionListener(this);
}

#pragma mark - drawing

void BrunGraphComponent::paint(Graphics& g) {
    _shouldCheckState = false;
    _processor.getBrun2Model()->getTuning()->paint(_processor, g, getLocalBounds()); // paint the tuning
}

void BrunGraphComponent::resized() {
    // don't repaint _brunGraph here...it's repainted on a timer
}

#pragma mark - touch

void BrunGraphComponent::_resetAnyKeysInUse() {
    for (int i = _mouseDownNotes.size(); --i >= 0;) {
        auto noteDown = _mouseDownNotes.getUnchecked(i);
        if (noteDown >= 0) {
            _processor.getKeyboardState()->noteOff(_midiChannel, noteDown, 0.0f);
            _mouseDownNotes.set(i, -1);
        }
        _mouseOverNotes.set(i, -1);
    }
}

void BrunGraphComponent::_updateNoteUnderMouse(const MouseEvent& e, bool isDown) {
    _updateNoteUnderMouse(e.getEventRelativeTo(this).position, isDown, e.source.getIndex());
}

void BrunGraphComponent::_updateNoteUnderMouse(Point<float> pos, bool isDown, int fingerNum) {
    auto const bt = dynamic_cast<Brun*>(_processor.getBrun2Model()->getTuning().get());
    if(bt != nullptr) {
        // do not play notes if we have NPO Override Enabled
        if(bt->getNPOOverrideEnable())
            return;
        
        // do not play notes if we're not showing Gral
        if(bt->getDisplayMode() != Brun::DisplayMode::Gral)
            return;
    }
    
    auto const newNote = _processor.getBrun2Model()->nnForDeviceSpace(pos.toInt());
    auto const oldNote = _mouseOverNotes.getUnchecked(fingerNum);
    auto const oldNoteDown = _mouseDownNotes.getUnchecked(fingerNum);
    auto const eventVelocity = WilsonicProcessorConstants::defaultVelocity;
    if (oldNote != newNote) {
        _repaintNote(oldNote);
        _repaintNote(newNote);
        _mouseOverNotes.set(fingerNum, newNote);
    }

    if (isDown) {
        if (newNote != oldNoteDown) {
            if (oldNoteDown >= 0) {
                _mouseDownNotes.set(fingerNum, -1);
                if (!_mouseDownNotes.contains(oldNoteDown))
                    _processor.getKeyboardState()->noteOff(_midiChannel, oldNoteDown, eventVelocity);
            }
            if (newNote >= 0 && !_mouseDownNotes.contains(newNote)) {
                _processor.getKeyboardState()->noteOn(_midiChannel, newNote, eventVelocity);
                _mouseDownNotes.set(fingerNum, newNote);
            }
        }
    } else if (oldNoteDown >= 0) {
        _mouseDownNotes.set(fingerNum, -1);
        if (!_mouseDownNotes.contains(oldNoteDown))
            _processor.getKeyboardState()->noteOff(_midiChannel, oldNoteDown, eventVelocity);
    }
}

void BrunGraphComponent::mouseDown(const MouseEvent& e) {
    auto const pos = e.position;
    auto const newNote = _processor.getBrun2Model()->nnForDeviceSpace(pos.toInt());
    if (newNote >= 0 && mouseDownOnKey(newNote, e))
        _updateNoteUnderMouse(e, true);
}

void BrunGraphComponent::mouseUp(const MouseEvent& e) {
    _updateNoteUnderMouse(e, false);
    auto const pos = e.position;
    auto const note = _processor.getBrun2Model()->nnForDeviceSpace(pos.toInt());
    if (note >= 0)
        mouseUpOnKey(note, e);
}

void BrunGraphComponent::mouseDrag(const MouseEvent& e) {
    auto pos = e.position;
    auto const newNote = _processor.getBrun2Model()->nnForDeviceSpace(pos.toInt());
    if (newNote >= 0 && mouseDraggedToKey(newNote, e))
        _updateNoteUnderMouse(e, true);
}

void BrunGraphComponent::mouseMove(const MouseEvent& e) {
    _updateNoteUnderMouse(e, false);
}

bool BrunGraphComponent::mouseDownOnKey(int, const MouseEvent&) {
    return true;
}

bool BrunGraphComponent::mouseDraggedToKey(int, const MouseEvent&) {
    return true;
}

void BrunGraphComponent::mouseUpOnKey(int, const MouseEvent&) {
}

void BrunGraphComponent::mouseWheelMove(const MouseEvent&, const MouseWheelDetails& /* wheel */) {
}

void BrunGraphComponent::mouseEnter(const MouseEvent& e) {
    _updateNoteUnderMouse(e, false);
}

void BrunGraphComponent::mouseExit(const MouseEvent& e) {
    _updateNoteUnderMouse(e, false);
}

// keyboard is on a timer so not sure how this is an optimization
void BrunGraphComponent::_repaintNote(int noteNum) {
    ignoreUnused(noteNum);
}

#pragma mark - keyboard

void BrunGraphComponent::handleNoteOn(MidiKeyboardState* source, int midiChannel, int nn, float velocity) {
    ignoreUnused(source, midiChannel, nn, velocity);
    _shouldCheckState = true; // (probably being called from the audio thread, so avoid blocking in here)
}

void BrunGraphComponent::handleNoteOff(MidiKeyboardState* source, int midiChannel, int nn, float velocity) {
    ignoreUnused(source, midiChannel, nn, velocity);
    _shouldCheckState = true; // (probably being called from the audio thread, so avoid blocking in here)
}

# pragma mark - actionlistener

void BrunGraphComponent::actionListenerCallback(const String& message) {
    if(message == _processor.getMIDIPanicMessage()) {
        _resetAnyKeysInUse();
    }
}
