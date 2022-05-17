#ifndef ASOCKET_H
#define ASOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <iostream>

class ASocket
{
	private:
		int					sock;
		struct sockaddr_in 	address;

	public:
		ASocket(int port);
		ASocket();
		int	test_connection(int);
		~ASocket();

		struct sockaddr_in& 	get_address();
		int						get_sock();
		int						get_connection();

};

#endif