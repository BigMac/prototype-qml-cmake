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
        std::cout << "Message received "<< message.getTypeDiscriminator() <<std::endl;
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
        std::cout << "onMessageReceivedErrror " << ec.message() << std::endl;
    }
};

int main(int argc, char *argv[])
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


    std::cout << ss.str() << std::endl;

    auto listener = std::make_shared<MockListener>();
    ClientConnection connection;
    connection.connectToServer("127.0.0.1", listener);
    connection.run();

    /*GuiEntryPoint entryPoint;
    std::shared_ptr<InventoryCore> core = std::make_shared<InventoryCore>();
    return entryPoint.exec(argc, argv, core);*/
    return 0;
}
