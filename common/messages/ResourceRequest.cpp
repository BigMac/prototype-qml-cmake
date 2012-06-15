#include "ResourceRequest.h"

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
    //std::vector<char> data(m_url.begin(), m_url.end());
    SerializedMessage result;
    result.setTypeDiscriminator("QmlRequest");
    result.setData(m_url);
    return result;
}


std::shared_ptr<ResourceRequest> ResourceRequest::deserialize(SerializedMessage& serialized)
{
    assert(serialized.getTypeDiscriminator() == "QmlRequest");
    return std::make_shared<ResourceRequest>(serialized.getDataAsString());
}

