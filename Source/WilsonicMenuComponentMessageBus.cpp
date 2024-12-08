/*
  ==============================================================================

    WilsonicMenuComponentMessageBus.cpp
    Created: 20 Feb 2024 9:30:25pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "WilsonicMenuComponentMessageBus.h"

WilsonicMenuComponentMessageBus WilsonicMenuComponentMessageBus::__instance;

WilsonicMenuComponentMessageBus::WilsonicMenuComponentMessageBus()
{
    
}

// Singleton access to the MessageBus
WilsonicMenuComponentMessageBus& WilsonicMenuComponentMessageBus::getInstance()
{
    return __instance;
}

// Function to broadcast messages to listeners
void WilsonicMenuComponentMessageBus::broadcastMessage(const String& message)
{
    // Lock to prevent other threads from accessing the same data simultaneously
    const ScopedLock sl(_lock);

    // add to message queue
    _messages.add(message);

    if (_messageListener != nullptr)
    {
        _messageListener->handleMessage(message);
    }
}

// Function to set the listener
void WilsonicMenuComponentMessageBus::setMenuMessageListener(WilsonicMenuComponentMessageListener* listener)
{
    _messageListener = dynamic_cast<WilsonicMenuComponentMessageListener*>(listener);
}

const String WilsonicMenuComponentMessageBus::getMessages()
{
    // Lock to prevent other threads from accessing the same data simultaneously
    const ScopedLock sl(_lock);

    // accumulate message log
    String retVal = "";
    for(auto s : _messages)
    {
        retVal += s;
        retVal += "\n";
    }
    
    return retVal;
}

const String WilsonicMenuComponentMessageBus::getMessage()
{
    // Lock to prevent other threads from accessing the same data simultaneously
    const ScopedLock sl(_lock);

    //
    if(_messages.isEmpty())
    {
        return "";
    }
    else
    {
        auto const c = _messages.size();
        
        return _messages[c-1];
    }
}
