#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H
#include <string>
#include <memory>
#include <boost/asio.hpp>

class CommonConnection;
class CommonConnectionListener;
class ClientConnection
{
public:
    void connectToServer(const std::string& address,
                         std::shared_ptr<CommonConnectionListener> listener);
    void run();
private:
    void handleConnected(std::shared_ptr<CommonConnection> newConnection,
                         const boost::system::error_code& error);
    boost::asio::io_service m_ioService;
};

#endif // CLIENTCONNECTION_H
