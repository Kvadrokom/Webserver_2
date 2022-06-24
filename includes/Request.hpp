#ifndef RESPONDER_H
#define RESPONDER_H

#include <map>
#include <list>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include "Client.hpp"
#include <string>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>

struct Request
{
	std::string					method;
	std::string					Connection;
	int							Content_Length;
	Client						client;
	std::vector<std::string> 	arr;
	std::string					buf;

	Request();
	Request(Client& client);
	~Request();
	void	start();
};

#endif