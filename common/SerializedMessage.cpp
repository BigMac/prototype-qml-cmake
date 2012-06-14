#include "SerializedMessage.h"
#include "MessageRegistry.h"
#include <cassert>

SerializedMessage::SerializedMessage()
{
    data_size.push_back(0);
    message_type.push_back(0xFFFF);
}

SerializedMessage::SerializedMessage(NumericMessageTypeDiscriminator_t type,
                                     std::vector<char>& data) :
    data(data)
{
    data_size.push_back(data.size());
    message_type.push_back(type);
}

void SerializedMessage::setTypeDiscriminator(const std::string& type)
{
    message_type[0] = MessageRegistry::get_const_instance().getNumericMessageTypeDiscriminator(type);
}

const std::string& SerializedMessage::getTypeDiscriminator() const
{
    return MessageRegistry::get_const_instance().getStringMessageTypeDiscriminator(message_type[0]);
}

NumericMessageTypeDiscriminator_t SerializedMessage::getNumericTypeDiscriminator() const
{
    return message_type[0];
}

void SerializedMessage::prepareForReceive()
{
    assert(data_size.size() == 1);
    assert(data_size[0] > 0);
    data.resize(data_size[0], 0);
}

void SerializedMessage::prepareForSend()
{
    assert(data.size() > 0);
    assert(data_size.size() == 1);
    data_size[0] = data.size();
}
