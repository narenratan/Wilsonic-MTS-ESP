/*
  ==============================================================================

    MorphComponentMessageBus.cpp
    Created: 2 Mar 2024 5:21:51pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "MorphComponentMessageBus.h"

MorphComponentMessageBus MorphComponentMessageBus::__instance;

MorphComponentMessageBus::MorphComponentMessageBus()
{
    
}

// Singleton access to the MessageBus
MorphComponentMessageBus& MorphComponentMessageBus::getInstance()
{
    return __instance;
}

// Function to broadcast messages to listeners
void MorphComponentMessageBus::broadcastMessage(const String& message)
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
void MorphComponentMessageBus::setMenuMessageListener(MorphComponentMessageListener* listener)
{
    _messageListener = dynamic_cast<MorphComponentMessageListener*>(listener);
}

const String MorphComponentMessageBus::getMessages()
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

const String MorphComponentMessageBus::getMessage()
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
