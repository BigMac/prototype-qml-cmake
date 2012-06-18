#ifndef COMMONCONNECTION_H
#define COMMONCONNECTION_H
#include "CommonApi.h"
#include <boost/asio.hpp>
#include <memory>

class Message;
class CommonConnectionListener;
class DLL_SPEC CommonConnection : public std::enable_shared_from_this<CommonConnection>
{
public:
    typedef boost::asio::ip::tcp tcp;
    CommonConnection(std::shared_ptr<tcp::socket> socket,
                     std::shared_ptr<CommonConnectionListener> listener);
    virtual ~CommonConnection();
    void registerListener(std::shared_ptr<CommonConnectionListener> listener);

    void connected();
    size_t write(Message& message);
    void beginReceive();
    static std::shared_ptr<CommonConnection> create(std::shared_ptr<tcp::socket> socket,
                                                    std::shared_ptr<CommonConnectionListener> listener = std::shared_ptr<CommonConnectionListener>());
protected:
    void sizeReceived(const boost::system::error_code& ec,
                      std::size_t bytes);
    void dataReceived(const boost::system::error_code& ec,
                      std::size_t bytes);
    std::shared_ptr<tcp::socket> m_socket;
    std::shared_ptr<CommonConnectionListener> m_listener;
    std::vector<size_t> m_inboundMessageSize;
    std::vector<char> m_inboundBuffer;
    //std::string m_outboundData;
};

#endif // COMMONCONNECTION_H
