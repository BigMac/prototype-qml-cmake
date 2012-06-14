#ifndef COMMONCONNECTION_H
#define COMMONCONNECTION_H
#include "SerializedMessage.h"
#include <boost/asio.hpp>
#include <memory>

class CommonConnectionListener;
class CommonConnection : public std::enable_shared_from_this<CommonConnection>
{
public:
    typedef boost::asio::ip::tcp tcp;
    CommonConnection(std::shared_ptr<tcp::socket> socket,
                     std::shared_ptr<CommonConnectionListener> listener);
    virtual ~CommonConnection();
    void registerListener(std::shared_ptr<CommonConnectionListener> listener);

    void connected();
    size_t write(SerializedMessage& serializedMessage);
    void beginReceive();
    static std::shared_ptr<CommonConnection> create(std::shared_ptr<tcp::socket> socket,
                                                    std::shared_ptr<CommonConnectionListener> listener = std::shared_ptr<CommonConnectionListener>());
protected:
    void sizeReceived(const boost::system::error_code& ec,
                      std::size_t bytes);
    void typeReceived(const boost::system::error_code& ec,
                      std::size_t bytes);
    void dataReceived(const boost::system::error_code& ec,
                      std::size_t bytes);
    std::shared_ptr<tcp::socket> m_socket;
    std::shared_ptr<CommonConnectionListener> m_listener;
    SerializedMessage m_inboundMessage;

};

#endif // COMMONCONNECTION_H
