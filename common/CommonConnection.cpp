#include "CommonConnection.h"
#include "CommonConnectionListener.h"
#include "Message.h"
#include "messages/ResourceRequest.h"
#include "messages/ResourceResponse.h"
#include <cassert>

CommonConnection::CommonConnection(std::shared_ptr<tcp::socket> socket,
                 std::shared_ptr<CommonConnectionListener> listener) :
    m_socket(socket), m_listener(listener), m_inboundMessageSize(1)
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
    m_socket->async_receive(boost::asio::buffer(m_inboundMessageSize),
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
    m_inboundBuffer.resize(m_inboundMessageSize[0]);
    m_socket->async_receive(boost::asio::buffer(m_inboundBuffer),
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
        std::cout << "Data received: " << std::string(m_inboundBuffer.begin(), m_inboundBuffer.end()) << std::endl;
        std::string archiveData(m_inboundBuffer.begin(), m_inboundBuffer.end());
        std::istringstream archiveStream(archiveData);
        boost::archive::text_iarchive archive(archiveStream);
        Message* rawMsg(NULL);
        archive >> rawMsg;
        std::shared_ptr<Message> msg(rawMsg);
        m_listener->onMessageReceived(*this, msg);
        beginReceive();
    }
    else
    {
        std::cout << "dataReceived: " << ec.message() << std::endl;
    }
}

size_t CommonConnection::write(Message &message)
{
    std::ostringstream archiveStream;
    boost::archive::text_oarchive archive(archiveStream);
    Message* rawMsg = &message;
    archive << rawMsg;

    std::string outboundData = archiveStream.str();

    std::cout << "Sending " << outboundData << std::endl;
    boost::array<size_t, 1> outboundDataSize;
    outboundDataSize[0] = outboundData.size();
    std::vector<boost::asio::const_buffer> dataToSend;
    dataToSend.push_back(boost::asio::buffer(outboundDataSize));
    dataToSend.push_back(boost::asio::buffer(outboundData));
    return boost::asio::write(*m_socket, dataToSend);
}

std::shared_ptr<CommonConnection> CommonConnection::create(
        std::shared_ptr<tcp::socket> socket,
        std::shared_ptr<CommonConnectionListener> listener)
{
    return std::make_shared<CommonConnection>(socket, listener);
}
