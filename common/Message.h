#ifndef MESSAGE_H
#define MESSAGE_H
#include "MessageReceiver.h"
#include "SerializedMessage.h"
#include <memory>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>

class Message
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &, const unsigned int){}
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
        /* If you get a "no matching function for call to
         * ‘MessageReceiver::receive(std::shared_ptr<YourMessage>)’" error,
         * it means you forgot to add YourMessage  to MessageReceiver's list.
         * Go there and add RECEIVES(YourMessage) to its body. */
    }
};

#endif // MESSAGE_H
