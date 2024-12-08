/*
  ==============================================================================

    ScalaComponentMessageBus.cpp
    Created: 2 Mar 2024 5:23:15pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "ScalaComponentMessageBus.h"

ScalaComponentMessageBus ScalaComponentMessageBus::__instance;

ScalaComponentMessageBus::ScalaComponentMessageBus()
{
    
}

// Singleton access to the MessageBus
ScalaComponentMessageBus& ScalaComponentMessageBus::getInstance()
{
    return __instance;
}

// Function to broadcast messages to listeners
void ScalaComponentMessageBus::broadcastMessage(const String& message)
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
void ScalaComponentMessageBus::setMenuMessageListener(ScalaComponentMessageListener* listener)
{
    _messageListener = dynamic_cast<ScalaComponentMessageListener*>(listener);
}

const String ScalaComponentMessageBus::getMessages()
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

const String ScalaComponentMessageBus::getMessage()
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
