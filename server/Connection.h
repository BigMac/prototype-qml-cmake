#ifndef CONNECTION_H
#define CONNECTION_H
#include <boost/asio.hpp>
#include <memory>

class Connection : public std::enable_shared_from_this<Connection>
{
public:
    typedef boost::asio::ip::tcp tcp;
    Connection(boost::asio::io_service& io_service);
    void start();
    tcp::socket& getSocket() { return m_socket; }

private:
    tcp::socket m_socket;
};

#endif // CONNECTION_H
