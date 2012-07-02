#include "ConnectionListener.h"
#include "CommonConnection.h"
#include "ResourceRepositoryService.h"
#include "ResourceRepositoryFsmEvents.h"

ConnectionListener::ConnectionListener(std::shared_ptr<boost::recursive_mutex> processEventMutex) :
    m_processEventMutex(processEventMutex)
{}


void ConnectionListener::setService(ResourceRepositoryService& service)
{
    m_service = service;
}

void ConnectionListener::onMessageReceived(CommonConnection& connection,
                       std::shared_ptr<Message> message)
{
    m_connection = connection;
    message->accept(*this);
}

void ConnectionListener::receive(ResourceResponse & msg)
{
    boost::mutex::scoped_lock(*m_processEventMutex);
    m_service.process_event(msg);
}

void ConnectionListener::onMessageReceivedErrror(CommonConnection& connection,
                             const boost::system::error_code& ec)
{
    m_connection = connection;
    // TODO error handling
}

void ConnectionListener::onConnected(CommonConnection& connection)
{
    m_connection = connection;
    boost::mutex::scoped_lock(*m_processEventMutex);
    m_service.process_event(Connected(connection));
}
