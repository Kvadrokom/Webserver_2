#include "AServer.hpp"

AServer::AServer(int port, int backlog)
{
	listen_socket = new ListeningSocket(port, backlog);
}

ListeningSocket* AServer::getsocket() { return listen_socket; }

AServer::~AServer() { delete listen_socket; }