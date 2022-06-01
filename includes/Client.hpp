#ifndef CLIENT_H
#define CLIENT_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

enum ClientState 
{
	CLIENT_DEFAULT,
	CLIENT_RECEIVE_REQUEST,
	CLIENT_SEND_FILE,
	CLIENT_SEND_DATA,
	CLIENT_TERMINATED
};

struct Client 
{
	int 		sock;
	int 		fd;
	ClientState state;
	Client():sock(-1), fd(-1), state(CLIENT_DEFAULT){};
	Client(int sock, int fd, ClientState state) : sock(sock), fd(fd), state(state){};
	bool operator < (const Client c) const { return fd < c.fd; }
};

#endif