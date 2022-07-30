#ifndef LOCATIONDATA_H
#define LOCATIONDATA_H

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


class LocationData
{
	std::string path;
	std::string root;
	std::string method;
	std::string server_name;

	public:
		LocationData();
		LocationData(std::string& path_, std::string &root_, std::string &method_, std::string& name);
		~LocationData();

		void setPath(const std::string &path);
		void setRoot(const std::string &root);
		void setMethod(const std::string &method);
		void setName(const std::string &name);

		std::string getMethod() const;
		std::string getRoot() const;
		std::string getPath() const;
		std::string getName() const;
};

#endif