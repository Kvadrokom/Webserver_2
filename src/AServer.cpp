#include "AServer.hpp"

AServer::AServer(int domain, int service, int protocol, int port,
				u_long interface, int backlog)
{
	listen_socket = new ListeningSocket(domain, service, protocol, port,
								  interface, backlog);
}

ListeningSocket* AServer::getsocket() { return listen_socket; }

AServer::~AServer() { delete listen_socket; }