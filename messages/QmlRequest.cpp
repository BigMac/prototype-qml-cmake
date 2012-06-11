#include "QmlRequest.h"

BOOST_CLASS_EXPORT_GUID(QmlRequest, "QmlRequest")

QmlRequest::QmlRequest(const std::string& url)
    : m_url(url)
{
}

const std::string& QmlRequest::getUrl() const
{
    return m_url;
}
