#include "SerializedMessage.h"

SerializedMessage::SerializedMessage()
{
}

void SerializedMessage::setTypeDiscriminator(const std::string& type)
{
    m_typeDiscriminator = type;
}

const std::string& SerializedMessage::getTypeDiscriminator() const
{
    return m_typeDiscriminator;
}
