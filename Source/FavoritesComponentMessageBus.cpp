/*
  ==============================================================================

    FavoritesComponentMessageBus.cpp
    Created: 2 Mar 2024 5:24:34pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "FavoritesComponentMessageBus.h"

FavoritesComponentMessageBus FavoritesComponentMessageBus::__instance;

FavoritesComponentMessageBus::FavoritesComponentMessageBus() {
    
}

// Singleton access to the MessageBus
FavoritesComponentMessageBus& FavoritesComponentMessageBus::getInstance() {
    return __instance;
}

// Function to broadcast messages to listeners
void FavoritesComponentMessageBus::broadcastMessage(const String& message) {
    const ScopedLock sl(_lock);
    if (_messageQueue.size() >= __maxQueueSize) {
        _messageQueue.remove(0); // Remove the oldest message
    }
    _messageQueue.add(message);
    if (_messageListener != nullptr) {
        _messageListener->handleMessage(message);
    }
}

// Function to set the listener
void FavoritesComponentMessageBus::setMenuMessageListener(FavoritesComponentMessageBusListener* listener) {
    _messageListener = dynamic_cast<FavoritesComponentMessageBusListener*>(listener);
}

const String FavoritesComponentMessageBus::getMessages() {
    const ScopedLock sl(_lock);
    String retVal = "";
    for(auto s : _messageQueue) {
        retVal += s;
        retVal += "\n";
    }
    
    return retVal;
}

const String FavoritesComponentMessageBus::getMessage() {
    const ScopedLock sl(_lock);
    if(_messageQueue.isEmpty()) {
        return "";
    } else {
        auto const c = _messageQueue.size();
        
        return _messageQueue[c-1];
    }
}
