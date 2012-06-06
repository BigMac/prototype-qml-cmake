#include "Connection.h"
#include <iostream>
#include <cassert>
//#include <boost/bind.hpp>

Connection::Connection(std::shared_ptr<tcp::socket> socket) : m_buffer(100), m_socket(socket)
{
    std::cout << "Connection created" << std::endl;
}

void Connection::run()
{
    m_socket->async_read_some(boost::asio::buffer(m_buffer),
                             std::bind(&Connection::handleRequest,
                                       shared_from_this(),
                                       std::placeholders::_1,
                                       std::placeholders::_2));
}

void Connection::handleRequest(const boost::system::error_code& error, std::size_t bytes_received)
{
    std::cout << "handleRequest: " << error.message() << std::endl;
    if(bytes_received)
    {
        std::cout << "Got request from client: " << &m_buffer[0] << std::endl;
        std::cout << "Sending echo" << std::endl;
        size_t bytes_sent = boost::asio::write(*m_socket, boost::asio::buffer(m_buffer));
        assert(bytes_sent == m_buffer.size());
    }
    else
    {
        std::cout << "Empty receive" << std::endl;
    }
    if(!error)
        run();
}
