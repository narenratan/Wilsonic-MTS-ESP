/*
  ==============================================================================

    FavoritesComponentMessageBus.h
    Created: 2 Mar 2024 5:24:34pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class FavoritesComponentMessageBusListener
{
public:
    virtual ~FavoritesComponentMessageBusListener() {}
    virtual void handleMessage(const String& message) = 0;
};

class FavoritesComponentMessageBus
{
public:
    // Singleton access
    static FavoritesComponentMessageBus& getInstance();

    // broadcast messages to listeners
    void broadcastMessage(const String& message);

    // set the listener
    void setMenuMessageListener(FavoritesComponentMessageBusListener* listener);

    // retrieve messages
    const String getMessages();
    const String getMessage(); // most recent message for status label init
    
private:
    static FavoritesComponentMessageBus __instance;
    static constexpr int __maxQueueSize = 128;
    
    // Private constructor for singleton
    FavoritesComponentMessageBus();

    // Pointer to the listener
    FavoritesComponentMessageBusListener* _messageListener = nullptr;
    
    // StringArray of messages
    StringArray _messageQueue {};

    // lock
    CriticalSection _lock;
};
