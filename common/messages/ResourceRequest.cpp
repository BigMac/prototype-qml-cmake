#include "ResourceRequest.h"
#include <cassert>

ResourceRequest::ResourceRequest()
{
}

ResourceRequest::ResourceRequest(const std::string& url, bool binary)
    : m_resourceIsBinary(binary), m_url(url)
{
}

const std::string& ResourceRequest::getUrl() const
{
    return m_url;
}

