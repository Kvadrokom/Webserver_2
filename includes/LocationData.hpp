#ifndef LOCATIONDATA_H
#define LOCATIONDATA_H

#include "Http_server.hpp"


class LocationData
{
	std::string path;
	std::string root;
	std::string method;

	public:
		LocationData();
		LocationData(std::string& path_, std::string &root_, std::string &method_);
		~LocationData();

		void setPath(const std::string &path);
		void setRoot(const std::string &root);
		void setMethod(const std::string &method);

		std::string getMethod() const;
		std::string getRoot() const;
		std::string getPath() const;
};

#endif