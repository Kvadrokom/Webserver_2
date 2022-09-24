#ifndef RESPONCE_H
#define RESPONCE_H

#include <string>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include "Request.hpp"
#include <iostream>
#include "ServerParam.hpp"


enum STATE
{
	START,
	PREPARING,
	READY,
	DONE
};

struct Responce
{
	std::string			head;
	std::string			body;
	std::string			responce_code;
	std::string 		content;
	std::string 		response_;
	std::string 		www;
	std::string 		root;
	STATE 				state;
	int					code_number;
	Request 			req;

	Responce();	

	void 		start(ServerParam &file, Request& req,
					std::map<std::string, std::string> errors);
	int			check_req(ServerParam &file, Request& req);
	void		Responce_get(Request& req, std::map <std::string, std::string> errors);
	void		Responce_post(Request& req, std::map <std::string, std::string> errors);
	void		Responce_del(Request& req, std::map <std::string, std::string> errors);
	int			check_entity(ServerParam &file, Request& req, int i);
	void 		bad_request(Request& req, std::map <std::string, std::string> errors);
	void		make_answer();
	std::string	responce_answer(int state);
	void	init();
};

#endif