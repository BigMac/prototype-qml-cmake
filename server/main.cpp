#include "SimpleServer.h"
#include "CommonConnection.h"
#include "CommonConnectionListener.h"
#include "SerializedMessage.h"
#include "Message.h"
#include "messages/ResourceRequest.h"
#include "MessageReceiver.h"
#include "MessageSerializer.h"

class ServerConnectionListener : public CommonConnectionListener
{
public:
    virtual void onMessageReceived(CommonConnection& connection,
                                   SerializedMessage& message)
    {
        std::cout << "Message received " << std::endl;
        MessageSerializer serializer;
        auto deserializedMessage = serializer.deserialize(message);
        deserializedMessage->accept(m_receiver);
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
private:
    MessageReceiver m_receiver;
};


int main()
{
    auto listener = std::make_shared<ServerConnectionListener>();
    SimpleServer server;
    server.startListening(listener);
    return 0;
}
