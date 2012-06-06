#ifndef CONNECTION_H
#define CONNECTION_H
#include <boost/asio.hpp>
//#include <boost/enable_shared_from_this.hpp>
#include <functional>
#include <memory>

class Connection : public std::enable_shared_from_this<Connection>
{
public:
    typedef boost::asio::ip::tcp tcp;
    Connection(std::shared_ptr<tcp::socket> socket);
    ~Connection() { std::cout << "Closing connection" << std::endl; }
    void run();

    static std::shared_ptr<Connection> create(std::shared_ptr<tcp::socket> socket) { return std::make_shared<Connection>(socket); }
    tcp::socket& getSocket() { return *m_socket; }
private:
    void handleRequest(const boost::system::error_code &error, std::size_t bytes_received);
    std::vector<char> m_buffer;
    std::shared_ptr<tcp::socket> m_socket;
};

#endif // CONNECTION_H
