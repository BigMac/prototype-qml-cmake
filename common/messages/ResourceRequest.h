#ifndef RESOURCEREQUEST_H
#define RESOURCEREQUEST_H
#include "Message.h"
#include <string>

class ResourceRequest : public MessageImplementation<ResourceRequest>
{
public:
    ResourceRequest();
    ResourceRequest(const std::string& url);
    const std::string& getUrl() const;
    virtual SerializedMessage serialize() const;
    static std::shared_ptr<ResourceRequest> deserialize(SerializedMessage& serialized);
private:
    std::string m_url;
};

#include "MessageRegistry.h"
REGISTER_BUILDER("ResourceRequest", &ResourceRequest::deserialize)

#endif // RESOURCEREQUEST_H
