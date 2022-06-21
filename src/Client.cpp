#include "Client.hpp"

Client::Client(int sock, int fd, ClientState state) : sock(sock), fd(fd), state(state)
{
	init();
}

Client::Client():sock(-1), fd(-1), state(CLIENT_DEFAULT)
{
	init();
}


bool Client::operator < (const Client c) const { return fd < c.fd; }

void Client::init()
{
	for (size_t i = 0; i < 1024; i++)
	{
		accept[i] = '\0';
		sendto[i] = '\0';
	}
		
}