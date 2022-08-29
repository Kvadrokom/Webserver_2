#ifndef PARSER_H
#define PARSER_H


#include "LocationData.hpp"
#include <iostream>
#include <sstream>
#include <iterator>
#include "ServerParam.hpp"
#include <cstdlib>

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

		void parser_server();
		void parser_location();

		size_t 			get_locsize() const;
		ServerParam 	*getServers();
		size_t 			get_servsize() const;
		LocationData *	get_loc();

};

#endif