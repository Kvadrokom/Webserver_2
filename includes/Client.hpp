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

struct Client 
{
	int 						sock;
	char						accept[1024];
	std::vector < std::string> 	arr;
	int 						fd;
	Request						req;
	Responce					answer;
	ServerParam					param;
	std::string					buffer;
	Client();
	Client(int sock, int fd, const ServerParam& param);
	void recieve_req(std::string str);
	bool operator<(const Client c) const;
	void init();
};

#endif