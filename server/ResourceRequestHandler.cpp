#include "ResourceRequestHandler.h"
#include "messages/ResourceRequest.h"
#include "messages/ResourceResponse.h"
#include "CommonConnection.h"

ResourceRequestHandler::ResourceRequestHandler(CommonConnection& connection) :
    m_connection(connection)
{
}


void ResourceRequestHandler::receive(ResourceRequest& msg)
{
    auto response = std::make_shared<ResourceResponse>(msg);
    std::vector<char> dummyData;
    dummyData.push_back('b');
    dummyData.push_back('g');
    response->setData(dummyData);
    m_connection.write(*response);
}
