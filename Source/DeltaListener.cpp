/*
 ==============================================================================
 
 DeltaListener.cpp
 Created: 11 Apr 2023 5:12:39pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "DeltaListener.h"

DeltaListener::DeltaListener() {
}

DeltaListener::~DeltaListener() {
}

void DeltaListener::changeListenerCallback (ChangeBroadcaster* source) {
    if (auto* customBroadcaster = dynamic_cast<DeltaBroadcaster*>(source)) {
        //const Point<int> delta = customBroadcaster->getDelta();
        // Do something with the delta
        //DBG("DeltaListener:: Received delta: " << delta.getY());
    }
}
