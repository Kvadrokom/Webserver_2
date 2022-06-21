#ifndef PARSER_H
#define PARSER_H


#include "LocationData.hpp"
#include "ServerParam.hpp"

class Parser_conf
{
	ServerParam*				servers;
	std::vector<std::string>	pars;
	size_t						loc_size;
	size_t						serv_size;
	LocationData*				loc;
	

	public:
		Parser_conf(const char *conf);
		Parser_conf();
		~Parser_conf();

		// void parser_config();
		void parser_server();
		void parser_location();

		size_t 			get_locsize() const;
		ServerParam 	*getServers();
		size_t 			get_servsize() const;
		LocationData *	get_loc();

};

#endif