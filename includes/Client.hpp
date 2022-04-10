#ifndef CLIENT_H
#define CLIENT_H

#include "ASocket.hpp"

enum ClientState 
{
	CLIENT_RECEIVE_REQUEST,
	CLIENT_SEND_FILE,
	CLIENT_SEND_DATA,
	CLIENT_TERMINATED
};

struct Client 
{
	int 		channel;
	sockaddr_in peer;
};

#endif