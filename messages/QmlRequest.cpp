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
    return result;
}
