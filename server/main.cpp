#include "SimpleServer.h"
#include "CommonConnection.h"
#include "CommonConnectionListener.h"
#include "SerializedMessage.h"

class ServerConnectionListener : public CommonConnectionListener
{
public:
    virtual void onMessageReceived(CommonConnection& connection,
                                   SerializedMessage& message)
    {
        std::string msgContent(message.data.begin(), message.data.end());
        std::cout << "Message received " << msgContent << std::endl;
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
