#include "QmlRequest.h"

QmlRequest::QmlRequest(const std::string& url)
    : m_url(url)
{
}

const std::string& QmlRequest::getUrl() const
{
    return m_url;
}
