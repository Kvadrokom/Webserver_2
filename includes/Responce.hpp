#ifndef RESPONCE_H
#define RESPONCE_H

#include <string>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Request.hpp"
#include <iostream>
#include "ServerParam.hpp"


enum STATE
{
	START,
	PREPARING,
	READY,
	DONE,
	CLOSE
};

struct Responce
{
	std::string			head;
	std::string			body;
	std::string			responce_code;
	std::string 		content;
	std::string 		response_;
	std::string 		www;
	STATE 				state;
	int					code_number;
	Request 			req;

	Responce();	

	void 	start(ServerParam &file, Request& req);
	int		check_req(ServerParam &file, Request& req);
	void	Responce_get(Request& req);
	void	Responce_post(Request& req);
	void	Responce_del(Request& req);
	int		check_entity(ServerParam &file, Request& req, int i);
	void 	bad_request(Request& req);
	void	make_answer();
	void	init();
};

#endif