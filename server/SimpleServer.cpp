#include "SimpleServer.h"
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <string>

SimpleServer::SimpleServer()
{
}

void SimpleServer::startListening()
{
    typedef boost::asio::ip::tcp tcp;
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 6666));

    for(;;)
    {
        tcp::socket socket(io_service);
        acceptor.accept(socket);
        std::string message("message 42");
        boost::asio::write(socket, boost::asio::buffer(message));
    }
}
