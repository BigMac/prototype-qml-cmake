#ifndef SIMPLESERVER_H
#define SIMPLESERVER_H
#include <boost/asio.hpp>
#include <memory>

class Connection;

class SimpleServer
{
typedef boost::asio::ip::tcp tcp;
public:
    SimpleServer();
    void startListening();
private:
    void startAccept();
    void handleAccept(std::shared_ptr<Connection> newConnection,
                      const boost::system::error_code& error);

    boost::asio::io_service m_ioService;
    tcp::acceptor m_acceptor;
};

#endif // SIMPLESERVER_H
