#ifndef BSOCKET_H
#define BSOCKET_H

#include "ASocket.hpp"

class BindingSocket: public ASocket
{
private:
	int		connection;

public:
	BindingSocket(int domain, int service, int protocol, int port,
				u_long interface);
	~BindingSocket();
	BindingSocket();

	int connect_to_network(int sock, struct sockaddr_in address);
	void set_connection(int connect);
	int get_connection();
};

#endif