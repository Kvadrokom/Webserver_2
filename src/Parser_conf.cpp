#include "Parser_conf.hpp"

Parser_conf::Parser_conf(const char* conf):servers(0), pars(), loc_size(0), serv_size(0),
											loc(NULL)
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
			else if (pars[k] == "server")
				serv_size++;
		}
		servers = new ServerParam[serv_size];
		loc = new LocationData[loc_size];
		parser_location();
		parser_server();
	}
}

Parser_conf::Parser_conf(): servers(0), pars(), loc_size(0), serv_size(0),
											loc(NULL){};

void	Parser_conf::parser_server()
{
	int j = 0;
	// size_t count = 0;
	size_t k = 0;

	if (servers)
	{
		for (size_t i = 0; i < pars.size(); i++)
		{
			if (pars[i] == "listen")
			{
				servers[j++].setPort(atoi(pars[i + 1].c_str()));
			}
		}
		j = -1;
		for (size_t i = 0; i < pars.size(); i++)
		{
			if (pars[i] == "location")
			{
				getServers()[j].getLocation().push_back(loc[k]);
				k++;
			}
			else if (pars[i] == "server")
				j++;
		}
	}
}

void	Parser_conf::parser_location()
{
	int j = 0;
	for (size_t i = 0; i < pars.size(); i++)
	{
		if (pars[i] == "location")
		{
			loc[j].setPath(pars[i + 1]);
			for (unsigned long x = i + 1; x < pars.size() && pars[x] != "location"; x++)
			{
				if (pars[x] == "root")
					loc[j].setRoot(pars[x + 1]);
				else if (pars[x] == "method")
				{
					for (size_t k = x + 1; pars[k] != "$"; k++)
					{
						loc[j].setMethod(pars[x + 1]);
					}					
				}
				else if (pars[x] == "server_name")
					loc[j].setName(pars[x + 1]);
				else if (pars[x] == "max_body")
					loc[j].setMaxBody(atoi(pars[x + 1].c_str()));
			}
			j++;
		}
	}
}

Parser_conf::~Parser_conf() { delete[] servers; }

ServerParam* Parser_conf::getServers() { return servers; }

size_t Parser_conf::get_locsize() const{ return loc_size; }

size_t 		Parser_conf::get_servsize() const{ return serv_size; }

LocationData *Parser_conf::get_loc() { return loc; }