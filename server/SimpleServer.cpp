#include "SimpleServer.h"
#include <string>
#include "Connection.h"

SimpleServer::SimpleServer() : m_acceptor(m_ioService, tcp::endpoint(tcp::v4(), 6666))
{}

void SimpleServer::startListening()
{
    startAccept();
    m_ioService.run();
}

void SimpleServer::startAccept()
{
    auto newConnection = std::make_shared<Connection>(m_ioService);

    m_acceptor.async_accept(newConnection->getSocket(),
                            [&](const boost::system::error_code& error){
                            handleAccept(newConnection,
                                         error); });
}

void SimpleServer::handleAccept(std::shared_ptr<Connection> newConnection,
                                const boost::system::error_code& error)
{
    if(!error)
        newConnection->start();
    startAccept();
}
