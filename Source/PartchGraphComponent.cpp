/*
  ==============================================================================

    PartchGraphComponent.cpp
    Created: 5 Jun 2024 8:47:51pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AppExperiments.h"
#include "PartchModel.h"
#include "PartchGraphComponent.h"
#include "Microtone.h"

#pragma mark - lifecycle

PartchGraphComponent::PartchGraphComponent(WilsonicProcessor& processor) : WilsonicComponentBase(processor) {
    _mouseOverNotes.insertMultiple(0, -1, 32);
    _mouseDownNotes.insertMultiple(0, -1, 32);
    _processor.addActionListener(this);
    // parent has a timer that calls repaint
}

PartchGraphComponent::~PartchGraphComponent() {
    _processor.removeActionListener(this);
}

#pragma mark - drawing

void PartchGraphComponent::paint(Graphics& g) {
    _shouldCheckState = false;
    _processor.getPartchModel()->getTuning()->paint(_processor, g, getLocalBounds()); // paint the tuning
}

void PartchGraphComponent::resized() {
    // don't repaint _brunGraph here...it's repainted on a timer
}

#pragma mark - touch

void PartchGraphComponent::_resetAnyKeysInUse() {
    for (int i = _mouseDownNotes.size(); --i >= 0;) {
        auto const noteDown = _mouseDownNotes.getUnchecked(i);
        if (noteDown >= 0) {
            _processor.getKeyboardState()->noteOff(_midiChannel, noteDown, 0.0f);
            _mouseDownNotes.set(i, -1);
        }
        _mouseOverNotes.set(i, -1);
    }
}

void PartchGraphComponent::_updateNoteUnderMouse(const MouseEvent& e, bool isDown) {
    _updateNoteUnderMouse(e.getEventRelativeTo(this).position, isDown, e.source.getIndex());
}

void PartchGraphComponent::_updateNoteUnderMouse(Point<float> pos, bool isDown, int fingerNum) {
    auto const bt = dynamic_cast<Partch*>(_processor.getPartchModel()->getTuning().get());
    if(bt != nullptr) {
        // do not play notes if we have NPO Override Enabled
        if(bt->getNPOOverrideEnable())
            return;
    }
    
    auto const newNote = _processor.getPartchModel()->nnForDeviceSpace(pos.toInt());
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

void PartchGraphComponent::mouseDown(const MouseEvent& e) {
    auto const pos = e.position;
    auto const newNote = _processor.getPartchModel()->nnForDeviceSpace(pos.toInt());
    if (newNote >= 0 && mouseDownOnKey(newNote, e))
        _updateNoteUnderMouse(e, true);
}

void PartchGraphComponent::mouseUp(const MouseEvent& e) {
    _updateNoteUnderMouse(e, false);
    auto const pos = e.position;
    auto const note = _processor.getPartchModel()->nnForDeviceSpace(pos.toInt());
    if (note >= 0)
        mouseUpOnKey(note, e);
}

void PartchGraphComponent::mouseDrag(const MouseEvent& e) {
    auto pos = e.position;
    auto const newNote = _processor.getPartchModel()->nnForDeviceSpace(pos.toInt());
    if (newNote >= 0 && mouseDraggedToKey(newNote, e))
        _updateNoteUnderMouse(e, true);
}

void PartchGraphComponent::mouseMove(const MouseEvent& e) {
    _updateNoteUnderMouse(e, false);
}

bool PartchGraphComponent::mouseDownOnKey(int, const MouseEvent&) {
    return true;
}

bool PartchGraphComponent::mouseDraggedToKey(int, const MouseEvent&) {
    return true;
}

void PartchGraphComponent::mouseUpOnKey(int, const MouseEvent&) {
}

void PartchGraphComponent::mouseWheelMove(const MouseEvent&, const MouseWheelDetails& /* wheel */) {
}

void PartchGraphComponent::mouseEnter(const MouseEvent& e) {
    _updateNoteUnderMouse(e, false);
}

void PartchGraphComponent::mouseExit(const MouseEvent& e) {
    _updateNoteUnderMouse(e, false);
}

// keyboard is on a timer so not sure how this is an optimization
void PartchGraphComponent::_repaintNote(int noteNum) {
    ignoreUnused(noteNum);
}

#pragma mark - keyboard

void PartchGraphComponent::handleNoteOn(MidiKeyboardState* source, int midiChannel, int nn, float velocity) {
    ignoreUnused(source, midiChannel, nn, velocity);
    _shouldCheckState = true; // (probably being called from the audio thread, so avoid blocking in here)
}

void PartchGraphComponent::handleNoteOff(MidiKeyboardState* source, int midiChannel, int nn, float velocity) {
    ignoreUnused(source, midiChannel, nn, velocity);
    _shouldCheckState = true; // (probably being called from the audio thread, so avoid blocking in here)
}

# pragma mark - actionlistener

void PartchGraphComponent::actionListenerCallback(const String& message) {
    if(message == _processor.getMIDIPanicMessage()) {
        _resetAnyKeysInUse();
    }
}
