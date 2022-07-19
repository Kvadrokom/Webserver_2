#ifndef REQUEST_H
#define REQUEST_H

#include <map>
#include <list>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <string>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include "Response_code.hpp"

#define CRLF		"\r\n"
#define CRLF_CRLF	"\r\n\r\n"

enum req_stat
{
	// DEF_REQ,
	HEADER,
	BODY,
	END_REQ
};

enum ClientState
{
	CLIENT_DEFAULT,
	CLIENT_START,
	CLIENT_RECEIVE_REQUEST,
	CLIENT_SEND_DATA,
	CLIENT_TERMINATED
};

struct Request
{
	std::string					method;
	std::string					Connection;
	std::string					path;
	int							Content_Length;
	std::vector<std::string> 	arr;
	std::string					buf;
	std::string					Transfer_Encoding;
	req_stat					req_status;
	ClientState					state;
	ClientStatusCode			status;
	std::string					sendto;
	std::string					header;
	std::string					body;
	std::string					chunked_body;

	void	recieve(std::vector<std::string>& arr, std::string& str);
	Request();
	~Request();
	void	start();
	void	init();
	void	parse_header();
	void	get_body_length();
	void	get_body_chunked();
	void	parse_body();
};
int		allowed_req(std::string& str);
void	ft_toupper(std::string& str);

#endif