#include "MessageRegistry.h"
#include <algorithm>

bool MessageRegistry::registerBuilder(const std::string& typeDiscriminator,
                                      BuilderFunction_t builder)
{
    m_registeredBuilders[typeDiscriminator] = builder;
    return true;
}


MessageRegistry::RegisteredBuildersMap_t::const_iterator
MessageRegistry::getIterator(NumericMessageTypeDiscriminator_t typeDiscriminator) const
{
    if(typeDiscriminator > m_registeredBuilders.size())
        throw MessageRegistry::MessageTypeNotRegistered(typeDiscriminator);
    auto builderIter = m_registeredBuilders.begin();
    std::advance(builderIter, typeDiscriminator);
    if(builderIter == m_registeredBuilders.end())
        throw MessageRegistry::MessageTypeNotRegistered(typeDiscriminator);
    return builderIter;
}


MessageRegistry::RegisteredBuildersMap_t::const_iterator
MessageRegistry::getIterator(const std::string& typeDiscriminator) const
{
    auto builderIter = m_registeredBuilders.find(typeDiscriminator);
    if(builderIter == m_registeredBuilders.end())
        throw MessageRegistry::MessageTypeNotRegistered(typeDiscriminator);
    return builderIter;
}


MessageRegistry::BuilderFunction_t
MessageRegistry::getBuilder(const std::string& typeDiscriminator) const
{
    return getIterator(typeDiscriminator)->second;
}

MessageRegistry::BuilderFunction_t MessageRegistry::getBuilder(
        NumericMessageTypeDiscriminator_t typeDiscriminator) const
{
    return getIterator(typeDiscriminator)->second;
}

NumericMessageTypeDiscriminator_t
MessageRegistry::getNumericMessageTypeDiscriminator(
        const std::string& typeDiscriminator) const
{
    return std::distance(m_registeredBuilders.begin(), getIterator(typeDiscriminator));
}

const std::string& MessageRegistry::getStringMessageTypeDiscriminator(
        NumericMessageTypeDiscriminator_t typeDiscriminator) const
{
    return getIterator(typeDiscriminator)->first;
}
