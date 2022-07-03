#ifndef SERVERPARAM_H
#define SERVERPARAM_H

#include <vector>
#include <iostream>
#include <string>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <set>
#include <fstream>
#include <sstream>
#include <fcntl.h>
#include "LocationData.hpp"

class ServerParam
{
	int 						port;
	std::vector<LocationData>	location;

	public:
		ServerParam(int port_, std::vector<LocationData>& location_);
		ServerParam();
		~ServerParam();

		std::vector<LocationData> &getLocation();
		void setPort(int port);
		int getPort() const;
};

#endif