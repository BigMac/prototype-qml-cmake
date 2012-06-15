#ifndef RESOURCEREQUEST_H
#define RESOURCEREQUEST_H
#include "../Message.h"
#include <string>

class ResourceRequest : public MessageImplementation<ResourceRequest>
{
public:
    ResourceRequest(const std::string& url);
    const std::string& getUrl() const;
    virtual SerializedMessage serialize() const;
    static std::shared_ptr<ResourceRequest> deserialize(SerializedMessage& serialized);
private:
    ResourceRequest();
    std::string m_url;
};

#endif // RESOURCEREQUEST_H
