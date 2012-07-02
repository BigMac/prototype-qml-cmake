#ifndef CONNECTIONLISTENER_H
#define CONNECTIONLISTENER_H

#include "CommonConnectionListener.h"
#include "messages/MessageReceiver.h"
#include <boost/thread.hpp>

class ResourceRepositoryService;

class ConnectionListener :
        public CommonConnectionListener,
        public MessageReceiver
{
public:
    ConnectionListener(std::shared_ptr<boost::recursive_mutex> processEventMutex);

    void setService(ResourceRepositoryService& service);

    virtual void onMessageReceived(CommonConnection& connection,
                                   std::shared_ptr<Message> message);
    virtual void onMessageReceivedErrror(CommonConnection& connection,
                                         const boost::system::error_code& ec);
    virtual void onConnected(CommonConnection& connection);

    virtual void receive(ResourceResponse & msg);
private:
    std::shared_ptr<boost::recursive_mutex> m_processEventMutex;
    ResourceRepositoryService& m_service;
    CommonConnection& m_connection;
};

#endif // CONNECTIONLISTENER_H
