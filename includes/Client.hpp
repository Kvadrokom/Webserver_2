#ifndef CLIENT_H
#define CLIENT_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <string>
#include "Request.hpp"
#include "Responce.hpp"
#include "ServerParam.hpp"
// enum ClientState
// {
// 	CLIENT_DEFAULT,
// 	CLIENT_START,
// 	CLIENT_RECEIVE_REQUEST,
// 	CLIENT_SEND_DATA,
// 	CLIENT_TERMINATED
// };

struct Client 
{
	int 						sock;
	char						accept[1024];
	// std::string					sendto;
	std::vector < std::string> 	arr;
	int 						fd;
	// ClientState 				state;
	// ClientStatusCode			status;
	Request						req;
	Responce					answer;
	ServerParam					param;
	Client();
	Client(int sock, int fd, const ServerParam& param);
	void recieve_req();
	bool operator<(const Client c) const;
	void init();
};

#endif