#include "Request.hpp"

Request::Request(Client& client):client(client)
{
	std::istringstream iss(client.accept);
	std::vector<std::string> arr((std::istream_iterator<std::string>(iss)),
									std::istream_iterator<std::string>());
	if (arr.size() > 3)
	{
		method = arr[0];
		for(size_t i = 0; i < arr.size(); ++i)
		{
			if (arr[i] == "Connection:")
				Connection = arr[i + 1];
			if (arr[i] == "Content-Length:")
				Content_Length = std::atoi(arr[i + 1].c_str());
		}
	}
}

Request::Request():client(), arr(){};

Request::~Request(){}

void	Request::start()
{
	
}