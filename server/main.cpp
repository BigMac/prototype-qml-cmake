#include "SimpleServer.h"
#include "CommonConnection.h"
#include "CommonConnectionListener.h"
#include "messages/Message.h"
#include "messages/ResourceRequest.h"
#include "ResourceRequestHandler.h"

class ServerConnectionListener : public CommonConnectionListener
{
public:
    virtual void onMessageReceived(CommonConnection& connection,
                                   std::shared_ptr<Message> message)
    {
        std::cout << "Message received " << std::endl;
        ResourceRequestHandler handler(connection);
        message->accept(handler);
    }

    virtual void onMessageReceivedErrror(CommonConnection& connection,
                                         const boost::system::error_code& ec)
    {
        std::cout << "Error received " << ec.message() <<std::endl;
    }

    virtual void onConnected(CommonConnection& connection)
    {
        std::cout << "New connection" << std::endl;
    }
};


int main()
{
    auto listener = std::make_shared<ServerConnectionListener>();
    SimpleServer server;
    server.startListening(listener);
    return 0;
}
