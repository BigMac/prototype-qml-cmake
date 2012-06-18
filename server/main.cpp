#include "SimpleServer.h"
#include "CommonConnection.h"
#include "CommonConnectionListener.h"
#include "Message.h"
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
    std::shared_ptr<Message> msg(new ResourceRequest("some url"));
    std::stringstream ss;
    boost::archive::text_oarchive ar(ss);
    //ar.register_type<ResourceRequest>();
    Message* raw = msg.get();
    ar << raw;

    Message* deserialized = NULL;
    std::istringstream iss(ss.str());
    boost::archive::text_iarchive iar(iss);
    //iar.register_type<ResourceRequest>();
    iar >> deserialized;

    auto listener = std::make_shared<ServerConnectionListener>();
    SimpleServer server;
    server.startListening(listener);
    return 0;
}
