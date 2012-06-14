#ifndef MESSAGESERIALIZER_H
#define MESSAGESERIALIZER_H
#include "SerializedMessage.h"
#include <memory>
#include <functional>
#include <map>

class Message;
class MessageSerializer
{
public:
    SerializedMessage serialize(std::shared_ptr<Message> msg) const;
    std::shared_ptr<Message> deserialize(SerializedMessage &input) const;
};

#endif // MESSAGESERIALIZER_H
