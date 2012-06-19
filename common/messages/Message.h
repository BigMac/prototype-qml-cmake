#ifndef MESSAGE_H
#define MESSAGE_H
#include "MessageReceiver.h"
#include <memory>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>

typedef uint32_t transactionId_t;
class Message
{
public:
    Message() : m_tid(0) {}
    virtual void accept(MessageReceiver& receiver) = 0;
    virtual ~Message() {}

    void setTransactionId(transactionId_t id) { m_tid = id; }
    transactionId_t getTransactionId() { return m_tid; }
private:
    transactionId_t m_tid;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & m_tid;
    }
};

template <typename Message_t>
class MessageImplementation : public Message
{
public:
    virtual void accept(MessageReceiver& receiver)
    {
        receiver.receive(static_cast<Message_t&>(*this));
        /* If you get a "no matching function for call to
         * ‘MessageReceiver::receive(std::shared_ptr<YourMessage>)’" error,
         * it means you forgot to add YourMessage  to MessageReceiver's list.
         * Go there and add RECEIVES(YourMessage) to its body. */
    }
};

#endif // MESSAGE_H
