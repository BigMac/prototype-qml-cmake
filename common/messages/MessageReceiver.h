#ifndef MESSAGERECEIVER_H
#define MESSAGERECEIVER_H

#include "UnsupportedMessageReceived.h"
#include <memory>

/* Sadly, this cannot be done by multiple inheritance because name resolution is
 * done before overload resolution and we get amiguity. We need all these overloads
 * to be in MessageReceiver. */
template<typename Message_t>
class ConcreteReceiver
{
public:
    virtual void receive(Message_t&) { throw UnsupportedMessageReceived<Message_t>(); }
};



class ResourceRequest;
class ResourceResponse;

class MessageReceiver :
        public ConcreteReceiver<ResourceRequest>,
        public ConcreteReceiver<ResourceResponse>
{
public:
    using ConcreteReceiver<ResourceRequest>::receive;
    using ConcreteReceiver<ResourceResponse>::receive;
};

#endif // MESSAGERECEIVER_H
