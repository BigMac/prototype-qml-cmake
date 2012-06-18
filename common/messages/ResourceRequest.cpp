#include "ResourceRequest.h"
#include <cassert>
BOOST_CLASS_EXPORT_GUID(ResourceRequest, "ResourceRequest")
ResourceRequest::ResourceRequest()
{
}

ResourceRequest::ResourceRequest(const std::string& url)
    : m_url(url)
{
}

const std::string& ResourceRequest::getUrl() const
{
    return m_url;
}

SerializedMessage ResourceRequest::serialize() const
{
    SerializedMessage result;
    result.setTypeDiscriminator("ResourceRequest");
    result.setData(m_url);
    return result;
}

std::shared_ptr<ResourceRequest> ResourceRequest::deserialize(SerializedMessage& serialized)
{
    assert(serialized.getTypeDiscriminator() == "ResourceRequest");
    return std::make_shared<ResourceRequest>(serialized.getDataAsString());
}

