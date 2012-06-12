#include "gui/GuiEntryPoint.h"
#include "core/InventoryCore.h"
#include "core/network/ServerConnection.h"
#include "core/network/ServerConnectionListener.h"
#include "MessageReceiver.h"
#include "MessageSerializer.h"
#include "QmlRequest.h"

class MockListener : public ServerConnectionListener
{
public:
    virtual void onDataReceived(ServerConnection* connection,
                                const boost::system::error_code& ec,
                                size_t bytesReceived,
                                const std::vector<char>& data)
    {
        if(!ec && bytesReceived)
        {
//            std::cout << "Data received: " << &data[0] << std::endl;
//            std::string input;
//            std::cout << "Send: ";
//            std::cin >> input;
//            connection->syncWrite(std::vector<char>(input.begin(), input.end()));
        }
        else
            std::cout << "Status: " << ec.message() << std::endl;
    }

    virtual void onConnected(ServerConnection* connection, const boost::system::error_code& ec)
    {
        std::cout << "Connected: " << ec.message() << std::endl;
        auto qmlReq = std::make_shared<QmlRequest>("url");
        connection->syncWrite(qmlReq);
    }
};

int main(int argc, char *argv[])
{
    auto listener = std::make_shared<MockListener>();
    ServerConnection connection(listener);
    connection.connect("127.0.0.1");
    connection.run();

    /*GuiEntryPoint entryPoint;
    std::shared_ptr<InventoryCore> core = std::make_shared<InventoryCore>();
    return entryPoint.exec(argc, argv, core);*/
    return 0;
}
