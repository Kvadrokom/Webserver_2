#ifndef SERVER_H
#define SERVER_H

#include "AServer.hpp"
#include <vector>
#include <string>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <set>
#include "Client.hpp"
#include <fstream>
#include "ListeningSocket.hpp"
#include <sstream>
#include <fcntl.h>
#include "Parser_conf.hpp"

class Server
{
private:
	int					sock;
	int					port;
	struct sockaddr_in 	address;

public:
	bool	make_nonblocking(int sock);
	int 	getSock() const;
	int 	setup();
	Server(int port);
	~Server();
};


#endif