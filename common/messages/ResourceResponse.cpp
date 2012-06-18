#include "ResourceResponse.h"
#include "ResourceRequest.h"
#include <sstream>
BOOST_CLASS_EXPORT_GUID(ResourceResponse, "ResourceResponse")
ResourceResponse::ResourceResponse(const ResourceRequest &request) :
    m_success(false), m_url(request.getUrl())
{
}

ResourceResponse::ResourceResponse() :
    m_success(false)
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
    m_data = std::vector<char>(data.begin(), data.end());
}

SerializedMessage ResourceResponse::serialize() const
{
    SerializedMessage result;
    result.setTypeDiscriminator("ResourceResponse");
    std::ostringstream ss;
    ss << m_url << m_success << getDataAsString();
    result.setData(ss.str());
    return result;
}

std::shared_ptr<ResourceResponse> ResourceResponse::deserialize(SerializedMessage& serialized)
{
    auto response = std::make_shared<ResourceResponse>();
    std::string input = serialized.getDataAsString();
    std::istringstream ss(input);
    std::string data;
    ss >> response->m_url >> response->m_success >> data;
    response->setData(data);
    return response;
}
