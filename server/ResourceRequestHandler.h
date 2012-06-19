#ifndef RESOURCEREQUESTHANDLER_H
#define RESOURCEREQUESTHANDLER_H
#include "messages/MessageReceiver.h"
#include <memory>

class CommonConnection;
class ResourceRequest;
class ResourceRequestHandler : public MessageReceiver
{
public:
    ResourceRequestHandler(CommonConnection& connection);
    void receive(ResourceRequest& msg);

private:
    CommonConnection& m_connection;
};

#endif // RESOURCEREQUESTHANDLER_H
