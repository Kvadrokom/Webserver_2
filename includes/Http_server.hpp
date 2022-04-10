#ifndef HSERVER_H
#define HSERVER_H

#include "AServer.hpp"
#include <vector>
#include <string>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <set>
#include "Client.hpp"
#include <fstream>
#include "BindingSocket.hpp"
#include <sstream>
#include <fcntl.h>

class Http_server: AServer
{
private:
	char			arr[1024];
	int				new_socket;
	std::set<int> 	clients;
	fd_set 			readset;
	int				mx;
	// timeval 		timeout;
	int				sock_sv;

	void accepter();
	void handler(int fd);
	void responder(int fd, std::string content, int errorCode);

public:
	Http_server();
	Http_server(int domain, int service, int protocol, int port,
				u_long interface, int backlog);
	~Http_server();

	void launch();
};




#endif