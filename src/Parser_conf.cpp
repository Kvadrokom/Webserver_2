#include "Parser_conf.hpp"

Parser_conf::Parser_conf(const char* conf):servers(0), pars()
{
	std::ifstream 	f(conf);
	
	if (f.good())
	{
		std::vector<std::string> parse((std::istream_iterator<std::string>(f)),
								   std::istream_iterator<std::string>());
		this->pars = parse;
		parser_config();
	}
}

void	Parser_conf::parser_config()
{
	int n = 0;
	for (size_t i = 0; i < pars.size(); i++)
	{
		if (pars[i] == "server" && pars[i + 1] == "{")
		{
			n++;
		}
	}
	if (n)
	{
		servers = new server_param[n];
		parser_server();
	}
}

void	Parser_conf::parser_server()
{
	int j = 0;
	for (size_t i = 0; i < pars.size(); i++)
	{
		if (pars[i] == "server" && pars[i + 1] == "{")
		{
			if (pars[i + 2] == "listen")
				servers[j].port = atoi(pars[i + 3].c_str());
			parser_location(i, &servers[j]);
			j++;
		}
	}
}

void	Parser_conf::parser_location(int i, server_param* servers)
{
	size_t j = i + 1;
	while (pars[j] != "server" && j < pars.size())
	{
		if (pars[j] == "location")
			servers->location.push_back(pars[j + 1]);
		j++;
	}
}

Parser_conf::~Parser_conf() { delete[] servers; }

server_param* Parser_conf::getServers() { return servers; }