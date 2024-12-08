/*
  ==============================================================================

    ScalaComponentMessageBus.h
    Created: 2 Mar 2024 5:23:15pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ScalaComponentMessageListener
{
public:
    virtual ~ScalaComponentMessageListener() {}
    virtual void handleMessage(const String& message) = 0;
};


class ScalaComponentMessageBus
{
public:
    // Singleton access
    static ScalaComponentMessageBus& getInstance();

    // broadcast messages to listeners
    void broadcastMessage(const String& message);

    // set the listener
    void setMenuMessageListener(ScalaComponentMessageListener* listener);

    // retrieve messages
    const String getMessages();
    const String getMessage(); // most recent message for status label init
    
private:
    static ScalaComponentMessageBus __instance;
    
    // Private constructor for singleton
    ScalaComponentMessageBus();

    // Pointer to the listener
    ScalaComponentMessageListener* _messageListener = nullptr;
    
    // StringArray of messages
    StringArray _messages {};

    // lock
    CriticalSection _lock;
};
