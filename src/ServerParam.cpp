#include "ServerParam.hpp"

ServerParam::ServerParam(int port_, std::vector<LocationData>& location_):
						port(port_), location(location_){};

ServerParam::ServerParam(): port(0), location(){};
ServerParam::~ServerParam(){};

int ServerParam::getPort() { return port; }
void ServerParam::setPort(int port_) { port = port_; }
std::vector<LocationData>& ServerParam::getLocation() { return location; }
