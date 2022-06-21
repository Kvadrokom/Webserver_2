#include "Server.hpp"

bool	Server::make_nonblocking(int sock) 
{
	int yes = 1;
	const int result = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	if (result < 0) 
	{
		return false;
	}
	return true;
}

Server::Server(int port)
{
	this->port = port;
}

int	Server::setup(int backlog)
{
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		return 0;
	if (!make_nonblocking(sock))
		return 0;
	int res = bind(sock, (sockaddr *)&address, sizeof address);
	if (res < 0)
		return 0;
	if (listen(sock, backlog) < 0)
		return 0;
	return 1;
}

int Server::getSock() const { return sock; }

Server::~Server(){};