#ifndef MESSAGEREGISTRY_H
#define MESSAGEREGISTRY_H
#include "SerializedMessage.h"

#include "messages/ResourceRequest.h"
#include "messages/ResourceResponse.h"

#include <boost/serialization/singleton.hpp>
#include <boost/lexical_cast.hpp>
#include <cstdint>
#include <stdexcept>
#include <functional>
#include <map>
#include <memory>
#include <string>

class Message;

class MessageRegistry : public boost::serialization::singleton<MessageRegistry>
{
public:
    typedef std::function<std::shared_ptr<Message>(SerializedMessage&)> BuilderFunction_t;
    class MessageTypeNotRegistered : public std::runtime_error
    {
    public:
        MessageTypeNotRegistered(NumericMessageTypeDiscriminator_t type) :
            std::runtime_error(boost::lexical_cast<std::string>(type)) {}
        MessageTypeNotRegistered(const std::string& type) :
            std::runtime_error(type) {}
    };

    bool registerBuilder(const std::string& typeDiscriminator,
                         BuilderFunction_t builder);
    BuilderFunction_t getBuilder(const std::string& typeDiscriminator) const;
    BuilderFunction_t getBuilder(NumericMessageTypeDiscriminator_t typeDiscriminator) const;

    NumericMessageTypeDiscriminator_t getNumericMessageTypeDiscriminator(const std::string& typeDiscriminator) const;
    const std::string& getStringMessageTypeDiscriminator(NumericMessageTypeDiscriminator_t typeDiscriminator) const;

private:
    typedef std::map<std::string, BuilderFunction_t> RegisteredBuildersMap_t;
    RegisteredBuildersMap_t m_registeredBuilders;

    RegisteredBuildersMap_t::const_iterator getIterator(NumericMessageTypeDiscriminator_t typeDiscriminator) const;
    RegisteredBuildersMap_t::const_iterator getIterator(const std::string& typeDiscriminator) const;
};

#endif // MESSAGEREGISTRY_H
