#include "Client.hpp"

Client::Client(int sock, int fd, const ServerParam& param) : sock(sock), fd(fd), req(), param(param)
{
	init();
}

Client::Client():sock(-1), fd(-1)
{
	init();
}

void	Client::recieve_req(std::string str)
{
	std::istringstream iss(accept);
	std::vector<std::string> arr((std::istream_iterator<std::string>(iss)), 
								std::istream_iterator<std::string>());
	this->arr = arr;
	buffer = str;
}

bool Client::operator < (const Client c) const { return fd < c.fd; }

void Client::init()
{
	for (size_t i = 0; i < 1024; i++)
	{
		accept[i] = '\0';
	}
		
}