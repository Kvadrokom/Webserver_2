#ifndef SERVERPARAM_H
#define SERVERPARAM_H

#include "Http_server.hpp"
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