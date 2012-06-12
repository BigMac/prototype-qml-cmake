#ifndef MESSAGE_H
#define MESSAGE_H
#include "MessageReceiver.h"
#include "SerializedMessage.h"
#include <memory>

class Message
{
public:
    virtual void accept(MessageReceiver& receiver) = 0;
    virtual SerializedMessage serialize() const = 0;
    virtual ~Message() {}
};

template <typename Message_t>
class MessageImplementation : public Message, public std::enable_shared_from_this<Message_t>
{
public:
    virtual void accept(MessageReceiver& receiver)
    {
        receiver.receive(this->shared_from_this());
    }
};

#endif // MESSAGE_H
