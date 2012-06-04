#include "ServerConnection.h"
#include "ServerConnectionListener.h"

ServerConnection::ServerConnection() : m_socket(m_ioService)
{
}

void ServerConnection::registerListener(std::shared_ptr<ServerConnectionListener> listener)
{
    m_listener = listener;
}

void ServerConnection::connect(const std::string& address)
{
    if(!m_listener)
    {
        std::cerr << "No ServerConnectionListener, aborting connect()";
        return;
    }
    tcp::resolver resolver(m_ioService);
    tcp::resolver::query query(address);

    tcp::resolver::iterator endPointIterator(resolver.resolve(query));
    m_socket.async_connect(*endPointIterator,
                           // Connection handler
                           [&](const boost::system::error_code& ec)
                            {
                                if(!ec) bindOnReceive();
                                m_listener->onConnected(ec);
                            });
}

void ServerConnection::bindOnReceive()
{
    m_socket.async_receive(boost::asio::buffer(m_buffer),
                           [&](const boost::system::error_code&, std::size_t)
                            { m_listener->onDataReceived(m_buffer); } );
}

size_t ServerConnection::syncWrite(std::vector<char> data)
{
    return boost::asio::write(m_socket, boost::asio::buffer(data));
}
