#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H
#include <boost/asio.hpp>
#include <memory>

class Message;
class ServerConnectionListener;

class ServerConnection
{
public:
    ServerConnection();
    ServerConnection(std::shared_ptr<ServerConnectionListener> listener);
    void registerListener(std::shared_ptr<ServerConnectionListener> listener);
    void connect(const std::string& address);
    void run();
    size_t syncWrite(std::shared_ptr<Message> msg);

private:
    void dataReceived(const boost::system::error_code& ec,
                      std::size_t bytes);
    void bindOnReceive();
    typedef boost::asio::ip::tcp tcp;
    boost::asio::io_service m_ioService;
    tcp::socket m_socket;
    std::vector<char> m_buffer;
    std::shared_ptr<ServerConnectionListener> m_listener;
};

#endif // SERVERCONNECTION_H
