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
		ASocket(int domain, int service, int protocol, int port, u_long interface);
		virtual int connect_to_network(int sock, struct sockaddr_in address) = 0;
		void	test_connection(int);
		virtual ~ASocket();
		ASocket();

		struct sockaddr_in 	get_address();
		int					get_sock();
		int					get_connection();

};

#endif