#include "QmlRequest.h"

QmlRequest::QmlRequest()
{
}

QmlRequest::QmlRequest(const std::string& url)
    : m_url(url)
{
}

const std::string& QmlRequest::getUrl() const
{
    return m_url;
}

SerializedMessage QmlRequest::serialize() const
{
    //std::vector<char> data(m_url.begin(), m_url.end());
    SerializedMessage result;
    result.setTypeDiscriminator("QmlRequest");
    result.setData(m_url);
    return result;
}


std::shared_ptr<QmlRequest> QmlRequest::deserialize(SerializedMessage& serialized)
{
    assert(serialized.getTypeDiscriminator() == "QmlRequest");
    return std::make_shared<QmlRequest>(serialized.getDataAsString());
}

