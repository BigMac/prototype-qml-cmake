#ifndef CONNECTION_H
#define CONNECTION_H
#include "SerializedMessage.h"
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
//#include <boost/enable_shared_from_this.hpp>
#include <functional>
#include <memory>
class Message;
class MessageReceiver;

class Connection : public std::enable_shared_from_this<Connection>
{
public:
    typedef boost::asio::ip::tcp tcp;
    Connection(std::shared_ptr<tcp::socket> socket);
    ~Connection() { std::cout << "Closing connection" << std::endl; }
    void run();

    static std::shared_ptr<Connection> create(std::shared_ptr<tcp::socket> socket) { return std::make_shared<Connection>(socket); }
    tcp::socket& getSocket() { return *m_socket; }
    void registerReceiver(std::shared_ptr<MessageReceiver> receiver);
private:
    void handleRequest(const boost::system::error_code &error, std::size_t bytes_received);
    std::vector<SerializedMessage> m_buffer;
    std::shared_ptr<tcp::socket> m_socket;
    std::shared_ptr<MessageReceiver> m_receiver;
};

#endif // CONNECTION_H
