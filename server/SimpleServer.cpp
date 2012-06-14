#include "SimpleServer.h"
#include "CommonConnection.h"
#include <string>
#include <iostream>

SimpleServer::SimpleServer() : m_acceptor(m_ioService, tcp::endpoint(tcp::v4(), 6666))
{}

void SimpleServer::startListening(std::shared_ptr<CommonConnectionListener> listener)
{
    m_listener = listener;
    std::cout << "Starting listening" << std::endl;
    startAccept();
    m_ioService.run();
}

void SimpleServer::startAccept()
{
    auto socket = std::make_shared<tcp::socket>(m_ioService);

    m_acceptor.async_accept(*socket,
                            std::bind(&SimpleServer::handleAccept,
                                        this,
                                        std::bind(&CommonConnection::create, socket, m_listener),
                                        std::placeholders::_1));
}

void SimpleServer::handleAccept(std::shared_ptr<CommonConnection> newConnection,
                                const boost::system::error_code& error)
{
    if(!error)
    {
        newConnection->connected();
    }
    startAccept();
}
