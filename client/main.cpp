#include "gui/GuiEntryPoint.h"
#include "connection/ClientConnection.h"
#include "CommonConnectionListener.h"
#include "CommonConnection.h"
#include "messages/ResourceRequest.h"
#include "messages/Serializer.h"
#include "gui/QtServiceFactory.h"
#include "gui/QtService.h"
#include "Dispatcher.h"
#include "events/OpenInterfaceWindowRequest.h"
#include "events/GuiResourceResponse.h"

class MockListener : public CommonConnectionListener
{
public:
    virtual void onMessageReceived(CommonConnection& connection,
                                   std::shared_ptr<Message> message)
    {
        std::cout << "Message received " << std::endl;
    }

    virtual void onConnected(CommonConnection& connection)
    {
        std::cout << "Connected " << std::endl;
        auto message = std::make_shared<ResourceRequest>("resources/qml/main.qml");
        message->setTransactionId(122);
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
    auto dispatcher = std::make_shared<Dispatcher>();
    auto service = QtServiceFactory::create(dispatcher);
    service->post(std::make_shared<OpenInterfaceWindowRequest>("dupa://resources/qml/main.qml"));
    service->post(std::make_shared<GuiResourceResponse>("resources/qml/main.qml"));
    service->run();

//    auto listener = std::make_shared<MockListener>();
//    ClientConnection connection;
//    connection.connectToServer("127.0.0.1", listener);
//    connection.run();

    /*GuiEntryPoint entryPoint;
    std::shared_ptr<InventoryCore> core = std::make_shared<InventoryCore>();
    return entryPoint.exec(argc, argv, core);*/
    return 0;
}
