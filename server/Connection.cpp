#include "Connection.h"

#include "Message.h"
#include "MessageReceiver.h"
#include "MessageSerializer.h"
#include "SerializedMessage.h"
#include "QmlRequest.h"
#include <iostream>
#include <cassert>

Connection::Connection(std::shared_ptr<tcp::socket> socket) :
    m_buffer(100), m_socket(socket), m_receiver(new MessageReceiver())
{
    std::cout << "Connection created" << std::endl;
}

void Connection::run()
{
    //boost::asio::async_read(m_socket, boost::asio::buffer(m_buffer),
//    m_socket->async_receive(m_buffer,
//                            std::bind(&Connection::handleRequest,
//                                      shared_from_this(),
//                                      std::placeholders::_1,
//                                      std::placeholders::_2));
}

void Connection::handleRequest(const boost::system::error_code& error, std::size_t bytes_received)
{
//    std::cout << "handleRequest: " << error.message() << std::endl;
//    if(bytes_received)
//    {
//        if(m_receiver)
//        {
//            MessageSerializer serializer;
//            std::cout << "rcvd: " << m_buffer[0].getTypeDiscriminator() << std::endl;
//            auto msg = serializer.deserialize(m_buffer[0]);
//            msg->accept(*m_receiver);
//        }
//    }
//    if(!error)
//        run();
}

void Connection::registerReceiver(std::shared_ptr<MessageReceiver> receiver)
{
    m_receiver = receiver;
}
