/*
 ==============================================================================

 BubbleDrawable.cpp
 Created: 18 May 2022 12:15:11pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include <JuceHeader.h>
#include "BubbleDrawable.h"
#include "WilsonicEditor.h"

BubbleDrawable::BubbleDrawable(const BubblePlacement placement, const String& singleCharacter, const String& bubbleMessage)
: _placement (placement)
, _singleCharacter (singleCharacter)
, _bubbleMessage (bubbleMessage)
, _icon (nullptr)
{
    jassert(_placement != 0);
    jassert(_singleCharacter.length() == 1);
    jassert(_bubbleMessage.length() > 0);
}

BubbleDrawable::BubbleDrawable(const BubblePlacement placement, shared_ptr<Image> icon, const String& bubbleMessage)
: _placement (placement)
, _singleCharacter ("")
, _bubbleMessage (bubbleMessage)
, _icon (icon)
{
    jassert(_placement != 0);
    jassert(_singleCharacter.length() == 0);
    jassert(_bubbleMessage.length() > 0);
    jassert(_icon != nullptr);
}

BubbleDrawable::~BubbleDrawable() {
}

void BubbleDrawable::paint(Graphics& g) {
    g.fillAll (WilsonicAppSkin::getBgColor());
    if (AppExperiments::showDebugBoundingBox) {
        g.setColour (Colours::yellowgreen);
        g.drawRect (getLocalBounds(), 1);
    }

    // layout
    auto area = getLocalBounds();
    auto center = area.getCentre();
    auto min_bounds_dim = min (area.getHeight(), area.getWidth());
    auto min_dim = min (min_bounds_dim, static_cast<int>(WilsonicAppSkin::minHitPointSize));
    auto fa = Rectangle<int>(0, 0, min_dim, min_dim);
    fa.setCentre (center);
    auto ea = Rectangle<float>(fa.getX(), fa.getY(), min_dim, min_dim);

    if (_icon == nullptr) {
        // draw the single character screen
        g.setColour (WilsonicAppSkin::getTextColor());
        g.drawText (_singleCharacter, fa, Justification::centred);
        ea.reduce (3, 3);
        g.drawEllipse (ea, 1.f);
    } else {
        // draw the icon
        g.drawImage (*_icon, ea, RectanglePlacement (RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize), false);
    }
}

void BubbleDrawable::resized() {

}

void BubbleDrawable::mouseEnter(const MouseEvent&) {
    if (_bubbleMessage.length() > 0) {
        WilsonicEditor::showBubbleMessage(*this);
    }
}

const String& BubbleDrawable::getBubbleMessage() {
    return _bubbleMessage;
}

void BubbleDrawable::setBubbleMessage(String newMessage) {
    _bubbleMessage = newMessage;
}

void BubbleDrawable::setIcon(shared_ptr<Image> icon) {
    jassert (icon != nullptr);
    _icon = icon;
    repaint();
}

const BubblePlacement BubbleDrawable::getBubblePlacement() {
    return _placement;
}
