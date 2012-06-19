#include "ResourceRequestHandler.h"
#include "messages/ResourceRequest.h"
#include "messages/ResourceResponse.h"
#include "CommonConnection.h"
#include <fstream>
#include <iterator>

ResourceRequestHandler::ResourceRequestHandler(CommonConnection& connection) :
    m_connection(connection)
{
}


void ResourceRequestHandler::receive(ResourceRequest& msg)
{
    std::ios_base::openmode flags = std::ios_base::in;
    if(msg.isResourceBinary())
        flags |= std::ios_base::binary;
    std::ifstream resource(msg.getUrl(), flags);
    std::cout << msg.getUrl() << " is open " << resource.is_open() << std::endl;

    std::vector<char> data((std::istreambuf_iterator<char>(resource)),
                           std::istreambuf_iterator<char>());

    auto response = std::make_shared<ResourceResponse>(msg);
    response->setData(data);
    response->setTransactionId(msg.getTransactionId());
    m_connection.write(*response);
}
