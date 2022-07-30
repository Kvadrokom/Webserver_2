#include "LocationData.hpp"

LocationData::LocationData(std::string& path_, std::string& root_, std::string& method_, std::string& name):
						path(path_), root(root_), method(method_), server_name(name){};

LocationData::LocationData(){};

LocationData::~LocationData(){};

void LocationData::setRoot(const std::string &root_) { root = root_; }

void LocationData::setMethod(const std::string &method_) { method = method_; }

std::string LocationData::getMethod() const { return method; }
std::string LocationData::getRoot() const { return root; }
std::string LocationData::getPath() const { return path; }
std::string LocationData::getName() const { return server_name; }

void LocationData::setPath(const std::string &path_){ path = path_; }

void LocationData::setName(const std::string &name){ server_name = name; }
