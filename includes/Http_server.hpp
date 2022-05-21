#ifndef HSERVER_H
#define HSERVER_H

// #include "AServer.hpp"
// #include <vector>
// #include <string>
// #include <sys/time.h>
// #include <sys/types.h>
// #include <unistd.h>
#include <map>
// #include "Client.hpp"
// #include <fstream>
// #include "BindingSocket.hpp"
// #include <sstream>
// #include <fcntl.h>
// #include "Parser_conf.hpp"
class Parser_conf;
// #include "Parser_conf.hpp"
#include "Server.hpp"

class Http_server
{
private:
	char						arr[1024];
	int							new_socket;
	std::set<Client> 			clients;
	std::map<int, ServerParam> 	servers;
	fd_set 						readset;
	fd_set 						writeset;
	fd_set 						masterset;
	int							mx;
	int							backlog;
	// Parser_conf					conf;
	// timeval 					timeout;

	void handler(int fd);
	void responder(int fd, std::string content, int errorCode);

public:
	Http_server(int backlog);
	int	setServ(Parser_conf &conf);
	~Http_server();
	void clear();
	void launch();
};




#endif