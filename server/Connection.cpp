#include "Connection.h"

#include "Message.h"
#include "MessageReceiver.h"
#include <iostream>
#include <cassert>
//#include <boost/bind.hpp>
#include <deque>

Connection::Connection(std::shared_ptr<tcp::socket> socket) :
    m_buffer(10), m_socket(socket), m_receiver(new MessageReceiver())
{
    std::cout << "Connection created" << std::endl;
}

void Connection::run()
{
    m_socket->async_receive(boost::asio::buffer(m_buffer),
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
        if(m_receiver)
            m_buffer.back()->accept(*m_receiver);
//        std::cout << "Got request from client: " << &m_buffer[0] << std::endl;
//        std::cout << "Sending echo" << std::endl;
//        size_t bytes_sent = boost::asio::write(*m_socket, boost::asio::buffer(m_buffer));
//        assert(bytes_sent == m_buffer.size());
    }
    if(!error)
        run();
}

void Connection::registerReceiver(std::shared_ptr<MessageReceiver> receiver)
{
    m_receiver = receiver;
}
