#ifndef MESSAGERECEIVER_H
#define MESSAGERECEIVER_H

#include "UnsupportedMessageReceived.h"
#include <memory>

/* Sadly, this cannot be done by multiple inheritance because name resolution is
 * done before overload resolution and we get amiguity. We need all these overloads
 * to be in MessageReceiver. */
#define RECEIVES(Message_t) \
virtual void receive(std::shared_ptr<Message_t>) { throw UnsupportedMessageReceived<Message_t>(); }


class ResourceRequest;
class ResourceResponse;

class MessageReceiver
{
public:
    RECEIVES(ResourceRequest)
    RECEIVES(ResourceResponse)
};

#endif // MESSAGERECEIVER_H
