#ifndef BSOCKET_H
#define BSOCKET_H

#include "ASocket.hpp"

class BindingSocket: public ASocket
{
private:
	int		connection;

public:
	BindingSocket(int port);
	~BindingSocket();
	BindingSocket();

	int connect_to_network(int sock, struct sockaddr_in address);
	void set_connection(int connect);
	int get_connection();
};

#endif