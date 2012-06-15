#include "CommonConnection.h"
#include "CommonConnectionListener.h"
#include "Message.h"
#include "SerializedMessage.h"
#include <cassert>

CommonConnection::CommonConnection(std::shared_ptr<tcp::socket> socket,
                 std::shared_ptr<CommonConnectionListener> listener) :
    m_socket(socket), m_listener(listener)
{
}

CommonConnection::~CommonConnection()
{
    std::cout << "Disconnected" << std::endl;
}

void CommonConnection::registerListener(std::shared_ptr<CommonConnectionListener> listener)
{
    m_listener = listener;
}

void CommonConnection::connected()
{
    assert(m_listener);
    m_listener->onConnected(*this);
    beginReceive();
}

void CommonConnection::beginReceive()
{
    m_inboundMessage = SerializedMessage();
    m_socket->async_receive(boost::asio::buffer(m_inboundMessage.data_size),
                           std::bind(&CommonConnection::sizeReceived,
                                     shared_from_this(),
                                     std::placeholders::_1,
                                     std::placeholders::_2)
                           );
}

void CommonConnection::sizeReceived(const boost::system::error_code& ec,
                  std::size_t bytes)
{
    if (bytes == 0 || ec)
    {
        std::cout << "Received: "<< ec.message() << std::endl;
        m_listener->onMessageReceivedErrror(*this, ec);
        return;
    }
    m_inboundMessage.prepareForReceive();
    m_socket->async_receive(boost::asio::buffer(m_inboundMessage.message_type),
                           std::bind(&CommonConnection::typeReceived,
                                     shared_from_this(),
                                     std::placeholders::_1,
                                     std::placeholders::_2)
                           );
}

void CommonConnection::typeReceived(const boost::system::error_code& ec,
                  std::size_t bytes)
{
    if(ec)
    {
        std::cout << "typeReceived: " << ec.message() << std::endl;
        return;
    }
    m_socket->async_receive(boost::asio::buffer(m_inboundMessage.data),
                           std::bind(&CommonConnection::dataReceived,
                                     shared_from_this(),
                                     std::placeholders::_1,
                                     std::placeholders::_2)
                           );
}

void CommonConnection::dataReceived(const boost::system::error_code &ec,
                                    std::size_t bytes)
{
    if(!ec)
    {
        m_listener->onMessageReceived(*this, m_inboundMessage);
        m_inboundMessage = SerializedMessage();
        beginReceive();
    }
    else
    {
        std::cout << "dataReceived: " << ec.message() << std::endl;
    }
}

size_t CommonConnection::write(SerializedMessage& serializedMessage)
{
    std::cout << "Sending " << serializedMessage.getTypeDiscriminator() << std::endl;
    serializedMessage.prepareForSend();
    std::vector<boost::asio::const_buffer> dataToSend;
    dataToSend.push_back(boost::asio::buffer(serializedMessage.data_size));
    dataToSend.push_back(boost::asio::buffer(serializedMessage.message_type));
    dataToSend.push_back(boost::asio::buffer(serializedMessage.data));
    return boost::asio::write(*m_socket, dataToSend);
}

std::shared_ptr<CommonConnection> CommonConnection::create(
        std::shared_ptr<tcp::socket> socket,
        std::shared_ptr<CommonConnectionListener> listener)
{
    return std::make_shared<CommonConnection>(socket, listener);
}
