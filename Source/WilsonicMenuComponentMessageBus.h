/*
  ==============================================================================

    WilsonicMenuComponentMessageBus.h
    Created: 20 Feb 2024 9:30:25pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class WilsonicMenuComponentMessageListener
{
public:
    virtual ~WilsonicMenuComponentMessageListener() {}
    virtual void handleMessage(const String& message) = 0;
};


class WilsonicMenuComponentMessageBus
{
public:
    // Singleton access
    static WilsonicMenuComponentMessageBus& getInstance();

    // broadcast messages to listeners
    void broadcastMessage(const String& message);

    // set the listener
    void setMenuMessageListener(WilsonicMenuComponentMessageListener* listener);

    // retrieve messages
    const String getMessages();
    const String getMessage(); // most recent message for status label init
    
private:
    static WilsonicMenuComponentMessageBus __instance;
    
    // Private constructor for singleton
    WilsonicMenuComponentMessageBus();

    // Pointer to the listener
    WilsonicMenuComponentMessageListener* _messageListener = nullptr;
    
    // StringArray of messages
    StringArray _messages {};

    // lock
    CriticalSection _lock;
};
