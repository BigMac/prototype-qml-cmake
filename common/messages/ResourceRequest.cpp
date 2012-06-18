#include "ResourceRequest.h"
#include <cassert>

BOOST_CLASS_EXPORT_IMPLEMENT(ResourceRequest)

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

