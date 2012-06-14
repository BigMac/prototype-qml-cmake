#ifndef SIMPLESERVER_H
#define SIMPLESERVER_H
#include <boost/asio.hpp>
#include <memory>

class CommonConnection;
class CommonConnectionListener;

class SimpleServer
{
typedef boost::asio::ip::tcp tcp;
public:
    SimpleServer();
    void startListening(std::shared_ptr<CommonConnectionListener> listener);
private:
    void startAccept();
    void handleAccept(std::shared_ptr<CommonConnection> newConnection,
                      const boost::system::error_code& error);

    std::shared_ptr<CommonConnectionListener> m_listener;
    boost::asio::io_service m_ioService;
    tcp::acceptor m_acceptor;
};

#endif // SIMPLESERVER_H
