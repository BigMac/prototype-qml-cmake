#include "MessageSerializer.h"
#include "MessageRegistry.h"
#include "Message.h"
#include <iostream>
#include <memory>

SerializedMessage MessageSerializer::serialize(std::shared_ptr<Message> msg) const
{
    return SerializedMessage();
}

std::shared_ptr<Message> MessageSerializer::deserialize(SerializedMessage &input) const
{
    const MessageRegistry& registry = MessageRegistry::get_const_instance();
    return registry.getBuilder(input.getTypeDiscriminator())(input);
}
