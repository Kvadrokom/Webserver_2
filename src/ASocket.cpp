#include "ASocket.hpp"

ASocket::ASocket(int port)
{
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	test_connection(sock);
}

ASocket::ASocket(){};

int	ASocket::test_connection(int item_to_test)
{
	if (item_to_test < 0)
	{
		perror("Failed to connect...");
		return (0);
	}
	return (1);
}

struct sockaddr_in& 	ASocket::get_address(){return address;}

int	ASocket::get_sock(){return sock;}

ASocket::~ASocket(){};