#include "LocationData.hpp"

LocationData::LocationData(std::string& path_, std::string& root_, std::string& method_):
						path(path_), root(root_), method(method_){};

LocationData::LocationData(){};

LocationData::~LocationData(){};

void LocationData::setRoot(const std::string &root_) { root = root_; }

void LocationData::setMethod(const std::string &method_) { method = method_; }

std::string LocationData::getMethod() const { return method; }
std::string LocationData::getRoot() const { return root; }
std::string LocationData::getPath() const { return path; }

void LocationData::setPath(const std::string &path_){ path = path_; }
