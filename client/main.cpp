#include "gui/GuiEntryPoint.h"
#include "core/InventoryCore.h"
#include "core/ClientConnection.h"
#include "CommonConnectionListener.h"
#include "CommonConnection.h"
#include "messages/ResourceRequest.h"

class MockListener : public CommonConnectionListener
{
public:
    virtual void onMessageReceived(CommonConnection& connection,
                                   std::shared_ptr<Message> message)
    {
        std::cout << "Message received " <<std::endl;
    }

    virtual void onConnected(CommonConnection& connection)
    {
        std::cout << "Connected " << std::endl;
        auto message = std::make_shared<ResourceRequest>("http://some.url");
        connection.write(*message);
    }
    virtual void onMessageReceivedErrror(CommonConnection& connection,
                                         const boost::system::error_code& ec)
    {
        std::cout << "onMessageReceivedErrror " << ec.message() << std::endl;
    }
};

int main(int argc, char *argv[])
{

    auto listener = std::make_shared<MockListener>();
    ClientConnection connection;
    connection.connectToServer("127.0.0.1", listener);
    connection.run();

    /*GuiEntryPoint entryPoint;
    std::shared_ptr<InventoryCore> core = std::make_shared<InventoryCore>();
    return entryPoint.exec(argc, argv, core);*/
    return 0;
}
