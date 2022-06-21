#ifndef RESPONCE_H
#define RESPONCE_H

#include <string>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Client.hpp"

struct Responce
{
	std::string	head;
	void	heading(const int content_size, const std::string &file);
	void	static_handle();
};


#endif