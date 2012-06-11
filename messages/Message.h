#ifndef MESSAGE_H
#define MESSAGE_H
#include "MessageReceiver.h"
#include <boost/serialization/base_object.hpp>
#include <memory>

namespace boost {
namespace serialization {
class access; // For friend access to serialization.
}
}


class Message
{
    template<class Archive>
    void serialize(Archive & ar, const unsigned int file_version){}
public:
    virtual void accept(MessageReceiver& receiver) = 0;
    virtual ~Message() {}
};


template <typename Message_t>
class MessageImplementation : public Message, public std::enable_shared_from_this<Message_t>
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int file_version)
    {
        boost::serialization::base_object<Message>(*this);
    }

public:
    virtual void accept(MessageReceiver& receiver)
    {
        receiver.receive(this->shared_from_this());
    }
};

#endif // MESSAGE_H
