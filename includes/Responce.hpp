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

struct Responce
{
	Responce();
	// Responce(const Request &req);
	Request req;

	void 	start(const ServerParam &file, const Request& req);
	void	static_handle();
};


#endif