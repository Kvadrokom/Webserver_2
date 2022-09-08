#include "ServerParam.hpp"

ServerParam::ServerParam(int port_, std::vector<LocationData>& location_):
						port(port_), location(location_)
{
	std::cout <<"Call constructor from ServerParam\n\n";
};

ServerParam::ServerParam(): port(0), location()
{
	std::cout <<"Call default constructor from ServerParam\n\n";
};
ServerParam::~ServerParam(){std::cout <<"Call destructor from ServerParam\n\n";};

int ServerParam::getPort() const { return port; }
void ServerParam::setPort(int port_) { port = port_; }
std::vector<LocationData>& ServerParam::getLocation() { return location; }