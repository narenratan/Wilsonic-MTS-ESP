/*
  ==============================================================================

    MorphComponentMessageBus.h
    Created: 2 Mar 2024 5:21:51pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class MorphComponentMessageListener
{
public:
    virtual ~MorphComponentMessageListener() {}
    virtual void handleMessage(const String& message) = 0;
};


class MorphComponentMessageBus
{
public:
    // Singleton access
    static MorphComponentMessageBus& getInstance();

    // broadcast messages to listeners
    void broadcastMessage(const String& message);

    // set the listener
    void setMenuMessageListener(MorphComponentMessageListener* listener);

    // retrieve messages
    const String getMessages();
    const String getMessage(); // most recent message for status label init
    
private:
    static MorphComponentMessageBus __instance;
    
    // Private constructor for singleton
    MorphComponentMessageBus();

    // Pointer to the listener
    MorphComponentMessageListener* _messageListener = nullptr;
    
    // StringArray of messages
    StringArray _messages {};

    // lock
    CriticalSection _lock;
};
