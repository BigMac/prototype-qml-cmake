#include "ServerConnection.h"
#include "ServerConnectionListener.h"

ServerConnection::ServerConnection() : m_socket(m_ioService), m_buffer(100)
{
}

ServerConnection::ServerConnection(std::shared_ptr<ServerConnectionListener> listener)
    : m_socket(m_ioService), m_buffer(100), m_listener(listener)
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

    //tcp::resolver::iterator endPointIterator(resolver.resolve(query));
    tcp::endpoint endpoint(tcp::v4(), 6666);
    m_socket.async_connect(//*endPointIterator,
                           endpoint,
                           // Connection handler
                           [&](const boost::system::error_code& ec)
                            {
                                if(!ec) bindOnReceive();
                                else std::cout << ec.message();
                                m_listener->onConnected(this, ec);
                            });
}

void ServerConnection::run()
{
    m_ioService.run();
}

void ServerConnection::bindOnReceive()
{
    m_socket.async_receive(boost::asio::buffer(m_buffer),
                           [&](const boost::system::error_code& ec, std::size_t bytes)
                            {
                                m_listener->onDataReceived(this, ec, bytes, m_buffer);
                                if(!ec)
                                    bindOnReceive();
                            } );
}

size_t ServerConnection::syncWrite(std::vector<char> data)
{
    return boost::asio::write(m_socket, boost::asio::buffer(data));
}
