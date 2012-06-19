#ifndef SERIALIZER_H
#define SERIALIZER_H
#include "Message.h"
#include "ResourceRequest.h"
#include "ResourceResponse.h"
#include <string>
#include <sstream>
#include <memory>

class Serializer
{
public:
    std::string serialize(const Message& message)
    {
        std::ostringstream archiveStream;
        boost::archive::text_oarchive archive(archiveStream);

        // Add all message types here in lexical order
        archive.register_type<ResourceRequest>();
        archive.register_type<ResourceResponse>();

        const Message* rawMsg = &message;
        archive << rawMsg;
        return archiveStream.str();
    }

    std::shared_ptr<Message> deserialize(const std::string& input)
    {
        std::istringstream archiveStream(input);
        boost::archive::text_iarchive archive(archiveStream);

        // Add all message types here in lexical order
        archive.register_type<ResourceRequest>();
        archive.register_type<ResourceResponse>();

        Message* rawMsg(NULL);
        archive >> rawMsg;
        return std::shared_ptr<Message>(rawMsg);
    }
};

#endif // SERIALIZER_H
