#include "gui/GuiEntryPoint.h"
#include "core/InventoryCore.h"
#include "core/network/ServerConnection.h"
#include "core/network/ServerConnectionListener.h"

class MockListener : public ServerConnectionListener
{
public:
    virtual void onDataReceived(ServerConnection* connection, std::vector<char> data)
    {
        std::cout << "Data received: " << &data[0] << std::endl;
    }

    virtual void onConnected(ServerConnection* connection, const boost::system::error_code& ec)
    {
        std::cout << "Connected: " << ec.message() << std::endl;
        std::vector<char> data = {'a', 'b', 'c'};
        connection->syncWrite(data);
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
