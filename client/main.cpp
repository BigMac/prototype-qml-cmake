#include "gui/GuiEntryPoint.h"
#include "core/InventoryCore.h"
#include "core/ClientConnection.h"
#include "CommonConnectionListener.h"
#include "CommonConnection.h"
#include "SerializedMessage.h"
#include "MessageReceiver.h"
#include "MessageSerializer.h"
#include "messages/ResourceRequest.h"

class MockListener : public CommonConnectionListener
{
public:
    virtual void onMessageReceived(CommonConnection& connection,
                                   SerializedMessage& message)
    {
        /*if(!ec && bytesReceived)
        {
//            std::cout << "Data received: " << &data[0] << std::endl;
//            std::string input;
//            std::cout << "Send: ";
//            std::cin >> input;
//            connection->syncWrite(std::vector<char>(input.begin(), input.end()));
        }
        else
            std::cout << "Status: " << ec.message() << std::endl;*/
    }

    virtual void onConnected(CommonConnection& connection)
    {
        std::cout << "Connected " << std::endl;
        auto message = std::make_shared<ResourceRequest>("http://some.url");
        SerializedMessage serialized = message->serialize();
        connection.write(serialized);
    }
    virtual void onMessageReceivedErrror(CommonConnection& connection,
                                         const boost::system::error_code& ec)
    {

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
