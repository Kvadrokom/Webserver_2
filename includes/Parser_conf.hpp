#ifndef PARSER_H
#define PARSER_H

#include "Http_server.hpp"

struct server_param
{
	int							port;
	std::vector<std::string>	location;
};

class Parser_conf
{
private:
	server_param*				servers;
	std::vector<std::string>	pars;

public:
	Parser_conf(const char *conf);
	void parser_config();
	void parser_server();
	void parser_location(int i, server_param* servers);

	server_param* getServers();
	~Parser_conf();
};


#endif