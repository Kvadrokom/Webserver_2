#ifndef HSERVER_H
#define HSERVER_H

#include <map>
#include <list>
#include "Server.hpp"
#include "Parser_conf.hpp"
#include "LocationData.hpp"
#include "ServerParam.hpp"

class Http_server
{
private:
	char						arr[1024];
	int							new_socket;
	std::list<Client> 			clients;
	std::map<int, ServerParam> 	servers;
	fd_set 						readset;
	fd_set 						writeset;
	// fd_set 						masterset;
	int							mx;
	int							backlog;
	Parser_conf					conf;
	std::vector<Server *>		server_pull;
	// timeval 					timeout;

	void handler(int fd);
	void responder(int fd, std::string content, int errorCode);

public:
	Http_server(int backlog, const Parser_conf& conf);
	int	setServ(Parser_conf &conf);
	~Http_server();
	void clear();
	void launch();
	void clear_set();
};

#endif