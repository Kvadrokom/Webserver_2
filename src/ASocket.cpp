#include "ASocket.hpp"

ASocket::ASocket(int domain, int service, int protocol, int port, u_long interface)
{
	address.sin_family = domain;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(interface);
	sock = socket(domain, service, protocol);
	test_connection(sock);
}

ASocket::ASocket(){};

void	ASocket::test_connection(int item_to_test)
{
	if (item_to_test < 0)
	{
		perror("Failed to connect...");
		exit(EXIT_FAILURE);
	}
}

struct sockaddr_in 	ASocket::get_address(){return address;}

int	ASocket::get_sock(){return sock;}

ASocket::~ASocket(){};