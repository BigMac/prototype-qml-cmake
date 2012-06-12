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

    typedef std::function<std::shared_ptr<Message>(SerializedMessage&)> BuilderFunction_t;
    void registerBuilder(const std::string& typeDiscriminator,
                         BuilderFunction_t builder);
private:
    std::map<std::string, BuilderFunction_t> m_registeredBuilders;
};

#endif // MESSAGESERIALIZER_H
