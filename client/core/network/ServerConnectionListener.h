#ifndef SERVERCONNECTIONLISTENER_H
#define SERVERCONNECTIONLISTENER_H
#include <vector>
#include <boost/system/error_code.hpp>

class ServerConnectionListener
{
public:
    virtual void onDataReceived(ServerConnection* connection, std::vector<char> data) = 0;
    virtual void onConnected(ServerConnection* connection, const boost::system::error_code& ec) = 0;
    virtual ~ServerConnectionListener() {}
};

#endif // SERVERCONNECTIONLISTENER_H
