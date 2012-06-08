#ifndef MESSAGERECEIVER_H
#define MESSAGERECEIVER_H

#include "UnsupportedMessageReceived.h"
#include <memory>

template <typename Message_t>
class ConcreteReceiver
{
public:
    virtual void receive(std::shared_ptr<Message_t>) { throw UnsupportedMessageReceived<Message_t>(); }
};

class QmlRequest;

class MessageReceiver :
        public ConcreteReceiver<QmlRequest>,
        public ConcreteReceiver<float>
{
};

#endif // MESSAGERECEIVER_H
