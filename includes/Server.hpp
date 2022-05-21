#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <iostream>
#include <string>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <set>
#include "Client.hpp"
#include <fstream>
#include <sstream>
#include <fcntl.h>
#include "Parser_conf.hpp"
#include <netinet/in.h>

class Server
{
private:
	int					sock;
	int					port;
	struct sockaddr_in 	address;

public:
	bool	make_nonblocking(int sock);
	int 	getSock() const;
	int 	setup(int backlog);
	Server(int port);
	~Server();
};


#endif