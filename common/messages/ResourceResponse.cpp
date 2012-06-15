#include "ResourceResponse.h"
#include "ResourceRequest.h"

ResourceResponse::ResourceResponse(const ResourceRequest &request) :
    m_success(false), m_url(request.getUrl())
{
}

void ResourceResponse::setSuccess(bool val)
{
    m_success = val;
}

const std::string& ResourceResponse::getRequestedUrl() const
{
    return m_url;
}

const std::vector<char>& ResourceResponse::getData() const
{
    return m_data;
}

std::string ResourceResponse::getDataAsString() const
{
    return std::string(m_data.begin(), m_data.end());
}

void ResourceResponse::setData(const std::vector<char>& data)
{
    m_data = data;
}

void ResourceResponse::setData(const std::string& data)
{
    m_data = decltype(m_data)(data.begin(), data.end());
}
