#include "MessageSerializer.h"
#include "Message.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <iostream>

SerializedMessage MessageSerializer::serialize(std::shared_ptr<Message> msg) const
{
    return msg->serialize();
}

std::shared_ptr<Message> MessageSerializer::deserialize(SerializedMessage &input) const
{
    auto builderIterator = m_registeredBuilders.find(input.getTypeDiscriminator());
    if(builderIterator == m_registeredBuilders.end())
        throw std::runtime_error("No builder registered for messages with type discriminator");
    return builderIterator->second(input);
}

void MessageSerializer::registerBuilder(const std::string& typeDiscriminator,
                                        BuilderFunction_t builder)
{
    m_registeredBuilders[typeDiscriminator] = builder;
}
