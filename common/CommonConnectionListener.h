#ifndef COMMONCONNECTIONLISTENER_H
#define COMMONCONNECTIONLISTENER_H
#include <boost/system/error_code.hpp>

class SerializedMessage;
class CommonConnection;
class CommonConnectionListener
{
public:
    virtual void onMessageReceived(CommonConnection& connection,
                                   SerializedMessage& message) = 0;
    virtual void onMessageReceivedErrror(CommonConnection& connection,
                                         const boost::system::error_code& ec) = 0;
    virtual void onConnected(CommonConnection& connection) = 0;
    virtual ~CommonConnectionListener() {}
};

#endif // COMMONCONNECTIONLISTENER_H
