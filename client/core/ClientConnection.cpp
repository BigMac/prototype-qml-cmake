#include "ClientConnection.h"
#include "CommonConnection.h"
#include <functional>

typedef CommonConnection::tcp tcp;

void ClientConnection::connectToServer(const std::string& address,
                                       std::shared_ptr<CommonConnectionListener> listener)
{
    if(!listener)
    {
        std::cerr << "No CommonConnectionListener, aborting connect()";
        return;
    }
//    tcp::resolver resolver(m_ioService);
//    tcp::resolver::query query(address);

    //tcp::resolver::iterator endPointIterator(resolver.resolve(query));
    auto socket = std::make_shared<tcp::socket>(m_ioService);
    tcp::endpoint endpoint(tcp::v4(), 6666);
    socket->async_connect(//*endPointIterator,
                           endpoint,
                           // Connection handler
                          std::bind(&ClientConnection::handleConnected,
                                    this,
                                    std::bind(&CommonConnection::create, socket, listener),
                                    std::placeholders::_1));
}


void ClientConnection::handleConnected(std::shared_ptr<CommonConnection> newConnection,
                                       const boost::system::error_code& error)
{
    if(!error)
    {
        newConnection->connected();
    }
}

void ClientConnection::run()
{
    m_ioService.run();
}
