#include "Parser_conf.hpp"

Parser_conf::Parser_conf(const char* conf):servers(0), pars(), loc_size(0)
{
	std::ifstream 	f(conf);
	
	if (f.good())
	{
		std::vector<std::string> parse((std::istream_iterator<std::string>(f)),
								   std::istream_iterator<std::string>());
		this->pars = parse;
		for (unsigned long k = 0; k < pars.size(); k++)
		{
			if (pars[k] == "location")
			loc_size++;
		}
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
		servers = new ServerParam[n];
		for (size_t i = 0; i < pars.size(); i++)
		{
			if (pars[i] == "server")
				parser_server(i);
		}	
	}
}

void	Parser_conf::parser_server(int i)
{
	static int j;
	// for (size_t i = 0; i < pars.size(); i++)
	// {
	// 	if (pars[i] == "server" && pars[i + 1] == "{")
	// 	{
	// 		if (pars[i + 2] == "listen")
	// 			servers[j].port = atoi(pars[i + 3].c_str());
	// 		parser_location(i, &servers[j]);
	// 		j++;
	// 	}
	// }
	if (servers)
	{
		i++;
		for (; (unsigned long)i < pars.size() && pars[i] != "server"; i++)
		{
			if (pars[i] == "listen")
			{
				servers[j].setPort(atoi(pars[i + 1].c_str()));
				j++;
			}
			else if (pars[i] == "location")
				parser_location(i, &servers[j]);
		}
	}
}

void	Parser_conf::parser_location(int i, ServerParam* servers)
{
	// size_t j = i + 1;
	// while (pars[j] != "server" && j < pars.size())
	// {
	// 	if (pars[j] == "location")
	// 		servers->location.push_back(pars[j + 1]);
	// 	j++;
	// }
	static int j;

	LocationData* loc = new LocationData[loc_size];
	for (; (unsigned long)i < pars.size() && pars[i] != "server"; i++)
	{
		if (pars[i] == "location")
		{
			loc[j].setPath(pars[i + 1]);
			for (unsigned long x = i + 1; x < pars.size() && pars[x] != "location"; x++)
			{
				if (pars[x] == "root")
					loc->setRoot(pars[x + 1]);
				else if (pars[x] == "method")
					loc->setMethod(pars[x + 1]);
			}
			servers->getLocation().push_back(loc[j++]);
		}	
	}
}

Parser_conf::~Parser_conf() { delete[] servers; }

ServerParam* Parser_conf::getServers() { return servers; }