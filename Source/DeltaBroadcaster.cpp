/*
 ==============================================================================

 DeltaBroadcaster.cpp
 Created: 11 Apr 2023 5:12:09pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "DeltaBroadcaster.h"

DeltaBroadcaster::DeltaBroadcaster() {
}

DeltaBroadcaster::~DeltaBroadcaster() {
}

void DeltaBroadcaster::setDelta (Point<int> newDelta) {
    _delta = newDelta;
    sendChangeMessage();
}

Point<int> DeltaBroadcaster::getDelta() const {
    return _delta;
}
