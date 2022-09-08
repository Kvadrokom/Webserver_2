#include "LocationData.hpp"

LocationData::LocationData():path(), root(), method(), server_name(), max_body(-1)
{
	std::cout <<"Call default constructor from LocationData\n\n";
};

// LocationData::LocationData(){};

LocationData::~LocationData(){std::cout <<"Call destructor from LocationData\n\n";};

void LocationData::setPath(const std::string &path_){ path = path_; }
void LocationData::setName(const std::string &name){ server_name = name; }
void LocationData::setRoot(const std::string &root_) { root = root_; }
void LocationData::setMethod(const std::string &method_) { method = method_; }
void LocationData::setMaxBody(int max_body){this->max_body = max_body;}

std::string LocationData::getMethod() const { return method; }
std::string LocationData::getRoot() const { return root; }
std::string LocationData::getPath() const { return path; }
std::string LocationData::getName() const { return server_name; }
int	LocationData::getMaxBody() const {return max_body;}

