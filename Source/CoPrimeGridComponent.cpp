/*
  ==============================================================================

    CoPrimeGridComponent.cpp
    Created: 27 Apr 2023 9:24:42pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "CoPrimeGridComponent.h"
#include "AppExperiments.h"
#include "AppTuningModel.h"
#include "CoPrime.h"
#include "CoPrimeModel.h"

#pragma mark - lifecyle

CoPrimeGridComponent::CoPrimeGridComponent(WilsonicProcessor& processor)
: WilsonicComponentBase(processor) {
    setOpaque(true);
    _mouseOverNotes.insertMultiple(0, -1, 32);
    _mouseDownNotes.insertMultiple(0, -1, 32);
    _processor.addActionListener(this);
}

CoPrimeGridComponent::~CoPrimeGridComponent() {
    _processor.removeActionListener(this);
}

#pragma mark - drawing

void CoPrimeGridComponent::paint(Graphics& g) {
    _shouldCheckState = false; // for keyboard drawing
    g.fillAll(_processor.getAppSkin().getBgColor());
    if (AppExperiments::showDebugBoundingBox) {
        g.setColour(Colours::darkcyan);
        g.drawRect(getLocalBounds(), 2);
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }

    // paint
    _processor.getCoPrimeModel()->getTuning()->paint(_processor, g, getLocalBounds());
}

void CoPrimeGridComponent::resized() {

}

#pragma mark - touch

void CoPrimeGridComponent::_resetAnyKeysInUse() {
    for (int i = _mouseDownNotes.size(); --i >= 0;) {
        auto noteDown = _mouseDownNotes.getUnchecked(i);
        if (noteDown >= 0) {
            _processor.getKeyboardState()->noteOff(_midiChannel, noteDown, 0.0f);
            _mouseDownNotes.set(i, -1);
        }
        _mouseOverNotes.set(i, -1);
    }
}

void CoPrimeGridComponent::_updateNoteUnderMouse(const MouseEvent& e, bool isDown) {
    _updateNoteUnderMouse(e.getEventRelativeTo(this).position, isDown, e.source.getIndex());
}

void CoPrimeGridComponent::_updateNoteUnderMouse(Point<float> pos, bool isDown, int fingerNum) {
    int const newNote = _processor.getCoPrimeModel()->nnForMouseInViewBounds(pos.toInt(), getLocalBounds());
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

void CoPrimeGridComponent::mouseDown(const MouseEvent& e) {
    auto const pos = e.position;
    auto const newNote = _processor.getCoPrimeModel()->nnForMouseInViewBounds(pos.toInt(), getLocalBounds());
    if (newNote >= 0 && mouseDownOnKey(newNote, e)) {
        _updateNoteUnderMouse(e, true);
    }
}

void CoPrimeGridComponent::mouseUp(const MouseEvent& e) {
    _updateNoteUnderMouse(e, false);
    auto const pos = e.position;
    auto const note = _processor.getCoPrimeModel()->nnForMouseInViewBounds(pos.toInt(), getLocalBounds());
    if (note >= 0) {
        mouseUpOnKey(note, e);
    }
}

void CoPrimeGridComponent::mouseDrag(const MouseEvent& e) {
    auto pos = e.position;
    auto const newNote = _processor.getCoPrimeModel()->nnForMouseInViewBounds(pos.toInt(), getLocalBounds());
    if (newNote >= 0 && mouseDraggedToKey(newNote, e)) {
        _updateNoteUnderMouse(e, true);
    }
}

void CoPrimeGridComponent::mouseMove(const MouseEvent& e) {
    _updateNoteUnderMouse(e, false);
}

bool CoPrimeGridComponent::mouseDownOnKey(int, const MouseEvent&) {
    return true;
}

bool CoPrimeGridComponent::mouseDraggedToKey(int, const MouseEvent&) {
    return true;
}

void CoPrimeGridComponent::mouseUpOnKey(int, const MouseEvent&) {

}

void CoPrimeGridComponent::mouseWheelMove(const MouseEvent&, const MouseWheelDetails& /* wheel */) {
    /*
    auto amount = (_orientation == horizontalKeyboard && wheel.deltaX != 0)
    ? wheel.deltaX : (_orientation == verticalKeyboardFacingLeft ? wheel.deltaY
                      : -wheel.deltaY);

    _setLowestVisibleKeyFloat(_firstKey - amount * _keyWidth);
     */
}

void CoPrimeGridComponent::mouseEnter(const MouseEvent& e) {
    _updateNoteUnderMouse(e, false);
}

void CoPrimeGridComponent::mouseExit(const MouseEvent& e) {
    _updateNoteUnderMouse(e, false);
}

// keyboard is on a timer so not sure how this is an optimization
void CoPrimeGridComponent::_repaintNote(int /* noteNum */) {
    //repaint(getRectangleForKey(noteNum).getSmallestIntegerContainer());
}


#pragma mark - keyboard

void CoPrimeGridComponent::handleNoteOn(MidiKeyboardState* /* source */, int /*midiChannel*/, int /* nn */, float /*velocity*/) {
    _shouldCheckState = true; // (probably being called from the audio thread, so avoid blocking in here)
}

void CoPrimeGridComponent::handleNoteOff(MidiKeyboardState* /* source */, int /*midiChannel*/, int /* nn */, float /*velocity*/)
 {
    _shouldCheckState = true; // (probably being called from the audio thread, so avoid blocking in here)
}

# pragma mark - actionlistener

void CoPrimeGridComponent::actionListenerCallback(const String& message) {
    if(message == _processor.getMIDIPanicMessage()) {
        _resetAnyKeysInUse();
    }
}
