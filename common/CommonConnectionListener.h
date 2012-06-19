#ifndef COMMONCONNECTIONLISTENER_H
#define COMMONCONNECTIONLISTENER_H
#include <boost/system/error_code.hpp>
#include <memory>

class Message;
class CommonConnection;
class CommonConnectionListener
{
public:
    virtual void onMessageReceived(CommonConnection& connection,
                                   std::shared_ptr<Message> message) = 0;
    virtual void onMessageReceivedErrror(CommonConnection& connection,
                                         const boost::system::error_code& ec) = 0;
    virtual void onConnected(CommonConnection& connection) = 0;
    virtual void onClose(CommonConnection& connection) throw () = 0;
    virtual ~CommonConnectionListener() {}
};

#endif // COMMONCONNECTIONLISTENER_H
