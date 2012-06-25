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
    tcp::resolver resolver(m_ioService);
    tcp::resolver::query query(address, "6666");
    tcp::resolver::iterator endPointIterator = resolver.resolve(query);
    tcp::resolver::iterator end;
    boost::asio::io_service io_service;
    boost::system::error_code error = boost::asio::error::host_not_found;
    while (error && endPointIterator != end)
    {
        auto socket = std::make_shared<tcp::socket>(m_ioService);
        socket->async_connect(//*endPointIterator,
                               *endPointIterator++,
                               // Connection handler
                              std::bind(&ClientConnection::handleConnected,
                                        this,
                                        std::bind(&CommonConnection::create, socket, listener),
                                        std::placeholders::_1));
    }
}


void ClientConnection::handleConnected(std::shared_ptr<CommonConnection> newConnection,
                                       const boost::system::error_code& error)
{
    if(!error)
        newConnection->connected();
    else
        std::cerr << error.message() << std::endl;
}

void ClientConnection::run()
{
    m_ioService.run();
}
